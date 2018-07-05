function Cd = getCd(profile, alpha)
%GETCD    Drag coefficient.
%
%	Cd = obj.getCd(alpha) gives the Cd for the given alpha
%	(angle of attack), which can be an scalar, vector or matrix between -pi
%	and +pi radiants.
% 
%   See also INTERP1
    alpha = mod(alpha + pi, 2*pi) - pi;
    alpha=sign(alpha).*min(max(profile.naca.alpha),abs(alpha));
    Cd=interp1(profile.naca.alpha, profile.naca.Cd, alpha);
end