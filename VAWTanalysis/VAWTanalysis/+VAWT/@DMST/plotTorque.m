function fig = plotTorque(vawt, hAxes)
%PLOTTORQUE  Plot torque coefficient against azimuth angle.
%
%   fig = obj.plotTorque plots the torque coefficient against azimuth
%   angle.
% 
%   fig = obj.plotTorque(hAxes) plots the torque coefficient against 
%   azimuth angle in the specific axes whose handle is hAxes.
%
%   See also PLOT, CLA.

    if nargin < 2
        axes=0;
    else
        axes=1;
    end
    
    theta=vawt.theta*180/pi;
    theta=theta(1:end/vawt.nblades);
    CT = zeros(vawt.NTSR,2*vawt.Nth/vawt.nblades);
    for iTSR = 1:vawt.NTSR
        CT(iTSR,:)=vawt.solution(iTSR).torque.CT(1:end/vawt.nblades);
    end
    if axes == 0
        fig = figure;
        hAxes=gca;
    end
    plot(hAxes,theta,CT)
    title(hAxes,'Torque coefficient during one period');
    xlabel(hAxes,'\theta');
    legend_names = cell(1,vawt.NTSR);
    for i=1:vawt.NTSR
        legend_names{i}=['TSR = ',num2str(vawt.TSR(i))];
    end
    l=legend(hAxes,legend_names);
    set(l,'Location','Best');
    grid(hAxes,'on')
end