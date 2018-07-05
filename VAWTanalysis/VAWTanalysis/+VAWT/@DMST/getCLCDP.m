function [CL, CD, alphaRefL, alphaRefD] = getCLCDP( vawt, theta, omega, alpha, W, alphaRate )
%GETCLCDP	Compute lift and drag coefficients for Paraschivoiu model
% 
%   [CLmod, CDmod, alphaRefL, alphaRefD] = vawt.getCLCDP(omega, alpha, W, alphaRate )
%   computes the lift and drag coefficients for Paraschivoiu model. omega
%   is the VAWT rotation speed, alpha is the angle of attack, W is the
%   blade relative velocity and alphaRate is the rate of change of the
%   angle of attack. alpha must be a positive value. The outputs are CLmod
%   and CDmod, lift and drag coefficients, respectively, and alphaRefL and
%   alphaRefD, refferene angle of attack for lift and drag characteristic,
%   respectively.
% 
%   See also GETCLCDS, GETCL, GETCD
    
    switch vawt.dStall.subModel
        case 'G'
            [CLd, CDd, alphaRefLd, alphaRefDd] = getCLCDG( vawt, omega, alpha, W, alphaRate );
        case 'S'
            [CLd, CDd, alphaRefLd, alphaRefDd] = getCLCDS( vawt, omega, alpha, W, alphaRate );
        case 'B'
            [CLd, CDd, alphaRefLd, alphaRefDd] = getCLCDB( vawt, omega, alpha, W, alphaRate );
    end
    
    
    CLn = vawt.getCl(alpha);
    CDn = vawt.getCd(alpha);
    
%     Athd=180/vawt.Nth;
%     Ath=Athd*pi/180;
%     condN=(sin(theta) < 0) & ((cos(theta) >= cos(195*pi/180+Ath/2)) & (cos(theta) <= cos(315*pi/180 - Ath/2)));
%     condD=(sin(theta) >= 0) | ((cos(theta) <= cos(195*pi/180-Ath/2)) | (cos(theta) >= cos(315*pi/180 + Ath/2)));
%     fn = condN + (((-2*(alpha-(vawt.alphaStall-Ath/2)).^2/(Ath)^2+1) .* (alpha<=vawt.alphaStall)) + ((2*(alpha-(vawt.alphaStall+Ath/2)).^2/(Ath)^2) .* (alpha>vawt.alphaStall)) ) .* (abs(alpha-vawt.alphaStall)<(Ath/2));
%     fd = condD + (((2*(alpha-(vawt.alphaStall-Ath/2)).^2/(Ath)^2) .* (alpha<=vawt.alphaStall)) + ((-2*(alpha-(vawt.alphaStall+Ath/2)).^2/(Ath)^2+1) .* (alpha>vawt.alphaStall)) ) .* (abs(alpha-vawt.alphaStall)<(Ath/2));
        
    fn=(cos(theta) < 0) & ((sin(theta) <= sin(105*pi/180)) & (sin(theta) >= sin(225*pi/180)));
    fd=(cos(theta) >= 0) | ((sin(theta) >= sin(105*pi/180)) | (sin(theta) <= sin(225*pi/180)));

    CL = CLn .* fn + CLd .* fd;
    CD = CDn .* fn + CDd .* fd;
    alphaRefL = alpha.* fn + alphaRefLd.* fd;
    alphaRefD = alpha.* fn + alphaRefDd.* fd;
end