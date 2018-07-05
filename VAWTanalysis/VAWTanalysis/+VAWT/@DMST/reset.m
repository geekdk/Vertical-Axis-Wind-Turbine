function reset(vawt)
%RESET   Reset VAWT solution.
%
%   obj = obj.reset recalculates Nth, theta, aspratio, diameter, omega, At
%   and thickness properties and erases all data in solution and diagnostic
%   structures.

    vawt.recalcNth;
    
    vawt.NTSR=length(vawt.TSR);
    
    thetaAux=((0.5/vawt.Nth):1/vawt.Nth:(1-0.5/vawt.Nth))*pi;
    vawt.theta1=thetaAux;
    vawt.theta2=thetaAux+pi;
    vawt.theta=[vawt.theta1,vawt.theta2];
    
    vawt.solution = struct('lambda',{},'velocity',{},'angle',{},'force',{},'torque',{},'power',{});
    vawt.solution(vawt.NTSR).lambda=[];
    
    output = struct ('intervaliterations', {}, 'iterations', {}, 'funcCount', {}, 'algorithm', {}, 'message',{});
    output(vawt.Nth*2).iterations = [];
    vawt.diagnostic = struct('exitFlag',{},'output', output,'residual',{});
    vawt.diagnostic(vawt.NTSR).residual=[];
    
    vawt.aspratio = vawt.height / vawt.chord;
    vawt.diameter = vawt.chord * vawt.nblades / vawt.solidity;
    vawt.omega=vawt.U*vawt.TSR*2/vawt.diameter;
    vawt.At = 2*pi./vawt.omega/(vawt.Nth*2);
    vawt.thickness = vawt.thick_chord/100*vawt.chord;
    
    disp('Solution has been reseted.');
end