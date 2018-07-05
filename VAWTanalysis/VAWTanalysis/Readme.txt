VAWT package Readme:

Author

	David Vallverdu

Co-Authors

	Peter Kozak
	Dietmar Rempfer

License
    
    Read license.txt

Information

    This package contains the necessary classes to analyse Vertical Axis 
    Wind Turbines (VAWTs) using the Stream Tube model and its different 
    derivations. There is support for fixed and variable pitch cases.
    All camputations are made with non dimensional values.

    Contents
	license.txt: license file.

		Matlab package:
			VAWT

        Matlab classes inside package VAWT:
            AeroProfile
            DMST

        Example.m: example file.

        Readme.txt: readme file.

        clcd_Naca0021: csv file containing information about Cl 
        and Cd for different values of AoA for Naca profile 0021.
		Obtained with FV N-S simulation using Star-CCM+.

		bem_diag.jpg: diagram of the output velocities along the wind stream.

		blade_diag.jpg: diagram of the geographical distribution of velocities
		in the blade.

Help
    
	type 'help VAWT' to see all available MATLAB documentation.
