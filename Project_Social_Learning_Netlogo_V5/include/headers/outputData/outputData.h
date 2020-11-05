/*-----------------------------------------------------------------------------
 *                      		OUTPUT_DATA
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  22/ 1/2017
 *
 * Summary:      This file contains the declaration of functions for writing
 *				 data into files.
 *
 *               The definition of these functions are in the file:
 *				 /sources/outputData.cpp
 *
 *---------------------------------------------------------------------------*/

#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

/* SetHeaderMoveFile
   This function set the headers for the file storing agents position. The
   file is written when DEBUG is active										 */
void setHeaderMoveFile(std::ofstream &move, /* file variable for storing data*/
					   int n);				/* number of agents				 */
					   
/* createFiles: 
   open and create file names acording to scenario of behavior				 */
void openFiles(std::ofstream &mFile, 	    /* file variable for mortality	 */
			   std::ofstream &inWhiteFile,  /* file variable for agents in 
			   								   white patch					 */
			   std::ofstream &inBlackFile); /* file variable for agents in
			   								   black patch					 */
			    
/* writeMortalityFile: 
   store mortality data 							     					 */
void writeMortalityFile(std::ofstream &mFile, /* file variable for mortality */
			   			int mortality[][REPLICATIONS]); /* array of data	 */

/* writeinWhiteFile: 
   store data on number of agents located in the white patch		 		 */			   			
void writeInWhiteFile(std::ofstream &inWhiteFile,/* file variable for agents in
													the white patch			 */ 
					  int inWhite[][REPLICATIONS]);/* array of data			 */
					  
/* writeInBlackFile: 
   store data on nuumber of agents in the black patch		 				 */
void writeInBlackFile(std::ofstream &inBlackFile,/* file variable for agents in
													the black patch			 */
		  	   		  int inBlack[][REPLICATIONS]);/* array of data		 	 */
		  	   
/* writeOmegaFile:
   write data into file containing the number of social learning agents.
   Only for the Mixed Population Mx											 */
void writeOmegaFile(std::ofstream &omegaFile, /* file variable for SL agents */
				    int socialMatrix[][REPLICATIONS]);/* array of data		 */

#endif /* OUTPUT_DATA_H */
