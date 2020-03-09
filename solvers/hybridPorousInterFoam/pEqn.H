    volScalarField rAU("rAU", 1.0/UEqn.A()); 
    surfaceScalarField rAUf("rAUf", fvc::interpolate(rAU)); 
    volVectorField HbyA(constrainHbyA(rAU*UEqn.H(), U, p));

    surfaceScalarField phiHbyA
    (
        "phiHbyA",
        fvc::flux(HbyA)
      + fvc::interpolate(rho*rAU)*fvc::ddtCorr(U, phi)
    );

    adjustPhi(phiHbyA, U, p);

    // Gravity Contribution
    surfaceScalarField phiG 
    (
       rAUf*fvc::interpolate(rho)*(g & mesh.Sf())
    );

    // Interfacial Force Contributions
    surfaceScalarField phiPc
    (
        (
            mixture.surfaceTensionForce()*(1.-Solidf) //activate free fluid interface model
	 +  fvc::interpolate(PcCoeff)*fvc::snGrad(alpha1)*Solidf //activate porous media model
        )*rAUf*mesh.magSf()
    );

    phiHbyA += (phiPc + phiG);

    // Update the pressure BCs to ensure flux consistency
    constrainPressure(p, U, phiHbyA, rAUf);

    while (pimple.correctNonOrthogonal())
    {
        fvScalarMatrix pEqn
        (
            fvm::laplacian(rAUf, p) == fvc::div(phiHbyA)        
        );

        pEqn.setReference(pRefCell, getRefCellValue(p, pRefCell));

        pEqn.solve();

        if (pimple.finalNonOrthogonalIter())
        {
            phi = phiHbyA - pEqn.flux();

            p.relax();

            U = HbyA + rAU*fvc::reconstruct(((phiPc+phiG) - pEqn.flux())/rAUf);
            U.correctBoundaryConditions();
	    #include "correctUBc.H"
        }
    }

    #include "continuityErrs.H"

    if (p.needReference())
    {
        p += dimensionedScalar
        (
            "p",
            p.dimensions(),
            pRefValue - getRefCellValue(p, pRefCell)
        );
    }

    

