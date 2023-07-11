#include "SecurityQueue.h"

void SecurityQueue::updateAverageWait(int lastWaitTime)
{
    this->averageWait = (this->averageWait * (this->passengersServiced - 1) + lastWaitTime) 
        / this->passengersServiced;
}

// tic's each passenger in the queue
void SecurityQueue::tic()
{
    for (int i = 0; i < this->passengerQueue.size(); i++) {
        auto pass = this->passengerQueue.front();
        pass.tic();
        this->passengerQueue.pop();
        this->passengerQueue.push(pass);
    }
}

void SecurityQueue::enqueue(Passenger passenger)
{
    this->passengerQueue.push(passenger);
}

Passenger SecurityQueue::dequeue()
{
    this->passengersServiced++; // update total passengers services

    Passenger pass = this->passengerQueue.front();
    updateAverageWait(pass.getWaitingTime());   // update average wait time

    this->passengerQueue.pop(); // remove front passenger from queue

    return pass;   // return reference to removed passenger
}

void SecurityQueue::reset()
{
    this->passengersServiced = 0;
}

float SecurityQueue::getAverageWait() const
{
    return this->averageWait;
}

int SecurityQueue::getPassengersServiced() const
{
    return this->passengersServiced;
}

bool SecurityQueue::isEmpty() const
{
    return this->passengerQueue.empty();
}
