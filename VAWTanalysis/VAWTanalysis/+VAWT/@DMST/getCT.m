function CT = getCT(vawt, CTb)
%GETCT    Non dimensional torque of all VAWT.
%
%   CT = vawt.getCT(CTb) returns the non dimensional torque (CT) of the 
%   overall turbine from the torque of one blade (CTb).
    CT=zeros(size(CTb));
    CTb=vawt.solidity*CTb/vawt.nblades;
    indCT=1:2*vawt.Nth;
    stepCT=2*vawt.Nth/vawt.nblades;
    for i=1:vawt.nblades
        CT=CT+[CTb(indCT>(stepCT*(i-1))),CTb(indCT<=(stepCT*(i-1)))];
    end
end