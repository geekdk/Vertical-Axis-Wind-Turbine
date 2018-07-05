function getPlots(vawt, option)
%GETPLOTS 	Plot generator of the VAWT solution.
% 
%   vawt.getPlots plots power coefficient against tip speed ratio and 
%   torque, residuals, flow  velocity, interference factor and angle of 
%   attack against azimuthal angle.
% 
%   vawt.getPlots(option) plots the VAWT solution different variables.
%   Possible values for option:
%       'all'       plots power coefficient against tip speed ratio and 
%                   torque, residuals, flow  velocity, interference factor
%                   and angle of attack against azimuthal angle.
%       'lambda'    interference factor (both in cartesian and polar
%                   coordinates) and residuals against azimuthal angle.
%       'residual'  plots residuals against azimuthal angle.
%       'alpha'     plots angle of attack (real and refference) and angle
%                   of attack rate of change (in time and in azimuthal
%                   angle) against azimuthal angle.
%       'force'     lift and drag coefficients and lift over drag against 
%                   azimuthal angle.
%       'torque'    plots power blade torque and VAWT torque coefficients
%                   against  azimuthal angle.
%       'power'     plots power coefficient againts tip speed ratio.
%       else        plots nothing.
%
%   See also PLOTVAWT, PLOTPOWER, PLOTTORQUE.
        
    if (nargin < 2) option = 'all'; end;
    
    
    CTb = zeros(vawt.NTSR,2*vawt.Nth);
    lambda = CTb;
    V = CTb;
    residuals = CTb;
    alpha = CTb;
    alphaEf = CTb;
    CL = CTb;
    CD = CTb;
    alphaRateTime = CTb;
    alphaRateTheta = CTb;
    for iTSR = 1:vawt.NTSR
        CTb(iTSR,:)=vawt.solution(iTSR).torque.CTb(1:end);
        lambda(iTSR,:)=vawt.solution(iTSR).lambda.all(1:end);
        V(iTSR,:)=vawt.solution(iTSR).velocity.V(1:end);
        residuals(iTSR,:)=vawt.diagnostic(iTSR).residual(1:end);
        CL(iTSR,:)=vawt.solution(iTSR).force.CL(1:end);
        CD(iTSR,:)=vawt.solution(iTSR).force.CD(1:end);
        alpha(iTSR,:)=vawt.solution(iTSR).angle.alpha(1:end)*180/pi;
        alphaEf(iTSR,:)=vawt.solution(iTSR).angle.alphaEf(1:end)*180/pi;
        alphaRateTime(iTSR,:)=vawt.solution(iTSR).angle.alphaRate(1:end)*180/pi;
        alphaRateTheta(iTSR,:)=vawt.solution(iTSR).angle.alphaRate(1:end)/vawt.omega(iTSR);
    end
    
    switch option
        case 'all'
            vawt.plotPower;
            vawt.plotTorque;
            vawt.plotVAWT(CTb,'One blade torque coefficient');
            vawt.plotVAWT(lambda,'Interference factor');
            vawt.plotVAWT(V,'Flow velocity');
            vawt.plotVAWT(residuals,'Zeros');
            vawt.plotVAWT(alpha,'Angle of attack');
            vawt.plotVAWT(alphaRateTime,'d(AoA)/dt');
        case 'lambda'
            vawt.plotVAWT(lambda,'Interference factor');
            vawt.polarVAWT(lambda,'Interference factor');
            vawt.plotVAWT(residuals,'Residual');
        case 'residual'
            vawt.plotVAWT(residuals,'Residual');
        case 'alpha'
            vawt.plotVAWT(alpha,'\alpha');
            vawt.plotVAWT(alphaEf,'\alpha_{eff}');
            vawt.plotVAWT(alphaRateTime,'d\alpha/dt');
            vawt.plotVAWT(alphaRateTheta,'d\alpha/d\theta');
        case 'force'
            vawt.plotVAWT(CL,'CL');
            vawt.plotVAWT(CD,'CD');
            vawt.plotVAWT(CL./CD,'E');
        case 'torque'
            vawt.plotTorque;
            vawt.plotVAWT(CTb,'One blade torque coefficient');
        case 'power'
            vawt.plotPower;
        otherwise
            % do nothing...
    end
end