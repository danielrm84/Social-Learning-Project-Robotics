/*-----------------------------------------------------------------------------
 *                      		RUN_WORLD
 *
 * Author:      Daniel Romero Mujalli
 * Last update:  14/ 2/2017
 *
 * Summary:      This file contains the declaration of all functions used
 *				 during the run World phase of the main program. This
 *				 phase consists of moving the agents, tracking their position,
 *				 perceiving neighbors, running the perceptron, updating their 
 *				 energy, cheking for mortality, creating newborn agents, and 
 *				 applying inheritance depending on the scenario of behavior. 
 *
 *               The declaration of these functions are in the file:
 *				 /include/runWorld/runWorld.h
 *
 *---------------------------------------------------------------------------*/

#include "../miscellaneous/miscellaneous.h"

/* checkWhereIsTheAgent
   This function checks if the agent is located in or outside patches and
   updates the input to the perceptron affecting perception of ground color	 */
void checkWhereIsTheAgent(Agent myAgent[], int i, Agent feedingAreas[], 
					 	  int n_areas, float inX[])
{
    float d, x0, y0, x1, y1, r;		/* variables for distance, radius and 
									   position								 */
    int m = 0;						/* index for inX[] input to perceptron	 */
    
    
    x0 = myAgent[i].getxPosition();
    y0 = myAgent[i].getyPosition();
	
    /* Initialization of agent i											 */  
    myAgent[i].white = false;
    myAgent[i].black = false;
    
    /* Check whether agent i is located in a given feeding area		     	 */ 
    for (int j = 0; j < n_areas; j++)
    {
        x1 = feedingAreas[j].getxPosition();
        y1 = feedingAreas[j].getyPosition();
        r  = feedingAreas[j].getRadius();
        d = getDistance(x0, y0, x1, y1);
        
        /* Check Black area													 */
        if(d < r && j == 0)
        {
        	// update input to perceptron to black area
            inX[m] = 0.0; m++; inX[m] = 1.0; m = 0;
            myAgent[i].black = true;
        }
        /* Check White area													 */
        else if(d < r && j == 1)
        {
        	// update input to perceptron to white area
            inX[m] = 1.0; m++; inX[m] = 0.0; m = 0;
            myAgent[i].white = true;
            
            /* Refresh agent i energy according to effect of feeding area	 */
            
        }
        /* Check grey Area 													 */
        else if(!myAgent[i].white && !myAgent[i].black)
    	{
        	inX[m] = 0.0; m++; inX[m] = 0.0; m = 0;    
    	}
        if(j > 2) // catch exception
		{ 
			cout << "SITES > 2: please update code 'whereIsTheAgent' to allow"; 
			cout << "more than 2 feeding areas" << endl;
			cin.get();
		}
    } 
}
/*---------------------- End of checkWhereIsTheAgent function ---------------*/

/* updateAgentEnergy
   This function updates agent energy according to its location (whether white,
   black or grey patch) and to othe scenario of environment.				 */
void updateAgentEnergy (Agent myAgent[], int i, int z, int max_iterations, 
						float black_effect, float white_effect, 
						float grey_effect)
{
	float e = 0.0;						/* effect on agent energy			 */
	int m;
	// if in black area
	if(myAgent[i].black)
	{
		e = black_effect;
            
        #ifdef ABRUPT_CHANGE
            
        if(z < max_iterations / 2){e = energy_b;}
        else{e = white_effect;}
            
        #endif /* ABRUPT_CHANGE*/
            
        myAgent[i].refreshEnergy(e);
	}
	// if in white area
	else if(myAgent[i].white)
	{
		e = white_effect;
            
        #ifdef ABRUPT_CHANGE
            
        if(z < max_iterations / 2){ e = energy_w; }
        else{ e = black_effect; }
            
        #endif /* ABRUPT_CHANGE*/
            
        myAgent[i].refreshEnergy(e);
	}
	// if in grey area
	if(!myAgent[i].white && !myAgent[i].black)// Grey
    {
        e = grey_effect;
        myAgent[i].refreshEnergy(e);    
    }
    else if(myAgent[i].white && myAgent[i].black) // catch error: white and 
												  // black same time
    {
    	cout << "error in updateAgentEnergy: agent simultaneously in "; 
		cout <<	"white and black areas" << endl;
    	cin.get();
	}
}
/*---------------------- End of updateAgentEnergy function ------------------*/

/* checkNeighbors
   This function tells to agents perceptron the number of neighbors
   located in the same patch.
   This function only works for Mixed and SL								 */
void checkNeighbors(Agent myAgent[], int n, Perceptron myPerceptron[], 
 					int agents_inWhite, int agents_inBlack)
{
	for (int i = 0; i < n; i++)
    {
    	// if white
        if(myAgent[i].white){myPerceptron[i].setNeighbors(agents_inWhite);}
		// if black 
        if(myAgent[i].black){myPerceptron[i].setNeighbors(agents_inBlack);} 
        // if grey
        if(!myAgent[i].white && !myAgent[i].black)         		   
        {myPerceptron[i].setNeighbors(1);}
        // catch error
        else if(myAgent[i].white && myAgent[i].black)			
        {
            cout << "error >> NEIGHBORS*BlackandWhiteSameTime " << endl;
            cin.get();
        }
        
        #ifdef DEBUG
        // cout << "NEIGHBORS " << myPerceptron[i].getNeighbors() << endl;
        #endif
    }
}
/*---------------------- End of checkNeighbors function ---------------------*/

