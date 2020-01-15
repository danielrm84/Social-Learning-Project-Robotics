/*-----------------------------------------------------------------------------
 *                      	CLASS GENETIC ALGORITHM
 *
 * Author:      Daniel Romero Mujalli
 * Written:      21/1/2013
 * Last update:   8/7/2016
 *
 * Summary:      This file defines the members, methods and
 *               functions from  class Chromosome
 *               Prototypes in Genetic_Algorithm.h   
 *                              
 *---------------------------------------------------------------------------*/
/*		Libraries: 										                     */
#include "../miscellaneous/miscellaneous.h"
using namespace std;
/*-----------------------------------------------------------------------------
 *			Member and methods definition
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *                  CONSTRUCTORS:
 *---------------------------------------------------------------------------*/
 Chromosome::Chromosome(){selected = false;}
 
 Chromosome::Chromosome(int n, int best_n_indiv)
 {
 	fitness = 0; selected = false; mutRate = 0.03;
 	populationN = n;
 	best_n = best_n_indiv;
 }
/*-----------------------------------------------------------------------------
 *       OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/
/* 		     set Initial values of genes									 */
void Chromosome::setGenesInitialValues(int myArray[][LENGTH], int nGenes)
{
	float r;
	bool done;
	/*n: individual; g: gene IDs 											 */
	for (int g = 0; g < nGenes; g++)
	{
		done = false;
		do
		{
			for (int l = 0; l < LENGTH; l++)
			{
				r = rand()/(RAND_MAX + 1.0);
				if(r >= 0.5){myArray[g][l] = 1;}
				else{myArray[g][l] = 0;}
			}
			if(toDecimal(myArray, g) <= MAX_VAL){done = true;}
		}while(done == false);
	}
}
/* 	Convert initial genes values from binary to decimals for representing
	neural network weights	  											     */		
void Chromosome::setGAWeights(int myArray[][LENGTH], int nGenes, bool input)
{
	float ctte = 100000; /* Allows to get fraction numbers after convertion 
							from binary to decimals 						 */ 					 
	float w;
	for (int g = 0; g < nGenes; ++g)
	{
		w = (toDecimal(myArray, g)/ctte) - MIN_WEIGHT;
		if(input){inWeights[g] = w;} // If input_Chromosome
		else{hidWeights[g] = w;}
	}
}
/* 					Fitness calculation							 		     */
void Chromosome::fitnessFunction(float energy, float maxE, float x0, float y0,
								 float xf, float yf, float maxD)
{
	float fitE, fitD;
	fitE = energy/(maxE+maxD);
	fitD = getDistance(x0, y0, xf, yf)/(maxD);
	//if(fitD < 10){fitE = 0.0;}
	fitness = (fitE + fitD);
}
/* 		  mutate array of genes with probablity mut_rate					 */
void Chromosome::mutate(int myArray[][LENGTH], int nGenes)
{
	float r; 
	for (int g = 0; g < nGenes; g++)
	{
		for (int l = 0; l < LENGTH; l++)
		{
			r = rand()/(RAND_MAX + 1.0);
			if(r <= mutRate)
			{
				if(myArray[g][l]){myArray[g][l] = 0;}
				else{myArray[g][l] = 1;}
			}
		}
	}
}
/*				 Set and get functions										 */
float Chromosome::getFitness(){ return fitness;}
void  Chromosome::setFitness(float value){fitness = value;}
void Chromosome::setMutationRate(float value){mutRate = value;}
void Chromosome::setPopulationNumber(int n){populationN = n;}
void Chromosome::setBest_n(int X){best_n = X;}
