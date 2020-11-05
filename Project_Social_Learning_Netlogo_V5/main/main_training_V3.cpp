/*-----------------------------------------------------------------------------
 *                      MAIN: TRAINING ROBOTS
 *
 *     Using genetic algorithms GA to train feedforward artificial NN
 *							  
 * Author:       Daniel Romero Mujalli
 * Written:      30/ 7/2019
 * Last update:  24/10/2019
 *
 * Summary:      Robots are trained to navigate a 2D arena with obstacles and
 *				 walls.
 *               The training algorithm used GA and backpropagation to
 *               train the NN weights. Then, all values are stored in a file.
 *               1st file: input-to-hidden weights (+ bias)
 *               2nd file: hidden-to-output weights (+ bias)
 *               It is important to consider how the weights are
 *               stored in the file when reading out from them
 *---------------------------------------------------------------------------*/
 /* Libraries */
 #include "../include/miscellaneous/miscellaneous.h"
 using namespace std;
 
 /*-----------------------------------------------------------------------------
 *                      	  CONSTANTS
 *---------------------------------------------------------------------------*/
 /* Iterations:																 */
 #define ITERA_TRAINING    500	/* Iteration number (robot steps) during
								   //training with Genetic Algorithms			 */
 #define TRIALS            1	/* number of times robots are rerolled and
								   tested before check fitness and set 
								   inheritance								 */
 #define GENERATIONS       20	/* number of generation in GA training		 */								   								   
 #define ITERA_NN         500	/* Iteration number for training 
								   backpropagation							 */
 //#define N_OBSTACLES		20  /* number of objects in the arena			 */
 //#define OBJ_RADIUS			 3	/* radious of the circular objects			 */
 //#define OBJ_EFFECT			-5  /* effect of obstacles on agent energy		 */
 #define FOOD_ITEMS		   5000  /* nr of food items in the arena			 */
 #define FOOD_SIZE		     3  /* size of the food items					 */
 #define FOOD_EFFECT		 10  /* effect of food items on agent energy      */
 
 #define P_size				40  /* size of the population of robots			 */
 #define Best_N				10  /* the best N idividual robots				 */
 #define E					0  /* initial energy of robots					 */
 #define MV					0.2 /* genetic variance normal distribution      */
 #define Nr_of_NN			10   /* the number of NN to be stored in file at 
 								   //the end of training    					 */
 #define MUTATION_RATE      0.03 /* mutation rate, affects inheritance       */
 
								   
 // Size of the arena given by Max_X, Max_Y in parameter.h
 
