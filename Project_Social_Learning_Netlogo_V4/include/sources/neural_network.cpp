/*-----------------------------------------------------------------------------
 *                      CLASS NEURAL NETWORK
 *
 * Author:      Daniel Romero Mujalli
 * Written:     13/12/2012
 * Last update: 20/ 3/2013
 *
 * Summary:      In this file are defined the member
 *               functions and methods of class NeuralNetwork.
 *               See class NeuralNetwork in neural_network.h.
 *				 The network uses Bias X0 = 1
 *		  If abs(min) != abs(max){ modify random number generators!}
 *---------------------------------------------------------------------------*/
//		Libraries:
#include "../miscellaneous/miscellaneous.h"
 using namespace std;
/*-----------------------------------------------------------------------------
 *					Member and methods definition
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *  CONSTRUCTORS:
 *	
 * 			Basically, only the matrices of weights W are initialized
 *	   		The input variables comes from the sensors, from the main        
 *---------------------------------------------------------------------------*/
NeuralNetwork::NeuralNetwork(){} /* default out*/

NeuralNetwork::NeuralNetwork(float min, float max)
{
	lrate  = NN_LEARNING_RATE; /* default										 */ 
	minW   = min;
	maxW   = max;
	
	setRandomWeights(minW, maxW);

}	

/*-----------------------------------------------------------------------------
 *                  OTHER MEMBER FUNCTIONS AND METHODS
 *---------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------- 
 * Function name:         setRandomWeights
 *  
 *   Set random weights to connect layers of the neural network
 *
 *	 Important! : Include the bias	
 *	 the relation of min and max must be for example like:
 *   min = -10 max = 20 to generate random values between (-10; 10)   
 *---------------------------------------------------------------------------*/
void NeuralNetwork::setRandomWeights(float min, float max)
{
	int rows, columns;
	
	if(HIDDEN == 0)
	{
		rows = XsINPUT + 1;
		columns = OUTPUT;
		
		for(int i = 0; i < rows; i++)
		{	
			for(int j = 0; j < columns; j++)
			{
				W[i][j] = min + (2.0*max)*rand ()/(RAND_MAX + 1.0);
			}
		}
		
	} else{
			rows    = XsINPUT + 1;
			columns = HIDDEN;
			
			for(int i = 0; i < rows; i++)
			{	
				for(int j = 0; j < columns; j++)
				{
					inW[i][j] = min + (2.0*max)*rand ()/(RAND_MAX + 1.0);
				}
			}
			
			setOutWeights(min, max);
		  }
	
} 	

/*-----------------------------------------------------------------------------
 * Function name:          setOutWeights
 *  
 * 	 Initializes the matrix of weights outW[][] which is used in calculating
 * 	 the values for the output layer 
 *   rows    : number of hidden layer neurons or new variables
 *	 columns : number of neurons in the output layer
 *
 *	 Important! : HIDDEN + 1, to calculate Bias from HIDDEN to OUTPUT
 *   the relation of min and max must be for example like:
 *   min = -10 max = 20 to generate random values between (-10; 10)  
 *---------------------------------------------------------------------------*/
void NeuralNetwork::setOutWeights(float min, float max)
{
	int rows    = HIDDEN + 1; 
	int columns = OUTPUT;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			 outW[i][j] = min + (2.0*max)*rand ()/(RAND_MAX + 1.0);
		}
	}
}
/*-----------------------------------------------------------------------------
 * Function name:          setWeightsFromGA
 *  
 * 	 Initializes the matrix of weights inW and outW from a Genetic Algorithm
 * 	 See Genetic_Algorithm.h
 *   
 *	 The function fills the input and output weight matrixes of the NN from
 *	 two vectors (input and hidden)
 *
 *	 As vector, is the way weights are stored from GA.
 *
 *   BIAS is included for both input and hidden.
 *
 *   min = -10 max = 10 according to Acerbi et al. 2007.
 *
 *	 It could be change in GA class (Genetic_Algorithm.h and *.cpp).  
 *---------------------------------------------------------------------------*/
