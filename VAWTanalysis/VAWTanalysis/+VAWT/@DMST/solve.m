function solve(vawt)
%SOLVE      VAWT solver.
% 
%   vawt.solve solves the whole wind turbine for the interference factor
%   and the rest of variables and stores them to the solution and
%   diagnostic structures.
% 
%   See also SOLVECASE, POSTPROCESS.
    for iTSR = 1:vawt.NTSR
        disp(['Solving VAWT with TSR = ',num2str(vawt.TSR(iTSR)),' ...']);
        vawt.solveCase (iTSR);
        vawt.postProcess(iTSR);
        disp(['VAWT with TSR = ',num2str(vawt.TSR(iTSR)),' successfully solved.']);
    end

end
