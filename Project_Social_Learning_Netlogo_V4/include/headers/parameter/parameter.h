/*-----------------------------------------------------------------------------
 *                      		PARAMETER
 *
 * Author:      Daniel Romero Mujalli
 * Last update:   6/ 2/2017
 *
 * Summary:      In this file, all relevant parameter values for the simulation
 *				 are set.
 *
 *---------------------------------------------------------------------------*/

#ifndef PARAMETER_H
#define PARAMETER_H

/*-----------------------------------------------------------------------------
 *                      	  PARAMETERS
 *---------------------------------------------------------------------------*/

#define ITERA           20000	 /* iteration number ( this is NOT number of 
								 								generations) */
#define REPLICATIONS      1 //20	 /* number of independent runs of experiment */

/* Arena or Spatial dimensions Parameters:									 */
#define Max_X            500 //500.0 //1000.0	 /* X dimesion (Acerbi et al used 200.0		 */ 
								 /*						our work: 500.0)     */
#define Max_Y            500 // 500.0 //1000.0	 /* Y dimension 						 	 */

/* Patch Parameters:												 */
// IMPORTANT!! if you want to add more than 2 patches, the code needs to
// be changed in startworld(), creation of patches
#define NUMBER_OF_PATCHES   2	 /* number of patches.           	     	 */
#define WHITE_PATCH_EFFECT  0.0  /* effect of white patch on agent energy    */
#define BLACK_PATCH_EFFECT  1.0  /* effect of black patch on agent energy    */
#define GREY_PATCH_EFFECT   3.0  /* effect of grey patch on agent energy	 */
#define PATCH_DIAMETER    150.0  // diameter of a patch 
                                 // (Acerbi et al used 60)
                                 
/* Agents Parameters:														 */
#define N                  10	 // number of Agents/individuals. 		 
								 // Currently, the NN files support up to 100
#define Max_E            2000.0  /* maximum energy of agents 				 */
#define IN_X                2	 // number of inputs to perceptron (Ground 
								 //								 Controller)
#define MAX_VEL            10.0	 /* agent maximum speed 					 */
#define REACH              5.0 /* range of vision (distance) 				 */
#define AGENT_RADIUS        1.0  /* agent body radius, Acerbi et al used 0.36*/
#define LEARNING_RATE       0.1	 /* basal learning rate (for AL, SL and Mx)  */
#define RND_W               3.0  /* for starting random behavior RB, weights 
														  within (-3; 3)     */
#define MUT_RATE            0.03 /* for mutating weights in perceptron (only 
												Innate/GE ground controller) */
#define MUT_PHI             0.03 /* for mutating phi in perceptron (Mx ground 
																 controller) */
#define MUT_OMEGA           0.1  // for mutating omega in Mx perceptron
								 // Marocco & Acerbi 2007 used 10%
#define OLD_AGENT		  2000	 // An agent is considered old if age >= value

								 

#endif /*PARAMETER_H*/
