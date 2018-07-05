function [Cl, Cd] = getClCd(profile, alpha)
%GETCLCD    Lift and drag coefficients.
%
%	[Cl, Cd] = obj.getClCd(alpha) gives the Cl and Cd for the given alpha
%	(angle of attack), which can be an scalar, vector or matrix between -pi
%	and +pi radiants.
% 
%   See also INTERP1
    alpha = mod(alpha + pi, 2*pi) - pi;
    alpha=sign(alpha).*min(max(profile.naca.alpha),abs(alpha));
    Cl=interp1(profile.naca.alpha, profile.naca.Cl, alpha);
    Cd=interp1(profile.naca.alpha, profile.naca.Cd, alpha);
end