// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

tmp<fvVectorMatrix> tUEqn
(
    (1./eps)*(fvm::ddt(U) + fvm::div(phiByEps, U)  + MRF.DDt(U))
  + (1./eps)*(turbulence->divDevSigma(U))

    //implicit Drag term
  + fvm::Sp(Drag,U)

 ==
    fvOptions(U)
);
fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvOptions.correct(U);
}
