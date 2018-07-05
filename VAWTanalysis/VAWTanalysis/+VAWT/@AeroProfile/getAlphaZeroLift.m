function getAlphaZeroLift(profile)
%GETAPLHAZEROLIFT    Compute the angle of attack at zero lift.
%
%	profile.getAlphaZeroLift computes the angle of attack at zero lift of
%	the profile.
    alpha=profile.naca.alpha(abs(profile.naca.alphaDeg)<90);
    Cl=profile.naca.Cl(abs(profile.naca.alphaDeg)<90);
    profile.alphaZeroLift = alpha(Cl==min(abs(Cl)));
    profile.alphaZeroLiftDeg = profile.alphaZeroLift*180/pi;
end

