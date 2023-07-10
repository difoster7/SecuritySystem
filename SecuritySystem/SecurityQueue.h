#pragma once
#include <queue>
#include "Passenger.h";

using namespace std;

class SecurityQueue
{
private: 
	queue<Passenger> passengerQueue;
	int passengersServiced;
	float averageWait;
	
	void updateAverageWait(int lastWaitTime);

public:
	void tic();
	void enqueue(Passenger* passenger);
	Passenger* dequeue();
	void reset();
	float getAverageWait() const;
	int getPassengersServiced() const;
	bool isEmpty() const;
};

