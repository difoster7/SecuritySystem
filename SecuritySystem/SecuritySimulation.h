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
	double arrivalTime;	// seconds
	double arrivalRate;	// passengersPerSecond
	int lengthOfDay;	// seconds
	int passengersServiced;
	vector<SecurityStats> dailyStats;
	SecurityQueue credentialQueue;
	SecurityStation credentialsStation;
	SecurityQueue scanningQueue;
	vector<SecurityStation> scanningStations;
	default_random_engine e;
	exponential_distribution<> expoRandNums;

	void tic();
	void genNextArrivalTime();
	bool allStationsEmpty();
	void reset();
	void updateStats();

public:
	SecuritySimulation(double arrivalsPerHour = 90, int hoursInDay = 20);
	void setArrivalRate(double arrivalsPerHour);
	void setLengthOfDay(double hours);
	void simulateDay();
	SecurityStats getStats();

};

