function [lambda2,fval,exitflag2,output2] = solveLambda2(vawt, iTSR, ith, lambda1, alphaAnt)
%SOLVELAMBDA2       Solve interference factor at an azimuthal angle
%                   position
%   
%   [lambda1,fval,exitflag1,output1] = vawt.solveLambda1(iTSR, ith, alphaAnt)
%   returns the interference factor (lambda2) for the given tip speed ratio
%   index (iTSR), azimuthal angle index (ith), upwind interference factor 
%   (lambda1) and angle of attack of the previous azimuthal position. It 
%   only works on the rear half-cycle.
% 
%   fval, exitflag2 and output2 are the outputs of fzero.
% 
%   See also FZERO.

    if (nargin < 5) alphaAnt=0; end
    options=optimset(@fzero);
    fun=@(lambda) vawt.getLambdaEq2(iTSR, ith, lambda, lambda1, alphaAnt);
    lambda0o=[0,1];
    if isnan(fun(lambda0o(1))) || isnan(fun(lambda0o(2))) || sign(fun(lambda0o(2)))==sign(fun(lambda0o(1)))
        lambda0=max(2*lambda1-1, lambda1/2);
    else
        lambda0=[0,1];
    end
% %   Debuging help
%     ith
%     if ith==53
%         lambda1
%         alphaAnt
%         options=optimset('Display','iter');
%         
%         x = lambda0o(1):0.001:lambda0o(2);
%         r = zeros(size(x));
%         for i = 1:50
%             r=fun(x);
%         end
%         plot(x,r)
%         grid on;
%         
%         bottom=fun(lambda0o(1))
%         top=fun(lambda0o(2))
%     end
    [lambda2,fval,exitflag2, output2]=fzero(fun,lambda0,options);
    if isfield(output2,'intervaliter')
        lambda2=2*lambda1-1;
        output2=struct('intervaliterations',output2.intervaliter,'iterations', output2.iterations, 'funcCount', output2.funcCount, 'algorithm', output2.algorithm, 'message',output2.message);
    elseif lambda2 < 0
        lambda2 = 2*lambda1-1;
    end
end