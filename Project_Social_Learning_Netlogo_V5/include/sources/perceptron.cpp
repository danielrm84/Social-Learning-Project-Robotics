/*-----------------------------------------------------------------------------
 *                      	CLASS PERCEPTRON
 *
 * Author:      Daniel Romero Mujalli
 * Written:     17/ 2/2013
 * Last update:  5/11/2013
 *
 * Summary:      Definition of Member and functions of Class Perceptron.
 *               According to Acerbi et al. 2007.
 *                  
 *               Details about this class in perceptron.h
 * 
 *---------------------------------------------------------------------------*/
//		Libraries:
#include "../miscellaneous/miscellaneous.h"
using namespace std;
/*-----------------------------------------------------------------------------
 *  CONSTRUCTORS:
 *	       
 *---------------------------------------------------------------------------*/
 Perceptron::Perceptron(){}
/*-----------------------------------------------------------------------------
 *  MEMBERS AND FUNCTIONS       
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------- 
 * Function name:         readInputs
 *---------------------------------------------------------------------------*/
 void Perceptron::readInputs(float inXs[IN_X])    
 {
  	int rows = IN_X;	

   	for (int i = 0; i < rows; ++i)
   	{
	   /* No bias											 				 */ 		
 		input[i] = inXs[i];
   	}	
 }
/*----------------------------------------------------------------------------- 
 * Function name:         feedForward
 *---------------------------------------------------------------------------*/
void Perceptron::feedForward()
{
	int rows = IN_X;

	e = 0; /* initialization												 */ 
	for(int i = 0; i < rows; i++)
	{
		e = input[i]*weights[i] + e;
	}
	output = sigmoid(e);
}

/*----------------------------------------------------------------------------- 
 * Function name:         sigmoid
 *---------------------------------------------------------------------------*/
float Perceptron::sigmoid(float e)
{ 
	float maxS = 0.91;
	float minS = 0.099;
	float sigmoid;	
/*-----------------------------------------------------------------------------
 *         Apply sigmoid:
 *---------------------------------------------------------------------------*/
	sigmoid = (1.0/(1.0 + exp(-e)));		
/*-----------------------------------------------------------------------------
 *          Exploring xs limits of the sigmoid function
 *---------------------------------------------------------------------------*/
	if(sigmoid < minS)     { return  sigmoid = 0.0;}	/* linearVel goes 0	 */ 
	else if(sigmoid > maxS){ return  sigmoid = 1.0;}	/* lv stay the same  */ 
	else 			       { return  sigmoid;      }
}

/*----------------------------------------------------------------------------- 
 * Function name:        sigmoidDeriv
 *---------------------------------------------------------------------------*/
float Perceptron::sigmoidDeriv(float sigmoid)
{
	float result;

	result = sigmoid*(1 - sigmoid);

	return result;
}

/*----------------------------------------------------------------------------- 
 * Function name:        backPropagation
 *---------------------------------------------------------------------------*/
