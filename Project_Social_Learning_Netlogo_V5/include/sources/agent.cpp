/*-----------------------------------------------------------------------------
 *                      CLASS AGENT: Member and methods
 *
 * Author:      Daniel Romero Mujalli
 * Written:     26/11/2012
 * Last update: 12/ 3/2013
 *
 * Summary:      In this file are defined the member functions and methods of 
 *				 class agent.
 *               
 *               See class agent in agent.h.
 *				 It is also important to include 'agentFunctions.h' 
 *				 
 *				 IMPORTANT!
 * 				 If abs(MaxVel) != abs(MinVel) { modify random number 
 *															   generators! }
 *---------------------------------------------------------------------------*/
/*		Libraries:                                                           */
#include "../miscellaneous/miscellaneous.h"
 using namespace std;
/*-----------------------------------------------------------------------------
 *                  CONSTRUCTORS:
 *---------------------------------------------------------------------------*/		
Agent::Agent (){}											// default

Agent::Agent (float maxxPos, float maxyPos, float maxVel, float r, float maxE)
{
	
/*	To obtain random decimal values, it is necessary to put the following
	formula: smallest_value (float) + 
	(greatest or range(float)*rand()/(RAND_MAX + 1.0)						
	Careful with radius + (maxxPos - 2*radius)*rand()... 					 */

	theta    =   7.0*rand()/(RAND_MAX + 1.0);
	if(toAngle(theta) > 360) {theta = theta - 360;}
    if(toAngle(theta) <   0) {theta = 360 + theta;}	
	radius   =   r;
	deltat   =   0.1;
	xPos     =   radius + (maxxPos - (2*radius))*rand()/(RAND_MAX + 1.0);
	yPos     =   radius + (maxyPos - (2*radius))*rand()/(RAND_MAX + 1.0);
	leftVel  =   -maxVel + (2.0*maxVel*rand()/(RAND_MAX + 1.0));
	rightVel =   -maxVel + (2.0*maxVel*rand ()/(RAND_MAX + 1.0));
	energy   =   maxE;
	age   = 0;
	white = false;
	black = false;
}
/*-----------------------------------------------------------------------------
 *                  FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/
/* 		set agent Linear Velocity 											 */

void Agent::computeLinearVel()
{
	linearVel = getLinearVelocity(leftVel, rightVel);
}
 	
/*		Refresh all agent values: 											 */

void Agent::nextMove()
{
	angularVel = getAngularVelocity(rightVel, leftVel, radius);
	xOld = xPos;
	yOld = yPos;
	xPos = getNextxPosition(xPos, linearVel, deltat, theta);
	yPos = getNextyPosition(yPos, linearVel, deltat, theta);
	theta = getNextTheta(theta, angularVel, deltat);
/*-----------------------------------------------------------------------------
 *   IMPORTANT!
 *	 Do not confuse getxPosition() and getyPosition() functions from
 *   the Agent class (agent.h) with those from agentFunctions file             
 *---------------------------------------------------------------------------*/
}

/*----------------------------------------------------------------------------- 
 * Function name:        refreshEnergy
 *---------------------------------------------------------------------------*/
void Agent::refreshEnergy(float e){energy -= e; if(energy < 0){energy = 0;}}

void Agent::addUpEnergy(float e){ energy += e; }
/*----------------------------------------------------------------------------- 
 * Function name:        age functions
 *---------------------------------------------------------------------------*/
 int Agent::getAge(){return age;}		  // 	 returns agent age
 void Agent::refreshAge(){age++;} 		  //     age++
 void Agent::resetAge(){age = 0;}	 	  //     reset to 0 
/*----------------------------------------------------------------------------- 
 * Function name:        set and get functions
 *---------------------------------------------------------------------------*/
float Agent::getxPosition(){return xPos;} //	 returns position x
float Agent::getyPosition(){return yPos;} //	 returns position y
float Agent::getRadius(){return radius;}  //	 returns agent radius 
float Agent::getTheta(){return theta;}	  // 	 returns agent orientation theta
float Agent::getEnergy(){return energy;}  //  	 returns agent energy
float Agent::getxOld(){return xOld;}	  // 	 returns x before nextMove()
float Agent::getyOld(){return yOld;}	  // 	 returns y before nextMove()

float Agent::getAgentLinearVel(){return linearVel;} // returns linear Velocity
void Agent::setLinearVel(float lv){linearVel = lv;} // set linearVel
void Agent::setxPosition(float x){xPos = x;} 	    //  set new x on agent i 
void Agent::setyPosition(float y){yPos = y;} 		//  set new y on agent i
void Agent::setLeftVel(float left){leftVel = left;} // set leftVel on agent i

void Agent::setRightVel(float right){rightVel = right;} // set rightVel
void Agent::setEnergy(float e){energy = e;}			    // set energy on agenti
