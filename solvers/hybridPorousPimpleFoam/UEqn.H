    fvVectorMatrix UEqn
    (
	//Inertial Terms
        (1./eps)*(fvm::ddt(U) + fvm::div(phiByEps, U) )

	//Viscous Terms
      - (1/eps)*(fvm::laplacian(laminarTransport.nu(),U))
      - (1/eps)*(fvc::div(laminarTransport.nu()*dev2(T(fvc::grad(U)))))

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
                  - fvc::snGrad(p)
                ) * mesh.magSf()
		+(g & mesh.Sf())
            )
        );
    }
