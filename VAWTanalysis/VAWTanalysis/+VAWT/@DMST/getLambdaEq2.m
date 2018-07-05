function residual2 = getLambdaEq2(vawt, iTSR, ith, lambda, lambda1, alphaAnt)
%GETLAMBDAEQ2     Lambda Equation of the rear half-cycle.
%
%   residual2 = vawt.getLambdaEq2(iTSR, ith, lambda, lambda1, alphaAnt) 
%   returns the differenciation (residual1) of the thrust coefficient 
%   obtained by loads  mehthod and the one obtained by conservation method 
%   for a given tip speed ratio index (iTSR), azimuthal angle index (ith), 
%   interference factor (lambda), upwind interference factor (lambda1) and
%   angle of attack of the anterior node (alphaAnt).
    V2=(2*lambda1-1).*lambda;
    W=vawt.getW(V2, vawt.TSR(iTSR), vawt.theta(ith));
    beta=vawt.getBeta(V2, vawt.TSR(iTSR), vawt.theta(ith));
    alpha=vawt.getAlpha(vawt.theta(ith), beta, vawt.pitch(ith));
    
    if strcmp(vawt.dStall.model,'N')
        [CL, CD0] = vawt.getClCd(alpha);
    else
        Sa = sign(alpha);
        alpha = abs(alpha); % dynamic stall models only accept positive angles of attack
        alphaAnt = abs(alphaAnt);
        alphaRate=(alpha-alphaAnt*(ith>(vawt.Nth+1)))/(vawt.At(iTSR)/(1+(ith==(vawt.Nth+1))));
        switch vawt.dStall.model
            case 'G'
                [CL, CD0] = getCLCDG( vawt, vawt.omega(iTSR), alpha, vawt.U*W, alphaRate );
            case 'S'
                [CL, CD0] = getCLCDS( vawt, vawt.omega(iTSR), alpha, vawt.U*W, alphaRate );
            case 'B'
                [CL, CD0] = getCLCDB( vawt, vawt.omega(iTSR), alpha, vawt.U*W, alphaRate );
            case 'P'
                [CL, CD0] = getCLCDP( vawt, vawt.theta(ith), vawt.omega(iTSR), alpha, vawt.U*W, alphaRate );
        end
        CL = Sa.*CL; % restore the lift sign
    end
    if vawt.aspratio<=0
        CDi=0;
    else
        CDi= vawt.solidity*CL.^2/(pi*vawt.aspratio*vawt.nblades);
    end
    CD=CD0+CDi;
    
    cond=sin(vawt.theta(ith)) > sin(-vawt.thetaMin);
    sTheta=cond.*sin(-vawt.thetaMin) + ~cond.*sin(vawt.theta(ith));
    CFx2=-vawt.solidity/pi*W.^2.*(CD.*cos(beta)-CL.*sin(beta))./sTheta./(2*lambda1-1).^2;
    
    cond= lambda >= 43/60;
    residual2=CFx2 - ( cond.*(4*lambda.*(1-lambda)) + ~cond.*(1849/900-26*lambda/15) );
end