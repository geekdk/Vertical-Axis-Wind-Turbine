function fig = polarVAWT(vawt, val, titleName, hAxes)
%POLARVAWT  Plot in polar coordinates any field that depends on azimuth
%           angle.
%
%   fig = obj.polarVAWT(val, titleName) plots the given field (val) against
%   azimuth angle with the title titleName. It uses polar coordinates.
%
%   fig = obj.polarVAWT(val, titleName, hAxes) plots the given field (val) 
%   against azimuth angle with the title titleName in the specific axes 
%   whose handle is hAxes. It uses polar coordinates.
% 
%   See also POLAR, PLOTVAWT, CLA.

    if nargin < 4
        axes=0;
    else
        axes=1;
    end
    
    if length(val(1,:)) > 1
        theta=(ones(vawt.NTSR,1)*vawt.theta)';
        value=val';
        if axes == 0
            fig = figure;
            hAxes = gca;
        end
        polar(hAxes,theta,value)
        title(hAxes,titleName)
        grid(hAxes,'on')
        if vawt.NTSR > 1
            legend_names = cell(1,vawt.NTSR);
            for i=1:vawt.NTSR
                legend_names{i}=['TSR = ',num2str(vawt.TSR(i))];
            end
            l=legend(hAxes,legend_names);
            set(l,'Location','Best');
        end
    else
        disp('This value is not dependent on azimuth angle.');
    end
end