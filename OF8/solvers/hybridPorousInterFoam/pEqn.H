{
    if (correctPhi)
    {
        rAU.ref() = 1.0/UEqn.A();
    }
    else
    {
        rAU = 1.0/UEqn.A();
    }

    surfaceScalarField rAUf("rAUf", fvc::interpolate(rAU()));
    volVectorField HbyA(constrainHbyA(rAU()*UEqn.H(), U, p));
    surfaceScalarField phiHbyA
    (
        "phiHbyA",
        fvc::flux(HbyA)
      + MRF.zeroFilter(fvc::interpolate(rho*rAU())*fvc::ddtCorr(U, phi, Uf))
    );
    MRF.makeRelative(phiHbyA);

    if (p.needReference())
    {
        fvc::makeRelative(phiHbyA, U);
        adjustPhi(phiHbyA, U, p);
        fvc::makeAbsolute(phiHbyA, U);
    }

    //Gravity Contribution
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

    phiHbyA += (phiG + phiPc);

    // Update the pressure BCs to ensure flux consistency
    constrainPressure(p, U, phiHbyA, rAUf, MRF);

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

            U = HbyA + rAU()*fvc::reconstruct(((phiG+phiPc) - pEqn.flux())/rAUf);
            U.correctBoundaryConditions();
            fvOptions.correct(U); 
            #include "correctUBc.H"
        }
    }

    #include "continuityErrs.H"

    // Correct Uf if the mesh is moving
    fvc::correctUf(Uf, U, phi);

    // Make the fluxes relative to the mesh motion
    fvc::makeRelative(phi, U);

    if (p.needReference())
    {
        p += dimensionedScalar
        (
            "p",
            p.dimensions(),
            pRefValue - getRefCellValue(p, pRefCell)
        );
    }

    if (!correctPhi)
    {
        rAU.clear();
    }
}
