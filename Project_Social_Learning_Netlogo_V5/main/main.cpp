/*-----------------------------------------------------------------------------
 *                   MAIN: THE EFFECT OF SOCIAL LERNING IN A SMALL POPULATION
 *							  			an agent-based simulation
 *
 *							  
 * Author:      Daniel Romero Mujalli
 * Written:      21/10/2013
 * Last update:  11/ 1/2017
 *
 * Summary:      The purpose of the model is to investigate how social learning
 *               affects the performance of individuals living in a small
 *				 population, as compared to asocial learning, innate behavior
 *				 (genetic inheritance and random behavior (control).
 *				 Our measures of performance were: 1) proportion of agents 
 *				 (individuals) exhibiting the "best behavior" and 2) cumulative 
 *				 mortality per trial; under different scenarios of environmental
 *				 change: static, abrupt change and gradual change. 
 *				 We followed the general methods as in Acerbi et al. (2007) and 
 *				 Marocco and Acerbi (2007).
 *
 *				 This program is an update to the code available as
 *				 supplementary material of the original article. In this version,
 *				 only the static environmental scenario is simulated.
 *
 *				 Here individuals are simulated as virtual agents moving around
 *				 the environment. Each agent has its own neuro-controller to
 *				 perceive the environment and make autonomous decisions.
 *---------------------------------------------------------------------------*/
 /* Libraries */
 #include "../include/miscellaneous/miscellaneous.h"
 using namespace std;

/*-----------------------------------------------------------------------------
 *                       IMPORTANT! TO SET UP EXPERIMENT
 *---------------------------------------------------------------------------*/
/* To modify the treatment of behavior, the scenario of environment, and
   parameter values go to:
   
   ../include/headers/parameter/
   
   Currently this update supports: 
   - all behaviors
   - only the static scenario of the environment							 */
/*-----------------------------------------------------------------------------
 *                       PUBLIC VARIABLES
 *---------------------------------------------------------------------------*/
// These variables store the data used to write output files 
int inWhite[ITERA][REPLICATIONS];	/* array used to write inWhiteFile	 	 */
int inBlack[ITERA][REPLICATIONS];	/* array used to write inBlackFile   	 */
int mortality[ITERA][REPLICATIONS]; /* array used for writing mFile	     	 */
#ifdef MIXED
int socialMatrix[ITERA][REPLICATIONS]; /* array used to write omegaFile  	 */
#endif /* MIXED */

