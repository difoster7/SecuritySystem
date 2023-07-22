#include "SecurityStats.h"

// PRECONDITION: daysTracked has already been incremented
float SecurityStats::calculateNewAverage(float num1, float num2, int numNewDays)
{
    return ((num1 * (this->daysTracked - numNewDays)) + (num2 * numNewDays)) / this->daysTracked;
}

void SecurityStats::addStats(SecurityStats newStats)
{
    addStats(newStats.getPassengersServiced(), newStats.getCredQueueTime(), newStats.getCredCheckTime(),
        newStats.getScanQueueTime(), newStats.getScanStationTime(), newStats.getDaysTracked());
}

void SecurityStats::addStats(int passengersServiced, float credQueueTime, float credCheckTime, float scanQueueTime, float scanStationTime, int numNewDays = 1)
{
    this->daysTracked += numNewDays;
    this->passengersServiced += passengersServiced;
    this->credQueueTime = calculateNewAverage(this->credQueueTime, credQueueTime, numNewDays);
    this->credCheckTime = calculateNewAverage(this->credCheckTime, credCheckTime, numNewDays);
    this->scanQueueTime = calculateNewAverage(this->scanQueueTime, scanQueueTime, numNewDays);
    this->scanStationTime = calculateNewAverage(this->scanStationTime, scanStationTime, numNewDays);
}

float SecurityStats::getStage1Time() const
{
    return this->credQueueTime + this->credCheckTime;
}

float SecurityStats::getStage2Time() const
{
    return this->scanQueueTime + this->scanStationTime;
}

float SecurityStats::getTotalTime() const
{
    return getStage1Time() + getStage2Time();
}

int SecurityStats::getPassengersServiced() const
{
    return this->passengersServiced;
}

float SecurityStats::getCredQueueTime() const
{
    return this->credQueueTime;
}

float SecurityStats::getCredCheckTime() const
{
    return this->credCheckTime;
}

float SecurityStats::getScanQueueTime() const
{
    return this->scanQueueTime;
}

float SecurityStats::getScanStationTime() const
{
    return this->scanStationTime;
}

int SecurityStats::getDaysTracked() const
{
    return this->daysTracked;
}
