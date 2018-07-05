function solveCase(vawt, iTSR)
%SOLVECASE      Solves the interference factor.
% 
%   vawt.solveCase(iTSR) solves the interference factor for the given tip
%   speed ratio index (iTSR).
% 
%   See also SOLVE, SOLVELAMBDA1, SOLVELAMBDA2, FZERO.

% Initialize vectors and structures
lambda1 = zeros(1,vawt.Nth);
lambda2 = lambda1;
alpha = zeros(1,vawt.Nth);
r=alpha;
eF = alpha;
output = struct ('intervaliterations', {}, 'iterations', {}, 'funcCount', {}, 'algorithm', {}, 'message',{});
output(vawt.Nth*2).iterations = [];

% Compute interference factor for the first azimuthal angle position
[lambda1(1),r(1), eF(1), output(1)]=vawt.solveLambda1(iTSR,1);
beta=vawt.getBeta(lambda1(1),vawt.TSR(iTSR),vawt.theta(1));
alpha(1)=vawt.getAlpha(vawt.theta(1),beta, vawt.pitch(1));

% Interference factor for the rest of the front half-cycle
for ith=2:vawt.Nth
    [lambda1(ith),r(ith), eF(ith), output(ith)]=vawt.solveLambda1(iTSR,ith,alpha(ith-1));
    beta=vawt.getBeta(lambda1(ith),vawt.TSR(iTSR),vawt.theta(ith));
    alpha(ith)=vawt.getAlpha(vawt.theta(ith),beta, vawt.pitch(ith));
end

% Interference factor for the rear half-cycle
for ith2=1:vawt.Nth
    ith=ith2+vawt.Nth;
    ith1=vawt.Nth+1-ith2;
    [lambda2(ith2),r(ith), eF(ith), output(ith)]=vawt.solveLambda2(iTSR,ith,lambda1(ith1),alpha(ith-1));
    beta=vawt.getBeta(lambda2(ith2)*(2*lambda1(ith1)-1),vawt.TSR(iTSR),vawt.theta(ith));
    alpha(ith)=vawt.getAlpha(vawt.theta(ith),beta, vawt.pitch(ith));
end

% Store interference factor and diagnostics
vawt.solution(iTSR).lambda = struct('uw',lambda1,'dw',lambda2(end:-1:1),'all',[lambda1,lambda2]);
vawt.diagnostic(iTSR) = struct('exitFlag', eF, 'output', output, 'residual', r);
end
