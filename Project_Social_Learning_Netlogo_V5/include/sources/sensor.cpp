/*-----------------------------------------------------------------------------
 *                      	CLASS SENSOR: Member and methods
 *
 * Author:      Daniel Romero Mujalli
 * Written:     23/12/2012
 * Last update:  5/11/2013
 *
 * Summary:      In this file are defined the member functions and methods
 *               of class Sensor declared in sensor.h 
 *               This class implements agent sensors used in navigation
 *               
 *---------------------------------------------------------------------------*/
/*		Libraries: 															 */
#include "../miscellaneous/miscellaneous.h"
using namespace std;
/*-----------------------------------------------------------------------------
 *					Member and methods definition
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *                  CONSTRUCTORS:
 *---------------------------------------------------------------------------*/
 /* default																	 */
 Sensor::Sensor(){}
 
 /* build a sensor object with specific reach (length), radius (agent body,
 	note they are circular), position in space (of agent) and orientation angle
	theta																	 */
 Sensor::Sensor(float length, float r, float agentx, float agenty, float angle)
 {
 	scope   = toRadian(AGENT_SIGHT/SENSOR_NUMBER);
 	reach   = length; 
 	radius  = r;
 	xOrigin = agentx;
 	yOrigin = agenty;
    theta    = angle;
 	
 }
 
/*-----------------------------------------------------------------------------
 *                  OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------- 
 * Function name:           setAngles; getAngles; getScope
 *  
 *   allow to set and get the location angle and scope of sensor i
 *      
 *---------------------------------------------------------------------------*/
 void Sensor::setAlfa(float angle){ alfa = angle; }
 float Sensor::getAlfa(){ return alfa; }
 
 void Sensor::setAlfaX(float angle){ alfaX = angle; }
 float Sensor::getAlfaX(){ return alfaX; }
 
 float Sensor::getTheta(){ return theta; }
 void Sensor::setTheta(float angle){theta = angle;}
 
 float Sensor::getScope(){ return scope; }
 
 void Sensor::setDetection(int value){detection = value;}
 int Sensor::getDetection(){return detection;}
 
 void Sensor::setCenter(float x, float y){xOrigin = x; yOrigin = y;}
 
 void Sensor::setMaxDim(float x, float y){maxX = x; maxY = y;}
 
/*---------------------------------------------------------------------------- 
 * Function name:           setSights
 *  
 *   Sets sensor sights according to quadrant location of sensors
 *      
 *---------------------------------------------------------------------------*/
 void Sensor::setSights()
 {
 	float x, y, xshort, yshort, angle;
 	
	angle = toAngle(alfaX);
	
	/* check quadrant to calculate X and Y components of sights				 */
 	int quadrant = testQuadrant(angle);
 	
 	/* put angle to radians in order to use the angle in next function		 */
 	angle = toRadian(angle);
  	
  	/* get X and Y components of sensor reach. Sensor reach start at center
	   of the agent body													 */
  	getTriangleXY(quadrant, angle, x, y, reach);
  	
  	/* xshort and yshort are the components from the center of the agent to the
	  border of the body													 */
  	getTriangleXY(quadrant, angle, xshort, yshort, radius);
  	
  	/* Set sensor Sights. This is adding the calculated modules to agent center
	  																		 */
  	xSight = xOrigin + x;
  	ySight = yOrigin + y;
  	xShortSight = xOrigin + xshort;
  	yShortSight = yOrigin + yshort;
 }
 
/*---------------------------------------------------------------------------- 
 * Function name:           checkSights
 *  
 *   It checks detection, and then stores sensors view in a pointer
 *
 *   Since tan(90) and tan(270) are undefine, another method inside this
 *	 function was implemented to cover this special case
 *
 *		I NEED TO REWRITE THIS FUNCTION!!
 *   
 *---------------------------------------------------------------------------*/
 bool Sensor::checkSight(float xObject, float yObject)
 {
	float b, angle, d, min;
  	float point1[2], point2[2];
  	bool onSight = false;
	
	/* special case:														 */
  	if(toAngle(alfaX) == 90 || toAngle(alfaX) == 270)
  	{
    	onSight = interceptCircleSpecialCase(xSight, xObject, yObject, radius, 
                                         	 point1, point2);
        //cout << "special case, onsight = " << onSight << endl;
  	}
  	else /* common cases													 */
  	{
    	slope = tan(alfaX);
    	b = getYIntercept (ySight, xSight, slope);
    	
    	onSight = interceptLineCircle(slope, b, xObject, yObject, radius, 
									  point1, point2);
		//cout << "normal case, onsight = " << onSight << endl;
  	}
 	
	/* if interception														 */ 
  	if(onSight == true)
    {
      	angle = relativeAngle(xOrigin, yOrigin, xObject, yObject, xSight, 
    	                      ySight);
      	angle = toAngle(angle);
      	
		/* If intercept and angle within sensor scope,         				 */
      	//if(angle <= (AGENT_SIGHT/2)) 
      	//{
        	min = getDistance(xOrigin, yOrigin, point1[0], point1[1]);
        	d   = getDistance(xOrigin, yOrigin, point2[0], point2[1]);
        	
        	//cout << "distance d = " << d << endl;
        	
        	/* take the minimum distance to interception					 */
        	if(min < d ){ d = min;} 
        	/* if the distance of the closer interception point - radius is
			   <= to the sensor reach - radius, then detection == true		 */
        	if((d - radius)<= (reach - radius))
        	{
          		return true;
        	}
      	//}
      	else{ onSight = false;}
    }
  	if(onSight == false)
  	{
	  /* No detection*/
    	return false;	
  	} 	
 }

/*----------------------------------------------------------------------------- 
 * Function name:         getxCor
 *  
 * get the center / origin x coordinate of the sensor
 *---------------------------------------------------------------------------*/   				 
  float Sensor::getxCor(){ return xOrigin; }
  
/*----------------------------------------------------------------------------- 
 * Function name:         getyCor
 *  
 * get the center / origin y coordinate of the sensor
 *---------------------------------------------------------------------------*/   				 
  float Sensor::getyCor(){ return yOrigin; }

/*----------------------------------------------------------------------------- 
 * Function name:         getSights
 *  
 * give the value of all sensor sights to reference variables (pointers of &)
 *---------------------------------------------------------------------------*/ 
 void Sensor::getSight(float &xsight, float &ysight, float &xshort, 
					  float &yshort)
 {
	xsight = xSight;
	ysight = ySight;
  	xshort = xShortSight;
  	yshort = yShortSight;
 }

/*----------------------------------------------------------------------------- 
 * Function name:         checkSighttoBorder
 *  
 * return true if a sensor sight intercept with arena border
 *---------------------------------------------------------------------------*/
 bool Sensor::checkSighttoBorder()
 {
	if(xSight > maxX || xSight < 0 || ySight > maxY || ySight < 0)
  	{
  	
    	return true;
  	}
  	else { return false; }
 }
   
