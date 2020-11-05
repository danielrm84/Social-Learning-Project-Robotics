/*-----------------------------------------------------------------------------
 *                      	CLASS PERCEPTRON
 *
 * Author:      Daniel Romero Mujalli
 * Written:     17/ 2/2013
 * Last update:  5/11/2013
 *
 * Summary:      Class Perceptron, designed for ground color processing
 *               according to Acerbi et al. 2007.
 *                  
 *               Definitions of members in perceptron.cpp
 *               Both, initialization of weights and learning rate values
 *               depend on condition (whether SL, AL, GE, RS)
 *               
 *    Note: Maybe it would be great to use phi (randomly set at beggining),          
 *    also for individual and social learning.
 *	  Number of neighbors cannot be zero, because it includes the target
 *	  robot. This mean that the smallest value should be 1 and max N robots
 *	  usually 10.
 *	  Sigmoid was standarized in the range (0.09, s = 0; 0.91, s = 1)
 * 	  both extreme values produce an indetermination in sigmoid function
 *	  so, be aware! 
 * 	  With these values, lrate = 0.1 converge solution after 1050 iterations
 *	  in this sense, agent energy should allow agents to interact the world
 * 	  in a reasonable manner in order to make it possible to discover the
 *	  solution          
 *---------------------------------------------------------------------------*/
#ifndef PERCEPTRON_H
#define PERCEPTRON_H 
/*-----------------------------------------------------------------------------
 *                        PUBLIC CONSTANTS 
 *---------------------------------------------------------------------------*/
#define IN_X	     2 		/* Number of input variables
							   The number of outputs is one					 */ 
 							 
#define LENGTH_BIN	20		/* length of genes, in binary					 */ 
#define MAX_VALUE  600000	/* When divided by ctte in function GAweights(),
							   allow to control for Maximum value of weights */ 
#define MAX_Phi    100000   /* Allow to control Max value of phi in function
							   setPhi(), before dividing phi by ctte 		 */ 
#define MIN_W		3.0		/* Min allowed weight value 				     */ 
#define noPreference 2.2	/* This is the value for each weight in order to
							   set a non-preference behavior at beginning.
							   This is, for sigmoid (value = 0.90), which
							   corresponds to no modification of linearVel   */ 
/*-----------------------------------------------------------------------------
 *                        THE CLASS STARTS
 *---------------------------------------------------------------------------*/
class Perceptron
{
	
private:
	
