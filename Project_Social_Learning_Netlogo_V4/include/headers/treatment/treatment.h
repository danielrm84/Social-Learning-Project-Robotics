/*-----------------------------------------------------------------------------
 *                      		TREATMENT
 *
 * Author:      Daniel Romero Mujalli
 * Last update:   7/ 2/2017
 *
 * Summary:      In this file scenarios of behavior and environment can be
 *				 set.
 *
 *				 Activate only one scenario of behavior and one scenario of
 *				 environment.
 *
 *				 Currently this version of the code implements only the
 *				 static environmental scenario. 
 *
 *				 All scenarios of behavior are implemented.
 *
 *---------------------------------------------------------------------------*/

#ifndef TREATMENT_H
#define TREATMENT_H

/*-----------------------------------------------------------------------------
 *                      BEHAVIOR TREATMENTS
 *              activate (uncomment) only one scenario of behavior
 *---------------------------------------------------------------------------*/
 #define MIXED
// #define SOCIAL
// #define ASOCIAL
// #define GEN_EVOL
// #define RND_SEARCH
/*-----------------------------------------------------------------------------
 *                    ENVIRONMENT TREATMENTS
 *              activate (uncomment) only one scenario of environment
 *---------------------------------------------------------------------------*/
// #define NO_TREATMENT
 #define STATIC
// #define ABRUPT_CHANGE
// #define MIGRATION
 /* Activate ONE_MIGRANT_AT_A_TIME below to test one realeased migrant 
    robot at a time, as in our experiment 	                                 */
//	#define ONE_MIGRANT_AT_A_TIME	// remember to set maximum_migrants below	
// #define GRADUAL	  // Important, our GRADUAl change experimental setup used: 
 					  // AGENT ENERGY 2000 and 7000; siteDiameter 200; renew 5.0 
					   
#ifdef GRADUAL

#define EFFECT             0.0001       /* wear down and recovery rates		 */
#define MAX_ENERGY_EFFECT  3.0   		/* maximum negative effect of patches 
										   on agent energy     		 		 */ 
#define MIN_ENERGY_EFFECT  0.0   		/* Agents cannot gain energy 		 */
#define RENEW              5.0		    /* affects the recovery rate of patches 
										   				             		 */

#endif /* GRADUAL */

#ifdef MIGRATION

#define MAX_MIGRANTS	5			    /* maximum number of migrants allowed*/

#endif /* MIGRATION */				
	
					   
#endif /* TREATMENT_H */			
