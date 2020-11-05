/*-----------------------------------------------------------------------------
 *                      	MISCELLANEOUS
 *
 * Author:      Daniel Romero Mujalli
 * Written:     31/12/2012
 * Last update: 24/10/2019
 *
 * Summary:      Includes all the header files or libraries used in
 *				 the project.
 *
 *---------------------------------------------------------------------------*/
 #ifndef MICELLANEOUS_H
 #define MICELLANEOUS_H
 /* Libraries */


#include "../headers/treatment/treatment.h"
#include "../headers/parameter/parameter.h"
#include "../headers/parameter/classParameter.h"
#include "../headers/debug/debug.h"



#include "../headers/classes/sensor.h"
#include "../headers/classes/agent.h"
#include "../headers/classes/neural_network.h"

#include "../headers/classes/Genetic_Algorithm.h"
#include "../headers/classes/perceptron.h"

#include "../headers/initialization/initialization.h"
#include "../headers/runWorld/runWorld.h"
#include "../headers/runWorld/migrationExclusive.h"


#include "../headers/sensorFunctions/sensorFunctions.h"
#include "../headers/agentFunctions/agentFunctions.h"
#include "../headers/geneticFunctions/geneticFunctions.h"


#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "../headers/outputData/outputData.h"
#include "../headers/readWeights/readWeights.h"



/* For compatibility with ubuntu, disable all the headers below				 */

#include "../sources/sensorFunctions.cpp" 
#include "../sources/sensor.cpp" 
#include "../sources/agent.cpp"
#include "../sources/neural_network.cpp"
#include "../sources/Genetic_Algorithm.cpp"
#include "../sources/perceptron.cpp"
#include "../sources/agentFunctions.cpp"
#include "../sources/geneticFunctions.cpp"
#include "../sources/initialization.cpp"
#include "../sources/readWeights.cpp"
#include "../sources/runWorld.cpp"
#include "../sources/migrationExclusive.cpp"
#include "../sources/outputData.cpp"

#endif
