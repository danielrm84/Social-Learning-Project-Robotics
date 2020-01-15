/*-----------------------------------------------------------------------------
 *                      		CLASS_PARAMETER
 *
 * Author:      Daniel Romero Mujalli
 * Last update:   6/ 2/2017
 *
 * Summary:      This file contains parameter values for those parameters
 *				 used in class sensor (sensor.h) and class neural network
 *				 (neural_network.h)
 *
 *---------------------------------------------------------------------------*/

#ifndef CLASS_PARAMETER_H
#define CLASS_PARAMETER_H

/*-----------------------------------------------------------------------------
 *                       CLASS SENSOR: 
 *---------------------------------------------------------------------------*/
#define SENSOR_NUMBER   8 /* number of frontal sensors of the agent			 */
#define AGENT_SIGHT   360 /* cone of sight of the agent (in degrees)		 */
/*-----------------------------------------------------------------------------
 *                       CLASS NEURAL NETWORK: 
 *---------------------------------------------------------------------------*/
#define XsINPUT  8     /* Number of inputs or entries to the neural network  */ 
#define HIDDEN   0 //10    /* Number of neurons in the hidden layer				 */ 
#define OUTPUT   2     /* Output neurons									 */

#define NN_LEARNING_RATE 	0.001 /* default learning rate of NN 			 */

#endif /* CLASS_PARAMETER */
