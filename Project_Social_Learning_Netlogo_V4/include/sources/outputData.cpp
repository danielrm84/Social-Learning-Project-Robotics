/*-----------------------------------------------------------------------------
 *                      		OUTPUT_DATA
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  22/ 1/2017
 *
 * Summary:      This file contains the definition of the functions in
 *				 the file:
 *				 /include/headers/outputData/outputData.h
 *
 *---------------------------------------------------------------------------*/

#include "../miscellaneous/miscellaneous.h"

/* SetHeaderMoveFile
   This function set the headers for the file storing agents position. The
   file is written when DEBUG is active										 */
void setHeaderMoveFile(std::ofstream &move, int n)
{
	for (int i = 0; i < n; i++)
    {
        move << "A_" << i << ","<<","<<",";//"\t\t\t";
    }
    move << "\n";
    for (int i = 0; i < n; i++)
    {
        move << "Pos_X" << "," << "Pos_Y,Theta,Detection,";//"Pos_X\tPos_Y\tTheta\t";   
    }
    move << "\n";
}
/*---------------------- End of setHeaderMoveFile ---------------------------*/

/* createFiles: 
   open and create file names acording to scenario of behavior				 */
void openFiles(std::ofstream &mFile, std::ofstream &inWhiteFile,
			          std::ofstream &inBlackFile)
{
		/* Opening files: 													 */
	#ifdef MIXED 

	mFile.open("Mortality_Mx.xls");
	inBlackFile.open("inBlackArea_Mx.xls");
	inWhiteFile.open("inWhiteArea_Mx.xls");

	#endif

	#ifdef SOCIAL

	mFile.open("Mortality_SL.xls");
	inBlackFile.open("inBlackArea_SL.xls");
	inWhiteFile.open("inWhiteArea_SL.xls");

	#endif

	#ifdef ASOCIAL

	mFile.open("Mortality_AL.xls");
	inBlackFile.open("inBlackArea_AL.xls");
	inWhiteFile.open("inWhiteArea_AL.xls");

	#endif

	#ifdef GEN_EVOL

	mFile.open("Mortality_GE.xls");
	inBlackFile.open("inBlackArea_GE.xls");
	inWhiteFile.open("inWhiteArea_GE.xls");

	#endif

	#ifdef RND_SEARCH

	mFile.open("Mortality_RS.xls");
	inBlackFile.open("inBlackArea_RS.xls");
	inWhiteFile.open("inWhiteArea_RS.xls");

	#endif
}
/*---------------------- End of openFiles -----------------------------------*/

/* writeMortalityFile: 
   store mortality data 							     					 */
void writeMortalityFile(std::ofstream &mFile, 
			   int mortality[][REPLICATIONS])
{

/* Headers:																 	 */ 
	for (int k = 0; k < REPLICATIONS; k++)
	{
    	mFile << "R_" << k << "\t";
	}
	mFile << "\n";
/* copy results to files 												 	 */ 
	for (int z = 0; z < ITERA; z++)
	{
    	for (int k = 0; k < REPLICATIONS; k++)
    	{
        	mFile << mortality[z][k] << "\t";
    	}
    	mFile << "\n";
	}
}
/*---------------------- End of writeMortalityFile --------------------------*/

/* writeinWhiteFile: 
   store data on number of agents located in the white patch		 		 */
void writeInWhiteFile(std::ofstream &inWhiteFile, 
					  int inWhite[][REPLICATIONS])
{

/* Headers:																 	 */ 
	for (int k = 0; k < REPLICATIONS; k++)
	{
    	inWhiteFile << "White_R_" << k << "\t";
	}
	inWhiteFile << "\n";
// copy results to files 												 
	for (int z = 0; z < ITERA; z++)
	{
    	for (int k = 0; k < REPLICATIONS; k++)
    	{
        	inWhiteFile << inWhite[z][k] << "\t";
    	}
    	inWhiteFile << "\n";
	}
}
/*---------------------- End of writeInWhiteFile function -------------------*/

/* writeInBlackFile: 
   store data on nuumber of agents in the black patch		 				 */
void writeInBlackFile(std::ofstream &inBlackFile, 
		  	   		  int inBlack[][REPLICATIONS])
{
/* Headers:																 	 */ 
	for (int k = 0; k < REPLICATIONS; k++)
	{
    	inBlackFile << "Black_R_" << k << "\t";
	}
	inBlackFile << "\n";
/* copy results to files 												 	 */ 
	for (int z = 0; z < ITERA; z++)
	{
    	for (int k = 0; k < REPLICATIONS; k++)
    	{
        	inBlackFile << inBlack[z][k] << "\t";
    	}
    	inBlackFile << "\n";
	}
}
/*---------------------- End of writeInBlackFile function -------------------*/

/* writeOmegaFile:
   write data into file containing the number of social learning agents.
   Only for the Mixed Population Mx											 */
void writeOmegaFile(std::ofstream &omegaFile, 
					int socialMatrix[ITERA][REPLICATIONS])
{
	
	omegaFile.open("SocialRobots_Mx.xls");
	for (int k = 0; k < REPLICATIONS; k++)
	{
    	omegaFile << "R_" << k << "\t";
	}
	omegaFile << "\n";
/* copy results to files 												 	 */ 
	for (int z = 0; z < ITERA; z++)
	{
    	for (int k = 0; k < REPLICATIONS; k++)
    	{ 
        	omegaFile << socialMatrix[z][k] << "\t";
    	}
    	omegaFile << "\n";
	}
}
/*---------------------- End of writeOmegaFile ------------------------------*/
