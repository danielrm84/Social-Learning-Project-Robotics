/*-----------------------------------------------------------------------------
 *                      	CLASS AGENT
 *
 * Author:      Daniel Romero Mujalli
 * Written:     26/11/2012
 * Last update: 24/10/2019
 *
 * Summary:      This file contains the declaration of the class "Agent", its
 *               members, methods and variables.
 *   
 *               For the definition of its members see /sources/Agent.cpp
 *				 This class uses functions contained in 'agentFunctions.h'
 *				 which is required as a header called from the main routine
 *				 in order to work. An alternative is to include 
 *				 miscellaneous.h which includes all the headers used in this
 * 				 work Romero-Mujalli et al.
 *---------------------------------------------------------------------------*/
 #ifndef AGENT_H 	// To avoid the compiler from dropping an error because
 #define AGENT_H	// getting multiple times into the same library

class Agent {

private:
	float xPos, yPos, leftVel, rightVel, theta, linearVel, angularVel;
	float deltat, radius, xOld, yOld;
	float energy, maxEnergy;
	int age;

public:
	/*-------------------------------------------------------------------------
     *                  CONSTRUCTORS:
     *-----------------------------------------------------------------------*/
    /* Defalut: 															 */ 
	Agent();
	
	/* Create an Agent with random position (x,y), random velocity, fixed radius
	and energy																 */
	Agent(float maxxPos,		// Maximum X dimension of space 
		  float maxyPos, 	    // Maximum Y dimension of space
		  float maxVel, 		// Maximum Velocity of the agent
		  float r, 				// Agent's radius
		  float maxE); 			// Energy of the agent
	
/*-----------------------------------------------------------------------------
 *                  OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------- 
 * Function name:       computeLinearVel
 *
 *		   compute the LinearVelocity using the velocity of both wheels: 
 *		   left and right velocities.
 *---------------------------------------------------------------------------*/	
     void computeLinearVel();
/*----------------------------------------------------------------------------- 
 * Function name:        nextMove
 *
 *		   Stores the current (x,y) position which is used to check overlap
 *		   with other obstacles including other agents.
 *		   Then, refresh the values for the center (x,y), orientation theta, and
 *		   angular velocity.
 *---------------------------------------------------------------------------*/
	void  nextMove();    		
/*----------------------------------------------------------------------------- 
 * Function name:        refreshEnergy
 *
 *		   refresh agent energy E = E - e;
 *		   Important! if agent energy is to be increased, the input to the 
 *		   function should be -e (negative value!)
 *---------------------------------------------------------------------------*/
	void refreshEnergy(float e); // reduce energy in e units
	void addUpEnergy(float e); // increase energy in e units
/*----------------------------------------------------------------------------- 
 * Function name:        age functions
 *---------------------------------------------------------------------------*/
	int getAge();				//   returns the age of the agent
	void refreshAge(); 		    //   increase the age of the agent in one unit
	void resetAge();			//   reset the age to 0 
/*----------------------------------------------------------------------------- 
 * Function name:        set and get functions
 *---------------------------------------------------------------------------*/
	void setxPosition(float x);   // set the given x coordinate to the agent 
	void setyPosition(float y);   // set the given y coordinate to the agent
	void setLeftVel(float left);  // set given velocity to the agent left wheel
	void setRightVel(float right);// set given velocity to agent right wheel
	void setEnergy(float e);	  // set the agent energy to a given value
	void setLinearVel(float lv);  // set agent linearVelocity to given value
	
	float getxPosition();			//   get the actual x position of the agent
	float getyPosition();			//   get the actual y position of the agent
	float getRadius();				// return the radius of the agent 
	float getTheta();				// return agent orientation angle theta
	float getEnergy();				// return the energy of the agent
	float getxOld();				// return the previous x coordinate
	float getyOld();				// return the previous y
	float getAgentLinearVel();		// return the linear Velocity of the agent
/*-----------------------------------------------------------------------------
 *                  PUBLIC VARIABLES:
 *---------------------------------------------------------------------------*/
     bool white, black;		/* used according to Acerbi et al. 2007, to check
	 						   whether a given agent is in the white or black
							   patch									 	 */
	 bool selected;	        /* true if selected, e.g., for reproduction      */
};
#endif
