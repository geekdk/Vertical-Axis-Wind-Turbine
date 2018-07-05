function [CLmod, CDmod, alphaRefL, alphaRefD] = getCLCDB( vawt, omega, alpha, W, alphaRate )
%GETCLCDB	Compute lift and drag coefficients for Berg model
% 
%   [CLmod, CDmod, alphaRefL, alphaRefD] = vawt.getCLCDB(omega, alpha, W, alphaRate )
%   computes the lift and drag coefficients for Berg model. omega is the
%   VAWT rotation speed, alpha is the angle of attack, W is the blade
%   relative velocity and alphaRate is the rate of change of the angle of
%   attack. alpha must be a positive value. The outputs are CLmod and
%   CDmod, lift and drag coefficients, respectively, and alphaRefL and
%   alphaRefD, refferene angle of attack for lift and drag characteristic,
%   respectively.
% 
%   See also GETCLCDG, GETCL, GETCD
    [CLdyn, CDdyn, alphaRefL, alphaRefD] = vawt.getCLCDG(omega, alpha, W, alphaRate);

    CLs = vawt.getCl(alpha);
    CDs = vawt.getCd(alpha);
    
    CLmod = CLs + ((vawt.dStall.Am * vawt.alphaStall - alpha) / (vawt.dStall.Am * vawt.alphaStall - vawt.alphaStall) .* (CLdyn - CLs)) .* (alpha <= vawt.dStall.Am * vawt.alphaStall);
    CDmod = CDs + ((vawt.dStall.Am * vawt.alphaStall - alpha) / (vawt.dStall.Am * vawt.alphaStall - vawt.alphaStall) .* (CDdyn - CDs)) .* (alpha <= vawt.dStall.Am * vawt.alphaStall);

end