function [CLdyn, CDdyn, alphaRefL, alphaRefD] = getCLCDG( vawt, omega, alpha, W, alphaRate )
%GETCLCDG	Compute lift and drag coefficients for Gormont model
% 
%   [CLmod, CDmod, alphaRefL, alphaRefD] = vawt.getCLCDG(omega, alpha, W, alphaRate )
%   computes the lift and drag coefficients for Gormont model. omega is the
%   VAWT rotation speed, alpha is the angle of attack, W is the blade
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
    M = W ./ vawt.speedSound;
%     M=zeros(size(W));

    M1L = 0.4 + 5*(0.06 - vawt.thickness / vawt.chord);
    M2L = 0.9 + 2.5*(0.06 - vawt.thickness / vawt.chord);
    phiMaxL = 1.4 + 6*(0.06 - vawt.thickness / vawt.chord);
    M1D = 0.2;
    M2D = 0.7 + 2.5*(0.06 - vawt.thickness / vawt.chord);
    phiMaxD = 1 + 2.5*(0.06 - vawt.thickness / vawt.chord);

    phi2L = phiMaxL .* max (0, min (1, (M - M2L) / (M1L - M2L)));
    phi1L = phi2L/2;
    phi2D = phiMaxD .* max (0, min (1, (M - M2D) / (M1D - M2D)));
    phi1D = 0;

    S = sqrt(abs(vawt.chord*alphaRate./(2*W)));

    Sc = 0.006 +1.5*(0.06 - vawt.thickness / vawt.chord);

    AalphaL = (phi1L .* S).*(S <= Sc) + (phi1L.*Sc + phi2L.*(S - Sc)).*(S > Sc);
    AalphaD = (phi1D .* S).*(S <= Sc) + (phi1D.*Sc + phi2D.*(S - Sc)).*(S > Sc);

%             K1 = (alphaRate >= 0) - 0.5.*(alphaRate < 0);
    K1 = (SaRs+1)*1.5/2-0.5;

    alphaRefL = alpha - K1 .* AalphaL;
    alphaRefD = alpha - K1 .* AalphaD;
    
    m = min((vawt.getCl(alphaRefL) - vawt.getCl(vawt.alphaZeroLift)) ./ (alphaRefL - vawt.alphaZeroLift) , (vawt.getCl(vawt.alphaStall) - vawt.getCl(vawt.alphaZeroLift)) ./ (vawt.alphaStall - vawt.alphaZeroLift));
    CLdyn = vawt.getCl(vawt.alphaZeroLift) + m.* (alpha - vawt.alphaZeroLift);
    CDdyn = vawt.getCd(alphaRefD);
end