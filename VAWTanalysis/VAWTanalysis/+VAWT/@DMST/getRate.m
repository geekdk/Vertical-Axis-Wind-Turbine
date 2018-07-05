function [fRate, signfRate] = getRate( f, Ax, xB )
%GETRATE 	Rate of change

%   [fRate, signfRate] = getRate( f, Ax, xB ) computes the second order 
%   rate of change of the function vector f on the independent variable 
%   whose limits are descrived by the vector xB = [a, b] and whose inner
%   step is Ax.

    if (nargin < 3) xB = [0, 0]; end
    
    fM = (f(:,1:end-1) + f(:,2:end)) /2;
    fE = [fM,xB(2)];
    fW = [xB(1),fM];
    fRate = (fE - fW);
    fRate = fRate / Ax;
    signfRate = sign ( fRate );
end

