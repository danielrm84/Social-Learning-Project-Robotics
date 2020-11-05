/*-----------------------------------------------------------------------------
 *                      		INITIALIZATION
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  22/ 1/2017
 *
 * Summary:      This file contains the definition of the functions in
 *				 the file:
 *				 /include/headers/initialization/initialization.h
 *
 *---------------------------------------------------------------------------*/

#include "../miscellaneous/miscellaneous.h"

/* Create Patches
   This function create circular patches in the environment. At current stage,
   it is limited to maximum two patches 									 */
void createPatches(Agent patch[], int n, int max_x, int max_y, 
	float radius)
{
	// variables to store patch position, radius and distance
    float d, x0, y0, x1, y1, r0, r1;
    
    /* create non-overlapping patches 									 */
    do
    {
        for (int i = 0; i < n; i++)
        {
            patch[i] = Agent(max_x, max_y, 0.0, radius, 0.0);
        }
        r0 = patch[0].getRadius();
        x0 = patch[0].getxPosition();
        y0 = patch[0].getyPosition();
        x1 = patch[1].getxPosition();
        y1 = patch[1].getyPosition();
        r1 = patch[1].getRadius();
        d = getDistance(x0, y0, x1, y1);
		
		#ifdef DEBUG    
        // cout << "distace among patches " << d << endl;
        #endif
        
    }while(d < (r0 + r1));	
}
/*-------------- End of Create Patches --------------------------------------*/

/* Set the effect of patches on agent's energy
   Set the values for the white and black patches according to the scenario
   of environment.
   Currently, it is only implemented for the static, abrupt and no treatment
   scenarios																 */
void setEffectOfPatches(float &energy_w, float &energy_b)
{
	#ifdef NO_TREATMENT
        
    energy_w = WHITE_PATCH_EFFECT; /* both patches have no effect on agent 
										 energy		 						 */
    energy_b = WHITE_PATCH_EFFECT;
        
    #endif /* NO_TREATMENT */
        
    #ifdef STATIC
        
    energy_w = WHITE_PATCH_EFFECT;
    energy_b = BLACK_PATCH_EFFECT;
        
    #endif /* STATIC */
        
    #ifdef ABRUPT_CHANGE
        
    energy_w = WHITE_PATCH_EFFECT;
    energy_b = BLACK_PATCH_EFFECT;
        
    #endif /* ABRUPT_CHANGE */
}
/*----------- End of setEffectOfPatches	-------------------------------------*/

/* Create Agents
   create n Agent objects 													 */
void createAgents(Agent myAgent[], int n, float energy, float max_vel, 
					float agent_radius, int max_x, int max_y)
 {
 	/* building N agents											         */
    for (int i = 0; i < n; i++)
    {
        myAgent[i] = Agent(max_x, max_y, max_vel, agent_radius, energy);
    }
   
    
 }
/*---------------------- End of createAgents  -------------------------------*/

/* Create agents outside patches
   Create n_agents agents outside patches									 */
void createAgentsOutsidePatches(Agent myAgent[], int n_agents, float energy, 
                              float max_vel, float agent_radius, int max_x, 
							  int max_y, Agent patch[], int n_patches)
{
	// variables to store patch position, radius and distance
    float x0, y0, x1, y1, r0, r1, r, x, y, d1, d2;
	// store values from patches
		r0 = patch[0].getRadius();
        x0 = patch[0].getxPosition();
        y0 = patch[0].getyPosition();
        x1 = patch[1].getxPosition();
        y1 = patch[1].getyPosition();
        r1 = patch[1].getRadius();
        
	/* re-initialization of agents. Agents get initial random positions outside 
	   patches														 */
    for (int i = 0; i < n_agents; i++)
    {
        
        do
        {
            myAgent[i] = Agent(max_x, max_y, max_vel, agent_radius, energy);
            x = myAgent[i].getxPosition();
            y = myAgent[i].getyPosition();
            r = myAgent[i].getRadius();
           d1 = getDistance(x0, y0, x, y);
           d2 = getDistance(x1, y1, x, y);
           
        }while(d1 < (r0 + r) || d2 < (r1 + r));
    }
    
    #ifdef DEBUG
    
    // cout << "re-initializing Agent --> done!" << endl;
    
    #endif
}
/*--------------- End of createAgentsOutsidePatches  ------------------------*/

/* Create sensors
   create the sensors of the agent					   					 	 */
