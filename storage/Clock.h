#pragma once
#ifndef CLOCK
#define CLOCK

#include <time.h>
#include <iostream>
using namespace std;

class Clock {
public:
	clock_t startTime, endTime;
	double inter;

	void start() { startTime = clock(); }
	
	double end() 
	{ 
		endTime = clock();
		inter = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		return inter;
	}

	void print()
	{
		cout << inter << endl;
	}
};

#endif