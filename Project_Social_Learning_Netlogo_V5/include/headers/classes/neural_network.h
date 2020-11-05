/*-----------------------------------------------------------------------------
 *                      	CLASS NEURAL NETWORK
 *
 * Author:      Daniel Romero Mujalli
 * Written:     12/12/2012
 * Last update: 20/ 3/2013
 *
 * Summary:      In this file is defined the class NeuralNetwork along with
 *               its members, methods and variables.   
 *               For definitions of its members see neural_network.cpp
 *
 *               This class build a neural network of the kind:
 *               "multiple layer perceptron". It is composed of 3 layers:
 *               one input, one hidden and one output layer, with fixed
 *               neurons number XsINPUT, HIDDEN, OUTPUT respectively
 *
 *               Default learning rate = 0.001
 *---------------------------------------------------------------------------*/
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H 
/*-----------------------------------------------------------------------------
 *                        THE CLASS STARTS
 *---------------------------------------------------------------------------*/
class NeuralNetwork {

private:
                       
    
	float W[XsINPUT + 1][OUTPUT];	 /* weights of 2 layers NN				 */
	/* 3 layer NN use inW and outW											 */ 
	float inW[XsINPUT + 1][HIDDEN];  /* 1st weights matrix  W (input to hidden)
                                                                             */  
    float outW[HIDDEN + 1][OUTPUT];  /* Next weights matrix W' hidden to output
                                                                             */ 
    float input[XsINPUT + 1];        /* matrix of XsINPUT + bias variables   */ 
    float hiddenLayer[HIDDEN + 1];   /* Store hidden layer neuron values after
                                        activation                           */
    float minW, maxW;                /* range of weights values				 */ 
    float e[OUTPUT];                 /* stores the output e from the neural 
                                        network after feed forward           */ 
    float output[OUTPUT];            /* stores the output of the network     */
    float deltaOutput[OUTPUT];       /* errors of output layer               */
    float deltaHidden[HIDDEN];       /* errors of hidden layer               */
    /*Next variable store the outputs for each neuron in the hidden layer
      Bias included. This is used in backpropagating                         */
    float storeHiddenOutput[HIDDEN + 1][OUTPUT]; 
    float lrate;                     /* Learning rate                        */
                                    
public:
	/*-------------------------------------------------------------------------
     *                  		CONSTRUCTORS:
     *-----------------------------------------------------------------------*/
    /* default constructor					 								 */
	NeuralNetwork();				
    
    /* constructor with specified range (min, max) for the weights			 */
	NeuralNetwork(float min, 			/* desired minimum value			 */
				  float max);			/* desired maximum value			 */

	/*-------------------------------------------------------------------------
     *                  OTHER MEMBER FUNCTIONS AND METHODS
     *-----------------------------------------------------------------------*/
	/*------------------------------------------------------------------------- 
 	 * Function name:         setRandomWeights
 	 *  
	 *   Set random weights to connect layers of the neural network
 	 *
 	 *	 Important! : Include the bias	
 	 *	 the relation of min and max must be for example like:
 	 *   min = -10 max = 20 to generate random values between (-10; 10)   
 	 *-----------------------------------------------------------------------*/
	 void setRandomWeights(float min,  /*desired minimum value*/ 
	 					   float max); /*desired maximum value*/
	 	
    /*------------------------------------------------------------------------- 
     * Function name:         setInitialWeights
     *  
     * Initializes the matrix of weights inW[][] which is used in calculating
     * the values for neurons in the hidden layer.
	 *
	 * Constructor with specified range, calls this funcition automatically     
     *--=--------------------------------------------------------------------*/
     void setInputWeights(float min, 	/* desired minimum value			 */ 
	 					  float max);	/* desired maximum value			 */
     
    /*------------------------------------------------------------------------- 
     * Function name:           setOutWeights
     *  
     * Initializes the matrix of weights outW[][] which is used in calculating
     * the values for the output layer
	 *
	 * Constructor with specified range, calls this funcition automatically       
     *-----------------------------------------------------------------------*/
     void setOutWeights(float min,		/* desired minimum value			 */ 
	 					float max);		/* desired maximum value			 */

    /*------------------------------------------------------------------------- 
     * Function name:         setWeightsFromGA
     *  
     * Initializes the matrix of weights inW[][] and outW[][] from training     
     *--=--------------------------------------------------------------------*/
     void setWeightsFromGA(float *vector);  /* vector of weights			 */
     
     void setWeightsFromGA(float *input,	/* vector holding input weights  */ 
	 					   float *hidden);	/* vector hold weights hid->out	 */

