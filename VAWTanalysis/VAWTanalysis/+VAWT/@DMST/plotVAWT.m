function fig = plotVAWT(vawt, val, titleName, hAxes)
%PLOTVAWT  Plot any field that depends on azimuth angle.
%
%   fig = obj.plotVAWT(val, titleName) plots the given field (val) against
%   azimuth angle with the title titleName.
%
%   fig = obj.plotVAWT(val, titleName, hAxes) plots the given field (val) 
%   against azimuth angle with the title titleName in the specific axes 
%   whose handle is hAxes.
% 
%   See also PLOT, CLA.

    if nargin < 4
        axes=0;
    else
        axes=1;
    end

    if length(val) == 1
        disp([titleName,' = ',num2str(val)])
    elseif size(val) == size(vawt.TSR)
        if axes == 0
            fig = figure;
            hAxes = gca;
        end
        plot(hAxes,vawt.TSR, val)
        title(hAxes,titleName)
        xlabel(hAxes,'TSR');
        grid(hAxes,'on')
    else
        theta=vawt.theta*180/pi;
        if vawt.NTSR == 1
            if axes == 0
                fig = figure;
                hAxes=gca;
            end
            plot(hAxes,theta(1:end/2), val(1:end/2), 'b', theta(end/2:end), val(end/2:end), 'g')
            title(hAxes,titleName)
            xlabel(hAxes,'\theta');
            l=legend(hAxes,'Upwind','Downwind');
            set(l,'Location','Best');
            grid(hAxes,'on')
        else
            if axes == 0
                fig = figure;
                hAxes=gca;
            end
            plot(hAxes,theta,val)
            title(hAxes,titleName)
            xlabel(hAxes,'\theta');
            legend_names = cell(1,vawt.NTSR);
            for i=1:vawt.NTSR
                legend_names{i}=['TSR = ',num2str(vawt.TSR(i))];
            end
            l=legend(hAxes,legend_names);
            set(l,'Location','Best');
            grid(hAxes,'on')
        end
    end
end