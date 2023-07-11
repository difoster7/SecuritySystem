#pragma once
#include "Passenger.h"

class SecurityStation
{
private:
	Passenger passenger;
	int averageWaitTimeTheoretical;
	int currentTime;
	int passengersServiced;
	float averageWaitActual;
	bool empty;
	int currentWait;
	bool passengerDone;

	void calculateNextWait();

public:
	void tic();
	void setPassenger(Passenger passenger);
	void reset();
	bool isEmpty() const;
	Passenger getPassenger() const;
	Passenger retrievePassenger();
	int getPassengersServiced() const;
	float getAverageWaitTime() const;
};

