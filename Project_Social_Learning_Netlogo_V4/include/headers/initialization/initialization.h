/*-----------------------------------------------------------------------------
 *                      		INITIALIZATION
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  18/ 1/2017
 *
 * Summary:      This file contains the declaration of all functions used
 *				 during the initialization phase of the main program. This
 *				 phase consists on creating the world, patches, agents, their
 *				 neural networks, perceptron and sensors (WORLD SET UP).
 *
 *               The definition of these functions are in the file:
 *				 /sources/initialization.cpp
 *
 *---------------------------------------------------------------------------*/

#ifndef INITIALIZATION_H
#define INITIALIZATION_H

/* Create Patches
   This function create circular patches in the environment. At current stage,
   it is limited to maximum two patches 									 */
void createPatches(Agent patch[],  /* The array of patches of type Agent 	 */
					 int n, 	   /* the number of patches (maximum 2) 	 */
					 int max_x,    /* maximum x dimension of the environment */
					 int max_y,    /* maximum y dimension of the environment */
					 float radius);/* the radius of the patches		 		 */
					 
/* Set the effect of patches on agent's energy
   Set the values for the white and black patches according to the scenario
   of environment.
   Currently, it is only implemented for the static, abrupt and no treatment
   scenarios																 */
void setEffectOfPatches(float &energy_w, /* variable to store the value for the
											white patch		   				 */
						float &energy_b);/* variable to store the value for the
											black patch						 */

/* Create Agents
   create n Agent objects 													 */
void createAgents(Agent myAgent[],   /* array of agents						 */
				 int n, 			 /* the number of agents to be created	 */
				 float energy,       /* initial energy of the agent			 */    
				 float max_vel, 	 /* maximum velocity the agent can reach */
				 float agent_radius, /* radius defining the agent body       */
				 int max_x, 		 /* maximum x dimension of environment   */
				 int max_y);		 /* maximum y dimension of environment   */

/* Create agents outside patches
   Create n_agents agents outside patches									 */
void createAgentsOutsidePatches(Agent myAgent[], /* array of agents			 */
							  int n_agents, 	 /* number of agents		 */
							  float energy, 	 /* energy of the agent	 	 */
                              float max_vel, 	 /* maximum velocity of agent*/
							  float agent_radius,/* body radius of agent	 */
							  int max_x, 		 /* maximum x dimension of the
							  						environment				 */
							  int max_y, 		 /* maximum y dimension of the
							  						environment				 */
							  Agent patch[], 	 /* array of patches		 */	
							  int n_patches);	 /* number of patches		 */


/* Sensor initialization
   create the sensors of the agent					   					 	 */
void createSensors(Agent myAgent[], 				/* array of agents  	 */
				   Sensor mySensor[][SENSOR_NUMBER],/* array of sensors		 */ 
				   int n, 							/* number of agents		 */
				   float reach, 			/* reach (distance) of the sensor*/
				   int max_x, 			/* maximum x dimension of environment*/
				   int max_y);			/* maximum y dimension of environment*/


/* 	Create neural networks (NN) 
	Create n NN with inputNN number of neurons in the input layer, hiddenNN
	neurons in the hidden layer, and outputNN neurons in the output layer. The
	values for these parameters are set in the file "classParameter.h".
	Romero-Mujalli et al. 2016 used values of (8, 10, 2).
	This function adds a bias to each layer, except for the output layer.
	Weight values of NN are read from files (inWeights_NN_100.xls and 
											  outWeghts_NN_100.xls)
	IMPORTANT: The files contain information for up to 100 individuals/agents*/

void createNeuralNetworks(NeuralNetwork myNetwork[],/* array of NN			 */ 
					  	  int n, 					/* number of NN			 */
					  	  int inputNN, 			    /*number of neurons in input
													  layer					 */
					  	  int hiddenNN, 			/*number of neurons in the
													  hidden layer			 */
					  	  int outputNN); 			/*number of neurons in the
													  output layer			 */

/* Create perceptron or ground controller
   Create the perceptron of the agent. Its function is to perceive ground color
   and affect the preference of the agent for a given patch			  		 */
void createPerceptron(Perceptron myPerceptron[],/* array of perceptrons of type
												   Perceptron				 */
				 int n_agents, 					/* number of agents			 */
				 float learning_rate, 			/* learning rate of learning
				 								   behavior					 */
				 float mut_rate,		/* mutation rate for the innate
				 						   behavior (also genetic evolution  */
				 float omega_mut_rate,  /* mutation rate of the parameter omega
				 						   which defines whether the agent
										   learns asocially or socially. Only
										   for mixed behavior Mx			 */
				 float phi_mut_rate, 	/* mutation rate of the parameter phi
				 						   affecting the learning rate of the
										   agent learning behaivor. Only for
										   mixed behavior Mx 				 */
				 float rnd_w);			/* value limiting the range of values
				 						   possible for setting random weights
										   in the random behavior (control)
										   weight = random-uniform (-rnd_w, 
										   rnd_w)	 						 */


#endif /* INITIALIZATION_H */