/*-----------------------------------------------------------------------------
 *                      FUNCTION PROTOTYPES / DECLARATIONS
 *---------------------------------------------------------------------------*/
 bool check4food(Agent myAgent[], int agent_i, Agent food[], int n_foodItems);
 
 void selectBestAgents(Agent myAgent[], int best_n, int pop_size, int ID_selection[]);
 
 void reproduce(Agent myAgent[], int pi, int pj, NeuralNetwork myNetwork[]);
 void reproduceThreeLayersNN(Agent myAgent[], int pi, int pj, NeuralNetwork myNetwork[]);
 
 void weightsToFile(NeuralNetwork myNetwork[], int nr_of_nn, int ID_selection[]);
 
 void writeFile(ofstream &myFile, float *vector, int rows);
 
 // setTarget
 void setTarget(float target[]);
 
 // set coordinate range (min, max) based on segment. The segment indicate
 // the quadrant where the cluster will be located
 void setRangeBasedOnSegment(int segment, float &min, float &max, float Max_Dim);


 
 /*----------------------------------------------------------------------------
 *                       THE PROGRAM STARTS: main function
 *---------------------------------------------------------------------------*/
 int main()
 {
 	
 	/* Variables															 */
 	float min = -3.0;
 	float max =  3.0;
 	float input[XsINPUT];
 	float target[OUTPUT];   							// NN target for backpro
 	float leftVel, rightVel;
 	int ID_selection[Best_N];
 	int partner;
 	int segment; // segment indicating where in x or y axis the cluster will be 
	 			 // located
 	float minx, maxx, miny, maxy; // dimensions constraining location of cluster
 	int low, top; // loop control variables
 	// to track the trajectory of each agent
 	ofstream move, foraging;
	move.open("Movement.csv");
	//foraging.open("food.csv");
	setHeaderMoveFile(move, P_size);
 	
 	/* RESETING SEED:														 */ 
    srand(time(NULL));
    
    /* FIRST PHASE: WORLD SETUP												 */
    // set Obstacles as agent object:
    //Agent obstacles[N_OBSTACLES];
    
    // set food items as agent object:
    Agent food[FOOD_ITEMS];
    
    // set robots as agent objects
    Agent myAgent[P_size];    			   /* create N Agents     			 */ 
    Sensor mySensor[P_size][SENSOR_NUMBER]; /* create sensors for N agents	 */
    NeuralNetwork myNetwork[P_size];       /* create N neural networks (NN)
										  One NN per agent 				     */
										  
	bool border, object;
	
										  
	
   /*-------------------------------------------------------------------------
    *                       CREATE THE WORLD
    *-----------------------------------------------------------------------*/
    cout << "Creating world ... ";
     
    // place random obstacles:
    //createAgents(obstacles, N_OBSTACLES, 0, 0, OBJ_RADIUS, Max_X, Max_Y);
    // place food randomly on the arena
    createAgents(food, FOOD_ITEMS, 0, 0, FOOD_SIZE, Max_X, Max_Y);
    // set age to zero (resetAge) as measurement of status: eaten or not
    // age = 0 -> food item is available (not eaten yet)
    for(int i = 0; i < FOOD_ITEMS; i++) { food[i].resetAge(); }  
    
    // place robots on the arena
    createAgents(myAgent, P_size, E, MAX_VEL, AGENT_RADIUS, Max_X, Max_Y);

    // create their sensors
	createSensors(myAgent, mySensor, P_size, REACH, Max_X, Max_Y);
	// create their ANN with random weights in range (min, max)
	for (int i = 0; i < P_size; i++)
	{
		myNetwork[i] = NeuralNetwork(min, max);
	}
	// update sensors: check for detections
	refreshDetection(mySensor, myAgent, P_size);
	// update inputs to neural network (from sensor)
	/* reading detection from sensors to NN								  */ 
    for (int i = 0; i < P_size; i++)
    {
    	for (int j = 0; j < SENSOR_NUMBER; j++)
       {
  			input[j] = mySensor[i][j].getDetection();
       }
    	myNetwork[i].readInputs(input);
	}
	 
	// DEBUG: Get and print weights of ANN
    // float inW[XsINPUT + 1][HIDDEN], outW[HIDDEN + 1][OUTPUT];
    // myNetwork[0].getWeights(*inW, *outW);
    /*
	for (int i = 0; i < XsINPUT + 1; i++) 
	{
		for (int j = 0; j < HIDDEN; j++)
		{
			cout << "inW: " << inW[i][j] << endl; 	
		} 	
	}
	*/
	cout << "Done!" << endl ; 
   /*---------------------------------------------------------------------------
    *                       RUN THE WORLD
    *-------------------------------------------------------------------------*/
    
    // set target for backpro
    setTarget(target);
    cout << "target: " << target[0] << "; " << target[1] << endl;
    
    cout << "Starting training for " << GENERATIONS << " generations ... "; 
	cout << "\n" << endl;
	
	for(int g = 0; g < GENERATIONS; g++)
	{
		cout << "generation " << g << " of " << GENERATIONS << endl;
		
		// write file position of food items
		/*for (int i = 0; i < FOOD_ITEMS; i++)
		{
			foraging << food[i].getxPosition() << ",";//"\t";
           	foraging << food[i].getyPosition() << ",";//"\t";
		}
		foraging << "\n";
		*/
		
		for(int k = 0; k < TRIALS; k++)
		{
			cout << "trials: " << k << " of " << TRIALS << endl;
			
			for (int z = 0; z < ITERA_TRAINING; z++)
			{
				// check for edible food items
				for (int i = 0; i < P_size; i++)
				{
					if (check4food(myAgent, i, food, FOOD_ITEMS))
					{
						myAgent[i].addUpEnergy(FOOD_EFFECT);
					}
				}
		
				// agents move
		 
				/* Move agents: calculate next position based on the linear
				velocity lv given by the neural network NN. 
				Before calculatign lv, the left and right velocities
				are set when running the NN							 		 */
				for (int i = 0; i < P_size; i++)
   		 		{
       		 		myNetwork[i].runAgentNeuralNetwork(leftVel, rightVel);
       		 		
       		 		//cout << "agent_" << i << " x, y: " << myAgent[i].getxPosition() << ", " << myAgent[i].getyPosition() << endl;
       		 		
       		 		for (int j = 0; j < SENSOR_NUMBER; j++)
                    {
                      input[j] = mySensor[i][j].getDetection();
                      
                      //cout << "sensor_" << i << " x, y: " << mySensor[i][j].getxCor() << ", " << mySensor[i][j].getyCor() << endl;
                    }
                    
       		 		
					// training with backpro
					if (g < (GENERATIONS) && signalTranslation(input, SENSOR_NUMBER) == 0)
            			{ myNetwork[i].backPropagation(target); }
       		 		
       		 		
       		 		//cout << "VL: " << leftVel << endl;
       		 		//cout << "VR: " << rightVel << endl;
       		 		
        			myAgent[i].setLeftVel(leftVel);
        			myAgent[i].setRightVel(rightVel);
        			myAgent[i].computeLinearVel();
        			//cout << "linear vel: " << myAgent[i].getAgentLinearVel() << endl;
       		
        
   	   				// set the next position:
        			myAgent[i].nextMove();
        			
        			//cout << "agent orientation: ";
        			//cout << "theta: " << toAngle(myAgent[i].getTheta() ) << endl;
       				//cout << "Agent_" << i << " nextx, nexty: "; 
					//cout << myAgent[i].getxPosition() << ", "; 
					//cout << myAgent[i].getyPosition() << endl;
					/*if (myAgent[i].getEnergy() < 0) 
					{
						cout << "agent with negative energy!" << endl;
					}*/
					
					for (int j = 0; j < SENSOR_NUMBER; j++)
                    {
                      input[j] = mySensor[i][j].getDetection();
                      
                      //cout << "sensor_" << i << " x, y: " << mySensor[i][j].getxCor() << ", " << mySensor[i][j].getyCor() << endl;
                    }
					
					//if(g < GENERATIONS ) // && k < TRIALS)
					if(g < GENERATIONS / 2)
        		    {
        			  if (myAgent[i].getxPosition() / myAgent[i].getxPosition() != 1)
        			  { cout << myAgent[i].getxPosition(); 
					  cin.get();}
           			  move << myAgent[i].getxPosition() << ",";//"\t";
           			  move << myAgent[i].getyPosition() << ",";//"\t";
					  move << myAgent[i].getTheta() << ",";//"""\t";
					  move << signalTranslation(input, SENSOR_NUMBER) << ",";
        		    }
        		    
        		    // check for borders and overlap with other agents
				
					border = checkBorderCollision(myAgent, i, Max_X, Max_Y);
				
					for(int j = 0; j < P_size; j++)
					{
						if (i != j)
						{
							object = checkOverlap(myAgent, i, j, Max_X, Max_Y, MAX_VEL, false, true);		
						}
					}
				
    			} 	
    			
    			
				//if(g < GENERATIONS ) {move << "\n";} //&& k < TRIALS)
				if(g < GENERATIONS / 2){move << "\n";}
			
			
    			// refresh agent sensors, detection of obstacles and input this
    			// info to the NN
    			// update sensors
    			for (int i = 0; i < P_size; i++)
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
   				refreshDetection(mySensor, myAgent, P_size);
    
    		/* reading detection from sensors to NN							*/ 
    			for (int i = 0; i < P_size; i++)
    			{
    				//cout << "agent_" << i << " detection: " << endl;
        			for (int j = 0; j < SENSOR_NUMBER; j++)
        			{
            			input[j] = mySensor[i][j].getDetection();
            			//cout << "input vector pos " << j << ": " << input[j] << endl;
        			}
        			myNetwork[i].readInputs(input);
        			
        			//cin.get();
        		}
    		} // END OF ITERA TRAINING LOOP
    
    	// Reroll: randomly drag and drop the agents in the arena, and
    	// reactivate food items
    
    		// drag and drop
    		for (int i = 0; i < P_size; i++)
    		{
    			myAgent[i] = Agent(Max_X, Max_Y, MAX_VEL, AGENT_RADIUS, 
							       myAgent[i].getEnergy());
				
			}
     
    		// reactivate fooditems
    		for(int i = 0; i < FOOD_ITEMS; i++){ food[i].resetAge(); }
    	
		} // END OF TRIALS LOOP
	
		// select the best_N agents
		selectBestAgents(myAgent, Best_N, P_size, ID_selection);
	
		// print selected agents:
		//for (int i = 0; i < Best_N; i++) { cout << ID_selection[i] << ", ";}
 		//cout << endl;
 	
 		// unblock the selected indv so their slots are available to place new generation
 		for (int i = 0; i < Best_N; i++) 
	 	{
	 		myAgent[ID_selection[i]].selected = false;
	 	}
 	
 		// select mating partners (self-fertilization allowed)
		for(int i = 0; i < Best_N; i++)
		{
			// randomly select partner from ID_selected
			partner = rand() % Best_N;
		
			// reproduction and inheritance with implicit genetics
			if(HIDDEN == 0)
			{
				reproduce(myAgent, ID_selection[i], ID_selection[partner], myNetwork);
			}
			else
			{
				reproduceThreeLayersNN(myAgent, ID_selection[i], ID_selection[partner], myNetwork);
			}
			
		}
		
		// drag and drop food items
		if (g < (GENERATIONS / 2)) // Random food items
		{
			createAgents(food, FOOD_ITEMS, 0, 0, FOOD_SIZE, Max_X, Max_Y);
		} else 
		{ 	// clustered food items
			// the food items are distributed within clusters
			// select a cluster (total clusters = 16): 1st: (Max_X / 4, Max_Y / 4)
			// set range of X coord given by min_/max_segment
			// set values for loop control variables
			low = 0;
			top = FOOD_ITEMS / 4;
			for (int i = 0; i < 4; i++)
			{
				segment = rand() % 4;
				setRangeBasedOnSegment(segment, minx, maxx, Max_X);
				segment = rand() % 4;
				setRangeBasedOnSegment(segment, miny, maxy, Max_Y);
				//cout << "minx = " << minx << " maxx = " << maxx << endl;
				//cout << "miny = " << miny << " maxy = " << maxy << endl;
				for (int j = low; j < top; j++)
				{
					food[j].setxPosition(minx + (maxx - 2*minx)*rand()/(RAND_MAX + 1.0));
					food[j].setyPosition(miny + (maxy - 2*miny)*rand()/(RAND_MAX + 1.0)); 
				}
				// update loop control variables:
				low = top - 1;
				top = top + (FOOD_ITEMS / 4);
				//cout << "low: " << low << " top: " << top << endl;	
			}
				     			
		}
		
		// Reroll: randomly drag and drop the agents in the arena, and
    		// reactivate food items
    
    		// drag and drop
    		for (int i = 0; i < P_size; i++)
    		{
    			myAgent[i] = Agent(Max_X, Max_Y, MAX_VEL, AGENT_RADIUS, 
							       myAgent[i].getEnergy());
				
			}
			
		// refresh agent sensors, detection of obstacles and input this
    			// info to the NN
    			// update sensors
    			for (int i = 0; i < P_size; i++)
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
   				refreshDetection(mySensor, myAgent, P_size);
    
    		/* reading detection from sensors to NN							*/ 
    			for (int i = 0; i < P_size; i++)
    			{
    				//cout << "agent_" << i << " detection: " << endl;
        			for (int j = 0; j < SENSOR_NUMBER; j++)
        			{
            			input[j] = mySensor[i][j].getDetection();
            			//cout << "input vector pos " << j << ": " << input[j] << endl;
        			}
        			myNetwork[i].readInputs(input);
        			
        			//cin.get();
        		}
			
 	} // END OF GENERATIONS LOOP
 	
 	cout << "\n" << "End of tranining" << "\n" << endl;
 	
 	cout << "Writing weight files ... " << endl;
 	
 	// select the nr of NN to be written into the file
 	selectBestAgents(myAgent, Nr_of_NN, P_size, ID_selection);
 	
 	// write file
 	weightsToFile(myNetwork, Nr_of_NN, ID_selection);
 	
 	move.close();
 	//foraging.close();
 	
 	cout << "done" << endl;
 	
 	return 0;
 }
 
