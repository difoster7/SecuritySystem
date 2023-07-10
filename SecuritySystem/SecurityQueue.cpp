#include "SecurityQueue.h"

void SecurityQueue::updateAverageWait(int lastWaitTime)
{
}

void SecurityQueue::tic()
{
}

void SecurityQueue::enqueue(Passenger* passenger)
{
    this->passengerQueue.push(&passenger);
}

Passenger* SecurityQueue::dequeue()
{
    return nullptr;
}

void SecurityQueue::reset()
{
}

float SecurityQueue::getAverageWait() const
{
    return 0.0f;
}

int SecurityQueue::getPassengersServiced() const
{
    return 0;
}

bool SecurityQueue::isEmpty() const
{
    return false;
}
