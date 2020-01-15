/*-----------------------------------------------------------------------------
 *                      AGENT MOVEMENT ECUATIONS:
 *
 * Author:      Daniel Romero Mujalli
 * Written:     26/11/2012
 * Last update:  8/ 7/2016
 *
 * Summary:      This file contains the declaration of all the functions
 *               related to the movement of the agent.
 *               The definition of these functions are in the file:
 *				 /sources/agentFunctions.cpp
 *
 *---------------------------------------------------------------------------*/
 #ifndef AGENTFUNCTIONS_H
 #define AGENTFUNCTIONS_H

/* Returns linear velocity of agent i as an average of left and right 
   velocities																 */
float getLinearVelocity (float leftVel, 	/* velocity of left wheel		 */
                         float rightVel);   /* velocity of right wheel       */

/* Returns next X position of agent i as a function of linear velocity and its
   orientation angle theta													 */
float getNextxPosition (float xPos, 		/* actual X						 */
                        float linearVel, 	/* linear velocity				 */
                        float deltat, 		/* time interval				 */
                        float theta); 		/* angle (orientation)			 */

/* Returns next Y position of agent i as a function of its linear velocity and
   its ortientation angle theta												 */
float getNextyPosition (float yPos, 		/* actual Y						 */
                        float linearVel, 	/* Linear velocity				 */
                        float deltat, 		/* time interval				 */
                        float theta);		/* angle of ortientation		 */

/* Returns angular velocity of agent i										 */
float getAngularVelocity (float rightVel, 	/* right velocity				 */
                          float leftVel, 	/* left velocity				 */
                          float radius); 	/* agent radius					 */

/* Return the next angle of vision or orientation (i. e. next theta)		 */
float getNextTheta (float theta, 			/* actual theta				 	 */
                    float angularVel, 		/* angular velocity			 	 */
                    float deltat);			/* time interval				 */
                    
/* Checks overlap. If overlap == true, roll back to old agent position		 */ 
bool checkOverlap(Agent myArray[], 			/* array of agents				 */
                  int i,					/* ith agent	 				 */
                  int j,					/* jth agent					 */
                  float maxX, 				/* maximum space X value		 */
                  float maxY,				/* maximum space Y value		 */
                  float maxVel,				/* maximum velocity allowed		 */
                  bool beginning,			/* is the first time setting 
				  							   agent position?				 */
                  bool collisions_affect_energy); /* Does collition affect 
				  								  energy? 					 */
                  
/* Cheks collition of agent i with objects. Objects and agents are from the
   same class (as Agent)													 */ 
void checkForObjects(Agent myArray[],		/* array of agents				 */
                     int agent_i,			/* agent ID						 */
                     Agent myObject[],		/* array of objects				 */
                     int nObjects);			/* length of array of objects 	 */
                     
/* Checks borders. For movement inside main Function: 
								1st check border, then overlap				 */ 
bool checkBorder(Agent myArray[], 			/* array of agents				 */
                 int id, 					/* agent id	 					 */
                 float maxX, 				/* Maximum space X value		 */
                 float maxY);				/* Maximum space Y value		 */
                 
/* Checks collision to borders. Collisions affect energy		  			 */ 
bool checkBorderCollision(Agent myArray[], 	/* array of agents				 */
                         int id, 		    /* agent id						 */
                         float maxX, 		/* Maximum space X value		 */
                         float maxY);		/* Maximum space Y value		 */
#endif
