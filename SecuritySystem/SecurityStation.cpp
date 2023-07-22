#include "SecurityStation.h"

void SecurityStation::calculateNextWait()
{
	//TODO: update this with exponential function
	this->currentWait = 30;
}

// initializes member variable (constructor helper function)
void SecurityStation::init()
{
	this->averageWaitTheoretical = 0;
	this->currentTime = 0;
	this->passengersServiced = 0;
	this->averageWaitActual = 0;
	this->currentWait = 0;
	this->passengerDone = true;
}

SecurityStation::SecurityStation()
{
	this->averageWaitTheoretical = -1;
	init();
}

// tics current time and current passengers time
// if current time is greater than or equal to the current wait, 
// marks the passenger as done
void SecurityStation::tic()
{
	this->currentTime++;
	this->passenger.tic();
	if (this->currentTime >= this->currentWait) {
		this->passengerDone = true;
	}
}

void SecurityStation::setPassenger(Passenger passenger)
{
	passenger.resetWait();
	this->passengerDone = false;
	this->passenger = passenger;
	calculateNextWait();
}

void SecurityStation::setAverageWaitTime(int averageWait)
{
	this->averageWaitActual = averageWait;
}

void SecurityStation::reset()
{
	this->averageWaitActual = 0;
	this->passengersServiced = 0;
}

Passenger SecurityStation::getPassenger() const
{
	return this->passenger;
}

int SecurityStation::getPassengersServiced() const
{
	return this->passengersServiced;
}

float SecurityStation::getAverageWaitTime() const
{
	return this->averageWaitActual;
}
