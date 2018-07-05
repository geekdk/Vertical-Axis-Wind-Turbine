function CTb = getCTb(vawt, V, Vt, W, theta, CL, CD)
%GETCTB     Non dimensional torque of one blade.
%
%   CTb = vawt.getCTb(V, Vt, W, theta, CL, CD) returns the non dimensional
%   torque of one blade in respect to the blade for the given flow velocity 
%   (V), induced velocity (Vt), relative velocity (W), lift and drag
%   coefficients (CL and CD) and azimuth angle (theta).
    beta=vawt.getBeta(V, Vt, theta);
    Lx=-(CL.*W.^2 ).*sin(beta); 
    Ly= (CL.*W.^2 ).*cos(beta);
    Dx= (CD.*W.^2 ).*cos(beta);
    Dy= (CD.*W.^2 ).*sin(beta);
    Fx=Lx+Dx;
    Fy=Ly+Dy;
    CTb=-ones(size(Vt))*cos(theta).*Fx - ones(size(Vt))*sin(theta).*Fy;
end