/* runPerceptron
   feedforward, and modify perceptron weights through learning when apply	 */
void runPerceptron(Perceptron myPerceptron[], int agent_i, float groundTarget)
{

	#ifdef MIXED
    	
    myPerceptron[agent_i].runMixedLearning(groundTarget);
        
    #endif
        
    #ifdef SOCIAL
        
    myPerceptron[agent_i].runSocialLearning(groundTarget);
        
    #endif
        
    #ifdef ASOCIAL
        
    myPerceptron[agent_i].runIndividualLearning(groundTarget);
        
    #endif
        
    #ifdef GEN_EVOL
        
    myPerceptron[agent_i].runGeneticEvolution();
        
    #endif
        
    #ifdef RND_SEARCH
        
    myPerceptron[agent_i].runRandomSearch();
        
    #endif
}
/*---------------------- End of runPerceptron function ----------------------*/

/* replaceTheAgent: 
   replace the dead agent with a newborn in a random positon, with full 
   energy, random orientation and, located outside the patches      		 */
void replaceTheAgent(Agent myAgent[], int i, Agent patches[], float max_x, 
					 float max_y, float max_vel, float radius, float max_e)
{
	// variables to store agent properties
	float x, y, r;
	// variables to store patch properties and measure distance
	float x0, y0, r0, x1, y1, r1, d1, d2;
	
	// store position and size of patches
	// patch 0:
	x0 = patches[0].getxPosition();
	y0 = patches[0].getyPosition();
	r0 = patches[0].getRadius();
	// patch 1:
	x1 = patches[1].getxPosition();
	y1 = patches[1].getyPosition();
	r1 = patches[1].getRadius();
	
	// place the new agent outside the patches
	do
    {
    	myAgent[i] = Agent(max_x, max_y, max_vel, radius, max_e);
                x = myAgent[i].getxPosition();
                y = myAgent[i].getyPosition();
                r = myAgent[i].getRadius();
                d1 = getDistance(x0, y0, x, y);
                d2 = getDistance(x1, y1, x, y);
            }while(d1 < (r0 + r) || d2 < (r1 + r));
}
/*---------------------- End of replaceTheAgent function --------------------*/

/* runInheritance: 
   the newborn inherits traits from alive agents. Weight values are reset to 
   default 																	 */
void runInheritance(Agent myAgent[], int i, int n, Perceptron myPerceptron[], 
     NeuralNetwork myNetwork[], float lrate, double rnd_w)
{	
    int rn;					/* to select random robot						 */
    float sumE = 0.0;
    bool done = false;

    /* check if all robots are dead 										 */ 
    for (int j = 0; j < n; j++){sumE += myAgent[j].getEnergy();}
    
	if(sumE <= 0) 		/* all dead. No inheritance							 */ 
    {
    	#ifdef MIXED
    	
    	myPerceptron[i] = myPerceptron[i];
    	myPerceptron[i].mutateOmega();
    	myPerceptron[i].setNoPreference();
    	myAgent[i].resetAge();
    	myNetwork[i] = myNetwork[i];
    	
    	#endif
		
		#ifdef SOCIAL
    	
        myPerceptron[i].startSocialLearning(lrate);
        myAgent[i].resetAge();
        myNetwork[i] = myNetwork[i];
		
		#endif
		
		#ifdef ASOCIAL
		
		myPerceptron[i].startIndividualLearning(lrate);
		myAgent[i].resetAge();
		myNetwork[i] = myNetwork[i];
		
		#endif 
		
		#ifdef GEN_EVOL
		
		myPerceptron[i] = myPerceptron[i];
		myPerceptron[i].mutateWeights();
		myAgent[i].resetAge();
		myNetwork[i] = myNetwork[i];
		
		#endif
		
		#ifdef RND_SEARCH
		
		myPerceptron[i].startRandomSearch(rnd_w);
		myAgent[i].resetAge();
		myNetwork[i] = myNetwork[i];
		
		#endif
    }
    
    /* there are still robots alive						 					 */ 
    else
    {
        done = false; 							/* loop initialization 		 */ 
        do
        {
            rn = (rand() % n); 					/* random number [0, N -1]	 */ 
            if(myAgent[rn].getEnergy() > 0.0)
            {
            	// inheritance occurs:
                #ifdef MIXED
    	
    			myPerceptron[i] = myPerceptron[rn];
    			myPerceptron[i].mutateOmega();
    			myPerceptron[i].setNoPreference();
    			myAgent[i].resetAge();
    			//myNetwork[i] = myNetwork[rn];
    	
    			#endif
		
				#ifdef SOCIAL
    	
        		myPerceptron[i].startSocialLearning(lrate);
        		myAgent[i].resetAge();
        		//myNetwork[i] = myNetwork[rn];
		
				#endif
		
				#ifdef ASOCIAL
		
				myPerceptron[i].startIndividualLearning(lrate);
				myAgent[i].resetAge();
				//myNetwork[i] = myNetwork[rn];
		
				#endif 
		
				#ifdef GEN_EVOL
		
				myPerceptron[i] = myPerceptron[rn];
				myPerceptron[i].mutateWeights();
				myAgent[i].resetAge();
				//myNetwork[i] = myNetwork[rn];
		
				#endif
			
				#ifdef RND_SEARCH
		
				myPerceptron[i].startRandomSearch(rnd_w);
				myAgent[i].resetAge();
				//myNetwork[i] = myNetwork[rn];
		
				#endif
                done = true;
            }
        }while(!done);
    }
}
/*---------------------- End of runInheritance function ---------------------*/
