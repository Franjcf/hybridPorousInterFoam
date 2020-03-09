surfaceScalarField::Boundary& phiBf =
        phi.boundaryFieldRef();

forAll(mesh.boundary(), patchi) 
    {
	if ( isA< fixedValueFvPatchField<vector> >(U.boundaryField()[patchi]) )
        {
        //do nothing 
	}	

	else if ( isA< fixedValueFvPatchField<vector> >(Uwetting.boundaryField()[patchi]) )
        {
	phiBf[patchi] = (Uwetting.boundaryField()[patchi] & mesh.Sf().boundaryField()[patchi])
		       +(UnonWetting.boundaryField()[patchi] & mesh.Sf().boundaryField()[patchi]);

        U.boundaryFieldRef()[patchi] = Uwetting.boundaryField()[patchi]
			              +UnonWetting.boundaryField()[patchi];
	}
}

