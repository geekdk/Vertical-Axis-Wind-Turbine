function alpha = getAlpha(theta, beta, pitch)
%GETALPHA    Compute the angle of attack.
%
%	alpha = getAlpha(theta, beta) computes the angle of attack (angle
%	between tangential velocity and relative velocity) as:
%       angle of attack = mod( pi + beta - theta, 2*pi) - pi
%   Where theta is the azimuth angle and beta is the angle between X axis
%   and relative velocity.
%
%   See also MOD.
    if (nargin < 3) pitch = 0; end
    alpha = mod( pi + beta - theta, 2*pi) - pi + pitch;
end