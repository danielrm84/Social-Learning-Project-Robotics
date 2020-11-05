/*-----------------------------------------------------------------------------
 *                      	GENETIC FUNCTIONS
 *
 * Author:      Daniel Romero Mujalli
 * Written:      22/1/2013
 * Last update:  19/2/2013
 *
 * Summary:      This file includes function prototypes used in 
 *               Chromosome class
 *               For definitions see geneticFunctions.cpp
 *               
 *---------------------------------------------------------------------------*/
#ifndef GENETICFUNCTIONS_H
#define GENETICFUNCTIONS_H
/*----------------------------------------------------------------------------- 
 * Function name:         toDecimal
 *  
 * Convert an array of binaries to a decimal number
 *  
 *---------------------------------------------------------------------------*/ 
 int toDecimal(int myArray[][LENGTH],	/* array of genes in binary			 */
 			   int g);					/* specific gene ID					 */
 			   
/*----------------------------------------------------------------------------- 
 * Function name:         toBinary
 *  
 * Convert decimal to binary and stores in array
 *   
 *---------------------------------------------------------------------------*/ 
 void toBinary(int number,				/* my decimal number				 */
  			   int myArray[][LENGTH], 	/* my array of binary				 */
			   int g);					/* gene ID which receive convertion	 */
			   
/*----------------------------------------------------------------------------- 
 * Function name:        selectTheBest
 *  
 * Select the best X number of individuals from population according to fitness
 *   
 *---------------------------------------------------------------------------*/
void selectTheBest(Chromosome myChrom[], /* a chromosome object				 */
				   int best_X,			 /* select the best X individuals	 */ 
				   int popNumber);		 /* population size					 */
				   
/*----------------------------------------------------------------------------- 
 * Function name:        reproduceSelected
 *  
 * The selected best_X individuals are allow to reproduce
 * Important! The original population is replaced by a new one. There is no
 * addition of individuals.
 *
 *  maxOffspring = popNumber / best_X;  must be an integer!!  
 *---------------------------------------------------------------------------*/
 void reproduceSelected(Chromosome myChromIn[], 	/* choromosome object of 
 													   input weights		 */
 						Chromosome myChromHid[], 	/* chromosome object of
						 							   hidden weights		 */
 					    int best_X, 				/* selected best X indv	 */
						int popNumber);				/* population size		 */
						
/*----------------------------------------------------------------------------- 
 * Function name:        copy
 *  
 * Makes an exact copy from the parent chromosome to the offspring
 * 
 *---------------------------------------------------------------------------*/
 void copy(Chromosome myChromIn[],		/* chromosome object of input weights*/ 
 		   Chromosome myChromHid[], 	/* chromosome object of hidden weight*/
		   int parent, 					/* parent ID, which act as template  */
 		   int offspring);				/* offspring ID who reveives copy	 */
 		   
#endif