	float e;					/* neuron output before activation			 */ 
	float weights[IN_X];		/* weights of the perceptron from in to out	 */ 
	float input[IN_X];			/* vector for reading inputs 				 */ 
	float output;				/* output after activation					 */ 
	float deltaOutput;			/* error in output layer (for backpro)		 */ 
	float lrate;				/* learning rate. Value depends on condition */ 	
	bool omega;					/* omega w, true social learning (SL), false
								   asocial learning (IL)					 */ 
	float phi;					/* streght of learning in range [0, 1]		 */ 
	int myArray[IN_X][LENGTH_BIN];	/* stores genes (weights of GA) in binary*/ 
	int phiArray[1][LENGTH_BIN];    /* stores phi in binary					 */ 
	float mutationRate;			/* mutation rate of wegihts inheritance in GA*/
	float omegaMutRate;			/* mutation rate of omega (mixed learning Mx)*/
	float neighbors;			/* number of neighbors in same area			 */
	float backproLearningRate;	/* learning rate used in backpro. Value changes
									depending on condition					 */ 
		
public:
/*-----------------------------------------------------------------------------
 *                         CONSTRUCTORS:
 *---------------------------------------------------------------------------*/	
 Perceptron();
/*-----------------------------------------------------------------------------
 *                  OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/	
/*----------------------------------------------------------------------------- 
 * Function name:         readInputs
 *  
 * Reads inputs from ground sensor (ground color)  
 *---------------------------------------------------------------------------*/
 void readInputs(float inXs[IN_X]); /* copy input from inXs[] to class variable
 									   input[]								 */
 									   
/*----------------------------------------------------------------------------- 
 * Function name:           feedForward
 *  
 *   Runs Perceptron from input to output, including activation of output
 *   
 *---------------------------------------------------------------------------*/
 void feedForward();
 
/*----------------------------------------------------------------------------- 
 * Function name:           sigmoid
 *  
 *   Sigmoid as activation function.
 *   It returns the value in the range (0, 1).
 *---------------------------------------------------------------------------*/
 float sigmoid(float e);			/* apply sigmoid of e f(e)				 */
 
/*----------------------------------------------------------------------------- 
 * Function name:           sigmoidDeriv
 *  
 *   Return the derivation of Sigmoid function:
 *      f(e)' = f(e)*(1 - f(e))     
 *---------------------------------------------------------------------------*/
 float sigmoidDeriv(float sigmoid);	/* derivative of sigmoid f'(sigmoid)	 */
 
/*----------------------------------------------------------------------------- 
 * Function name:           backPropagation
 *  
 *   Back propagates the error through the network and re-initializes all
 *   the weights.
 *   
 *   It is possible to use zero as target. Or apply as Acerbi et al 2007,
 *	  adding random value within (-lrate, +lrate) to weights
 *---------------------------------------------------------------------------*/
  void backPropagation(float target);	/* given target, example target = 0.0*/
  
/*----------------------------------------------------------------------------- 
 * Function name:        setBinaryGenes
 *
 *	Used in Genetic Algorithm for setting weight values as genes in binary
 *---------------------------------------------------------------------------*/
void setBinaryGenes();

/*----------------------------------------------------------------------------- 
 * Function name:        GAWeights
 *
 *	Translate binary genes to decimals and values are store in weights matrix
 *---------------------------------------------------------------------------*/		
void GAWeights();

/*----------------------------------------------------------------------------- 
 * Function name:        mutateWeights
 *
 *	Mutate weights. Usually during inheritance
 *---------------------------------------------------------------------------*/	
void mutateWeights();

/*----------------------------------------------------------------------------- 
 * Function name:        setPhiGenes
 *
 * Set random phi genes in binary
 *---------------------------------------------------------------------------*/
void setPhiGenes();

/*----------------------------------------------------------------------------- 
 * Function name:        setPhiFromGenes
 *
 *	Translate phi from binary to decimal and store in class variable phi
 *---------------------------------------------------------------------------*/		
void setPhiFromGenes();

/*----------------------------------------------------------------------------- 
 * Function name:        mutatePhi
 *
 *	Mutate phi. Usually during inheritance
 *---------------------------------------------------------------------------*/	
void mutatePhi();

/*----------------------------------------------------------------------------- 
 * Function name:        mutateOmega
 *
 *	Mutate omega. Usually during inheritance
 *---------------------------------------------------------------------------*/	
void mutateOmega();

/*----------------------------------------------------------------------------- 
 * Function name:        BinToDecimal
 *
 *	Convert from binary to decimal
 *---------------------------------------------------------------------------*/	
int BinToDecimal(int myArray[][LENGTH_BIN],	/* array of binaries of length
											   LENGTH_BIN 					 */
 				 int g);					/* and ID g						 */
 				 
/*----------------------------------------------------------------------------- 
 * Function name:         DecimaltoBinary
 *  
 * Convert decimal to binary and stores in array
 *   
 *---------------------------------------------------------------------------*/ 
void DecimalToBinary(int number,				/* decimal for converting	 */
					 int myArray[][LENGTH_BIN], /* array to store in binary	 */
					 int g);					/* ID of where to store
					 							   converted decimal value in
												   the array				 */
												   
/*----------------------------------------------------------------------------- 
 * Function name:        startIndividualLearning
 *
 *	  Set weights and learning rate according to Acerbi et al 2007, for
 *	  individual learning. value represent the desired value for lrate
 *	
 *	  Weights are set to non-preference
 *---------------------------------------------------------------------------*/
 void startIndividualLearning(float learningRate);	/* desired learning rate */
 
/*----------------------------------------------------------------------------- 
 * Function name:        runIndividualLearning
 *
 *	  Changes weigth values using backpropagation
 *---------------------------------------------------------------------------*/
 void runIndividualLearning(float target);		/* given target				 */
 
/*----------------------------------------------------------------------------- 
 * Function name:        startSocialLearning
 *
 *	  Set weights according to Acerbi et al 2007, for  social learning, i. e.
 *	  non-preference
 *
 *---------------------------------------------------------------------------*/
 void startSocialLearning(float learningRate); 		/* desired learning rate */
 
/*----------------------------------------------------------------------------- 
 * Function name:        runSocialLearning
 *
 *	  Set learning rate as a linear function of number of neighbors occuping 
 * 	  the same feeding site 
 *---------------------------------------------------------------------------*/
 void runSocialLearning(float target);	/* given target, example target = 0.0*/
 
/*----------------------------------------------------------------------------- 
 * Function name:        startGeneticEvolution
 *
 *	  Starts a Genetic Algorithms with weights in binary and mutation = rate
 *	  Dying robots inherit their weights from the one with greater energy
 *---------------------------------------------------------------------------*/
 void startGeneticEvolution(float rate);	/* desired mutation rate		 */
 
/*----------------------------------------------------------------------------- 
 * Function name:        runGeneticEvolution
 *		w = values [-3, 3]
 *
 *	  IMPORTANT!!
 *	  Dying robots inherit their weights from the one with greater energy
 *---------------------------------------------------------------------------*/
 void runGeneticEvolution();
 
/*----------------------------------------------------------------------------- 
 * Function name:        startRandomSearch
 *		w = values (-3, 3)
 *
 *	  Weights are set randomly at starting as well as for newborn robots
 *	  in the range (-value, +value)
 *---------------------------------------------------------------------------*/
 void startRandomSearch(float value);	/* set weight range	(- value, value) */ 
 
/*----------------------------------------------------------------------------- 
 * Function name:        runRandomSearch
 *
 *	  Applies feedforward to perceptron. Weights are set randomly to newborns
 *---------------------------------------------------------------------------*/
 void runRandomSearch();
 
/*----------------------------------------------------------------------------- 
 * Function name:        startMixedLearning
 *
 *	  Weights are set to noPreference. The parameters omega (which indicates if
 *	  robot relies also in social cues) and phi (streght of learning) are
 *	  randomly set, omega (0 or 1); phi [0, 1]
 *
 *	  default: omega is randomly set. Otherwise change omega values using
 *	  setOmega()
 *---------------------------------------------------------------------------*/
 void startMixedLearning(float mutRateOmega,	/* mutation rate for omega	 */
  						 float mutRatePhi); 	/* mutation rate for phi	 */
 
/*----------------------------------------------------------------------------- 
 * Function name:        runMixedLearning
 *
 *	  calculates backprolearningRate depending on parameters value. 
 *	  if omega = false (i. e. omega == 0),
 *	  backproLearningRate = phi. If omega = true; 
 *	  backproLearningRate = phi*signal intensity, which depends
 *	  on number of robots located in the same foraging area.
 *---------------------------------------------------------------------------*/
 void runMixedLearning(float target);	/* given target, example target = 0.0*/
 
/*----------------------------------------------------------------------------- 
 * Function name:        set and get functions
 *---------------------------------------------------------------------------*/
 float getOutput();					/* return perceptron output after 
 									   activation							 */
 float getOmega();					/* return current value of omega		 */
 float getPhi();					/* return current value of phi			 */
 int getNeighbors();				/* return actual number of neighbors	 */
 void setPhi(float learningRate);	/* set desired laerning rate for phi	 */
 void setNeighbors(int number);		/* set number of neighbors				 */
 void setNoPreference();			/* reset weight values to non-preference */
 void setOmega(bool w);				/* set desired value for omega			 */
}; 
#endif
