    fvVectorMatrix UEqn
    (
	//Inertial Terms
        (1./eps)*(fvm::ddt(rho, U) + fvm::div(rhoPhiByEps, U) )

	//Viscous Terms
      - (1/eps)*(fvm::laplacian((rho*mixture.nu()),U))
      - (1/eps)*(fvc::div((rho*mixture.nu())*dev2(T(fvc::grad(U)))))

	//Implicit Darcy-Brinkman Drag Term
      + fvm::Sp(Drag,U) 

    );

    UEqn.relax();

    if (pimple.momentumPredictor()) 
    {
        solve
        (
            UEqn
         ==
            fvc::reconstruct
            (
                (
		     //activate free fluid interface model
                     mixture.surfaceTensionForce()*(1.-Solidf) 
                     //activate porous media model
	          +  fvc::interpolate(PcCoeff)*fvc::snGrad(alpha1)*Solidf 
                  - fvc::snGrad(p)
                ) * mesh.magSf()
		+fvc::interpolate(rho)*(g & mesh.Sf())
            )
        );
    }
