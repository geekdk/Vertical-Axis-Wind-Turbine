function W = getW(V, Vt, theta)
%GETW    Relative non dimensional velocity.
%
%   W = getW(V, Vt, theta) returns the relative non dimensional
%   velocity for the given flow velocity (Vt), induced velocity (Vt) (both
%   are non dimensional) and azimuth angle (theta).
    Vtx=-Vt*cos(theta);
    Vty=-Vt*sin(theta);
    W=sqrt( (V - Vtx).^2 + (-Vty).^2 );
end