void Perceptron::backPropagation(float target)
{
/*-----------------------------------------------------------------------------
 *		Output error:
 *---------------------------------------------------------------------------*/
	deltaOutput = target - output;
	
/*-----------------------------------------------------------------------------
 *		Next input weights. 
 *		
 * 		wij' = wij + lrate*delta*sigmoidDerivative*activated_i
 *---------------------------------------------------------------------------*/	
	int rows = IN_X;

    for(int i = 0; i < rows; i++)
	{	
		weights[i] = weights[i] + backproLearningRate*deltaOutput*
			             sigmoidDeriv(output)*input[i];	
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:        setBinaryGenes
 *---------------------------------------------------------------------------*/
void Perceptron::setBinaryGenes()
{
	float r;
	bool done;
	int nGenes = IN_X;
	int length = LENGTH_BIN;

	for (int g = 0; g < nGenes; g++)
	{
		done = false;
		do
		{
			for (int l = 0; l < length; l++)
			{
				r = rand()/(RAND_MAX + 1.0);
				if(r >= 0.5){myArray[g][l] = 1;}
				else{myArray[g][l] = 0;}
			}
			
			if(BinToDecimal(myArray, g) <= MAX_VALUE){done = true;}
			
		}while(done == false);	
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:        GAWeights
 *---------------------------------------------------------------------------*/		
void Perceptron::GAWeights()
{
	int nGenes = IN_X;
	float ctte = 100000; /* Allows to get fraction numbers after convertion 
							from binary to decimals 						 */ 
						 
	float w;
	for (int g = 0; g < nGenes; ++g)
	{
		w = (BinToDecimal(myArray, g)/ctte)- MIN_W;
		weights[g] = w;
	}
}
/*----------------------------------------------------------------------------- 
 * Function name:        mutateWeights
 *---------------------------------------------------------------------------*/	
void Perceptron::mutateWeights()
{
	float r;
	int nGenes = IN_X;
	int length = LENGTH_BIN; 
	
	for (int g = 0; g < nGenes; g++)
	{
		for (int l = 0; l < length; l++)
		{
			r = rand()/(RAND_MAX + 1.0);
			
			if(r <= mutationRate)
			{
				if(myArray[g][l]){myArray[g][l] = 0;}
				else{myArray[g][l] = 1;}
			}
		}
	}
	GAWeights();
}
/*----------------------------------------------------------------------------- 
 * Function name:        setPhiGenes
 *---------------------------------------------------------------------------*/
void Perceptron::setPhiGenes()
{
	float r;
	bool done;
	int nGenes = 1;
	int length = LENGTH_BIN;

	for (int g = 0; g < nGenes; g++)
	{
		done = false;
		do
		{
			for (int l = 0; l < length; l++)
			{
				r = rand()/(RAND_MAX + 1.0);
				if(r >= 0.5){phiArray[g][l] = 1;}
				else{phiArray[g][l] = 0;}
			}
			if(BinToDecimal(phiArray, g) <= MAX_Phi){done = true;}
		}while(done == false);	
	}
}
/*----------------------------------------------------------------------------- 
 * Function name:        setPhiFromGenes
 *---------------------------------------------------------------------------*/		
void Perceptron::setPhiFromGenes()
{
	int nGenes = 1;
	float ctte = 100000; /* Allows to get fraction numbers after convertion 
							from binary to decimals 						 */ 
						 
	for (int g = 0; g < nGenes; ++g)
	{
		phi = (BinToDecimal(phiArray, g)/ctte);
		
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:        mutatePhi
 *---------------------------------------------------------------------------*/	
void Perceptron::mutatePhi()
{
	float r;
	int nGenes = 1;
	int length = LENGTH_BIN; 
	
	for (int g = 0; g < nGenes; g++)
	{
		for (int l = 0; l < length; l++)
		{
			
			r = rand()/(RAND_MAX + 1.0);
			
			if(r <= mutationRate)
			{
				if(phiArray[g][l]){phiArray[g][l] = 0;}
				else{phiArray[g][l] = 1;}
			}
			
		}
	}
	setPhiFromGenes();
}

/*----------------------------------------------------------------------------- 
 * Function name:        mutateOmega
 *---------------------------------------------------------------------------*/	
void Perceptron::mutateOmega()
{
	float r;
	
	r = rand()/(RAND_MAX + 1.0);
	if(r <= omegaMutRate)
	{
		if(omega){omega = false;}
		else{omega = true;}
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:        BinToDecimal
 *---------------------------------------------------------------------------*/	
int Perceptron::BinToDecimal(int myArray[][LENGTH_BIN], int g)
{
	int length  = LENGTH_BIN;
	int decimal = 0;	
	
	for (int l = 0; l < length; l++)
	{
		if(myArray[g][l])
		decimal += int(pow(double(2), l));
	}
	
	return decimal;
}

/*----------------------------------------------------------------------------- 
 * Function name:        DecimalToBinary
 *---------------------------------------------------------------------------*/	
void DecimalToBinary(int number, int myArray[][LENGTH_BIN], int g)
{
	int length = LENGTH_BIN;

	for (int l = 0; l < length; l++)
	{
		myArray[g][l] = number % 2;
		number /=2;
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:        startIndividualLearning
 *---------------------------------------------------------------------------*/
 void Perceptron::startIndividualLearning(float learningRate)
 {
 	int rows = IN_X;
/*-----------------------------------------------------------------------------
 *		Weights initialization --> Null values
 *---------------------------------------------------------------------------*/
 	for (int i = 0; i < rows; i++){weights[i] = noPreference;}

/*-----------------------------------------------------------------------------
 *		set Learning rate = learningRate: 0.1 or 1.0
 *---------------------------------------------------------------------------*/
 	lrate = learningRate;
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        runIndividualLearning
 *---------------------------------------------------------------------------*/
 void Perceptron::runIndividualLearning(float target)
 {
 	backproLearningRate = lrate;
 	feedForward();
 	backPropagation(target);
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        startSocialLearning
 *---------------------------------------------------------------------------*/
 void Perceptron::startSocialLearning(float learningRate)
 {
 	int rows = IN_X;
 	
/*-----------------------------------------------------------------------------
 *		Weights initialization --> Non-preference
 *---------------------------------------------------------------------------*/
 	for (int i = 0; i < rows; i++){weights[i] = noPreference;}

 	lrate = learningRate;
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        runSocialLearning
 *---------------------------------------------------------------------------*/
 void Perceptron::runSocialLearning(float target)
 {
/*-----------------------------------------------------------------------------
 * set backpro Learning rate = value depends on neighbors in same feeding area
 *---------------------------------------------------------------------------*/
 	backproLearningRate = float(lrate*neighbors);
 	
/*-----------------------------------------------------------------------------
 *		runs perceptron and sets new weights
 *---------------------------------------------------------------------------*/
 	feedForward();
 	backPropagation(target);
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        startGeneticEvolution
 *---------------------------------------------------------------------------*/
 void Perceptron::startGeneticEvolution(float rate)
 {
 	int rows = IN_X;
 	mutationRate = rate;
 	
 	for (int i = 0; i < rows; i++)
 	{
 		setBinaryGenes();
 		GAWeights();
 	}
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        runGeneticEvolution
 *---------------------------------------------------------------------------*/ 
 void Perceptron::runGeneticEvolution(){ feedForward(); }
 
/*----------------------------------------------------------------------------- 
 * Function name:        startRandomSearch
 *---------------------------------------------------------------------------*/ 
 void Perceptron::startRandomSearch(float value)
 {
 	int rows = IN_X;
 	
 	for (int i = 0; i < rows; i++)
 	{
 		weights[i] = -value + (2.0*value*rand()/(RAND_MAX + 1.0));
 	}
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        runRandomSearch
 *---------------------------------------------------------------------------*/
 void Perceptron::runRandomSearch(){ feedForward(); } 
 
/*----------------------------------------------------------------------------- 
 * Function name:        startMixedLearning
 *---------------------------------------------------------------------------*/
 void Perceptron::startMixedLearning(float mutRateOmega, float mutRatePhi)
 {
 	omegaMutRate = mutRateOmega; /* Marocco y Acerbi 2007 uses 10%			 */ 
 	mutationRate = mutRatePhi;
 	
 	int rows = IN_X;
/*-----------------------------------------------------------------------------
 *		Weights initialization --> Null values
 *---------------------------------------------------------------------------*/
 	for(int i = 0; i < rows; i++){weights[i] = noPreference;}
/*-----------------------------------------------------------------------------
 *		Random set of parameters omega (social or asocial) and phi (strenght)
 *---------------------------------------------------------------------------*/
	float rn;
	
	/* omega:																 */ 
	rn = rand()/(RAND_MAX + 1.0);
	if(rn >= 0.5){ omega = true;}
	else{omega = false;}
 }   
 
/*----------------------------------------------------------------------------- 
 * Function name:        runMixedLearning
 *---------------------------------------------------------------------------*/
 void Perceptron::runMixedLearning(float target)
 {

/*-----------------------------------------------------------------------------
 *		set backpro Learning rate. Depends on neighbors in same feeding site, 
 *	and parameters omega and phi
 *---------------------------------------------------------------------------*/
 	if(omega){backproLearningRate = float(phi*neighbors);}
 	else{backproLearningRate = phi;}
/*-----------------------------------------------------------------------------
 *		runs perceptron and sets new weights
 *---------------------------------------------------------------------------*/
 	feedForward();
 	backPropagation(target);	
 }
 
/*----------------------------------------------------------------------------- 
 * Function name:        set and get functions
 *---------------------------------------------------------------------------*/
 float Perceptron::getOutput(){return output;}
 float Perceptron::getOmega(){return omega;}
 float Perceptron::getPhi(){return phi;}
 int Perceptron::getNeighbors(){return neighbors;}
 void Perceptron::setPhi(float learningRate){ phi = learningRate; }
 void Perceptron::setNeighbors(int number){neighbors = number;}
 void Perceptron::setNoPreference()
 {
 	int rows = IN_X;
 	for(int i = 0; i < rows; i++){weights[i] = noPreference;}
 }
 void Perceptron::setOmega(bool w)
 {
 	omega = w;
 }
