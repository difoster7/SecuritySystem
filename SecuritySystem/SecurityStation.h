#pragma once
#include "Passenger.h"

class SecurityStation
{
private:
	Passenger passenger;
	int averageWaitTheoretical;
	int currentTime;
	int passengersServiced;
	float averageWaitActual;
	int currentWait;
	bool passengerDone;
	bool empty;

	void calculateNextWait();
	void init();

public:
	SecurityStation();
	SecurityStation(int averageWait) : averageWaitTheoretical(averageWait) { init(); };
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

