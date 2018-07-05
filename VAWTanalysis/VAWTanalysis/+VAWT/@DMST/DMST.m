classdef DMST < VAWT.AeroProfile
%DMST Double Multiple Streamtube class
%   
%   DMST objects are objects aimed to solve VAWTs using Double-Multiple
%   Sreamtube Model sith Dyanamic Stall Modifications.
%
%   DMST class is a subclass of AeroProfile. Hence, DMST objects are handle
%   objects.
%
%   All units used in DMST properties and outputs are International System
%   unless stated otherwise.
%
%   DMST Inherited Properties:
%       AeroProfile class - All AeroProfile properties.
%   
%   DMST Properties:
%       solidity - VAWT solidity.
%       TSR - VAWT tip speed ratio.
%       nblades - VAWT number of blades.
%       U - Free stream velocity.
%       chord - Blade chord.
%       thickness - Blade thickness.
%       diameter -  VAWT diameter.
%       height - VAWT blade height.
%       aspratio - VAWT blade aspect ratio. height / chord.
%       omega - VAWT rotation speed.
%       speedSound - Speed of sound.
%       theta - Azimuthal angle.
%       At - Time step between nodes.
%       dStall - Dyamic stall options.
%       wake - Wake interaction options.
%       pitch - Constant pitch added to the blade in rad.
%       solution - Output structure array.
%       diagnostic - Solver diagnostic structure array.
%       Nth - Half the number of nodes.
%       thetaMin - Minimum value of azimuth angle when computing thrust.
%
%   DMST Methods: 
%       DMST - Constructor
%       set - Set a new value to  any parameter or option.
%       solve - Solve the whole VAWT.
%       solveCase - Solve interference factor for a single value of TSR.
%       solveLambda1 - Solve interference factor for a single node of the 
%       front half.
%       solveLambda2 - Solve interference factor for a single node of the 
%       rear half.
%       getLambdaEq1 - Function used by fzero inside solveLambda1.
%       getLambdaEq2 - Function used by fzero inside solveLambda2.
%       postProcess - Compute all the output variables from the 
%       interference factor.
%       reset - Reset VAWT solution.
%       recalcNth - Auxiliary function for reset.
%       getCP - Non dimensional power coefficient.
%       getCT - Non dimensional torque of all VAWT.
%       getCTb - Non dimensional torque of a blade.
%       getCLCDG - Lift and drag coefficients using Gormont model.
%       getCLCDB - Lift and drag coefficients using Berg model.
%       getCLCDS - Lift and drag coefficients using Strickland model.
%       getCLCDP - Lift and drag coefficients using Paraschivoiu model.
%       plotPower - Plot power coefficient.
%       plotTorque - Plot torque coefficient against azimuth angle.
%       plotVAWT - Plot any field that depends on azimuth angle.
%       polarVAWT - Same as plotVAWT but in polar coordinates.
% 
%   DMST Static Methods:
%       getW - Non dimensional relative velocity.
%       getBeta - Flight path angle.
%       getAlpha - Angle of attack.
%       getRate - Rate of change of any vector.
%       getRateLoop - Rate of change of any vector. Periodic functions
%       only.
%
%   See also AEROPROFILE, HANDLE, FZERO, SET.
    
    properties (SetAccess = protected)
        solidity %VAWT solidity.
%TSR - VAWT tip speed ratio.
% 
%   Can either be a scalar or a vector.
        TSR
        nblades %VAWT number of blades.


        U %Free stream velocity
        density %Flow density.
        chord %Blade chord.
        thickness %Blade thickness.
        diameter %VAWT diameter.
        height %VAWT blade height. height = 0 -> 2D case.
        aspratio %VAWT blade aspect ratio. height / chord.
        omega %VAWT rotation speed.
        speedSound %Speed of sound.
        theta %Azimuthal angle vector. length(theta) = 2*Nth.
        At %Time step between nodes of theta.
        
        dStall %Structure with the dynamic stall options. 
        
        wake %Wake interaction option. wake = 0 -> no wake interaction.
        
        pitch %Constant pitch added to the blade in rad.

