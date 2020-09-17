// Calculate Porous Media Velocities
Uwetting = Solid*M1*(
         - fvc::grad(p)
         + (1.-alpha1)*fvc::grad(pc)
         -  pc*fvc::grad(alpha1)
         +  rho1*g
         );

UnonWetting = Solid*M2*(
         -fvc::grad(p)
         -alpha1*fvc::grad(pc)
         -pc*fvc::grad(alpha1)
         +rho2*g
        );

Uwetting.correctBoundaryConditions();
UnonWetting.correctBoundaryConditions();
Solidf = fvc::interpolate(Solid);