    /*-------------------------------------------------------------------------
 	 * Function name:         getWeights
 	 *  
 	 * get NN weights into vector (*W)    
 	 *-----------------------------------------------------------------------*/
	void getWeights(float *vector); /* vector to store weights*/

	/*------------------------------------------------------------------------- 
     * Function name:        	 getWeightsThreeLayersNN
     *  
     * get NN weights and stored into vectors input and hidden
	 * input  stored weights from inW
	 * hidden stored weights from outW    
     *--=--------------------------------------------------------------------*/
     void getWeights(float *input,		/* vector to stored weights in-> hid */
	  				 float *hidden);	/* vector to stored weights hid->out */
    
	/*------------------------------------------------------------------------- 
     * Function name:         setWeightsFromFile
     *  
     * It is important first to store values into vectors and then pass them
     * through this function. Vectors store all the values for N=10 NN from 
     * file.
	 * 
	 * m and h are used as control variables to point the right position in
     * both vectors
     *--=--------------------------------------------------------------------*/
	 void setWeightsFromFile(float vector[],	 /* vector holding weights to pass
	 											to W matrix in NN			 */
							 int &m); 		 /* control variable for length of
							 										    array*/
																		  
    /*------------------------------------------------------------------------- 
     * Function name:         setWeightsFromFileThreeLayersNN
     *  
     * It is important first to store values into vectors and then pass them
     * through this function. Vectors store all the values for N=10 NN from 
     * file.
	 * 
	 * m and h are used as control variables to point the right position in
     * both vectors
     *--=--------------------------------------------------------------------*/
     void setWeightsFromFile(float input[],	 /* vector holding weights to pass
	 											to inW matrix in NN			 */
	 						 float hidden[], /* vector holding weights to pass
							  					to outW matrix in NN		 */
							 int &m, 		 /* control variable for length of
							 										    array*/
							 int &h);		 /* control varuable for length of 
							 											array*/
     
    /*------------------------------------------------------------------------- 
     * Function name:            readInputs
     *  
     *   Read inputs to the NN, from a vector 
     *      
     *-----------------------------------------------------------------------*/
     void readInputs(float inXs[XsINPUT]);	 /*	vector of length XsINPUT	 */
     
    /*------------------------------------------------------------------------- 
     * Function name:            feedForward
     *  
     *   Runs the NeuralNetwork from input to output. It calculates the values
     *   for activated neurons on hidden layer and also the output of the NN,
     *	 which are stored in hiddenLayer[] and e[] respectively
     *-----------------------------------------------------------------------*/
     void feedForward();

    /*------------------------------------------------------------------------- 
     * Function name:             sigmoid
     *  
     *   Activation function wich apply sigmoid to the output of the nNetwork.
     *   It returns the value in the range (0, 1).
     *-----------------------------------------------------------------------*/
     float sigmoid(float e);		/* sigmoid of e -> f(e)					 */

    /*------------------------------------------------------------------------- 
     * Function name:          sigmoidDeriv
     *  
     *   Return the derivation of Sigmoid function:
     *      f(e)' = f(e)*(1 - f(e))  
     *    
     *------------------------------------------------ ----------------------*/
     float sigmoidDeriv(float sigmoid);		/* f'(sigmoid) 					 */

    /*------------------------------------------------------------------------- 
     * Function name:        runAgentNeuralNetwork
     *  
     *   This execute the neural network functions and output agent left and
     *   right velocities. 
	 *
	 *	 Note that the function doesnot return anything but change the values
	 *	 of input variables (arguments) 
	 *	 
	 *	 IMPORTAT!
	 *	 If you want to run the network for something not
     *   related to agent navigation with wheels, then avoid using this 
     *   function 
     *-----------------------------------------------------------------------*/
     void runAgentNeuralNetwork(float &rightVel, /* right velocity as ref	 */ 
	 							float &leftVel); /* left  velocity as ref	 */

    /*------------------------------------------------------------------------- 
     * Function name:           backPropagation
     *  
     *   Back propagates the error through the network and re-initializes all
     *   the weights, but does not affect any BIAS.
     *       
     *-----------------------------------------------------------------------*/
     void backPropagation(float *target);
     
	/*------------------------------------------------------------------------- 
 	 * Function name:        set and get functions
 	 *-----------------------------------------------------------------------*/
 	/* Get the output error. This is the error after checking with given target
   	   Values are stored using a pointer									 */
     void getOutputError(float *error);
     
    /* Set a desired learning rate. Default is 0.001					     */
     void setLearningRate(float rate);
     
    /* get actual learning rate												 */
     float getLearningRate();
     
    /*-------------------------------------------------------------------------
     *                  PUBLIC VARIABLES:
     *-----------------------------------------------------------------------*/
};
#endif
