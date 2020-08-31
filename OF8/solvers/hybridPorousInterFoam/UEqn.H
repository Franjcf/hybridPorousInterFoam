    MRF.correctBoundaryVelocity(U);

    fvVectorMatrix UEqn
    (
	//Inertial Terms
        (1./eps)*(fvm::ddt(rho, U) + fvm::div(rhoPhiByEps, U) + MRF.DDt(rho, U))

	//Viscous Terms
	+(1./eps)*(turbulence->divDevTau(rho, U))

	//Implicit Drag Term
        + fvm::Sp(Drag,U)

     ==
        fvOptions(rho, U)
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
         ==
            fvc::reconstruct
            (
             (
		//activate solid-free interface model
                mixture.surfaceTensionForce()*(1.-Solidf)
                //activate porous media model
             +  fvc::interpolate(PcCoeff)*fvc::snGrad(alpha1)*Solidf
             - fvc::snGrad(p)
             ) * mesh.magSf()
                +fvc::interpolate(rho)*(g & mesh.Sf()) 
            )
        );
        fvOptions.correct(U);
    }