void createSensors(Agent myAgent[], Sensor mySensor[][SENSOR_NUMBER], int n, 
					float reach, int max_x, int max_y)
 {
    /* set SENSOR_NUMBER sensors (see sensor.h) per sensor object. One sensor
    object per agent. total N sensor objects                            	 */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < SENSOR_NUMBER; j++)
        {
            mySensor[i][j] = Sensor(reach, myAgent[i].getRadius(), 
                         myAgent[i].getxPosition(), myAgent[i].getyPosition(),
                         myAgent[i].getTheta());
            mySensor[i][j].setMaxDim(max_x, max_y);
        }
        refreshSensors(mySensor, i);
    }
 }
/*---------------------- End of create sensors  -----------------------------*/

/* 	Create neural networks (NN) 
	Create n NN with inputNN number of neurons in the input layer, hiddenNN
	neurons in the hidden layer, and outputNN neurons in the output layer. The
	values for these parameters are set in the file "classParameter.h".
	Romero-Mujalli et al. 2016 used values of (8, 10, 2).
	This function adds a bias to each layer, except for the output layer.
*/
void createNeuralNetwork(NeuralNetwork myNetwork[], int n, int inputNN, int outputNN)
{
	int totalweights = (inputNN+1) * outputNN * n;
	int m, h;
	float vector[totalweights];
	
	ifstream myFile;
	myFile.open("weights.xls");
	readWeights(myFile, vector, totalweights);
	myFile.close();
	
	m = 0;
	for (int i = 0; i < n; i++)
	{
		myNetwork[i].setWeightsFromFile(vector, m);
	}
}


void createNeuralNetworksThreeLayersNN(NeuralNetwork myNetwork[], int n, int inputNN, 
					  int hiddenNN, int outputNN)
 {
	/* 				Set NN weights from file 								 */
 	
	/* read values of weigths for the input and hidden layer of the NN from file:
	   inWeight_NN_100.xls and outWeight_NN_100.xls							 */ 
    int in = (inputNN+1) * hiddenNN * n;
    int hid = (hiddenNN+1) * outputNN * n;
    int m, h;
    float inW[in], hidW[hid];
    ifstream inFile, outFile;
	/* set weights															 */	
    inFile.open("inWeights_NN.xls");
    //inFile.open("inWeights_NN.csv");
	readWeights(inFile, inW, in);
    inFile.close();

    outFile.open("outWeights_NN.xls");
    //outFile.open("outWeights_NN.csv");
    readWeights(outFile, hidW, hid);
    outFile.close();
    /* building N neural networks 											 */ 
    m = h = 0;
    for (int i = 0; i < n; i++)
    {
        myNetwork[i].setWeightsFromFile(inW, hidW, m, h);
    } 
 }
/*---------------------- End of createNeuralNetworks  -----------------------*/

/* Create perceptron or ground controller
   Create the perceptron of the agent. Its function is to perceive ground color
   and affect the preference of the agent for a given patch			  		 */
void createPerceptron(Perceptron myPerceptron[], int n_agents, 
					  float learning_rate, float mut_rate, float omega_mut_rate, 
					  float phi_mut_rate, float rnd_w)
{
								
	/* starting ground controller depending on treatment of behavior         */ 
    for (int i = 0; i < n_agents; i++)
    {
    	#ifdef MIXED
    	
        myPerceptron[i].startMixedLearning(omega_mut_rate, phi_mut_rate);
        myPerceptron[i].setPhi(learning_rate);
        myPerceptron[i].setNeighbors(1);
        
        /* set half AL and half SL (MIXED only)								 */
        if(i < N/2){ myPerceptron[i].setOmega(true); }
		else{ myPerceptron[i].setOmega(false); }
		        
        #endif
        
        #ifdef SOCIAL
        
        myPerceptron[i].startSocialLearning(learning_rate);
        myPerceptron[i].setNeighbors(1);
        
        #endif
        
        #ifdef ASOCIAL
        
        myPerceptron[i].startIndividualLearning(learning_rate);
        
        #endif
        
        #ifdef GEN_EVOL
        
        myPerceptron[i].startGeneticEvolution(mut_rate);
        
        #endif
        
        #ifdef RND_SEARCH
        
        myPerceptron[i].startRandomSearch(rnd_w);
        
        #endif
    }
}
/*---------------------- End of createPerceptron  ---------------------------*/
