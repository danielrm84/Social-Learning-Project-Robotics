/*-----------------------------------------------------------------------------
 *                      	GENETIC FUNCTIONS
 *
 * Author:      Daniel Romero Mujalli
 * Written:      22/1/2013
 * Last update:  19/2/2013
 *
 * Summary:      This file includes function definitions declared in 
 *               geneticFunctions.h and usually used in Chromosome class
 *               
 *               
 *---------------------------------------------------------------------------*/
 /*		Libraries: 										                     */
#include "../miscellaneous/miscellaneous.h"
using namespace std;
/*----------------------------------------------------------------------------- 
 * Function name:         toDecimal
 *  
 * Convert an array of binaries to a decimal number
 * n: individual; g: gene IDs  
 *---------------------------------------------------------------------------*/ 
int toDecimal(int myArray[][LENGTH], int g)
{
	int decimal = 0;	
	for (int l = 0; l < LENGTH; l++)
	{
		if(myArray[g][l])
		decimal += int(pow(double(2), l));
	}
	return decimal;
}
/*----------------------------------------------------------------------------- 
 * Function name:         toBinary
 *  
 * Convert decimal to binary and stores in array
 *   
 *---------------------------------------------------------------------------*/ 
void toBinary(int number, int myArray[][LENGTH], int g)
{
	for (int l = 0; l < LENGTH; l++)
	{
		myArray[g][l] = number % 2;		/* store remainer of number / 2		 */
		number /=2;						/* update number as number / 2		 */
	}
}
/*----------------------------------------------------------------------------- 
 * Function name:        selectTheBest
 *  
 * Select the best X number of individuals from population according to fitness
 * and change the value of a bool variable if selected
 *---------------------------------------------------------------------------*/
void selectTheBest(Chromosome myChrom[], int best_X, int popNumber)
{
	int best;
	float max;
	
	for (int i = 0; i < best_X; i++)
	{
		max = -0.10;
		for (int j = 0; j < popNumber; j++)
		{
			/* check if already selected as one of the best					 */
			if(myChrom[j].selected == false)
			{
				if(myChrom[j].getFitness() > max)
				{
					max = myChrom[j].getFitness(); 
					best = j; 
				}
			}
		}
		myChrom[best].selected = true;
	}
}
/*----------------------------------------------------------------------------- 
 * Function name:        reproduceSelected
 *  
 * The selected best_X individuals are allow to reproduce
 * Important! The original population is replaced by a new one. There is no
 * addition of individuals
 * maxOffspring must be an integer!!  
 *---------------------------------------------------------------------------*/
 void reproduceSelected(Chromosome myChromIn[], Chromosome myChromHid[], 
 						int best_X, int popNumber)
 {
 	int maxOffspring = popNumber/best_X;
 	int count;
 	int m = 0;
 	
 	for (int i = 0; i < popNumber; i++)
 	{
 		if(myChromIn[i].selected || myChromHid[i].selected)
 		{
 			count = 0;
 			do
 			{
 				copy(myChromIn, myChromHid, i, m);
 				myChromIn[m].mutate(myChromIn[m].inputGenes, 
 			                        GENES_INPUT);
 				myChromHid[m].mutate(myChromHid[m].hiddenGenes, 
 						       	     GENES_HIDDEN);
 				count++;
 				m++;
 				
 			}while(count < maxOffspring);
 		}
 	}
 }
/*----------------------------------------------------------------------------- 
 * Function name:        copy
 *  
 * Makes an exact copy from the parent chromosome to the offspring
 * 
 *---------------------------------------------------------------------------*/
 void copy(Chromosome myChromIn[], Chromosome myChromHid[], int parent, 
 		   int offspring)
 {
 	int i = parent;
 	int m = offspring;
 	
 	for (int g = 0; g < GENES_INPUT; g++)
 	{
 		for (int l = 0; l < LENGTH; l++)
 		{
 			myChromIn[m].inputGenes[g][l] = myChromIn[i].inputGenes[g][l];
 		}
 	}
 	
 	for (int g = 0; g < GENES_HIDDEN; g++)
 	{
 		for (int l = 0; l < LENGTH; l++)
 		{
 			myChromHid[m].hiddenGenes[g][l] = myChromHid[i].hiddenGenes[g][l];
 		}
 	}
 }
