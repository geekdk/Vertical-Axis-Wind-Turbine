function [CP, CP1, CP2] = getCP(vawt, TSR, CTb)
%GETCP      Compute power coefficient
% 
%   [CP, CP1, CP2] = vawt.getCP(TSR, CTb) integrates the blade torque
%   coefficient along the azimuthal angle of the turbine using the trapz
%   MATLAB function. TSR is the tip speed ratio and CTb is the blade torque
%   coefficient. The outputs are CP, CP1 and CP2, the power coefficient of
%   the whole, front and half turbine, respectively.
% 
%   See also TRAPZ

    CP=TSR*vawt.solidity/(2*pi).*trapz([-vawt.theta(1),vawt.theta], [CTb(end),CTb]);

    theta1= [ 0, vawt.theta(1:end/2), pi ];
%     theta2= [ pi, vawt.theta(end/2+1:end), 2*pi];
    CTb1 = [ (CTb(1)+CTb(end))/2,CTb(1:end/2),(CTb(end/2)+CTb(end/2+1))/2 ];
%     CTb2 = [ (CTb(end/2)+CTb(end/2+1))/2,CTb(end/2+1:end),(CTb(1)+CTb(end))/2 ];

    CP1=TSR*vawt.solidity/(2*pi).*(trapz(theta1, CTb1));
%     CP2=TSR*vawt.solidity/(2*pi).*(trapz(theta2, CTb2));
    CP2=CP-CP1;

end