/*-----------------------------------------------------------------------------
 *                      FUNCTION DEFINITIONS
 *---------------------------------------------------------------------------*/
 // check for food: if true, eat the item and increase one unit of energy
 bool check4food(Agent myAgent[], int agent_i, Agent food[], int n_foodItems)
 {
 	float x, y, r, d;
 	int status; // whether eaten or not (1 or 0)
 	bool itemFound = false;
	float xcor = myAgent[agent_i].getxPosition();
 	float ycor = myAgent[agent_i].getyPosition();
 	float radius = myAgent[agent_i].getRadius();
 	
 	int i = 0;
 	do{
 		x = food[i].getxPosition();
 		y = food[i].getyPosition();
 		r = food[i].getRadius();
 		status = food[i].getAge();
 		
 		d = getDistance(xcor, ycor, x, y);
 		if(d <= (radius + r) && status == 0)
		 { 
		 	itemFound = true;
		 	food[i].refreshAge();
		 }
 		
				
 		i++;
 		
	}while (itemFound == false && i < n_foodItems);
	
	return itemFound;
	
 } // end of check4food
 
 // select the best n individuals out of the population
 void selectBestAgents(Agent myAgent[], int best_n, int pop_size, int ID_selection[])
 {
 	// function parameters
 	int best, max;
	
	// catch exception
 	if(best_n > pop_size) 
		{ 
			cout << "Error in selectBestAgents: best_n greater than"; 
			cout << " the population size" << endl;
			cin.get();
		}
		
	// select best n individuals
	for (int i = 0; i < best_n; i++)
	{
		max = -1;
		for (int j = 0; j < pop_size; j++)
		{
		//	cout << "ID: " << j << " ; e = " << myAgent[j].getEnergy() << endl;
			// check if already selected as one of the best
			if(myAgent[j].selected == false)
			{
				if(myAgent[j].getEnergy() > max)
				{
					max = myAgent[j].getEnergy(); 
					best = j; 
				}
			}
		}
		myAgent[best].selected = true;
	//	cout << "selected: " << best << " e = " << myAgent[best].getEnergy() << endl;
		// update the vector of IDs
		ID_selection[i] = best; 
	}
 } // end of selectBestAgent
 
 // Reproduction and inheritance with implicit genetics
 
 // one layer NN
 void reproduce(Agent myAgent[], int pi, int pj, NeuralNetwork myNetwork[])
 {
 	// check parents ID:
 	//cout << "pi: " << pi << " pj: " << pj << endl;
 	
 	int x, counter;
 	// store length of vectors of weights
 	int length = (XsINPUT + 1)*OUTPUT;
    // create vectors to store parental (pi, pj) weights
    float W_i[length], W_j[length];
    // vectors of new weight values
    float new_W[length];
    // vectors of mean values
    float mu_W[length];
 	//cout << "in: " << in << " hid: " << hid << endl;
 	
 	// set nr of offspring
 	int offsp = (int)(P_size / Best_N);
 	//cout << "nr_offsp: " << offsp << endl;
 	
 	// get weights from parents i and j
 	myNetwork[pi].getWeights(W_i);
 	myNetwork[pj].getWeights(W_j);	
 	
 	
 	// get the mean values for each vector in and hid
 	for(int i = 0; i < length; i++) { mu_W[i] = (W_i[i] + W_j[i]) / 2;}
 	
 	//cout << "inW: " << endl; cout << mu_in[0] << " = " << Win_i[0] << " + " << Win_j[0] << endl;
 	//cout << "outW: " << endl; cout << mu_hid[0] << " = " << Whid_i[0] << " + " << Whid_j[0] << endl;
 	//cin.get();
 	//cout << "mu in: " << endl;
 	//for(int i = 0; i < in; i++) { cout << mu_in[i] << endl;}
 	
 	//cout << "mu_hid: " << endl;
	//for(int i = 0; i < hid; i++) { cout << mu_hid[i] << endl;}
	
	// create object normal distribution with custom seed
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
	default_random_engine generator (seed);
	
	// loop initialization
	x = counter = 0;
 	do
	{
		//cout << "agent_id: " << x << endl;
		//cout << "counter = " << counter << endl;
		//cout << "selected? " << myAgent[x].selected << endl;
	 	
		if(!myAgent[x].selected) // if false, i.e., not selected
	 	{
	 		// new inWeights
	 		//cout << "new in: " << endl;
			for(int k = 0; k < length; k++)
	 		{
	 			if (rand()/(RAND_MAX + 1.0) < MUTATION_RATE)
				 {
				 	normal_distribution<float> distribution(mu_W[k], sqrt(MV));
	 				new_W[k] = distribution(generator);
				 }
				 else {
				 	new_W[k] = mu_W[k]; // alternatively, W_i or _j (randomly)
				 }
	 			
	 			//cout << new_Win[k] << endl;
	 		}
	 		// new hidWeights
	 		//cout << "new hid: " << endl;

			// set weights into network
			myNetwork[x].setWeightsFromGA(new_W);
			// take the agent out from the pool of potential offspring:
			myAgent[x].selected = true;
			
			// offspring created, update counter
			counter++;
		}
		x++;
		
		if(counter > offsp) 
		{ 
			cout << "problem in reproduce::do while loop" << endl;
			cout << "counter > offsp, should not occur!" << endl;
			cin.get();
		}
		
	}while(counter < offsp);
 	
 	
 } // end reproduce
 
 // complex (three layers) neural network:
 void reproduceThreeLayersNN(Agent myAgent[], int pi, int pj, NeuralNetwork myNetwork[])
 {
 	// check parents ID:
 	//cout << "pi: " << pi << " pj: " << pj << endl;
 	
 	int x, counter;
 	// store length of vectors of weights
 	int in = (XsINPUT + 1)*HIDDEN;
    int hid = (HIDDEN + 1)*OUTPUT; 
    // create vectors to store parental (pi, pj) weights
    float Win_i[in], Win_j[in];
    float Whid_i[hid], Whid_j[hid];
    // vectors of new weight values
    float new_Win[in], new_Whid[hid];
    // vectors of mean values
    float mu_in[in], mu_hid[hid];
 	//cout << "in: " << in << " hid: " << hid << endl;
 	
 	// set nr of offspring
 	int offsp = (int)(P_size / Best_N);
 	//cout << "nr_offsp: " << offsp << endl;
 	
 	// get weights from parents i and j
 	myNetwork[pi].getWeights(Win_i, Whid_i);
 	myNetwork[pj].getWeights(Win_j, Whid_j);	
 	
 	
 	// get the mean values for each vector in and hid
 	for(int i = 0; i < in; i++) { mu_in[i] = (Win_i[i] + Win_j[i]) / 2;}
 	for(int i = 0; i < hid; i++){mu_hid[i] = (Whid_i[i] + Whid_j[i]) / 2;}
 	
 	//cout << "inW: " << endl; cout << mu_in[0] << " = " << Win_i[0] << " + " << Win_j[0] << endl;
 	//cout << "outW: " << endl; cout << mu_hid[0] << " = " << Whid_i[0] << " + " << Whid_j[0] << endl;
 	//cin.get();
 	//cout << "mu in: " << endl;
 	//for(int i = 0; i < in; i++) { cout << mu_in[i] << endl;}
 	
 	//cout << "mu_hid: " << endl;
	//for(int i = 0; i < hid; i++) { cout << mu_hid[i] << endl;}
	
	// create object normal distribution with custom seed
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
	default_random_engine generator (seed);
	
	// loop initialization
	x = counter = 0;
 	do
	{
		//cout << "agent_id: " << x << endl;
		//cout << "counter = " << counter << endl;
		//cout << "selected? " << myAgent[x].selected << endl;
	 	
		if(!myAgent[x].selected) // if false, i.e., not selected
	 	{
	 		// new inWeights
	 		//cout << "new in: " << endl;
			for(int k = 0; k < in; k++)
	 		{
	 			if (rand()/(RAND_MAX + 1.0) < MUTATION_RATE)
				 {
				 	normal_distribution<float> distribution(mu_in[k], sqrt(MV));
	 				new_Win[k] = distribution(generator);
				 }
				 else {
				 	new_Win[k] = mu_in[k]; // alternatively, Win_i or _j (randomly)
				 }
	 			
	 			//cout << new_Win[k] << endl;
	 		}
	 		// new hidWeights
	 		//cout << "new hid: " << endl;
			for(int k = 0; k < hid; k++)
	 		{
	 			if (rand()/(RAND_MAX + 1.0) < MUTATION_RATE)
	 			{
	 				normal_distribution<float> distribution(mu_hid[k], sqrt(MV));
	 				new_Whid[k] = distribution(generator);
				}
	 			else {
	 				new_Whid[k] = mu_hid[k]; // alternatively, Whid_i or _j (randomly)
				 }
	 			//cout << new_Whid[k] << endl;
			}
			// set weights into network
			myNetwork[x].setWeightsFromGA(new_Win, new_Whid);
			// take the agent out from the pool of potential offspring:
			myAgent[x].selected = true;
			
			// offspring created, update counter
			counter++;
		}
		x++;
		
		if(counter > offsp) 
		{ 
			cout << "problem in reproduce::do while loop" << endl;
			cout << "counter > offsp, should not occur!" << endl;
			cin.get();
		}
		
	}while(counter < offsp);
 	
 } // end of reproduceThreeLayersNN
 
 // write output file: weights of neural network
 void weightsToFile(NeuralNetwork myNetwork[], int nr_of_nn, int ID_selection[])
{
    
    if(HIDDEN == 0)
    {
    	ofstream myFile; // store weights of simple network architecture
    	int totalweights = (XsINPUT + 1) * OUTPUT; 
		float W[totalweights];
		
		myFile.open("weights.xls");
		
		for (int i = 0; i < nr_of_nn; i++)
		{
			myNetwork[ID_selection[i]].getWeights(W);
			writeFile(myFile, W, totalweights);	
		}
		
		myFile.close(); 
	}
	else
	{
		ofstream myFileinW; // file to store input weights
    	ofstream myFileOutW;// file to store outout weights
    	
		int in = (XsINPUT + 1)*HIDDEN;
    	int hid = (HIDDEN + 1)*OUTPUT;
		
    	float input[in];
    	float hidden[hid]; 
    	
    	//myFileinW.open("inWeights_NN.csv");
    	//myFileOutW.open("outWeights_NN.csv");
    	myFileinW.open("inWeights_NN.xls");
    	myFileOutW.open("outWeights_NN.xls");
    	
    	for (int i = 0; i < nr_of_nn; i++)
    	{  
			myNetwork[ID_selection[i]].getWeights(input, hidden);
        	writeFile(myFileinW, input, in);
        	writeFile(myFileOutW, hidden, hid);
		}
		
		myFileinW.close();
    	myFileOutW.close();
          
    } 
    
} // end of weights to file

// write file
void writeFile(ofstream &myFile, float *vector, int rows)
{
   for (int i = 0; i < rows; i++)
    {
        myFile << vector[i] << "\n";
    }    
}

// setTarget
void setTarget(float target[])
{
    int i = 0;
    target[i] = 10.0;
	i++;
	target[i] = 10.0;
}


// set coordinate range (min, max) based on segment. The segment indicate
// the quadrant where the cluster will be located
void setRangeBasedOnSegment(int segment, float &min, float &max, float Max_Dim)
{
	switch (segment)
	{
		case 0:
			min = 0;
			max = Max_Dim / 4;
			break;
		case 1:
			min = Max_Dim / 4;
			max = Max_Dim / 2;
			break;
		case 2:
			min = Max_Dim / 2;
			max = Max_Dim - (Max_Dim / 4);
			break;
		case 3:
			min = Max_Dim - (Max_Dim / 4);
			max = Max_Dim;
			break;
	}
}

