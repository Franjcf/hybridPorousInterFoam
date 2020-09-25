// Updating Relative Permeability Model
autoPtr<relativePermeabilityModel> krModel = relativePermeabilityModel::New("krModel",transportProperties,alpha1);
krModel->correct();
kr1=krModel->krb();
kr2=krModel->kra();

kr1f = fvc::interpolate(kr1,"kr1");
kr2f = fvc::interpolate(kr2,"kr2");

// Updating Mobilities
M1 = k0*kr1/mu1;
L1 = rho1*k0*kr1/mu1; 	
M2 = k0*kr2/mu2;
L2 = rho2*k0*kr2/mu2;
M = M1+M2;
L = L1+L2;

M1f = k0f*kr1f/mu1;
L1f = rho1*k0f*kr1f/mu1;	
M2f = k0f*kr2f/mu2;
L2f = rho2*k0f*kr2f/mu2;	
Mf = M1f+M2f;
Lf = L1f+L2f;

// Calculating Drag Coefficient
Dragf =1./Mf;
Drag= fvc::average(Dragf)*Solid;

// Updating Capillary Pressure Model
autoPtr<capillarityModel> myCapModel = capillarityModel::New("pc",transportProperties,alpha1);
myCapModel().correct();
pc = myCapModel().pc()*activateCapillarity; 
dPcdS = myCapModel().dpcdS()*activateCapillarity; 
PcCoeff = (  
	-pc
	+(1./M)*(M1*(1.-alpha1) - M2*(alpha1))*dPcdS
	);

//updating re-meshing indicatior for dynamic meshe
meshingIndicator = alpha1;
forAll(meshingIndicator,celli)
{
       	if (Solid[celli] == 1  && gradSolid[celli] == 0)
        {meshingIndicator[celli]= -10;}
}
