# Social-Learning-Project-Robotics
This repository contains the simulator I created and use for my research on social learning in small populations during my Master studies at the Simon Bolivar University in Venezuela. I programmed the simulator in C++ and can be visualize on Netlogo.


PROJECT SOCIAL LEARNING ( ROMERO-MUJALLI ET AL. 2017 JOURNAL OF ETHOLOGY)

URL: https://link.springer.com/article/10.1007%2Fs10164-016-0490-8

Cite this article as:
    Romero-Mujalli, D., Cappelletto, J., Herrera, E.A. et al. J Ethol (2017) 
    35: 61. https://doi.org/10.1007/s10164-016-0490-8

UNIVERSIDAD SIMÓN BOLÍVAR, CARACAS, VENEZUELA
UNIVERSIDAD CENTRAL DE VENEZUELA, CARACAS, VENEZUELA
POTSDAM UNIVERSITÄT, POTSDAM, DEUTSCHLAND


Contact information: 
Daniel Romero-Mujalli email: danielrm84@gmail.com



TERMS OF USE
If you decide to use any material of our work, the code, or part of it, please remember to
do the correct citation. Many thanks in advance!

Please also also refer to the license agreement as well.

UPDATED CODE

Project_Social_Learning_V4

*) main_Project_SL/

	contain the main function of the project.
	Run main_netlogo.cpp to run the model. This will also create a movement file that
	can be plotted using netlogo.

Experimental scenarios can be set at
	/include/headers/treatment/treatment.h

	- Scenario of Behavior: social learning SL, asocial learning AL, mixed population Mx,
		    
	  genetic evolution GE and Random Search RS (Control)


	- Scenario of Environment: static, abrupt change or gradual change. Also includes

	  Migration, an extra condition to test the feasibility of
 discovering alternatives
	(THE CURRENT UPDATED VERSION SUPPORTS ONLY THE STATIC SCENARIO)

	For details on parameter values used in the simulation please refer to the methods in
	Romero-Mujalli et al. 2017.

All parameter values can be set at
	/include/headers/parameter

	To run the project, 
	
	
	UBUNTU:
	
	
	check /include/headers/miscellaneous/miscellaneous.h: 
	all the sources (.cpp)
 should be commented (//)
	
	(THE MAKEFILE IN THIS VERSION IS OUTDATED)
	

	WINDOWS:

	
	make sure that all sources (.cpp) files are uncommented in
	
	/include/headers/miscellaneous/miscellaneous.h

	
	Build and compile the main.cpp with the program of your choice
	(example, dev c++)


**) main_training_V3.cpp

	this is the main routine used to train
the neural networks (NN). It is possible to train networks of different topology.
The networks are then store in output files.

	to run this file in ubuntu type to terminal: make training
	then: ./training (outdated!)
	for cleaning objects, type: make clean

***) include/

	this folder contains all the header files, including
clases, functions, sources and a miscellaneous file.

	I've included documentation on how to use each function and can be found 
	in the corresponding header file.

files (.h) 
        /include/headers/agentFunctions
	/include/headers/classes
	/include/headers/debug
	/include/headers/geneticFunctions
	/include/headers/initialization
	/include/headers/outputData
	/include/headers/parameter
	/include/headers/readWeights
	/include/headers/runWorld
	/include/headers/sensorFunctions
	/include/headers/treatment


