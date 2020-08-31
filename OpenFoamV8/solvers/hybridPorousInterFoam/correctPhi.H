CorrectPhi
(
    U,
    phi,
    p,
    surfaceScalarField("rAUf", fvc::interpolate(rAU())),
    geometricZeroField(),
    pimple,
    true
);

#include "continuityErrs.H"
