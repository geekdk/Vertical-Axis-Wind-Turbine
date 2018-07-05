function alphaMaxLoverD(profile)
%ALPHAMAXLOVERD    Compute the angle of attack for maximum L/D.
%
%	profile.alphaMaxLoverD computes the angle of attack for maximum lift
%	over drag of the profile.
    E=profile.naca.Cl./profile.naca.Cd;
    profile.alphaOptim=profile.naca.alpha(E==max(E) & profile.naca.alpha>0);
    profile.alphaOptimDeg=profile.naca.alphaDeg(E==max(E) & profile.naca.alpha>0);
end

