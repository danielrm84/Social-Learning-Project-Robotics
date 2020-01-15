/*-----------------------------------------------------------------------------
 *                      	SENSOR FUNCTIONS
 *
 * Author:      Daniel Romero Mujalli
 * Written:     28/12/2012
 * Last update:  5/11/2013
 *
 * Summary:      Here are defined some functinos used for the class Sensor
 *                
 *               For declaration and prototypes, see sensorFunctions.h               
 *               
 *---------------------------------------------------------------------------*/
/* LIBRARIES 																 */
 #include "../miscellaneous/miscellaneous.h"
 using namespace std;
/*---------------------------------------------------------------------------- 
 * Function name:           refreshSensors
 *  
 *   Update sensor values for agent i
 *      
 *---------------------------------------------------------------------------*/
void refreshSensors(Sensor myArray[][SENSOR_NUMBER], int agent_i)
{
	float theta, thetaUneven, thetaEven, alfa, alfax, angle;
	
	theta = myArray[agent_i][0].getTheta();
	
	thetaEven = thetaUneven = theta;
	
	float scope = myArray[agent_i][0].getScope();
	
	/* refresh each sensor j, depending whether it goes up or down from theta*/
	for(int j = 0; j < SENSOR_NUMBER; j++)
	{
		/* reset detection 													 */
		myArray[agent_i][j].setDetection(0);  
		
		if(j == 0)
		{
			alfax  = theta;
			alfa   = scope/2;
			thetaEven   = theta + alfa;
			thetaUneven = theta - alfa;
			
			myArray[agent_i][j].setAlfaX(alfax);
			myArray[agent_i][j].setAlfa(alfa);
			myArray[agent_i][j].setSights();
		}
		else
		{
			
			if((j%2) == 0)
			{
				alfax  = thetaEven + (scope)/2;
				alfa   = alfax - thetaEven;
				
				if(toAngle(alfax) < 0)
				{
					angle = 360 + toAngle(alfax);
					alfax = toRadian(angle);  
				}
				else if(toAngle(alfax) > 360)
				{
					angle = toAngle(alfax) - 360;
					alfax = toRadian(angle); 
				}
				
				myArray[agent_i][j].setAlfaX(alfax);
				myArray[agent_i][j].setAlfa(alfa);
				myArray[agent_i][j].setSights();
				thetaEven += scope;
			}
			else 
			{
				alfax = (thetaUneven - scope/2);
				alfa  = thetaUneven - alfax;
				if(toAngle(alfax) < 0)
				{
					angle = 360 + toAngle(alfax);
					alfax = toRadian(angle);  
				}
				else if(toAngle(alfax) > 360)
				{
					angle = toAngle(alfax) - 360;
					alfax = toRadian(angle); 
				}
				myArray[agent_i][j].setAlfaX(alfax);
				myArray[agent_i][j].setAlfa(alfa);
				myArray[agent_i][j].setSights();
				thetaUneven -= scope;
			}	 
		}
	}
}

/*---------------------------------------------------------------------------- 
 * Function name:           testQuadrant
 *  
 *   Check in which quadrant is located the angle and returns the quadrant
 *      
 *---------------------------------------------------------------------------*/
