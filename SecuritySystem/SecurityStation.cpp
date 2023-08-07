#include "SecurityStation.h"
#include <iostream>;

void SecurityStation::calculateNextWait()
{
	// update time next passenger is done
	double wait = this->expoRandNums(this->e);
	this->currentWait = this->currentTime + wait;

	// update average wait
	this->averageWaitActual = (this->averageWaitActual * this->passengersServiced + wait) / (this->passengersServiced + 1);
}

SecurityStation::SecurityStation(int averageCheckTime) : averageCheckTime(averageCheckTime), currentTime (0),
	passengersServiced (0), averageWaitActual (0), currentWait (0), passengerDone (true), empty(true)
{
	random_device seeder;
	const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	this->e = default_random_engine(seed);

	this->expoRandNums = exponential_distribution<>(1 / (double)this->averageCheckTime);
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

// Precondition: Security Station is currently empty
void SecurityStation::setPassenger(Passenger passenger)
{
	passenger.resetWait();
	this->passengerDone = false;
	this->empty = false;
	this->passenger = passenger;
	calculateNextWait();
}


void SecurityStation::reset()
{
	this->averageWaitActual = 0;
	this->passengersServiced = 0;
}

// Precondition: Security Station currently contains a passenger marked as Done
Passenger SecurityStation::getPassenger()
{
	this->empty = true;
	this->passengersServiced++;
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

double SecurityStation::getAverageWaitTime() const
{
	return this->averageWaitActual;
}

bool SecurityStation::isEmpty() const
{
	return this->empty;
}
