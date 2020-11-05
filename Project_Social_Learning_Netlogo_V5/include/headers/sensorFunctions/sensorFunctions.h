/*-----------------------------------------------------------------------------
 *                      	SENSOR FUNCTIONS
 *
 * Author:      Daniel Romero Mujalli
 * Written:     28/12/2012
 * Last update: 14/ 2/2017
 *
 * Summary:      Here are declared some functinos used for the class Sensor
 *               as for example the initializtion function of each agent
 *               sensors (refreshSensors())   
 *               For definitions, see sensorFunctions.cpp               
 *               
 *---------------------------------------------------------------------------*/
 #ifndef SENSORFUNCTIONS_H
 #define SENSORFUNCTIONS_H
/*----------------------------------------------------------------------------- 
 * Function name:        refreshSensors
 *		Refresh sensors short and long Sights orientation
 *---------------------------------------------------------------------------*/
 void refreshSensors(Sensor myArray[][SENSOR_NUMBER], /* array of sensors	 */
 					 int agent_i);					  /* agent owner of array*/
 					 
/*----------------------------------------------------------------------------- 
 * Function name:        testQuadrant
 *		show the quadrant where a given angle is located. It returns in which
 *	of the four (4) quadrants is the given angle, and mofify the angle for
 *	calculating X, Y components of sensor sights
 *---------------------------------------------------------------------------*/
 float testQuadrant(float &angle); /* the angle								 */
 
/*----------------------------------------------------------------------------- 
 * Function name:        getDistance
 *		calculates euclidian distance between two points in 2D space
 *---------------------------------------------------------------------------*/
 float getDistance(float x0,	/* X coordinate of point 0					 */ 
 				   float y0, 	/* Y coordinate of point 0					 */
				   float x1, 	/* X coordinate of point 1					 */
				   float y1);	/* Y coordinate of point 1					 */
				   
/*----------------------------------------------------------------------------- 
 * Function name:        toAngle
 *		Converts from randians to angle. Receive input radian, return angle
 *---------------------------------------------------------------------------*/
 float toAngle(float angle);
 
/*----------------------------------------------------------------------------- 
 * Function name:        toRadian
 *		converts from angle to radians. Receive input angle, returm radian
 *---------------------------------------------------------------------------*/
 float toRadian(float angle);
 
/*----------------------------------------------------------------------------- 
 * Function name:        getTriangleXY
 *		return x and y according to angle and hypotenuse. check quadrant first 
 *	to set properly sin or cos functions
 *---------------------------------------------------------------------------*/
 void getTriangleXY(int quadrant,	/* in which quadrant is the angle  		 */ 
 					float angle, 	/* the angle							 */
					float &x, 		/* X coordinate as ref to be modified 
									   inside the function					 */
					float &y, 		/* Y coordinate as ref to be modified
									   inside the function (sin(angle))		 */
					float h);		/* hypotenuse (Example: radius or reach	 */
					
/*----------------------------------------------------------------------------- 
 * Function name:        getYIntercept
 *		returns b from y = mx + b
 *---------------------------------------------------------------------------*/
 float getYIntercept(float y,	/* Y coordinate of the line					 */ 
 					 float x, 	/* X coordinate of line						 */
				     float m);	/* slope of the line						 */
 
/*----------------------------------------------------------------------------- 
 * Function name:        interceptLineCircle
 *		indicates through pointers the intercept of a line with a circle.
 *	This is used for sensor activation (i.e. set detection)
 *---------------------------------------------------------------------------*/
 bool interceptLineCircle (float m, 		 /* line slope					 */
 						   float b, 		 /* y intercept of a line		 */	
						   float h, 		 /* X coordinate of circle		 */
						   float k, 		 /* Y coordinate of circle		 */
						   float r,			 /* radius						 */
  	                       float point1[2],  /* for storing first point of 
							 					intercept		      		 */
						   float point2[2]); /* for storing second point of
						   						intercept					 */
						   						
/*----------------------------------------------------------------------------- 
 * Function name:        interceptCircleSpecialCase
 *		uses only in cases where the object is located 90 or 270 degrees from
 *	target, so to avoid dividing to zero in interceptLineCircle function
 *---------------------------------------------------------------------------*/
 bool interceptCircleSpecialCase(float xSight, /* the point to check for
 												  interception has this same
												  value for X coordinate	 */
  								 float h, 	   /* X coordinate of circle	 */
								 float k, 	   /* Y coordinate of circle	 */
								 float r,	   /* radius					 */
 	                             float point1[2], /* for storing firt point of
								  					 intercept				 */
								 float point2[2]);/* for storing second point
								 					 of intercept			 */
								 					 
/*----------------------------------------------------------------------------- 
 * Function name:        relativeAngle
 *		returns the angle of the interception points according to agent sight.
 *	This angle is compared to the AGENT_SIGHT in order to know whether the
 *  object is inside the vision range or not
 *---------------------------------------------------------------------------*/
 float relativeAngle(float x0, 			/* X coordinate of sensor center	 */
 					 float y0, 			/* Y coordinate of sensor center	 */ 
					 float xObject, 	/* X coordinate of intercept		 */
					 float yObject,		/* Y coordinate of intercept		 */
 					 float xSight, 		/* x component of sensor sight		 */
					 float ySight);		/* y component of sensor sight		 */
					 
/*----------------------------------------------------------------------------- 
 * Function name:        refreshDetection
 *		set detection of agent sensors: 1 detection, 0 no detection
 *	Check if there are agents on sight
 *---------------------------------------------------------------------------*/
 void refreshDetection(Sensor myArray[][SENSOR_NUMBER], /* array of sensors	 */ 
 					   Agent myAgents[], 				/* array of agents	 */
 					  int agentsNumber);				/* number of agents	in
					   									   array			 */
					   									   
/*----------------------------------------------------------------------------- 
 * Function name:        refreshObjectDetection
 *		checks if there are objects on sight
 *---------------------------------------------------------------------------*/
 void refreshObjectDetection(Sensor mySensor[][SENSOR_NUMBER], /* array of
 																  sensors	 */ 
 							 int agent_i,					   /* agent ID	 */
 							 Agent myObject[], 				   /* array of
							  									  objects	 */
							 int objNumber);				   /* number of 
							 									  objects  	 */
							 									  
/*----------------------------------------------------------------------------- 
 * Function name:        borderDetection
 *		checks for walls
 *---------------------------------------------------------------------------*/
 void borderDetection(Sensor mySensor[][SENSOR_NUMBER],	/* array of sensors  */
 				      int agent_i);						/* agent ID			 */
 				      
/*----------------------------------------------------------------------------- 
 * Function name:        signalTranslation
 *		convert to decimal values the detection vector (myArray) of length
 *		number of sensors. Sensors have value of 1 when detecting objects. NULL
 *		otherwise
 *---------------------------------------------------------------------------*/
int signalTranslation(float myArray[],  /* detection vector					 */ 
					  int lenght);
 				      
 #endif
