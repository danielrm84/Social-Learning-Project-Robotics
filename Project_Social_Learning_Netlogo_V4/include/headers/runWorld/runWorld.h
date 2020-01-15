/*-----------------------------------------------------------------------------
 *                      		RUN_WORLD
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  14/ 2/2017
 *
 * Summary:      This file contains the declaration of all functions used
 *				 during the run World phase of the main program. This
 *				 phase consists of moving the agents, tracking their position,
 *				 perceiving neighbors, running the perceptron, updating their 
 *				 energy, cheking for mortality, creating newborn agents, and 
 *				 applying inheritance depending on the scenario of behavior. 
 *
 *               The definition of these functions are in the file:
 *				 /sources/runWorld.cpp
 *
 *---------------------------------------------------------------------------*/

#ifndef RUN_WORLD_H
#define RUN_WORLD_H

/* checkWhereIsTheAgent
   This function checks if the agent is located in or outside patches and
   updates the input to the perceptron affecting perception of ground color	 */
void checkWhereIsTheAgent(Agent myAgent[],     /* Array of agents			 */
						  int i, 			   /* the ith agent				 */
						  Agent myPatches[],   /* array of patches			 */ 
						  int n_patches,	   /* number of patches			 */
					  	  float inX[]);		   /* array of inputs to percept */

/* updateAgentEnergy
   This function updates agent energy according to its location (whether white,
   black or grey patch) and to othe scenario of environment.				 */
void updateAgentEnergy (Agent myAgent[], 	/* array of agents				 */
						int i, 				/* the ith agent				 */
						int z, 				/* the zth iteration			 */
						int max_iterations, /* maximum number of iterations  */
						float black_effect, /* black patch effect on energy  */
						float white_effect, /* white patch effect on energy  */
						float grey_effect); /* grey zone effect on energy    */

/* checkNeighbors
   This function tells to agents perceptron the number of neighbors
   located in the same patch.
   This function only works for Mixed and SL								 */
void checkNeighbors(Agent myAgent[], 		   /* array of agents			 */
					int n, 					   /* number of agents in array  */
					Perceptron myPerceptron[], /* array of perceptrons		 */
					int agents_inWhite, 	   /* nr of agents in white patch*/
					int agents_inBlack);	   /* nr of agents in black patch*/
					
/* runPerceptron
   feedforward, and modify perceptron weights through learning when apply	 */
void runPerceptron(Perceptron myPerceptron[], /* array of perceptrons		 */
				   int agent_i, 			  /* the ith agent				 */
				   float groundTarget);		  /* backpro learning target     */
				   
/* replaceTheAgent: 
   replace the dead agent with a newborn in a random positon, with full 
   energy, random orientation and, located outside the patches      		 */
void replaceTheAgent(Agent myAgent[], 		/* array of agents				 */
					 int i, 				/* ith agent					 */
					 Agent patches[],  	    /* array of patches				 */
					 float max_x, 			/* max X space dimension		 */
					 float max_y,			/* max Y space dimension		 */
					 float max_vel, 		/* maximum velocity allowed		 */
					 float radius, 			/* agent radius (body)			 */
					 float max_e);			/* maximum agent initial energy	 */

/* runInheritance: 
   the newborn inherits traits from alive agents. Weight values are reset to 
   default 																	 */
void runInheritance(Agent myAgent[], 		   /* array of agents			 */
					int i, 					   /* ith agent					 */
					int n, 					   /* number of agents in array	 */
					Perceptron myPerceptron[], /* array of perceptrons		 */
     				NeuralNetwork myNetwork[], /* array of neural networks   */
					float lrate, 			   /* learning rate of perceptron*/
					float rnd_w);			   /* range value for weights of
											   the random behavior scenario  */
#endif /* RUN_WORLD_H */
