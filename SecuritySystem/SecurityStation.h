#pragma once

#include <random>
#include "Passenger.h"


class SecurityStation
{
private:
	Passenger passenger;
	int averageCheckTime;	// average number of seconds it takes for a passenger to pass through the station
	int currentTime;	// seconds
	int passengersServiced;
	double averageWaitActual;
	double currentWait;
	bool passengerDone;
	bool empty;
	default_random_engine e;
	exponential_distribution<> expoRandNums;

	void calculateNextWait();

public:
	SecurityStation(int averageCheckTime);
	void tic();
	void setPassenger(Passenger passenger);
	void reset();
	Passenger getPassenger();
	int getPassengersServiced() const;
	double getAverageWaitTime() const;
	bool getPassengerDone() const;
	bool isEmpty() const;
};

