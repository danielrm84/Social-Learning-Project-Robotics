// THIS PROGRAM HELPS ME TEST METHODS BEFORE IMPLEMENTATION INTO LARGER
// PROJECT

#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
 #include "../include/miscellaneous/miscellaneous.h"

void setRangeBasedOnSegment(int segment, float &min, float &max, float Max_Dim);

void testMissingArg(int arg1, int arg2);

int testTwoFunctionsSameName(int arg1);

int testTwoFunctionsSameName(int arg1, int arg2);

int main () {
	
	int rn;
	/* 
	float min, max, Max_X, Max_Y;
	
	
	// reset seed
	srand(time(NULL));
	
	// random integer values from 0 to 10
	for (int i = 0; i < 10; i++){
		std::cout << "random value (0,1): " << rand()/(RAND_MAX + 1.0) << std::endl;
	}
	
	// convert float to integer
	float f = 33.34;
	int i = (int)f;
	//std::cout << "integer: " << i << std::endl;
	
	// random normal
	// change seed every time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); 
	std::default_random_engine generator (seed);
	std::normal_distribution<float> distribution(0,1.0);
	
	for (int i = 0; i < 10; i++) 
	{ 
		std::normal_distribution<float> myDist(i,1.0);
		std::cout << myDist(generator) << std::endl;
	}
	
	std::cout << 100 % 4 << std::endl;
	
	// set values x, y coordinates
	Max_X = Max_Y = 1000;
	
	// set range on x coordinate
	rn = rand();
	std::cout << "segment x: " << rn << std::endl;
	setRangeBasedOnSegment(rn, min, max, Max_X);
	std::cout << "minx = " << min << " maxx = " << max << std::endl;
	
	// set range on y coordinate
	rn = rand() % 4;
	std::cout << "segment y: " << rn << std::endl;
	setRangeBasedOnSegment(rn, min, max, Max_Y);
	std::cout << "miny = " << min << " maxy = " << max << std::endl;
	
	// random floating value within min, max range
	for(int i = 0; i < 100; i++)
	{
		std::cout <<   2 + (10 - 2*2)*rand()/(RAND_MAX + 1.0) << std::endl;
	}
	
	
	testMissingArg(1, 22);
	
	std::cout << "functions equal name: " << std::endl;
	std::cout << testTwoFunctionsSameName(10) << std::endl;
	std::cout << testTwoFunctionsSameName(10,4) << std::endl;
	
	*/
	
	// test sensor class
	
	Sensor mySensor;
	
	mySensor.setCenter(0, 0);
	
	std::cout << mySensor.getxCor() << std::endl;
	std::cout << mySensor.getyCor() << std::endl;
	
	
	
	return 0;
}

void testMissingArg(int arg1, int arg2)
{
	
	if(!arg2) { std::cout << "only arg1: " << arg1 << std::endl;}
	else { std::cout << "arguments 1 and 2 detected! " << arg1 << " and "  << arg2 << std::endl;}
	
}
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

int testTwoFunctionsSameName(int arg1)
{
	arg1++;
	return (arg1);
}

int testTwoFunctionsSameName(int arg1, int arg2)
{
	return (arg1 + arg2);
}
