function [fRate, signfRate] = getRateLoop( f, Ax )
%GETRATELOOP 	Rate of change for periodic functions.

%   [fRate, signfRate] = getRateLoop( f, Ax ) computes the second order 
%   rate of change of the function vector f on the independent variable 
%   whose inner step is Ax. The derivated function must be periodic and f
%   must contain any number of full periods.

    fRate = ([f(2:end),f(1)] - [f(end),f(1:end-1)]) / (2*Ax);
    signfRate = sign ( fRate );
end

