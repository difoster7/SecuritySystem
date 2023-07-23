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
	this->empty = true;
}

// default constructor
// averageWaitTheoretical set to -1 to indicate it has not been set yet
SecurityStation::SecurityStation() : averageWaitTheoretical (-1)
{
	init();
}

SecurityStation::SecurityStation(int averageWait) : averageWaitTheoretical (averageWait)
{
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
	this->empty = false;
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

Passenger SecurityStation::getPassenger()
{
	this->empty = true;
	return this->passenger;
}

bool SecurityStation::getPassengerDone() const
{
	return this->passengerDone;
}

int SecurityStation::getPassengersServiced() const
{
	return this->passengersServiced;
}

float SecurityStation::getAverageWaitTime() const
{
	return this->averageWaitActual;
}

bool SecurityStation::isEmpty() const
{
	return this->empty;
}
