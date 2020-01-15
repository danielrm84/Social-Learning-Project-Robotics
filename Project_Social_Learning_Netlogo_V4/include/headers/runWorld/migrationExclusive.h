/*-----------------------------------------------------------------------------
 *                      		MIGRATION_EXCLUSIVE
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  12/ 2/2017
 *
 * Summary:      This file contains the declaration of functions exclusively
 *				 used for the migration experimental scenario.
 *
 *               The definition of these functions are in the file:
 *				 /sources/migrationExclusive.cpp
 *
 *---------------------------------------------------------------------------*/

#ifndef MIGRATION_EXCLUSIVE_H
#define MIGRATION_EXCLUSIVE_H

/* CheckAllOnTarget
   This function check and returns true if all agents are located in the white
   patch and are not moving 									 			 */
bool checkAllOnTarget(Agent myAgent[],    /* array of agents				 */ 
					  int n, 			  /* number of agents in array		 */
					  int agents_inWhite);/* number of agents in white patch */

#endif
