function recalcNth(vawt)
%RECALCNTH      Auxiliary function to calculate Nth
% 
%   See also RESET.
    
    oldNth=vawt.Nth;
    opt1=oldNth+(vawt.nblades-mod(oldNth,vawt.nblades))*(mod(oldNth,vawt.nblades)~=0);
    opt2=abs(oldNth-mod(oldNth,vawt.nblades)*(mod(oldNth,vawt.nblades)~=0));
    dif1=abs(oldNth-opt1);
    dif2=abs(oldNth-opt2);
    if dif1>dif2
        vawt.Nth=opt2;
    else
        vawt.Nth=opt1;
    end
    if length(vawt.pitch)~=2*vawt.Nth
        vawt.pitch = zeros(1,2*vawt.Nth);
    end
end

