%% VAWT package usage example
% This example aims to show VAWT package usage for solving vertical axis
% wind turbines. The main class used for this purpose is DMST inside VAWT.
% Type:
help VAWT
% to access the whole documentation of the VAWT package.

%% Creating the turbine object
% To create the turbine object, we simply call:
%                       solidity    TSR       # of blades   
myTurbine = VAWT.DMST      (   0.1   ,    2    ,        3       )
% TSR can also be a vector. You will be prompted to choose a profile.csv
% file. 'clcd_Naca0021.csv' is available in this directory. The object
% can also be created by specifing the csv file to be fetched:
% vawt = VAWT.DMST(0.1,2,3,'some_directory_path/lift_drag_csv_file.csv');
% Learn more about profile specification by typing:
help VAWT.AeroProfile
% and click on 'AeroProfile - Constructor' hyperlink.

%% Running the solver
% To run the solver, once the object has been created, we just type:
myTurbine.solve
% Note that running the solver implies some outputs on the command window.
% This process should not be interrupted or the output data will be
% corrupted.

%% Obtaining the output data
% To obtain an struct with all the calculated data, once the solver has
% been run at least once, we can type:
outStruct = myTurbine.solution;
% Now we can access each individual field by calling it. For example, we
% call the Torque Coefficient field:
torque = outStruct.torque.CT;
% To see all available output fields type:
outStruct
% or:
help VAWT.DMST/solution

%% Changing parameters
% If we want to change the initial parameters, we use the function 'set':
%            option    value
myTurbine.set  ('solidity' , 0.25 );
% Note that now, when you type:
myTurbine
% the property solidity in the object list has been modified to 0.25.
% A whole list of parameters and possible values that can be changed with
% this function can be seen by typing
help VAWT.DMST.set
% Note that whenever 'set' is called, the solution is erased with the
% function 'reset'. Type
help VAWT.DMST.reset
% for mor information.

%% TSR as a vector
% If we want to obtain the power coefficient for a range of TSR, we can use
% TSR as a vector:
myTurbine.set  ('TSR' , 1:0.5:4.5 );
% Then we solve the VAWT:
myTurbine.solve
% Now, the solution structure has become an array of structures (the
% structure diagnostics behaves the same way). To access the solution
% structure we need to specify the TSR:
iTSR = 1;
outStruct = myTurbine.solution(iTSR);
% Now outStruct containts the solution structure for the TSR corresponding
% to the first position of the TSR vector. Changing the value of iTSR would
% return the solution corresponding to the rest of the TSR values,
% according to which position they occupy in the TSR vector.

%% Pitch
% VAWT Analysis supports pitch, which is an offset angle applied to the
% blade (positive if the blade leading edge points outwards respetively to
% the blade trajectory). To apply a constant pitch of 1 rad:
myTurbine.set ('pitch',180/pi);
% To apply a non constant pitch, it has to be set as a vector of size 
% (1, 2*Nth) that corresponds to the vector of azimuthal angle vawt.theta.
% This is an example of a sine distributed pitch.
myTurbine.set ('pitch', 0.5*(1-cos(2*myTurbine.theta))*180/pi);
% You can check that the pitch is correcty set by plotting it:
plot(myTurbine.theta,myTurbine.pitch)
% Once the pitch is applied, you can solve as usual:
myTurbine.solve;
% Type
help VAWT.DMST/set
% for the characteristics of the pitch parameter.

%% Plotting data
% We can plot the results, once the object has been solved with 'getPlots'
% function:
myTurbine.getPlots
% This plots a bunch of variables. Also, this function can be called with
% options to specify which type of variables are tob e plotted. For
% example:
myTurbine.getPlots('alpha')
% Only plots the variables related to the angle of attack. To see a
% complete list of options type:
help VAWT.DMST.getPlots
