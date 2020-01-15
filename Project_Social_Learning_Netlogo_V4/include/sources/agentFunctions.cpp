/*-----------------------------------------------------------------------------
 *                      AGENT MOVEMENT ECUATIONS:
 *
 * Author:      Daniel Romero Mujalli
 * Written:     26/11/2012
 * Last update: 19/ 2/2013
 *
 * Summary:      In this file are defined all the functions
 *              declared in the header file "agentFunction.h"
 *              which rule agent movement. 
 *
 *---------------------------------------------------------------------------*/
/* LIBRARIES                                                                 */
#include "../miscellaneous/miscellaneous.h"
using namespace std;

/* Returns linear velocity of agent i										 */
float getLinearVelocity (float leftVel, float rightVel)
{    
    float linearVel;
    linearVel = (rightVel + leftVel)/2;

    return linearVel;
}

/* Returns next X position of agent i										 */
float getNextxPosition (float xPos, float linearVel, float deltat, float theta)
{
    float nextxPos;

    nextxPos = xPos + (deltat*linearVel*(cos(theta)));

    return nextxPos;
}

/* Returns next Y position of agent i										 */
float getNextyPosition (float yPos, float linearVel, float deltat, float theta)
{
    float nextyPos;

    nextyPos = yPos + (deltat*linearVel*(sin(theta)));

    return nextyPos;
} 

/* Returns angular velocity of agent i										 */
float getAngularVelocity (float rightVel, float leftVel, float radius)
{
    float angularVel;

    angularVel = (rightVel - leftVel)/(2*radius);

    return angularVel;
}

/* Return the next angle of vision (theta) of agent i						 */
float getNextTheta (float theta, float angularVel, float deltat)
{
    float nextTheta;

    nextTheta = theta + (angularVel*deltat);
    nextTheta = toAngle(nextTheta);
    if(nextTheta > 360) {nextTheta = nextTheta - 360;}
    if(nextTheta <   0) {nextTheta = 360 + nextTheta;}
    nextTheta = toRadian(nextTheta);

    return nextTheta;
}
/* Checks overlap. If overlap == true, roll back to old agent position	     */ 
bool checkOverlap(Agent myArray[], int i, int j, float maxX, float maxY,
                  float maxVel, bool beginning, bool collisions_affect_energy)
{
    bool overlap = false;
    
    float d, xi, yi, xj, yj, oldxi, oldyi, oldxj, oldyj, ri, rj;
    float e = 0;
    int loopcontrol = 0;
    
    if(i != j)
    {
	
            xi    = myArray[i].getxPosition();
            yi    = myArray[i].getyPosition();
            oldxi = myArray[i].getxOld();
            oldyi = myArray[i].getyOld();
            ri    = myArray[i].getRadius();

            xj    = myArray[j].getxPosition();
            yj    = myArray[j].getyPosition();
            oldxj = myArray[j].getxOld();
            oldyj = myArray[j].getyOld();
            rj    = myArray[j].getRadius();

            d = getDistance(xi, yi, xj, yj);
            if(d <= (ri + rj))
            {
                        if(beginning)
                        {
                            myArray[i] = Agent(maxX, maxY, maxVel, 
                                               myArray[i].getRadius(), 
                                               myArray[i].getEnergy());   
                        }
                        if(!beginning && collisions_affect_energy)
                        {
                            e++;
                            myArray[i].refreshEnergy(e); 
                            myArray[j].refreshEnergy(e);
                            e = 0;
                        }
                        
						xi = oldxi;
                        yi = oldyi;
                        myArray[i].setxPosition(xi);
                        myArray[i].setyPosition(yi);
                        overlap = true;
            }
                         
    }
    
    return overlap;
                
}
/* Checks borders. For movement: 1st check border, then overlap				 */ 
bool checkBorder(Agent myArray[], int id, float maxX, float maxY)
{
    bool overlap;
    
    float xi, yi, oldxi, oldyi, ri;
    
    xi    = myArray[id].getxPosition();
    yi    = myArray[id].getyPosition();
    oldxi = myArray[id].getxOld();
    oldyi = myArray[id].getyOld();
    ri    = myArray[id].getRadius();

    if((xi + ri) > maxX || (xi - ri) < 0){xi = oldxi; overlap = true;}
    if((yi + ri) > maxY || (yi - ri) < 0){yi = oldyi; overlap = true;}
    
    myArray[id].setxPosition(xi);
    myArray[id].setyPosition(yi); 
    
    return overlap;
}
/* Cheks for objects around and collisions									 */ 
void checkForObjects(Agent myArray[], int agent_i, Agent myObject[],
                    int nObjects)
{
    bool overlap;
    int loopcontrol = 0;
    float d, xi, yi, xj, yj, oldxi, oldyi, oldxj, oldyj, ri, rj;
    float e = 0;
    do
    {
        overlap = false;
        xi    = myArray[agent_i].getxPosition();
        yi    = myArray[agent_i].getyPosition();
        oldxi = myArray[agent_i].getxOld();
        oldyi = myArray[agent_i].getyOld();
        ri    = myArray[agent_i].getRadius();

        for(int j = 0; j < nObjects; j++)
        {
            xj    = myObject[j].getxPosition();
            yj    = myObject[j].getyPosition();
            rj    = myObject[j].getRadius();

            
            d = getDistance(xi, yi, xj, yj);
            if(d <= (ri + rj) && loopcontrol < 1)
            {
                e++;
                if(oldxi > 0 && oldyi > 0) //new for testing infinite loop
                {
                   xi = oldxi;
                   yi = oldyi; 
                }
                //cout << "collision agent-agent:" << endl; 
				//cout << "E before = " << myArray[agent_i].getEnergy() << endl;
                myArray[agent_i].setxPosition(xi);
                myArray[agent_i].setyPosition(yi);
                myArray[agent_i].refreshEnergy(e);
                
                //cout << "E after = " << myArray[agent_i].getEnergy() << endl;
                e = 0;
                overlap = true;
            } 
        }   
       loopcontrol++;
    }while(overlap == true && loopcontrol < 3);
}
/* Checks borders. For movement: 1st check border, then overlap				 */ 
bool checkBorderCollision(Agent myArray[], int id, float maxX, float maxY)
{
    bool overlap;
    float xi, yi, oldxi, oldyi, ri;
    float e = 0;
    
        xi    = myArray[id].getxPosition();
        yi    = myArray[id].getyPosition();
        oldxi = myArray[id].getxOld();
        oldyi = myArray[id].getyOld();
        ri    = myArray[id].getRadius();

        if((xi + ri) >= maxX || (xi - ri) <= 0){e++; xi = oldxi; overlap = true;}
        if((yi + ri) >= maxY || (yi - ri) <= 0){e++; yi = oldyi; overlap = true;}
        
        /*if (e > 0) 
		{ 
			cout << "collision agent-border:" << endl;
			cout << "e before: " << myArray[i].getEnergy() << endl;
		}*/
		
        myArray[id].refreshEnergy(e);
        myArray[id].setxPosition(xi);
        myArray[id].setyPosition(yi);
        
        /*if (e > 0) 
		{ 
			cout << "e after: " << myArray[i].getEnergy() << endl;
		}*/
		
		return overlap;
         
}
