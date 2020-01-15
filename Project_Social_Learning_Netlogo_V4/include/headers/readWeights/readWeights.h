/*-----------------------------------------------------------------------------
 *                      		READ_WEIGHTS
 *
 * Author:      Daniel Romero Mujalli
 * Last update:   7/ 2/2017
 *
 * Summary:      This file contains the declaration of the function used
 *				 for reading neural network weight values from file.
 *				 
 *
 *               The definition of this function is in the file:
 *				 /sources/readWeights.cpp
 *
 *---------------------------------------------------------------------------*/

#ifndef READ_WEIGHTS_H
#define READ_WEIGHTS_H

/*					  Read Weights
	read weights from files: inWeights_NN_100.xls and outWeights_NN_100.xls
	used by NN. Those files contain up to 100 NN (support for 100 agents)	 */
void readWeights(std::ifstream &myFile, /* file containing the weight values */
				 float weights[], 		/* vector for storing the weiights   */
				 int rows);				/* number of weights in given layer	 */


#endif /* READ_WEIGHTS_H */
