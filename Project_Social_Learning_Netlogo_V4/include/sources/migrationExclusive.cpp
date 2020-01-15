/*-----------------------------------------------------------------------------
 *                      		MIGRATION_EXCLUSIVE
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  12/ 2/2017
 *
 * Summary:      This file contains the definition of functions exclusively
 *				 used for the migration experimental scenario.
 *
 *               The declaration of these functions are in the file:
 *				 /include/runWorld/migrationExclusive.h
 *
 *---------------------------------------------------------------------------*/

#include "../miscellaneous/miscellaneous.h"

#ifdef MIGRATION
/* CheckAllOnTarget
   This function check and returns true if all agents are located in the white
   patch and are not moving 									 			 */
bool checkAllOnTarget(Agent myAgent[], int n, int agents_inWhite)
{
	int rn;				/* random number (integer)							 */
    float sum = 0;		/* total sum of agents velocity					 	 */
    bool done;			/* control if specific task is done					 */
    
    /* get the sum of agent velocities 										 */
    for(int i = 0; i < n; i++){ sum += myAgent[i].getAgentLinearVel();}
    
    /* if all agents on target and sum ~ 0: return true. This is used to start
	   the experimental scenario named migration.							 */
    if(white == N  &&
	   sum < 1.0   && 
	   sum > -1.0)
	{ 
		return true;
	}
}
/*-------------- End of CheckAllOnTarget ------------------------------------*/
#endif /* MIGRATION */

