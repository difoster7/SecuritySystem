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
	float averageWaitActual;
	int currentWait;
	bool passengerDone;
	bool empty;
	default_random_engine e;
	exponential_distribution<> expoRandNums;

	void calculateNextWait();
	void init();

public:
	SecurityStation();
	SecurityStation(int averageCheckTime) : averageCheckTime(averageCheckTime) { init(); };
	void tic();
	void setPassenger(Passenger passenger);
	void setAverageWaitTime(int averageWait);
	void reset();
	Passenger getPassenger();
	int getPassengersServiced() const;
	float getAverageWaitTime() const;
	bool getPassengerDone() const;
	bool isEmpty() const;
};

