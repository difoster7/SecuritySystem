#include "SecurityStation.h"

void SecurityStation::calculateNextWait()
{
	//TODO: update this with exponential function
	this->currentWait = 30;
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
	this->passenger = passenger;
}

void SecurityStation::reset()
{
	this->averageWaitActual = 0;
	this->passengersServiced = 0;
}

bool SecurityStation::isEmpty() const
{
	return this->empty;
}

// returns the current passenger without marking the security center as empty
// PRECONDITION: Security Station is not empty
Passenger SecurityStation::getPassenger() const
{
	return this->passenger;
}

// returns the current passenger and marks the security center as empty
// PRECONDITION: Security Station is not empty
Passenger SecurityStation::retrievePassenger()
{
	this->empty = true;
	this->passengerDone = false;
	calculateNextWait();

	return getPassenger();
}

int SecurityStation::getPassengersServiced() const
{
	return this->passengersServiced;
}

float SecurityStation::getAverageWaitTime() const
{
	return this->averageWaitActual;
}