/*-----------------------------------------------------------------------------
 *                       THE PROGRAM STARTS: main function
 *---------------------------------------------------------------------------*/
 int main()
 {
    /* RESETING SEED:														 */ 
    srand(time(NULL));
    
    /* VARIABLES:															 */ 
    float input[XsINPUT];			   /* array of inputs to NN. Values come 
									      from sensor detection. XsINPUT is 
									      defined in classParameter.h		 */
	float leftVel, rightVel;		   /* speed of left and right wheels of an 
									      agent								 */
									   
    /* 				DECLARATION OF CLASS VARIABLES or OBJECTS				 */ 
    Agent myAgent[N];  				   /* create N Agents     				 */ 
    Sensor mySensor[N][SENSOR_NUMBER]; /* create sensors for N agents	     */
    /* SENSOR_NUMBER is defined in classParameter.h and is used in sensor.h. It
	specifies the number of 'infrared' frontal sensors of an agent. Notice that 
	changing this may alter the performance of the current neural networks   */ 
    NeuralNetwork myNetwork[N];    	   /* create N neural networks (NN).
										  One NN per agent 				     */
										   
    /* VARIABLES NEEDED IN SIMULATION BASED ON ACERBI ET AL 2007			 */ 
    Agent patch[NUMBER_OF_PATCHES];    /* patch[0] = black patch,
										  patch[1] = white patch
										  they are defiend as stationary agents
										  									 */ 
	Perceptron myPerceptron[N];		   /* N gound controllers or perceptrons */	  
    float inX[IN_X];           		   /* array of inputs to perceptron.
										  notify whether an agent is inside or
										  outside the patches				 */ 
    float groundTarget = 0.0;  		   /* target for ground controller.
										  The preferece increase inside the 
										  patches 							 */ 
    int down = 0;              		   /* counter for dead agents. Used to fill
										  mortality[][] (public variable)    */
	float energy_w;					   /* energy effect of white path / iter */
	float energy_b;					   /* energy effect of black patch / iter*/
	float lv;						   /* linear velocity					 */
	float pout;						   /* perceptron output					 */
	
	bool object, border;			   /* check for collisions				 */
	
	// FILE TO STORE DATA ON EXPLORATORY BEHAVIOR
	int black;					/* counter: agents located in black patch	 */
	int white;					/* counter: agents located in white patch	 */
	ofstream mFile; 			/* file containing dead agents / iteration   */
	ofstream inBlackFile; 		/* file of number of agents in black patch   */
	ofstream inWhiteFile; 	    /* file of number of agents in white patch   */
	#ifdef MIXED
	ofstream omegaFile;       // Number of social learners in a Mx population
                        	  // per iteration, i.e. omega = 1
	int socialAgents;         /* counter: counts agents omega = 1 (Mx only)  */
	#endif /* MIXED */
	
	#ifdef DEBUG
	// check the exploratory behavior. 
	ofstream move;
	ofstream fpatch;
   // This file contain output data that can be analyzed using scatterplots
   // to track the trajectory of each agent
	move.open("Movement.csv");
	fpatch.open("patches.csv");
    // write headers:
	setHeaderMoveFile(move, N);
   
    #endif /* DEBUG */

    // print number of replications and iterations indicated by user
    cout << "Replications: " << REPLICATIONS << endl;
    cout << "\t of " << ITERA << " iterations each" << endl;

    for (int k = 0; k < REPLICATIONS; k++)
    {
    	
        #ifdef COUNT_ITERA_AND_REPLICATIONS
            
            cout << "replication: "    << k + 1 << " / " << REPLICATIONS << endl;
            
        #endif /* COUNT_ITERA_AND_REPLICATIONS */

/*-----------------------------------------------------------------------------
 *                       INITIALIZATION
 *---------------------------------------------------------------------------*/    

   		cout << "Creating world ... ";
   		// initialization create patches, agents, their sensors, load 
   		// the neural networks and create perceptron or ground controller
   		// Also set the effect of environment according to treatment
   		createPatches(patch, NUMBER_OF_PATCHES, Max_X, Max_Y, PATCH_DIAMETER/2);
   		
   
   		createAgentsOutsidePatches(myAgent, N, Max_E, MAX_VEL, AGENT_RADIUS, 
		   						   Max_X, Max_Y, patch, NUMBER_OF_PATCHES);
   
   		createSensors(myAgent, mySensor, N, REACH, Max_X, Max_Y);
   
   		if (HIDDEN == 0)
		{
   			createNeuralNetwork(myNetwork, N, XsINPUT, OUTPUT);
		} else {
			createNeuralNetworksThreeLayersNN(myNetwork, N, XsINPUT, HIDDEN, OUTPUT);
		}
   
   		// refresh sensor detection and inputs to Neural Networks
        refreshDetection(mySensor, myAgent, N);
    
    	/* reading detection from sensors to NN								  */ 
    	for (int i = 0; i < N; i++)
    	{
        	for (int j = 0; j < SENSOR_NUMBER; j++)
        	{
            	input[j] = mySensor[i][j].getDetection();
        	}
        	myNetwork[i].readInputs(input);
    	}

		// create perceptron or ground controller to perceive ground color
        createPerceptron(myPerceptron, N, LEARNING_RATE, MUT_RATE, MUT_OMEGA, 
					 	 MUT_PHI, RND_W);
	
   		/* set the effect of the environment       						     */
        setEffectOfPatches(energy_w, energy_b);
        
        // write patch file
        for (int i = 0; i < NUMBER_OF_PATCHES; i++)
        {
        	fpatch << patch[i].getxPosition() << ",";
        	fpatch << patch[i].getyPosition() << "\n";
		}
        
    
		cout << "done" << endl;
/*					END OF INITIALIZATION									 */
/*-----------------------------------------------------------------------------
 *                        RUNNING WORLD
 *---------------------------------------------------------------------------*/
        
		/* Running World starts:										 	 */
		cout << "runing World ... ";
		       
        for (int z = 0; z < ITERA; z++)
        {
        	#ifdef COUNT_ITERA_AND_REPLICATIONS
        	
            cout << "iteration: " << z + 1 << " / " << ITERA << endl;
            
            #endif /* COUNT_ITERA_AND_REPLICATIONS */
            
           /* Check if agent i is in a given patch, read input to ground
	   	      controller (perceptron) and update effect on its energy		 */
			
			// reset counters white, black
			white = black = 0;
			 
    		for (int i = 0; i < N; i++)
    		{
    			// checkWhereIsTheAgent update agent owns: agent.white and 
				// agent.black
        		checkWhereIsTheAgent(myAgent, i, patch, NUMBER_OF_PATCHES, inX);
       			myPerceptron[i].readInputs(inX);
       			updateAgentEnergy(myAgent, i, z, ITERA, energy_b, energy_w, 
				GREY_PATCH_EFFECT);
       			// count agents in white/black patches
       				 if(myAgent[i].black) { black++;}
				else if(myAgent[i].white) { white++;}
    		}
    		/* Store the number of agents in each patch       */
			inWhite[z][k] = white; 
			inBlack[z][k] = black; 
    		
    		#ifdef DEBUG
	
    		// cout << "agents in black patch " << black << endl;
    		// cout << "agents in white patch " << white << endl;
    
    		#endif /* DEBUG */
    		
    		/* check neighbors. This is only done for MIXED and SOCIAL 
			treatments     */
    		#ifdef MIXED
    		 
    		checkNeighbors(myAgent, N, myPerceptron, white, black);
    		 
    		#endif /* MIXED */
    		 
			#ifdef SOCIAL
    		 
    		checkNeighbors(myAgent, N, myPerceptron, white, black);
			 
			#endif /* SOCIAL */
    		
			// store the number of social agents found in the mixed population
			#ifdef MIXED
			
			for(int i = 0; i < N; i++)
			{
				if(myPerceptron[i].getOmega()){socialAgents++;}
			}
			socialMatrix[z][k] = socialAgents;
			
			#endif /* MIXED */
			
			/* Run the perceptron: feedforward the perceptron and mofify 
			   weights through learning when apply	  						 */
			for(int i = 0; i < N; i++)
			{ runPerceptron(myPerceptron, i, groundTarget); }
			 
			/* Move agents: calculate next position based on the linear
			   velocity lv given by the neural network NN. the lv is affected
			   by the output of the perceptron. This way the velocity can
			   be reduced when the agent is located in a patch. 
			   Before calculatign lv, the left and right velocities
			   are set when running the NN							 		 */
			for (int i = 0; i < N; i++)
    		{
        		myNetwork[i].runAgentNeuralNetwork(leftVel, rightVel);
        		myAgent[i].setLeftVel(leftVel);
        		myAgent[i].setRightVel(rightVel);
        		myAgent[i].computeLinearVel();
        
        		#ifdef DEBUG
        		// cout << "leftVel: " << leftVel << endl;
				// cout << "rightVel: " << rightVel << endl;
       			#endif
        
        		/* The perceptron affects movement behavior					 */
        		if(myAgent[i].white || myAgent[i].black)
        		{
       				// get linear vel
       				lv = myAgent[i].getAgentLinearVel();
        			// get the output of the perceptron
					pout = myPerceptron[i].getOutput(); 
					// calculate the actual linear velocity lv
					lv = pout * lv;
					
					#ifdef DEBUG
            		//cout << "output of perceptron: " << pout << endl;
            		//cout << "lv before: "; 
					//cout << myAgent[i].getAgentLinearVel();
            		//cout << "\t lv after: " << lv << endl;
           			#endif /* DEBUG */
					 
            		myAgent[i].setLinearVel(lv);	
        		}
        		// set the next position:
        		myAgent[i].nextMove();
        		
        		// update the agent age
        		myAgent[i].refreshAge();
        
        		#ifdef DEBUG
        		// cout << "oldx, oldy " << myAgent[i].getxOld() << " , "; 
				// cout << myAgent[i].getyOld() << endl;
       			// cout << "theta " << myAgent[i].getTheta() << endl;
       			// cout << "Agent_" << i << " nextx, nexty: "; 
				// cout << myAgent[i].getxPosition() << ", "; 
				// cout << myAgent[i].getyPosition() << endl;
				#endif
				
				for (int j = 0; j < SENSOR_NUMBER; j++)
                    {
                      input[j] = mySensor[i][j].getDetection();
                    }
		
				#ifdef DEBUG
				/* store only for the 1st replication			         */
        		if(k<1)
        		{
        			if (myAgent[i].getxPosition() / myAgent[i].getxPosition() != 1)
        			{ cout << myAgent[i].getxPosition(); 
					cin.get();}
           			move << myAgent[i].getxPosition() << ",";//"\t";
           			move << myAgent[i].getyPosition() << ",";//"\t";
					move << myAgent[i].getTheta() << ",";//"""\t";
					move << signalTranslation(input, SENSOR_NUMBER) << ",";
        		}
        		#endif /* DEBUG*/
        		
        		// check for borders and overlap with other agents
				for (int j = 0; j < N; j++)
				{
					object = checkOverlap(myAgent, i, j, Max_X, Max_Y, MAX_VEL, false, false);
				}
				
    			border = checkBorder(myAgent, i, Max_X, Max_Y);
    			
    			/*if(border == false && object == false && signalTranslation(input, SENSOR_NUMBER) != 0)
					{
						cout << "sensors are detecting something when they should not" << endl;
						
						cout << "agent_xy: " << myAgent[i].getxPosition() << ", " << myAgent[i].getyPosition() << endl;
						cout << "sensor_xy: " << mySensor[i][0].getxCor() << ", " << mySensor[i][0].getyCor() << endl;
						
						cin.get();
					}*/
        		
    		}
    		#ifdef DEBUG
    		if(k<1){move << "\n";}
    		#endif /* DEBUG */  
			
			
			
			// update energy, mortality and inheritance, sensor inputs, 
			//repeat loop
			for (int i = 0; i < N; i++)
    		{

        		if(myAgent[i].getEnergy() <= 0.0) 
        		{
        			// one more dead agent
            		down++;
            		/* replace the dead agent with a newborn in a random
					   positon, with full energy, random orientation and,
					   located outside the patches							*/
					replaceTheAgent(myAgent, i, patch, Max_X, Max_Y,
					   				MAX_VEL, AGENT_RADIUS, Max_E);
            		
					// the newborn inherits traits from life agents
            		// weight values of perceptron are reset to default
            		runInheritance(myAgent, i, N, myPerceptron, myNetwork,
					LEARNING_RATE, RND_W);    
        		}   
    		}
    		// store dead agents into the array mortality
    		mortality[z][k] = down;
    		
    		// refresh agent sensors, detection of obstacles and input this
    		// info to the NN
    		// update sensors
    		for (int i = 0; i < N; i++)
    		{
        		for (int j = 0; j < SENSOR_NUMBER; j++)
        		{
            		mySensor[i][j].setTheta(myAgent[i].getTheta());
            		mySensor[i][j].setCenter(myAgent[i].getxPosition(),
                                    		 myAgent[i].getyPosition());
        		}
        		refreshSensors(mySensor, i); 
    		}
    		
			// refresh sensor detection and inputs to Neural Networks
   			refreshDetection(mySensor, myAgent, N);
    
    		/* reading detection from sensors to NN							*/ 
    		for (int i = 0; i < N; i++)
    		{
        		for (int j = 0; j < SENSOR_NUMBER; j++)
        		{
            		input[j] = mySensor[i][j].getDetection();
        		}
        		myNetwork[i].readInputs(input);
    		}			 
			#ifdef MIXED
            socialAgents = 0;
            #endif /* MIXED */			
        }
        /* reset	counter */
        down = 0;
        
        cout << " done" << endl;
	}
    
//    // open files and write headers and data into files
//	openFiles(mFile, inWhiteFile, inBlackFile);
//    writeMortalityFile(mFile, mortality);
//    writeInWhiteFile(inWhiteFile, inWhite);
//    writeInBlackFile(inBlackFile, inBlack);
//    // close files:
//	mFile.close();
//	inWhiteFile.close();
//	inBlackFile.close();
//    
//	#ifdef MIXED
//    writeOmegaFile(omegaFile, socialMatrix);
//    omegaFile.close();
//	#endif /* MIXED*/
    
	#ifdef DEBUG
	
    move.close();
   	
    
	#endif /* DEBUG */
	
	return 0;
 }
/*-----------------------------------------------------------------------------
 *                        CHANGE-LOG AND OBSERVATIONS
 *---------------------------------------------------------------------------*/
 
