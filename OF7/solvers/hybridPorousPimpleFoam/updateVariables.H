//Calculating Drag Coefficient
Drag= fvc::average(laminarTransport.nu()/k0);

forAll(Drag,celli)
{
	if (Solid[celli] == 0)
		{Drag[celli]= 0;}
}

