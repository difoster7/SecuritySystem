#pragma once

#include <vector>;
#include <random>;

#include "Passenger.h";
#include "SecurityQueue.h";
#include "SecurityStation.h";
#include "SecurityStats.h";

using namespace::std;

class SecuritySimulation
{
private:	
	int currentTime;	// seconds
	int arrivalTime;	// seconds
	int arrivalRate;	// passengersPerHour
	int lengthOfDay;	// hours
	int passengersServiced;
	vector<SecurityStats> dailyStats;
	SecurityQueue credentialQueue;
	SecurityStation credentialsStation;
	SecurityQueue scanningQueue;
	vector<SecurityStation> scanningStations;
	default_random_engine e;
	exponential_distribution<> expoRandNums;

	void tic();
	bool newArrival();
	void genNextArrivalTime();
	bool allStationsEmpty();
	void reset();
	void updateStats();

public:
	SecuritySimulation(int arrivalRate = 90, int lengthOfDay = 20);
	void setArrivalRate(int arrivalRate);
	void setLengthOfDay(int hours);
	void simulateDay();
	SecurityStats getStats();

};

