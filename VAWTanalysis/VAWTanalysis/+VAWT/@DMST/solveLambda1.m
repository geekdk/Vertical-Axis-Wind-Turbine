function [lambda1,fval,exitflag1,output1] = solveLambda1(vawt, iTSR, ith, alphaAnt)
%SOLVELAMBDA1       Solve interference factor at an azimuthal angle
%                   position
%   
%   [lambda1,fval,exitflag1,output1] = vawt.solveLambda1(iTSR, ith, alphaAnt)
%   returns the interference factor (lambda1) for the given tip speed ratio
%   index (iTSR), azimuthal angle index (ith) and angle of attack of the
%   previous azimuthal position. It only works on the front half-cycle.
% 
%   fval, exitflag1 and output1 are the outputs of fzero.
% 
%   See also FZERO.
    if (nargin < 4) alphaAnt=0; end
    options=optimset(@fzero);
    fun=@(lambda) vawt.getLambdaEq1(iTSR, ith, lambda, alphaAnt);
    lambda0o=[0,1];
    if isnan(fun(lambda0o(1))) || isnan(fun(lambda0o(2))) || sign(fun(lambda0o(2)))==sign(fun(lambda0o(1)))
        lambda0=0.8;
        if isnan(fun(lambda0))
            lambda0=lambda0o(2);
        end
    else
        lambda0=[0,1];
    end
% %   Debuging help
%     ith
%     if ith==51
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
    [lambda1,fval,exitflag1,output1]=fzero(fun,lambda0,options);
    
end