void NeuralNetwork::setWeightsFromGA(float *vector)
{
	int m = 0;
	int rows    = XsINPUT + 1;
	int columns = OUTPUT;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			W[i][j] = vector[m];
			m++;
		}
	}

}

void NeuralNetwork::setWeightsFromGA(float *input, float *hidden)
{
	int m = 0;
	int rows    = XsINPUT + 1;
	int columns = HIDDEN;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			inW[i][j] = input[m];
			m++;
		}
	}
	
	rows    = HIDDEN + 1; 
	columns = OUTPUT;
	
	m = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			outW[i][j] = hidden[m];
			m++;
		}
	}

}
/*----------------------------------------------------------------------------- 
 * Function name:         getWeights
 *  
 * get NN weights into vector (*W)    
 *---------------------------------------------------------------------------*/
void NeuralNetwork::getWeights(float *vector)
{
	int m = 0;
	int rows = XsINPUT + 1;
	int columns = OUTPUT;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			vector[m] = W[i][j]; 
			m++;
		}
	}
}
/*----------------------------------------------------------------------------- 
 * Function name:         getWeightsThreeLayersNN
 *  
 * get NN weights into vectors (input/ output)    
 *---------------------------------------------------------------------------*/
void NeuralNetwork::getWeights(float *input, float *hidden)
{
   	int m = 0;
	int rows = XsINPUT + 1;
	int columns = HIDDEN;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			input[m] = inW[i][j]; 
			m++;
		}
	}
	
	rows    = HIDDEN + 1; 
	columns = OUTPUT;
	
	m = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			hidden[m] = outW[i][j];
			m++;
		}
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:         setWeightsFromFileThreeLayersNN
 *  
 * It is important first to store values into vectors and then pass them
 * through this function. Vectors store all the values for N=10 NN from file.
 * m and h are used as control variables to point the right position in both 
 * vectors
 *---------------------------------------------------------------------------*/
void NeuralNetwork::setWeightsFromFile(float vector[], int &m)
{
	int rows    = XsINPUT + 1;
	int columns = OUTPUT;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			W[i][j] = vector[m];
			m++;
		}
	}
}
/*----------------------------------------------------------------------------- 
 * Function name:         setWeightsFromFileThreeLayersNN
 *  
 * It is important first to store values into vectors and then pass them
 * through this function. Vectors store all the values for N=10 NN from file.
 * m and h are used as control variables to point the right position in both 
 * vectors
 *---------------------------------------------------------------------------*/
void NeuralNetwork::setWeightsFromFile(float input[], float hidden[], int &m,
    								   int &h)
{
	int rows    = XsINPUT + 1;
	int columns = HIDDEN;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			inW[i][j] = input[m];
			m++;
		}
	}
	
	rows    = HIDDEN + 1; 
	columns = OUTPUT;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			outW[i][j] = hidden[h];
			h++;
		}
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:           readInputs
 *  
 *   Read inputs to NN, form a vector
 *
 *	 Important! : rows = XsINPUT + 1, for the BIAS --> X0 = 1      
 *---------------------------------------------------------------------------*/
void NeuralNetwork::readInputs(float inXs[XsINPUT])    
{
   	int rows = XsINPUT + 1;
   	int j    = 0;
   	
   	for (int i = 0; i < rows; ++i)
   	{
   		if(i == 0){ input[i] = 1; } /* set bias							 */
    		
   		else
   			{ input[i] = inXs[j]; j++;}
   	}	
}

/*----------------------------------------------------------------------------- 
 * Function name:           feedForward
 *  
 *   Runs the NeuralNetwork from input to output. It returns right and left
 *   velocities of agent wheels using pointers
 *   rows    : number of variables
 *	 columns : number of neurons in the next layer
 *---------------------------------------------------------------------------*/

