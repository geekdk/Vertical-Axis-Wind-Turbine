function fig = plotPower(vawt, hAxes)
%PLOTPOWER  Plot power coefficient tip speed ratio.
%
%   fig = vawt.plotPower plots the power coefficient tip speed ratio.
% 
%   fig = obj.plotPower(hAxes) plots the power coefficient against tip
%   speed ratio in the specific axes whose handle is hAxes.
%
%   See also PLOT, CLA.
    
    if nargin < 2
        axes=0;
    else
        axes=1;
    end
    
    CP = zeros(1,vawt.NTSR);
    CP1 = CP;
    CP2 = CP;
    
    for iTSR = 1:vawt.NTSR
        CP1(iTSR) = vawt.solution(iTSR).power.CP1;
        CP2(iTSR) = vawt.solution(iTSR).power.CP2;
        CP(iTSR) = vawt.solution(iTSR).power.CP;
    end

    if vawt.NTSR == 1
        str1=['CP_front = ',num2str(round(CP1*1E4)*1E-4)];
        str2=['CP_back = ',num2str(round(CP2*1E4)*1E-4)];
        str=['C_P = ',num2str(round(CP*1E4)*1E-4)];
        if axes == 0
            disp(str1)
            disp(str2)
            disp(str)
        else
            cla(hAxes)
            text(0.5,0.8,str1,'Parent',hAxes,'Fontsize',16,'VerticalAlignment','middle','HorizontalAlignment','center')
            text(0.5,0.6,str2,'Parent',hAxes,'Fontsize',16,'VerticalAlignment','middle','HorizontalAlignment','center')
            text(0.5,0.3,str,'Parent',hAxes,'Fontsize',20,'VerticalAlignment','middle','HorizontalAlignment','center','EdgeColor','red')
        end

    else
        if axes == 0
            fig = figure;
            hAxes=gca;
        end
        plot(hAxes,vawt.TSR,CP,'b',vawt.TSR,CP1,'--g',vawt.TSR,CP2,'-.r')
        title(hAxes,'C_P against TSR')
        xlabel(hAxes,'TSR')
        ylabel(hAxes,'C_P')
        l=legend(hAxes,'C_P','C_{P,front}','C_{P,back}');
        set(l,'Location','Best');
        grid(hAxes,'on')
    end
end