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
 *               The declaration of this function is in the file:
 *				 /headers/readWeights/readWeights.h
 *
 *---------------------------------------------------------------------------*/

#include "../miscellaneous/miscellaneous.h"
using namespace std;

/*					  Read Weights
	read weights from files: inWeights_NN_100.xls and outWeights_NN_100.xls
	used by NN. Those files contain up to 100 NN (support for 100 agents)	 */
void readWeights(ifstream &myFile, float weights[], int rows)
{
	//cout << "new NN" << endl;
    for (int i = 0; i < rows; i++)
    {
        myFile >> weights[i];
        //cout << weights[i] << endl;;
    }    
}
