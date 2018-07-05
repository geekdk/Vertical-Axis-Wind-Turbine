function  vawt = set(vawt,optionName,value)
%SET   Set a new value to any parameter.
%
%   obj = obj.set(optionName,value) sets the property defined by
%   optionName to value. 
%           Option      |   Possible        |       Description
%                       |   values          |
%       ===================================================================
%           'solidity'  |   any real        |   solidity
%                       |   positive scalar |
%       -------------------------------------------------------------------
%           'nblades'	|   any natural     |   number of blades
%                       |   positive scalar |
%       -------------------------------------------------------------------
%           'TSR'       |   any real        |   tip speed ratio
%                       |   positive scalar |
%                       |   or row vector   |
%       -------------------------------------------------------------------
%           'height'	|   any real        |   blade height [m]
%                       |   positive scalar |
%       -------------------------------------------------------------------
%           'U'         |   any real        |   free stream velocity [m/s]
%                       |   positive scalar |
%       -------------------------------------------------------------------
%           'density'	|   any real        |   flow density [kg/m^3]
%                       |   positive scalar |
%       -------------------------------------------------------------------
%         'speedSound'  |   any real        |   flow speed of sound [m/s]
%                       |   positive scalar |
%       -------------------------------------------------------------------
%           'chord'     |   any real        |   blade chord
%                       |   positive scalar |
%       -------------------------------------------------------------------
%           'Nth'       |   any natural     |   Number of discretization
%                       |   positive scalar |   points of the azimuthal
%                       |                   |   angle in a half-cycle*
%       -------------------------------------------------------------------
%           'thetaMin'  |   any real        |   minimum value of azimuthal
%                       |   positive scalar |   azimuthal angle for which 
%                       |                   |   thrust must be computed.
%       -------------------------------------------------------------------
%           'stall'     |   'N', 'G', 'B',  |   dynamic stall model:
%                       |   'S', 'P'        |   none, Gormont, Berg, 
%                       |                   |   Strickland or Paraschivoiu
%       -------------------------------------------------------------------
%           'wake'      |   0, 1            |   wake interaction model:
%                       |                   |   0 -> not applied
%                       |                   |   1 -> applied
%       -------------------------------------------------------------------
%           'pitch'     |   any real scalar |   pitch added to the
%                       |   or vector of    |   blade [rad]
%                       |   length (1,2*Nth)|   *pitch is reseted to 0 if
%                       |                   |   Nth changes
%       -------------------------------------------------------------------

    other = 0;
    switch optionName
        case 'solidity'
            vawt.solidity=value(1);
            
        case 'nblades'
            vawt.nblades=value(1);
            
        case 'TSR'
            vawt.TSR=value;
            vawt.NTSR=length(value);
            
        case 'height'
            vawt.height=value(1);
            
        case 'U'
            vawt.U=value(1);
            
        case 'density'
            vawt.density=value(1);
            
        case 'speedSound'
            vawt.speedSound=value(1);
            
        case 'chord'
            vawt.chord=value(1);
            
        case 'Nth'
            vawt.Nth=value(1);
            
        case 'thetaMin'
            vawt.thetaMin=value(1);
            
        case 'stall'
            vawt.dStall=struct('model',value);
            if strcmp(value,'B')
                vawt.dStall.Am = input('Enter Am value: ');
            elseif strcmp(value,'P')
                vawt.dStall.subModel = input('Enter Gormont variation (G, S or B): ','s');
                if strcmp(vawt.dStall.subModel,'B')
                    vawt.dStall.Am = input('Enter Am value: ');
                elseif not(strcmp(vawt.dStall.subModel,'S') || strcmp(vawt.dStall.subModel,'G'))
                    vawt.dStall=struct('model','N');
                end
            elseif not(strcmp(value,'S') || strcmp(value,'G'))
                vawt.dStall=struct('model','N');
            end
            
        case 'wake'
            vawt.wake= value~=0;
            
        case 'pitch'
            if length(value(1,:))>=2*vawt.Nth
                vawt.pitch=value(1,1:2*vawt.Nth);
            else
                vawt.pitch=value(1,1)*ones(1,2*vawt.Nth);
            end
            
        otherwise
            other = 1;
    end
    if (~other) disp('Option successfully set.'); end
    vawt.reset;
end