void NeuralNetwork::feedForward()
{
	int rows, columns;
	float neuron;
	int m;
	
	if(HIDDEN == 0)
	{
		rows    = XsINPUT + 1;
		columns = OUTPUT;
	
		for(int i = 0; i < columns; i++){e[i] = 0;} /* initialization			 */

		for(int j = 0; j < columns; j++)
		{	
			for(int i = 0; i < rows; i++)
			{
				e[j] = input[i]*W[i][j] + e[j];
			}
		}
	}
	else 
	{
		rows    = XsINPUT + 1;
		columns = HIDDEN;
	
/*-----------------------------------------------------------------------------
 *	 this loop calculates the hidden layer as a function of the input variables
 *	 (stored in input[] ) and their weights inW[][]
 *
 *   hiddeLayer is the matrix of X' variables in the next layer
 *   HIDDEN + 1, because of the BIAS in the hidden layer
 *---------------------------------------------------------------------------*/  
    	m = 0;

    	hiddenLayer[m] = 1;		/* set Bias										 */
    
		for(int j = 0; j < columns; j++)
		{
			m++;
			neuron = 0;
			for(int i = 0; i < rows; i++)
			{
				neuron = input[i]*inW[i][j]	+ neuron;
			}
			hiddenLayer[m] = sigmoid(neuron);
		}

/*-----------------------------------------------------------------------------	 
 *    Next loop calculates the output e (2 outputs), which then is sent to the
 *	  activation function (sigmoid). It uses the hiddenlayer[] vector
 *	  calculated previously times their weights outW[][]
 *---------------------------------------------------------------------------*/
		rows    = HIDDEN + 1;
		columns = OUTPUT;
	
		for(int i = 0; i < columns; i++){e[i] = 0;} /* initialization			 */

		for(int j = 0; j < columns; j++)
		{	
			for(int i = 0; i < rows; i++)
			{
				e[j] = hiddenLayer[i]*outW[i][j] + e[j];
			}
		}	
	}	
}

/*----------------------------------------------------------------------------- 
 * Function name:           sigmoid
 *  
 *   Activation function wich apply sigmoid to the output of the nNetwork.
 *   e is the raw output from the network that can be re-sclaed. Here the 
 *   Sigmoid function output in the range (0, 1).
 *
 *	 One should take into account that Sigmoid function ranges within the open
 *   interval of (0, 1). So limits were added
 *---------------------------------------------------------------------------*/
float NeuralNetwork::sigmoid(float e)
{ 
	float maxS = 0.99;		/* maximum value allowed as function output		 */
	float minS = 0.01;		/* minimum value allowed as function output		 */
	float sigmoid;
	
/*-----------------------------------------------------------------------------
 *         Apply sigmoid:
 *---------------------------------------------------------------------------*/
		sigmoid = (1.0/(1.0 + exp(-e)));
		
/*-----------------------------------------------------------------------------
 *          Exploring limits of the sigmoid function
 *---------------------------------------------------------------------------*/
	if(sigmoid < minS)     { return  sigmoid = minS;}
	else if(sigmoid > maxS){ return  sigmoid = maxS;}
	else 			       { return  sigmoid;    	}
}

/*----------------------------------------------------------------------------- 
 * Function name:           sigmoidDeriv
 *  
 *   Return the derivation of Sigmoid function:
 *   	f(e)' = f(e)*(1 - f(e))  
 *    
 *---------------------------------------------------------------------------*/
float NeuralNetwork::sigmoidDeriv(float sigmoid)
{
	float result;

	result = sigmoid*(1 - sigmoid);

	return result;
}

/*----------------------------------------------------------------------------- 
 * Function name:           runAgentNeuralNetwork
 *  
 *   This execute the neural network functions and output agent left and
 *   right velocities. Here the sigmoid function has been scale to output in
 *   the range (-0.5, 0.5) in such a way that allows to output positive and 
 *   negative volicity for the agent wheels
 *
 *	 If you want to run the network for something not related to agent
 *   navigation with wheels, then avoid using this function 
 *   
 *---------------------------------------------------------------------------*/
void NeuralNetwork::runAgentNeuralNetwork(float &rightVel, float &leftVel)
{
	float scaling  =  0.5; 
	float maxVel   = 10.0;

/*----------------------------------------------------------------------------- 
 * 	Runs the neural network (only two outputs => wheels):
 *  	 agent velocity within the range (-10, 10)
 *---------------------------------------------------------------------------*/
 	/* Calculating left velocity and storing to output for calculating error */
 	int j = 0;
 	
	feedForward();
	
	leftVel   = 2.0*(sigmoid(e[j]) - scaling) * maxVel;
	
	output[j] = leftVel;
	
	if(abs(leftVel) < 0.001){leftVel = 0.0;}

	/* Calculating right velocity and storing to output for calculating error*/
	j++;
	 
	rightVel  = 2.0*(sigmoid(e[j]) - scaling) * maxVel;
	
	output[j] = rightVel;
	
	if(abs(rightVel) < 0.001){rightVel = 0.0;}

}

