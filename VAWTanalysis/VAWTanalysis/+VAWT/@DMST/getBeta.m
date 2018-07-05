function beta = getBeta(V, Vt, theta)
%GETBETA    Compute the flight path angle.
%
%	beta = getBeta(TSR, theta, lambda) computes the angle between X axis 
%   and relative velocity as:
%       beta=atan( Vt*sin(theta) / ( V + Vt*cos(theta) ) )
%   Where V is the non-dimensional flow velocity, theta is the azimuth 
%   angle and Vt is the non-dimensional blade phisical velocity.
%
%   See also ATAN2.
    beta=atan2(Vt*sin(theta),V+Vt*cos(theta));
end