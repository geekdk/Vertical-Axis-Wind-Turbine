function [CL, CD, alphaRefL, alphaRefD] = getCLCDS( vawt, omega, alpha, W, alphaRate )
%GETCLCDS	Compute lift and drag coefficients for Strickland model
% 
%   [CLmod, CDmod, alphaRefL, alphaRefD] = vawt.getCLCDS(omega, alpha, W, alphaRate )
%   computes the lift and drag coefficients for Stricklnad model. omega is
%   the VAWT rotation speed, alpha is the angle of attack, W is the blade
%   relative velocity and alphaRate is the rate of change of the angle of
%   attack. alpha must be a positive value. The outputs are CLmod and
%   CDmod, lift and drag coefficients, respectively, and alphaRefL and
%   alphaRefD, refferene angle of attack for lift and drag characteristic,
%   respectively.
% 
%   See also GETCL, GETCD
    tau=0.75E-2/vawt.Nth*omega;
    SaR = sign ( alphaRate );
    aR_tau_sup_lim=500;
    aR_tau=alphaRate/tau.*(alphaRate/tau<aR_tau_sup_lim & alphaRate/tau>-aR_tau_sup_lim) + aR_tau_sup_lim.*(alphaRate/tau>=aR_tau_sup_lim) - aR_tau_sup_lim.*(alphaRate/tau<=-aR_tau_sup_lim);
    SaRs=(1-exp(-aR_tau)).*(SaR>=0)+(-1+exp(aR_tau)).*(SaR<0);

    K1 = 0.75 + 0.25*SaRs;
    phiLift = 1.4 -6*(0.06 - vawt.thickness / vawt.chord);
    phiDrag = 1 -2.5*(0.06 - vawt.thickness / vawt.chord);
    alphaRefL = alpha - phiLift * K1 .* sqrt(abs(vawt.chord*alphaRate./(2*W))).*SaRs;
    alphaRefD = alpha - phiDrag * K1 .* sqrt(abs(vawt.chord*alphaRate./(2*W))).*SaRs;
    
    CLs= (alpha ./ (alphaRefL - vawt.alphaZeroLift)) .* vawt.getCl(alphaRefL);
    CDs = vawt.getCd(alphaRefD);
    
    CLn = vawt.getCl(alpha);
    CDn = vawt.getCd(alpha);
    
    Aad=2;
    Aa=Aad*pi/180;
    fn = (alpha<(vawt.alphaStall-Aa/2)) + (((-2*(alpha-(vawt.alphaStall-Aa/2)).^2/(Aa)^2+1) .* (alpha<=vawt.alphaStall)) + ((2*(alpha-(vawt.alphaStall+Aa/2)).^2/(Aa)^2) .* (alpha>vawt.alphaStall)) ) .* (abs(alpha-vawt.alphaStall)<(Aa/2));
    fs = (alpha>(vawt.alphaStall+Aa/2)) + (((2*(alpha-(vawt.alphaStall-Aa/2)).^2/(Aa)^2) .* (alpha<=vawt.alphaStall)) + ((-2*(alpha-(vawt.alphaStall+Aa/2)).^2/(Aa)^2+1) .* (alpha>vawt.alphaStall)) ) .* (abs(alpha-vawt.alphaStall)<(Aa/2));
        
    CL = CLn .* fn + CLs .* fs;
    CD = CDn .* fn + CDs .* fs;