/*----------------------------------------------------------------------------- 
 * Function name:           backPropagation
 *  
 *   Back propagates the error through the network and re-initializes all the
 *   weights, and also affects the BIAS.
 *   		    rows   --> variables (i)
 *    		   columns --> neurons   (j)
 *---------------------------------------------------------------------------*/
void NeuralNetwork::backPropagation(float *target)
{
	int rows, columns;
	int m;
	float error;
/*-----------------------------------------------------------------------------
 *		Output error:
 *---------------------------------------------------------------------------*/
	columns = OUTPUT;
	
	/* calculate output error according to given target						 */
	for(int j = 0; j < columns; j++){ deltaOutput[j] = target[j] - output[j];} //cout << "target " << target[j] << " output " << output[j] << endl;}


	if (HIDDEN == 0)
	{
		rows    = XsINPUT + 1;
	 	columns = OUTPUT;
 	
	 	for(int j = 0; j < columns; j++)
		{	
			for(int i = 0; i < rows; i++)
			{
				W[i][j] = W[i][j] + lrate*deltaOutput[j]*
				             sigmoidDeriv(sigmoid(e[j]))*input[i];
			}
    	}
	}
	else
	{
/*-----------------------------------------------------------------------------
 *		Hidden layer errors. 
 *		
 * 		Propagates the error delta. Also affects the BIAS
 *---------------------------------------------------------------------------*/
		rows = HIDDEN + 1;
    	m = 0; 	/* counter of hidden layer neurons in deltaHidden matrix	 */
	
	/* initialization														 */
    	for(int i = 0; i < rows; i++){ deltaHidden[i] = 0; }
	
	/* calculate propagated error											 */
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				deltaHidden[m] = outW[i][j]*deltaOutput[j] + deltaHidden[m];
			}
			m++;
		}
/*-----------------------------------------------------------------------------
 *		Next hidden weights:
 * 		wij' = wij + lrate*delta*sigmoidDerivative*activated_i
 *---------------------------------------------------------------------------*/
	 	rows    = HIDDEN + 1;
	 	columns = OUTPUT;
 	
	 	for(int j = 0; j < columns; j++)
		{	
			for(int i = 0; i < rows; i++)
			{
				outW[i][j] = outW[i][j] + lrate*deltaOutput[j]*
				             sigmoidDeriv(sigmoid(e[j]))*hiddenLayer[i];
			}
    	}
/*-----------------------------------------------------------------------------
 *		Next input weights. 
 *		
 * 		wij' = wij + lrate*delta*sigmoidDerivative*activated_i
 *---------------------------------------------------------------------------*/
		columns = HIDDEN;	
		rows    = XsINPUT + 1;

    	for(int i = 0; i < rows; i++)
		{	
			m = 1; /* counts activated hidden neurons number in hiddenLayer[]    */
			for(int j = 0; j < columns; j++)
			{
				inW[i][j] = inW[i][j] + lrate*deltaHidden[j]*
				             sigmoidDeriv(hiddenLayer[m])*input[i];
				m++;		
			}
		}
	}
}

/*----------------------------------------------------------------------------- 
 * Function name:        set and get functions
 *---------------------------------------------------------------------------*/
/* Get the output error. This is the error after checking with given target.
   Values are stored using a pointer										 */
void NeuralNetwork::getOutputError(float *error)
{
	for(int i = 0; i < OUTPUT; i++)
	{
		error[i] = deltaOutput[i];
	}
}

/* Set a desired learning rate. Default is 0.001							 */
void NeuralNetwork::setLearningRate(float rate){lrate = rate;}

/* get actual learning rate													 */
float NeuralNetwork::getLearningRate(){return lrate;}
