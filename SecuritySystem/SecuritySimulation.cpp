#include <ctime>;

#include "SecuritySimulation.h"

void SecuritySimulation::tic()
{
    this->currentTime++;
}

// generates time the next passenger arrives
void SecuritySimulation::genNextArrivalTime()
{
    this->arrivalTime = this->currentTime + this->expoRandNums(this->e);// this->expoRandNums(this->e);
}

void SecuritySimulation::simulateDay()
{
    int hour = 0;
    reset(); // reset each station before the day starts

    while (this->currentTime < this->lengthOfDay || (this->currentTime > this->lengthOfDay && !allStationsEmpty())) {

        if ((this->currentTime >= this->arrivalTime) && (this->currentTime < this->lengthOfDay)) { // check if a new passenger has arrived
            this->credentialQueue.enqueue(Passenger());
            this->passengersServiced++;
            genNextArrivalTime();
        }
        
        tic();  // tic self

        // if credential queue is not empty, and credentials station is empty, move passenger from queue to station
        if (!this->credentialQueue.isEmpty() && this->credentialsStation.isEmpty()) {
            this->credentialsStation.setPassenger(this->credentialQueue.dequeue());
        }

        this->credentialQueue.tic();    // tic credentials queue

        // if passenger is done at credential station, place in scanning queue
        if (this->credentialsStation.getPassengerDone() && !this->credentialsStation.isEmpty()) {
            this->scanningQueue.enqueue(this->credentialsStation.getPassenger());
        }

        this->credentialsStation.tic(); // tic credentials station
        
        // move passengers from scanning queue to stations
        for (int i = 0; i < scanningStations.size(); i++) {
            if (!this->scanningQueue.isEmpty() && scanningStations[i].isEmpty()) {
                //this->scanningQueue.dequeue();
                scanningStations[i].setPassenger(this->scanningQueue.dequeue());
            }
        }

        this->scanningQueue.tic();  // tic scanning queue

        // empty finished scanning stations and tic each
        for (int i = 0; i < scanningStations.size(); i++) {
            if (scanningStations[i].getPassengerDone() && !scanningStations[i].isEmpty()) {
                scanningStations[i].getPassenger();
            }
            scanningStations[i].tic();
        }

    } // end while loop

    updateStats();
}

void SecuritySimulation::setArrivalRate(double arrivalsPerHour)
{
    this->arrivalRate = arrivalsPerHour / (60 * 60);

    this->expoRandNums = exponential_distribution<> (arrivalRate);
}

// arrivalRate is the number of arrivals per hour
// lengthOfDay is the number of hours in a day simulation
SecuritySimulation::SecuritySimulation(double arrivalsPerHour, int hoursPerDay) :  currentTime (0), 
    arrivalRate (arrivalsPerHour / (60 * 60)), lengthOfDay (hoursPerDay * 60 * 60), passengersServiced (0), arrivalTime (0),
    dailyStats (), credentialQueue (SecurityQueue()), credentialsStation (SecurityStation(30)), scanningQueue (SecurityQueue())
{

    for (int i = 0; i < 4; i++) {
        scanningStations.push_back(SecurityStation(150));
   }

    random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : time(nullptr);
    this->e = default_random_engine(seed);
    this->expoRandNums = exponential_distribution<>(arrivalRate);

    genNextArrivalTime();

}

void SecuritySimulation::reset()
{
    this->passengersServiced = 0;
    this->currentTime = 0;

    this->credentialQueue.reset();
    this->credentialsStation.reset();
    this->scanningQueue.reset();
    for (auto scanStation : this->scanningStations) {
        scanStation.reset();
    }

    genNextArrivalTime();
}
void SecuritySimulation::updateStats()
{
    // calculate the average wait time from the scanning stations
    double aveScanStationWait = 0;
    for (const auto& station : this->scanningStations) {
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

void SecuritySimulation::setLengthOfDay(double hours)
{
    this->lengthOfDay = hours * 60 * 60;
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
    for (auto& const stats : this->dailyStats) {
        returnStats.addStats(stats);
    }
    
    return returnStats;
}
