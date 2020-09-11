{
    #include "alphaScheme.H"
    word alpharScheme("div(phirb,alpha)"); //scheme for relative velocity in porous media


    // Set the off-centering coefficient according to ddt scheme
    scalar ocCoeff = 0;
    {
        tmp<fv::ddtScheme<scalar>> tddtAlpha
        (
            fv::ddtScheme<scalar>::New
            (
                mesh,
                mesh.ddtScheme("ddt(alpha)")
            )
        );
        const fv::ddtScheme<scalar>& ddtAlpha = tddtAlpha();

        if
        (
            isType<fv::EulerDdtScheme<scalar>>(ddtAlpha)
         || isType<fv::localEulerDdtScheme<scalar>>(ddtAlpha)
        )
        {
            ocCoeff = 0;
        }
        else if (isType<fv::CrankNicolsonDdtScheme<scalar>>(ddtAlpha))
        {
            if (nAlphaSubCycles > 1)
            {
                FatalErrorInFunction
                    << "Sub-cycling is not supported "
                       "with the CrankNicolson ddt scheme"
                    << exit(FatalError);
            }

            if
            (
                alphaRestart
             || mesh.time().timeIndex() > mesh.time().startTimeIndex() + 1
            )
            {
                ocCoeff =
                    refCast<const fv::CrankNicolsonDdtScheme<scalar>>(ddtAlpha)
                   .ocCoeff();
            }
        }
        else
        {
            FatalErrorInFunction
                << "Only Euler and CrankNicolson ddt schemes are supported"
                << exit(FatalError);
        }
    }

    // Set the time blending factor, 1 for Euler
    scalar cnCoeff = 1.0/(1.0 + ocCoeff);

    tmp<surfaceScalarField> phiCN(phi);

    // Standard face-flux compression coefficient
    // surfaceScalarField phic(mixture.cAlpha()*mag(phi/mesh.magSf()));

    // Calculate the Crank-Nicolson off-centred volumetric flux
    if (ocCoeff > 0)
    {
        phiCN = surfaceScalarField::New
        (
            "phiCN",
            cnCoeff*phi + (1.0 - cnCoeff)*phi.oldTime()
        );
    }

    //Calculating Porous Media Velocities
    #include "updateDarcyVelocities.H"

    // Defining relative velocity
    Ur = ( Uwetting/max(alpha1,0.001) - UnonWetting/max((1.-alpha1),0.001) )/eps;
    surfaceScalarField phirPore(fvc::interpolate(Ur) & mesh.Sf());

    //surfaceScalarField::Boundary& phicBf =
    //phic.boundaryFieldRef();
    surfaceScalarField::Boundary& phirPoreBf =
        phirPore.boundaryFieldRef();

    // Do not compress interface at non-coupled boundary faces
    // (inlets, outlets etc.)
    //forAll(phic.boundaryField(), patchi)
    // {
    //    fvsPatchScalarField& phicp = phicBf[patchi];
    //
    //  if (!phicp.coupled())
    //      {
    //		phicp == 0;
    //      }
    //}

    // Correcting Ur at boundaries
    forAll(phirPore.boundaryField(), patchi)
    {

        fvsPatchScalarField& phirPorep = phirPoreBf[patchi];

        if (!phirPorep.coupled())
        {
              phirPorep == 0;
        }

        if ( (isA< fixedValueFvPatchField<vector> >(Uwetting.boundaryField()[patchi])) or
             (isA< fixedValueFvPatchField<vector> >(UnonWetting.boundaryField()[patchi])) )
        {

              //This is equal to Ur = U1/phiS1 -(U2)/phiS2 at the boundary
              phirPoreBf[patchi] =
                          (Uwetting.boundaryField()[patchi] & mesh.Sf().boundaryField()[patchi])
                         /(eps.boundaryField()[patchi]*alpha1.boundaryField()[patchi] + 0.001)
                         -(UnonWetting.boundaryField()[patchi] & mesh.Sf().boundaryField()[patchi])
                         /(eps.boundaryField()[patchi]*(1-alpha1.boundaryField()[patchi]) + 0.001);
        }
    }

    //Correct Single Field Velocity Boundary Coditions
    #include "correctUBc.H"


    if (MULESCorr)
    {
        #include "alphaSuSp.H"

        fvScalarMatrix alpha1Eqn
        (
            (
                LTS
              ? fv::localEulerDdtScheme<scalar>(mesh).fvmDdt(eps,alpha1)
              : fv::EulerDdtScheme<scalar>(mesh).fvmDdt(eps,alpha1)
            )
          + fv::gaussConvectionScheme<scalar>
            (
                mesh,
                phiCN,
                upwind<scalar>(mesh, phiCN)
            ).fvmDiv(phiCN, alpha1)
       // - fvm::Sp(fvc::ddt(dimensionedScalar(dimless, 1), mesh)
       //           + fvc::div(phiCN), alpha1)
         ==
            Su + fvm::Sp(Sp + divU, alpha1)
        );

        alpha1Eqn.solve();

        Info<< "Phase-1 volume fraction = "
            << alpha1.weightedAverage(mesh.Vsc()).value()
            << "  Min(" << alpha1.name() << ") = " << min(alpha1).value()
            << "  Max(" << alpha1.name() << ") = " << max(alpha1).value()
            << endl;

        tmp<surfaceScalarField> talphaPhi1UD(alpha1Eqn.flux());
        alphaPhi10 = talphaPhi1UD();

        if (alphaApplyPrevCorr && talphaPhi1Corr0.valid())
        {
            Info<< "Applying the previous iteration compression flux" << endl;
            MULES::correct
            (
                eps,
                alpha1,
                alphaPhi10,
                talphaPhi1Corr0.ref(),
                oneField(),
                zeroField()
            );

            alphaPhi10 += talphaPhi1Corr0();
        }

        // Cache the upwind-flux
        talphaPhi1Corr0 = talphaPhi1UD;

        alpha2 = 1.0 - alpha1;

        mixture.correct();
    }

    for (int aCorr=0; aCorr<nAlphaCorr; aCorr++)
    {
        #include "alphaSuSp.H"

        //surfaceScalarField phir(Solidf*phirPore+(1.-Solidf)*phic*mixture.nHatf());

 
        // Split operator
        tmp<surfaceScalarField> talphaPhi1Un
        (
           
            //flux in solid-free regions
            (1-Solidf)*fvc::flux
            (
                phiCN(),
                (cnCoeff*alpha1 + (1.0 - cnCoeff)*alpha1.oldTime())(),
                compressionScheme.rewind()
            )

	    //flux in porous media
            + Solidf*
            (fvc::flux
            (
                phiCN(),
                (cnCoeff*alpha1 + (1.0 - cnCoeff)*alpha1.oldTime())(),
                alpharScheme
            )            
            + fvc::flux
            (
                -fvc::flux(-phirPore, (alpha2*eps), alpharScheme),
                alpha1,
                alpharScheme
            )
            )

            //Alternative flux formulation (better porous contact angle results
            //but no fancy (i.e. PLIC) interface compression schemes.
            //(fvc::flux
            //(
            //    phiCN(),
            //    (cnCoeff*alpha1 + (1.0 - cnCoeff)*alpha1.oldTime())(),
            //    alpharScheme
            //)
            //+ fvc::flux
            //(
            //    -fvc::flux(-phir, (alpha2*eps), alpharScheme),
            //    alpha1,
            //    alpharScheme
            //)
            //)
        );  

        if (MULESCorr)
        {
            tmp<surfaceScalarField> talphaPhi1Corr(talphaPhi1Un() - alphaPhi10);
            volScalarField alpha10("alpha10", alpha1);

            MULES::correct
            (
                eps,
                alpha1,
                talphaPhi1Un(),
                talphaPhi1Corr.ref(),
                Sp,
                (-Sp*alpha1)(),
                oneField(),
                zeroField()
            );

            // Under-relax the correction for all but the 1st corrector
            if (aCorr == 0)
            {
                alphaPhi10 += talphaPhi1Corr();
            }
            else
            {
                alpha1 = 0.5*alpha1 + 0.5*alpha10;
                alphaPhi10 += 0.5*talphaPhi1Corr();
            }
        }
        else
        {
            alphaPhi10 = talphaPhi1Un;

            MULES::explicitSolve
            (
                eps,
                alpha1,
                phiCN,
                alphaPhi10,
                Sp,
                (Su + divU*min(alpha1(), scalar(1)))(),
                oneField(),
                zeroField()
            );
        }

        alpha2 = 1.0 - alpha1;

        mixture.correct();
    }

    if (alphaApplyPrevCorr && MULESCorr)
    {
        talphaPhi1Corr0 = alphaPhi10 - talphaPhi1Corr0;
        talphaPhi1Corr0.ref().rename("alphaPhi1Corr0");
    }
    else
    {
        talphaPhi1Corr0.clear();
    }

    #include "rhofs.H"

    if
    (
        word(mesh.ddtScheme("ddt(rho,U)"))
     == fv::EulerDdtScheme<vector>::typeName
     || word(mesh.ddtScheme("ddt(rho,U)"))
     == fv::localEulerDdtScheme<vector>::typeName
    )
    {
        rhoPhi = alphaPhi10*(rho1f - rho2f) + phiCN*rho2f;
    }
    else
    {
        if (ocCoeff > 0)
        {
            // Calculate the end-of-time-step alpha flux
            alphaPhi10 =
                (alphaPhi10 - (1.0 - cnCoeff)*alphaPhi10.oldTime())/cnCoeff;
        }

        // Calculate the end-of-time-step mass flux
        rhoPhi = alphaPhi10*(rho1f - rho2f) + phi*rho2f;
    }

    Info<< "Phase-1 volume fraction = "
        << alpha1.weightedAverage(mesh.Vsc()).value()
        << "  Min(" << alpha1.name() << ") = " << min(alpha1).value()
        << "  Max(" << alpha1.name() << ") = " << max(alpha1).value()
        << endl;
}
