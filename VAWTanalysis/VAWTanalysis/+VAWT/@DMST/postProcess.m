function postProcess(vawt, iTSR)
%POSTPROCESS  Compute all variables from interference factor
%
%   vawt.postProcess(iTSR) computes all variables form interference factor
%   and fills the solution structure for the given tip speed ratio index 
%   (iTSR).
%
%   See also DMST.

if (nargin < 2) iTSR = 1; end

% Input values: TSR and interference factor
TSR = vawt.TSR(iTSR);

lambda1=vawt.solution(iTSR).lambda.uw;
lambda2=vawt.solution(iTSR).lambda.dw;

% Non dimensional velocities computation
V1 = lambda1;
Ve = 2 * lambda1 - 1;
V2 = lambda2 .* Ve;
Vw = Ve .* (2 * lambda2 - 1);
V = [V1,V2(end:-1:1)];

W = vawt.getW(V, TSR, vawt.theta);

% Flight path angle
beta=vawt.getBeta(V, TSR, vawt.theta);

% Angle of attack
alpha=vawt.getAlpha(vawt.theta, beta, vawt.pitch);
alphaRate=vawt.getRateLoop(alpha,vawt.At(iTSR));

% Lift and drag coefficients
if strcmp(vawt.dStall.model,'N')
        [CL, CD0] = vawt.getClCd(alpha);
        alphaRefL = alpha;
        alphaRefD = alpha;
else
    switch vawt.dStall.model
        case 'G'
            [CL, CD0, alphaRefL, alphaRefD] = getCLCDG( vawt, vawt.omega(iTSR), abs(alpha), vawt.U*W, vawt.getRateLoop(abs(alpha),vawt.At(iTSR)) );
        case 'S'
            [CL, CD0, alphaRefL, alphaRefD] = getCLCDS( vawt, vawt.omega(iTSR), abs(alpha), vawt.U*W, vawt.getRateLoop(abs(alpha),vawt.At(iTSR)) );
        case 'B'
            [CL, CD0, alphaRefL, alphaRefD] = getCLCDB( vawt, vawt.omega(iTSR), abs(alpha), vawt.U*W, vawt.getRateLoop(abs(alpha),vawt.At(iTSR)) );
        case 'P'
            [CL, CD0, alphaRefL, alphaRefD] = getCLCDP( vawt, vawt.theta, vawt.omega(iTSR), abs(alpha), vawt.U*W, vawt.getRateLoop(abs(alpha),vawt.At(iTSR)) );
    end
    CL=CL.*sign(alpha);
    alphaRefL=alphaRefL.*sign(alpha);
    alphaRefD=alphaRefD.*sign(alpha);
end
if vawt.aspratio<=0
    CDi=0;
else
    CDi= vawt.solidity*CL.^2/(pi*vawt.aspratio*vawt.nblades);
end
CD=CD0+CDi;

% Wake model application if vawt.wake is set to true
if vawt.wake
    Nw=0.85*vawt.nblades*TSR;
    dw=2*vawt.chord*Nw; %It used to be dw=2*vawt.thickness*NW, but the wake with thickness width was too thin.
    pw=1-dw/(pi*vawt.diameter/2);
    CL(end/2+1:end)=CL(end/2+1:end)*pw;
    CD(end/2+1:end)=CD(end/2+1:end)*pw;
end

% Thrust coefficient computation
cond= vawt.solution(iTSR).lambda.all >= 43/60;
CFx = ( cond.*(4*vawt.solution(iTSR).lambda.all.*(1-vawt.solution(iTSR).lambda.all)) + ~cond.*(1849/900-26*vawt.solution(iTSR).lambda.all/15) );

% Effective angle of attack.
alphaEf=CL./vawt.CLa;

% Torque coefficient for a blade and for the whole turbine
CTb=vawt.getCTb(V, TSR, W, vawt.theta, CL, CD);
CT=vawt.getCT(CTb);

% Power coefficient
[CP, CP1, CP2] = vawt.getCP(TSR, CTb);

% Save results
vawt.solution(iTSR).velocity = struct('U', 1, 'V', V, 'V1', V1, 'Ve', Ve, 'V2', V2, 'Vw', Vw, 'W', W);
vawt.solution(iTSR).angle = struct('alpha',alpha,'beta',beta, 'alphaRate', alphaRate,'alphaEf',alphaEf,'alphaRefL', alphaRefL, 'alphaRefD', alphaRefD);
vawt.solution(iTSR).force = struct('CL',CL,'CD',CD,'CFx',CFx);
vawt.solution(iTSR).torque = struct('CTb',CTb,'CT',CT);
vawt.solution(iTSR).power = struct('CP', CP, 'CP1', CP1, 'CP2', CP2);
vawt.solution(iTSR).ratio = struct('L_D', CL./CD);

end