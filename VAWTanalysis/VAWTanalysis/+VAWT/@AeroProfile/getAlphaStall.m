function getAlphaStall(profile)
%GETALPHASTALL    Compute the angle of attack at stall.
%
%	profile.getAlphaStall computes the angle of attack at stall of
%	the profile. It also computes the slope of the linear part of the lift
%	curve.
    i1 = floor(length(profile.naca.alpha)/2);
    i2 = i1 + 1;
    
    dif1 = (profile.naca.Cl(i2) - profile.naca.Cl(i1))/(profile.naca.alpha(i2)-profile.naca.alpha(i1));
    
    for i = i2 : length(profile.naca.alpha)
        difi=( profile.naca.Cl(i+1) - profile.naca.Cl(i) )/( profile.naca.alpha(i+1) - profile.naca.alpha(i) );
        if abs((difi - dif1)/dif1) > 1.8/(2*pi)
            profile.alphaStall = profile.naca.alpha(i);
            profile.alphaStallDeg = profile.naca.alphaDeg(i);
            profile.CLa = (profile.naca.Cl(i-1)-profile.naca.Cl(i2))/(profile.naca.alpha(i-1)-profile.naca.alpha(i2));
            break
        end
    end
end