%SOLUTION - Structure array with the output variables.
% 
%   To know more about its contents, call this structure once the DMST
%   object has been solved. SOLUTION is an array and each position
%   corresponds to the same position of the TSR vector. Hence, to call the
%   solution structure, one must write 'obj.solution(i), where i is the
%   position.
        solution
%DIAGNOSTIC - Structure array with the diagnostic output of the solver.
% 
%   To know more about its contents, call this structure once the DMST
%   object has been solved. DIAGNOSTIC is an array and each position
%   corresponds to the same position of the TSR vector. Hence, to call the
%   solution structure, one must write 'obj.diagnostic(i), where i is the
%   position.
% 
%   See also FZERO.
        diagnostic 
        

        Nth %Number of discretization points of the azimuthal angle vector.

        thetaMin %Minimum value of azimuth angle when computing thrust.
    end
    
    properties (Access = protected)
        NTSR %Length of TSR vector.
        theta1 %Equals to theta(1:end/2)
        theta2 %Equals to theta(1+end/2:end)
    end
    
    methods
        function vawt = DMST(solidity, TSR, nblades, nacaFile)
%DMST    DMST Constructor
%   
%   obj = DMST(solidity, TSR, nblades, nacaFile) sets the object properties
%   that match the four arguments to the given values. Default values are:
%       solidity = 3*85.8/1030
%       TSR = 2.5
%       nblades = 3
%       nacaFile = []
%   The rest of the properties are set to default values that can bee seen
%   when calling the created object.
%
%   See also AEROPROFILE, SET.
            
            if (nargin < 1) solidity = 3*85.8/1030; end;
            if (nargin < 2) TSR = 2.5; end;
            if (nargin < 3) nblades = 3; end;
            if (nargin < 4) nacaFile = []; end;
            
            vawt = vawt@VAWT.AeroProfile(nacaFile);
            
            vawt.solidity=solidity;
            vawt.TSR=TSR;
            vawt.nblades=nblades;
            vawt.height=0;
            vawt.U=9;
            vawt.density=1.225;
            vawt.speedSound = sqrt(1.4*8.314*288/0.029);
            vawt.chord=0.0858;
            
            vawt.Nth=50;
            vawt.thetaMin=pi/2*0.05;
            
            vawt.dStall= struct('model','N');
            vawt.wake=0;
            
            vawt.reset;
        end 
        
        [CL, CD, alphaRefL, alphaRefD] = getCLCDG( vawt, omega, alpha, W, alphaRate )
        [CL, CD, alphaRefL, alphaRefD] = getCLCDS( vawt, omega, alpha, W, alphaRate )
        [CL, CD, alphaRefL, alphaRefD] = getCLCDB( vawt, omega, alpha, W, alphaRate )
        [CL, CD, alphaRefL, alphaRefD] = getCLCDP( vawt, theta, omega, alpha, W, alphaRate )
        [CP, CP1, CP2] = getCP(vawt, TSR, CTb)
        CT = getCT(vawt, CTb)
        CTb = getCTb(vawt, V, Vt, W, theta, Cl, Cd)
        getPlots(vawt, option)
        fig = plotPower(vawt, hAxes)
        fig = plotTorque(vawt, hAxes)
        fig = plotVAWT(vawt, val, titleName, hAxes)
        fig = polarVAWT(vawt, val, titleName, hAxes)
        reset(vawt)
        recalcNth(vawt)
        vawt = set(vawt,optionName,value)
        solve(vawt)
        solveCase(vawt, iTSR)
        postProcess(vawt, iTSR)
        [lambda1,fval,exitflag1,output1] = solveLambda1(vawt, iTSR, ith, alphaRate)
        [lambda2,fval,exitflag2,output2] = solveLambda2(vawt, iTSR, ith, lambda1, alphaRate)
        residual1 = getLambdaEq1(vawt, iTSR, ith, lambda, alphaRate)
        residual2 = getLambdaEq2(vawt, iTSR, ith, lambda, lambda1, alphaRate)
    end
    
    methods (Static)
        alpha = getAlpha(theta, beta, pitch)
        beta = getBeta(V, Vt, theta)
        W = getW(V, Vt, theta)
        
        [fRate, signfRate] = getRate( f, Ax )
        [fRate, signfRate] = getRateLoop( f, Ax )
    end
    
end

