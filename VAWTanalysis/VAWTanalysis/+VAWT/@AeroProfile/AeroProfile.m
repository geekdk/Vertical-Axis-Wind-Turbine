classdef AeroProfile < handle
%AEROPROFILE    Aerodynamic profile class.
%
%   AeroProfile objects are handle objects that contain data of lift and
%   drag coefficients of a determined profile for different values of angle
%   of attack.
%   
%   AeroProfile Properties: 
%       profileName - Profile name (e.g. 'Naca0012').
%       naca - Table that contains Cl, Cd and angle of attack data.
%       alphaOptim - Angle of attack for maximum Cl/Cd in rad.
%       alphaOptimDeg - Angle of attack for maximum Cl/Cd in degrees.
%       alphaZeroLift - Angle of attack for zero lift in rad.
%       alphaZeroLiftDeg - Angle of attack for zero lift in degrees.
%       alphaStall - Angle of attack at stall in rad.
%       alphaStallDeg - Angle of attack at stall in degrees.
%       CLa - Slope of the linear part of the lift curve in rad^-1
%       thick_chord - Thickness over chord ratio.
%
%   AeroProfile Methods: 
%       AeroProfile - Constructor
%       getClCd - Lift and drag coefficients.
%       getCl - Lift coefficient.
%       getCd - Drag coefficient.

%
%   See also HANDLE.
    
    properties (SetAccess = private)
        profileName %Profile name (e.g. 'Naca0012').
%NACA - Table with Cl, Cd and angle of attack data (both in degrees and in
%radiants) vectors.
        naca
        alphaOptim %Angle of attack for maximum Cl/Cd in rad.
        alphaOptimDeg %Angle of attack for maximum Cl/Cd in degrees.
        alphaZeroLift %Angle of attack for zero lift in rad.
        alphaZeroLiftDeg %Angle of attack for zero lift in degrees.
        alphaStall %Angle of attack at stall in rad.
        alphaStallDeg %Angle of attack at stall in degrees.
        CLa %Slope of the linear part of the lift curve in rad^-1
        thick_chord %Thickness over chord ratio.
    end
    
    methods
        function profile = AeroProfile(filename)
%AEROPROFILE    AeroProfile Constructor
%   
%   obj = AeroProfile loads the .csv file that contains a naca table
%   specified by the user. Then it translates the domain (angle of attack)
%   to a range from -180 to 180 degrees. It also initializes the angle of
%   attack for maximum lift over drag, stall and zero lift.
%
%   See also TABLE, READTABLE, WRITETABLE.
            if nargin < 1 || isempty(filename)
                choose = 1;
            else
                choose = 0;
            end
            if isempty(profile.naca)
                if choose == 1
                    disp('Choose .csv file that contains a valid naca table')
                    [NacaFilename, NacaPathname]=uigetfile('*.csv');
                else
                    NacaFilename=filename;
                    NacaPathname='';
                end
                profile.profileName=NacaFilename;
                fileID = fopen([NacaPathname,NacaFilename]);
                profile.thick_chord=cell2mat(textscan(fileID,'%f',1));
                fclose(fileID);
                datain=csvread([NacaPathname,NacaFilename],2,0);
                AoADeg=datain(:,1);
                Cd=datain(:,3);
                Cl=datain(:,4);
                % translate the profile data to a domain of -180 to +180 degrees.
                AoADeg=AoADeg(AoADeg>=0 & AoADeg <=180);
                Cl=Cl(AoADeg>=0 & AoADeg <=180);
                Cd=Cd(AoADeg>=0 & AoADeg <=180);
                alphaDeg=[-AoADeg(end:-1:2);AoADeg];
                Cl=[-Cl(end:-1:2);Cl];
                Cd=[Cd(end:-1:2);Cd];
                % overwrite the naca table
                profile.naca=table(alphaDeg, Cl, Cd);
                % add alpha in radians to naca table
                profile.naca.alpha=profile.naca.alphaDeg*pi/180;
            end
            
            % compute the alpha important values
            profile.alphaMaxLoverD;
            profile.getAlphaZeroLift;
            profile.getAlphaStall;
        end
        
        [Cl, Cd] = getClCd(profile, alpha)
        Cl = getCl(profile, alpha)
        Cd = getCd(profile, alpha)
    end
    
    methods (Sealed, Access = protected, Hidden)
        alphaMaxLoverD(profile)
        getAlphaZeroLift(profile)
        getAlphaStall(profile)
    end
    
end