float testQuadrant(float &angle)
 {
       if(angle <= 90 && angle >= 0) {angle = angle; return 1;}
       if(angle > 90 && angle <= 180){angle = 180 - angle; return 2;}
       if(angle > 180 && angle <= 270){angle = angle - 180; return 3;}
       if(angle > 270 && angle <= 360){angle = 360 - angle; return 4;}
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:           distance
 *  
 *   Outputs euclidian distance between two points (x0,y0) and (x1,y1)
 *      
 *---------------------------------------------------------------------------*/
 float getDistance(float x0, float y0, float x1, float y1)
 {
 	float distance;
 	
 	distance = float(sqrt((pow(double(x0 - x1), 2) + pow(double(y0 - y1), 2))));
 	
 	return distance;
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:           toAngle, toRadian
 *  
 *   Convert to angle or radians
 *      
 *---------------------------------------------------------------------------*/
 float toAngle(float angle){ return angle*180/M_PI;}
 
 float toRadian(float angle){ return angle*M_PI/180;}
 
/*----------------------------------------------------------------------------- 
 * Function name:           getYIntercept
 *  
 *   returns b from y = mx + b
 *      
 *---------------------------------------------------------------------------*/
 float getYIntercept(float y, float x, float m)
 {
 	float b = (y - m*x);
 	
 	return b;
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:           getTriangleXY
 *  
 *   Returns x and y values, according to the angle and hypotenuse h
 *      
 *---------------------------------------------------------------------------*/
 void getTriangleXY(int quadrant, float angle, float &x, float &y, float h)
 {
 	switch (quadrant)
    {
           case 1:
           {
           	x = h*cos(angle);
 			y = h*sin(angle);
 			break;
           }
           case 2:
           {
           	x = (-1.0)*h*cos(angle);
           	y = h*sin(angle);
           	break;
           }
           case 3:
           {
           	x = (-1.0)*h*cos(angle);
           	y = (-1.0)*h*sin(angle);
           	break;
           }
           case 4:
           {
           	x = h*cos(angle);
           	y = (-1.0)*h*sin(angle);
           	break;
           }
    }
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:           InterceptLineCircle
 *  
 *   Check for interception between a line y = mx + b and a circle centered in  
 *   (h,k) and radius r,  (x - h)^2 + (y - k)^2 = r^2
 *	 Stores the values (x,y) in the pointers *point1 and *point2
 *   Hint: The slope of a line, given alfa, is m = tang(alfa)
 *---------------------------------------------------------------------------*/
 bool interceptLineCircle (float m, float b, float h, float k, float r,
 								   float point1[2], float point2[2])
 {
 	/* constans for solving the roots of the quadratic equation
 					  aX^2 + vX + c = 0                                      */
	 float a, v, c; 
	 
 	a = 1 + float(pow(double(m), 2));
 	v = 2*m*(b - k) - (2*h);
 	c = float(pow(double(h), 2) - pow(double(r), 2) + pow(double(b-k), 2));
	
	/* If not intersection, return false									 */
 	if((float(pow(double(v), 2)) - 4*a*c) < 0){ return false;}
 	
	/* If intersection, then 											     */  
 	else 
 	{
 		/* point 1:															 */
 		point1[0] = (-v + sqrt(float(pow(double(v), 2)) - (4.0*a*c)))/(2.0*a);
 		point1[1] = (m*point1[0]) + b;
 		
 		/* point 2:															 */
 		point2[0] = (-v - sqrt(float(pow(double(v), 2)) - (4.0*a*c)))/(2.0*a);
 		point2[1] = (m*point2[0]) + b;
 		
 		return true;
 	}

 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        interceptCircleSpecialCase
 *		uses only in cases where the object is located 90 or 270 degrees from
 *	target, so to avoid dividing to zero in interceptLineCircle function
 *---------------------------------------------------------------------------*/
 bool interceptCircleSpecialCase(float xSight, float h, float k, float r,
 	                             float point1[2], float point2[2])
 {
 	/* constans for solving the roots of the quadratic equation
 					  aX^2 + vX + c = 0                                      */
 	float a, v, c;
 	
 	a = 1;
 	v = (-2.0)*k;
 	c = float(pow(double(xSight-h), 2) + pow(double(k), 2) - pow(double(r), 2));
	
	/* If not intersection, return false									 */
 	if((float(pow(double(v), 2)) - 4*a*c) < 0){ return false;}
 	
 	/* If intersection, then 											     */  
 	else 
 	{
 		/* point 1:															 */
 		point1[0] = xSight;
 		point1[1] = (-v + sqrt(float(pow(double(v), 2)) - (4.0*a*c)))/(2.0*a);
 		
 		/* point 2:															 */
 		point2[0] = xSight;
 		point2[1] = (-v - sqrt(float(pow(double(v), 2)) - (4.0*a*c)))/(2.0*a);
 		
 		return true;
 	}

 } 
 
/*----------------------------------------------------------------------------- 
 * Function name:           relativeAngle
 *  
 *   Returns x and y values, according to the angle and hypotenuse h
 *   Based on law of cosines   
 *---------------------------------------------------------------------------*/
 float relativeAngle(float x0, float y0, float xObject, float yObject,
 					 float xSight, float ySight)
 {
 	float angle;
 	
    float mod1 = float(sqrt(pow(double(xSight-x0),2)+pow(double(ySight-y0),2)));
    float mod2 = float(sqrt(pow(double(xObject-x0),2)+pow(double(yObject-y0),2)));
    
    float arg = ((xSight-x0)*(xObject-x0)+(ySight-y0)*(yObject-y0))/(mod1*mod2);
    
    angle = acos(arg);
    
    return angle;
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:           refreshDetection
 *  
 *   Check for detection of agents and walls
 *      
 *---------------------------------------------------------------------------*/
 void refreshDetection(Sensor myArray[][SENSOR_NUMBER], Agent myAgents[], 
 					   int agentsNumber)
 {
 	bool onSight = false;
 	bool border  = false;
 	
 	int m = 0;
 	
 	/* If it is only one individual then only checks for borders			 */
 	if(agentsNumber == 1)
 	{
 		for (int i = 0; i < agentsNumber; i++)
 		{
 			for (int j = 0; j < SENSOR_NUMBER; j++)
 			{
 				border = myArray[i][j].checkSighttoBorder();
 				if(border){myArray[i][j].setDetection(1); cout << "border detected!" << endl;} 
 				border = false;
 			}
 		}
 	}
 	else /* else, run the entire function									 */
 	{
 	
 		for(int i = 0; i < agentsNumber; i++)
 		{
 			while(m < agentsNumber)
 			{
 				if(m == i){m++;}
 				for(int j = 0; j < SENSOR_NUMBER; j++)
 				{
 					if(m < agentsNumber)
 					{
 						onSight = myArray[i][j].checkSight(myAgents[m].getxPosition(), 
 										     myAgents[m].getyPosition());
 						if(onSight){myArray[i][j].setDetection(1);} //cout << "object detected!" << endl;}
 						
 						if(!onSight)
 						{
 							border = myArray[i][j].checkSighttoBorder();
 						
 							if(border){myArray[i][j].setDetection(1);} //cout << "border detected!" << endl;}
 						
 						}
 					}
 					onSight = border = false;
 				}
 				m++;
 			}
 			m = 0;
 		}	
 	}	
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:           refreshObjectDetection
 *  
 *   Check for detection of objects
 *      
 *---------------------------------------------------------------------------*/
 void refreshObjectDetection(Sensor mySensor[][SENSOR_NUMBER], int agent_i,
 							 Agent myObject[], int objNumber)
 {
 	bool onSight = false;
 	
 	for (int i = 0; i < objNumber; i++)
 	{
 		for (int j = 0; j < SENSOR_NUMBER; j++)
 		{
 			onSight = mySensor[agent_i][j].checkSight(myObject[i].getxPosition(), 
 													  myObject[i].getyPosition());
 													  
 			if(onSight){mySensor[agent_i][j].setDetection(1);} 
 			
 			onSight = false;
 		}
 	}
 }
 
 /*----------------------------------------------------------------------------- 
 * Function name:           borderDetection
 *  
 *   Only check for walls. No objects
 *      
 *---------------------------------------------------------------------------*/
 void borderDetection(Sensor mySensor[][SENSOR_NUMBER], int agent_i)
 {
 	bool onSight = false;
 	for (int j = 0; j < SENSOR_NUMBER; j++)
 	{
 		onSight = mySensor[agent_i][j].checkSighttoBorder();
 		
 		if(onSight){mySensor[agent_i][j].setDetection(1); }
 		
 		onSight = false;
 	}
 }
 
 /*----------------------------------------------------------------------------- 
 * Function name:        signalTranslation
 *		convert to decimal values the detection vector (myArray) of length
 *		number of sensors. Sensors have value of 1 when detecting objects. NULL
 *		otherwise
 *---------------------------------------------------------------------------*/
int signalTranslation(float myArray[], int lenght)
{
    int decimal = 0; 
    
    for (int l = 0; l < lenght; l++)
    {
        if(myArray[l])
        decimal += int(pow(double(2.0), l));
    }
    return decimal;
}

