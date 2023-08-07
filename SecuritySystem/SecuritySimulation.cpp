#include <ctime>;

#include "SecuritySimulation.h"

void SecuritySimulation::tic()
{
    this->currentTime++;
}

bool SecuritySimulation::newArrival()
{
    if (this->arrivalTime >= currentTime) return true;

    return false;
}

// generates this time of the next arrival (times are in seconds)
void SecuritySimulation::genNextArrivalTime()
{
    this->arrivalTime = this->currentTime + this->expoRandNums(this->e) * 60 * 60;
}

void SecuritySimulation::simulateDay()
{

    reset(); // reset each station before the day starts

    while (this->currentTime < this->lengthOfDay * 60 * 60 && !allStationsEmpty()) {
        if (newArrival()) { // check if a new passenger has arrived
            this->credentialQueue.enqueue(Passenger());
            this->passengersServiced++;
        }
        
        tic();  // tic self

        // if credential queue is not empty, and credentials station is empty, move passenger from queue to station
        if (!this->credentialQueue.isEmpty() && this->credentialsStation.isEmpty()) {
            this->credentialsStation.setPassenger(this->credentialQueue.dequeue());
        }

        this->credentialQueue.tic();    // tic credentials queue

        // if passenger is done at credential station, place in scanning queue
        if (this->credentialsStation.getPassengerDone()) {
            this->scanningQueue.enqueue(this->credentialsStation.getPassenger());
        }

        this->credentialsStation.tic(); // tic credentials station

        // move passengers from scanning queue to stations
        for (auto scanStation : this->scanningStations) {
            if (!this->scanningQueue.isEmpty() && scanStation.isEmpty()) {
                scanStation.setPassenger(this->scanningQueue.dequeue());
            }
        }

        this->scanningQueue.tic();  // tic scanning queue

        for (auto scanStation : this->scanningStations) {
            // empty any finished scanning stations
            if (scanStation.getPassengerDone()) {
                scanStation.getPassenger();
            }

            scanStation.tic();  // tic scanning stations
        }
    } // end while loop

    updateStats();
}

void SecuritySimulation::setArrivalRate(int arrivalRate)
{
    exponential_distribution<> expoRandNums2(arrivalRate);
    this->expoRandNums = expoRandNums2;

    this->arrivalRate = arrivalRate;
}

// arrivalRate is the number of arrivals per hour
// lengthOfDay is the number of hours in a day simulation
SecuritySimulation::SecuritySimulation(int arrivalRate, int lengthOfDay) : 
    currentTime (0), arrivalRate (arrivalRate), lengthOfDay (lengthOfDay), passengersServiced (0),
    dailyStats (), credentialQueue (SecurityQueue()), credentialsStation (SecurityStation(30)), expoRandNums (arrivalRate),
    scanningQueue (SecurityQueue()), scanningStations{ SecurityStation(150) , SecurityStation(150) ,  SecurityStation(150) ,  SecurityStation(150) }
{
    random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : time(nullptr);
    default_random_engine e2(seed);
    this->e = e2;

    genNextArrivalTime();

}

void SecuritySimulation::reset()
{
    this->passengersServiced = 0;

    this->credentialQueue.reset();
    this->credentialsStation.reset();
    this->scanningQueue.reset();
    for (auto scanStation : this->scanningStations) {
        scanStation.reset();
    }
}
void SecuritySimulation::updateStats()
{
    // calculate the average wait time from the scanning stations
    float aveScanStationWait = 0;
    for (auto station : this->scanningStations) {
        aveScanStationWait += station.getAverageWaitTime();
    }
    aveScanStationWait /= 4;

    // create a security stat for the day
    SecurityStats dailyStat;
    dailyStat.addStats(this->passengersServiced, this->credentialQueue.getAverageWait(),
        this->credentialsStation.getAverageWaitTime(), this->scanningQueue.getAverageWait(), aveScanStationWait, 1);

    // add todays stats to the list
    this->dailyStats.push_back(dailyStat);
}
;

void SecuritySimulation::setLengthOfDay(int hours)
{
    this->lengthOfDay;
}

bool SecuritySimulation::allStationsEmpty()
{
    if (!this->credentialQueue.isEmpty()) return false;

    if (!this->credentialsStation.getPassengerDone()) return false;

    if (!this->scanningQueue.isEmpty()) return false;

    for (auto station : this->scanningStations) {
        if (!station.getPassengerDone()) return false;
    }

    return true;
}

// returns a summary of stats from all simulated days.
SecurityStats SecuritySimulation::getStats()
{
    SecurityStats returnStats;
    for (auto stats : this->dailyStats) {
        returnStats.addStats(stats);
    }
    return returnStats;
}
