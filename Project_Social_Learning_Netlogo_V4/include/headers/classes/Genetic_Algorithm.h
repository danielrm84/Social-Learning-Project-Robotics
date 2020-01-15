/*-----------------------------------------------------------------------------
 *                      	CLASS GENETIC ALGORITHM
 *
 * Author:      Daniel Romero Mujalli
 * Written:      21/1/2013
 * Last update:   8/7/2016
 *
 * Summary:      This file contains the declaration of the class Chromosome,
 *               its members, methods and variables.
 *               For the definition see /sources/Genetic_Algorithm.cpp
 *               
 *               This class	implements haploid, asexual organisms with two 
 *				 chromosomes coding the weights for both, the input and hidden
 * 				 layers (one hidden layer) of the feedforward neural networks
 *				 used in this work Romero-Mujalli et al. The genetic coded
 *				 NN are used in evolutionary experiments (training) to select for 
 *				 candidate NN that are going to govern the navigating behavior of
 * 				 the agents.
 *				 Default mutation rate = 0.03
 *               
 *---------------------------------------------------------------------------*/
#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
/*-----------------------------------------------------------------------------
 *                        PUBLIC CONSTANTS 
 *---------------------------------------------------------------------------*/
#define LENGTH	          19 					/* in bits. 				 */ 
#define MAX_VAL	     	400000 					/* Max value allow from binary 
												   numbers ## 				 */ 
#define MIN_WEIGHT        3.0 					/* Used as in Rnd() to take 
												   values (-3, 3) 			 */ 
#define GENES_INPUT        (XsINPUT + 1)*HIDDEN /* How many genes or weights in
												   Input Layer               */ 
#define GENES_HIDDEN       (HIDDEN  + 1)*OUTPUT	/* How many genes or weights in
												   hidden	 				 */
/* Each 'gene' codes for a weight in binary format (ones and zeros) of length 
   LENGTH. Then, each gene is translated to decimal value, to get the actual 
   value of the weight for the corresponding neuron in the neural network.
   For example, the first gene in the array of the input genes coding for the
   weights of the input layer will correspond to the weight affecting the
   sinapsis among the first neuron of the input layer (neuron 0 or bias) and the
   first neuron of the hidden layer 										 */
/*-----------------------------------------------------------------------------
 *  ## IMPORTANT ##
 *  
 * There is a file binary.cpp to test for the appropiate MAX_VAL and 
 * LENGTH for getting the desire range of values for the coded weights                   
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *                        THE CLASS STARTS
 *---------------------------------------------------------------------------*/
 class Chromosome
 {
 	
 private:
 	
 	float fitness, mutRate;			/* fitness value and mutation rate */
 	int populationN; 				/* population size						 */
	int best_n;						/* best n individuals to be selected	 */

 public:
/*-----------------------------------------------------------------------------
 *                  CONSTRUCTORS:
 *---------------------------------------------------------------------------*/
/* 		 default 															 */
 	Chromosome();
/*		 Take as input population size and how many individuals will be
		 selected (best_n, truncate selection). For example, select the best 10 
		 out of a population of N individuals								 */
 	Chromosome(int n, 			/* population size							 */
	 		   int best_n_indiv);/* select best n individuals in the pop  	 */
/*-----------------------------------------------------------------------------
 *                  OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------- 
 * Function name:         setGenesInitialValues
 *  
 * fills each gene of the array with binary values of length LENGTH, which are 
 * randomly set in the interval [0, MAX_VAL]. 
 *---------------------------------------------------------------------------*/ 
    void setGenesInitialValues(int myArray[][LENGTH],   /* length: in bits	 */
							   int nGenes);				/* number of genes	 */
/*----------------------------------------------------------------------------- 
 * Function name:         setGAWeights
 *  
 * translate the binary-coded genetic information to decimal values for the 
 * weights of the neural networks: weights for the input and hidden layers.
 * This funcion is used after setting genes initial values 
 * i. e. "setGenesInitialValues"
 *---------------------------------------------------------------------------*/
 	void setGAWeights(int myArray[][LENGTH], /* length bits 				 */
	 				  int nGenes, 			 /* number of genes in array	 */
					  bool input);			 /* TRUE: set weight values into 
					  							array of weights of the input 
												layer inWeights[]
												FALSE: set weight values into 
												array of weights of the hidden
												layer hidWeights[]	 		 */
/*----------------------------------------------------------------------------- 
 * Function name:        fitnessFunction
 *  
 * Compute the fitness of the chromosome, considering the distance between 
 * agent initial and final positions, and the agent energy  
 *---------------------------------------------------------------------------*/
 void fitnessFunction(float energy,		/* agent energy						 */
 					  float maxE, 		/* maximum energy					 */
					  float x0, 		/* X coordinate of initial position  */
					  float y0,			/* Y coordinate of initial postion   */
					  float xf, 		/* X final position					 */
					  float yf, 		/* Y final position					 */
					  float maxD);		/* Maximum horizontal or vertical 
					  					   distance							 */
 /*---------------------------------------------------------------------------- 
 * Function name:        mutate
 *  
 * Change bits within each gene with probability mutRate
 *   
 *---------------------------------------------------------------------------*/
 void mutate(int myArray[][LENGTH],		/* length: of bit chain				 */ 
 			 int nGenes);				/* number of genes					 */
/*----------------------------------------------------------------------------- 
 * Function name:       set and get functions
 *   
 *---------------------------------------------------------------------------*/
 float getFitness();					/* returns fitness of the chromosome */
 void setFitness(float value);			/* set fitness to given value		 */
 void setMutationRate(float value);		/* set the mutation rate     		 */
 void setPopulationNumber(int n);		/* set population size				 */
 void setBest_n(int X);					/* set best n individuals to be selected
 																 			 */

/*-----------------------------------------------------------------------------
 *                 PUBLIC VARIABLES
 *---------------------------------------------------------------------------*/
    int inputGenes[GENES_INPUT][LENGTH]; 	/* binary-coded weights input layer*/ 
 	int hiddenGenes[GENES_HIDDEN][LENGTH];  /* binary-coded weights	hidden layer*/ 
 	float inWeights[GENES_INPUT]; 			/* decimal values of the input layer 
	 										   weights, as they will be read by 
											   the NN						 */
	float hidWeights[GENES_HIDDEN]; 		/* decimal values of the hidden layer
											   weigths as they are going to be
											   read by the NN	     		 */
 	bool selected; 							/* checks if the given chromosome has
	 										   been selected as one of the best
																			 */ 
 };
 #endif
