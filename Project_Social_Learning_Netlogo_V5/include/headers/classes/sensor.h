/*-----------------------------------------------------------------------------
 *                      	CLASS SENSOR
 *
 * Author:      Daniel Romero Mujalli
 * Written:     23/12/2012
 * Last update:  5/11/2013
 *
 * Summary:      In this file is defined the class Sensor and also
 *               declared its members, methods and variables.   
 *               For definitions of its members see sensor.cpp
 *               This class implements agent sensors used in navigation
 *               
 *---------------------------------------------------------------------------*/
 #ifndef SENSOR_H
 #define SENSOR_H
/*-----------------------------------------------------------------------------
 *                        THE CLASS STARTS
 *---------------------------------------------------------------------------*/
 class Sensor 
{
 private:
  
	float scope, slope, reach;    	/* Scope: sensor range (angle)   
                                       Slope: from a line. Sensor reach      */
	float alfa, alfaX;            	/* Alfa: relative angle to theta (from agent 
                                       angular movement. It is set according to
									   scope and theta. Example suppose an
									   agent with scope o< , upper angle is
									   alfax, lower = alfa. Are use to set
									   sensor sights	                     */
	float theta;                    /* Agent orientation, from angular movement
																			 */
	float radius;                   /* Agent radius                          */
	float xSight, ySight;	        /* The farthest sensor sight             */
	float xShortSight, yShortSight; /* The shortest sensor sight = agent radius
																			 */
	float xOrigin, yOrigin;         /* Store agent position (x,y)            */
	int detection;                  /* stores detection value of sensor i    */
	float maxX, maxY;               /* Arena Max Dimension x,y               */
  
 public:
/*-----------------------------------------------------------------------------
 *                 		 CONSTRUCTORS:
 *---------------------------------------------------------------------------*/
 /* default																	 */
  Sensor();

 /* build a sensor object with specific reach (length), radius (agent body,
 	note they are circular), position in space (of agent) and orientation angle
	theta																	 */
  Sensor(float length, 		/* reach of the sensor							 */
  	     float r, 			/* agent radius									 */
		 float agentx, 		/* agent X position								 */
		 float agenty, 		/* agent Y position								 */
		 float angle);		/* angle theta of agent orientation				 */
  
/*-----------------------------------------------------------------------------
 *                  OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------- 
 * Function name:         setAlfa
 *  
 * set desired angle value to alfa (radians)     
 *---------------------------------------------------------------------------*/
  void setAlfa(float angle);

/*----------------------------------------------------------------------------- 
 * Function name:         getAlfa
 *  
 * get actual value of alfa (radians)     
 *---------------------------------------------------------------------------*/
 float getAlfa();
 
/*----------------------------------------------------------------------------- 
 * Function name:         setCenter
 *  
 * set center of sensor on actual agent position (agent center)     
 *---------------------------------------------------------------------------*/
  void setCenter(float x,	/* Agent center X coordinate					 */ 
  				 float y);	/* Agent center Y coordinate					 */
 
/*----------------------------------------------------------------------------- 
 * Function name:         setAlfaX
 *  
 * set desired value for alfax (in radians). Remember alfax is one of the two
 * angles within a scope    
 *---------------------------------------------------------------------------*/				  
  void setAlfaX(float angle);

/*----------------------------------------------------------------------------- 
 * Function name:         getAlfaX
 *  
 * return actual value of alfaX     
 *---------------------------------------------------------------------------*/  
  float getAlfaX();

/*----------------------------------------------------------------------------- 
 * Function name:         getxCor
 *  
 * get the center / origin x coordinate of the sensor
 *---------------------------------------------------------------------------*/   				 
  float getxCor();

/*----------------------------------------------------------------------------- 
 * Function name:         getyCor
 *  
 * get the center / origin y coordinate of the sensor
 *---------------------------------------------------------------------------*/   				 
  float getyCor();  

/*----------------------------------------------------------------------------- 
 * Function name:        setTheta
 *  
 * set theta (orientation angle of an agent)     
 *---------------------------------------------------------------------------*/
 void setTheta(float angle);

/*----------------------------------------------------------------------------- 
 * Function name:         getTheta
 *  
 * return theta (orientation of agent) startin angle of reference for sensors
 *---------------------------------------------------------------------------*/
  float getTheta();

/*----------------------------------------------------------------------------- 
 * Function name:         getScope
 *  
 * return sensor scope. Angle within alfa and alfaX
 *---------------------------------------------------------------------------*/  
  float getScope();

/*----------------------------------------------------------------------------- 
 * Function name:         setSights
 *  
 * Set X and Y components of short and long Sights
 *---------------------------------------------------------------------------*/
  void setSights();

/*----------------------------------------------------------------------------- 
 * Function name:         getSights
 *  
 * give the value of all sensor sights to reference variables (pointers of &)
 *---------------------------------------------------------------------------*/
  void getSight(float &xsight,	/* get X long Sight							 */
  				float &ysight,	/* get Y long Sight							 */ 
				float &xshort,	/* get X short Sight						 */ 
				float &yshort);	/* get Y short Sight						 */

/*----------------------------------------------------------------------------- 
 * Function name:         checkSight
 *  
 * return true if there is an interception of sensor sight with an object
 * (Not with the wall i. e. arena borders)
 *---------------------------------------------------------------------------*/  
  bool checkSight(float xObject,	/* object or agent x position			 */ 
  				  float yObject);	/* object or agentt y position			 */

/*----------------------------------------------------------------------------- 
 * Function name:         checkSighttoBorder
 *  
 * return true if a sensor sight intercept with arena border
 *---------------------------------------------------------------------------*/
  bool checkSighttoBorder();

/*----------------------------------------------------------------------------- 
 * Function name:         setDetection
 *  
 * set detection. Example: 1 --> detected ; 0 --> not detected
 *---------------------------------------------------------------------------*/
  void setDetection(int detection);
  
/*----------------------------------------------------------------------------- 
 * Function name:         getDetection
 *  
 * get detection state of sensor
 *---------------------------------------------------------------------------*/  
  int getDetection();

/*----------------------------------------------------------------------------- 
 * Function name:        setMaxDim
 *  
 * set limits of 2-D arena to the sensor object
 *---------------------------------------------------------------------------*/
  void setMaxDim(float x,	/* maximum X value of space						 */ 
  				 float y);	/* maximum Y value of space						 */
  
};
#endif
