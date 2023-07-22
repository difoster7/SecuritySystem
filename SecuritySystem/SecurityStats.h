#pragma once
#include <iostream>

class SecurityStats
{
private:
	int passengersServiced;
	float credQueueTime;
	float credCheckTime;
	float scanQueueTime;
	float scanStationTime;
	int daysTracked;

	float calculateNewAverage(float num1, float num2, int numNewDays);

public:
	void addStats(SecurityStats newDay);
	void addStats(int passengersServiced, float credQueueTime, float credCheckTime, float scanQueueTime, float scanStationTime, int numNewDays);
	float getStage1Time() const;
	float getStage2Time() const;
	float getTotalTime() const;
	int getPassengersServiced() const;
	float getCredQueueTime() const;
	float getCredCheckTime() const;
	float getScanQueueTime() const;
	float getScanStationTime() const;
	int getDaysTracked() const;

	static std::string convertToMinutes(int seconds);

	friend std::ostream& operator<<(std::ostream& os, const SecurityStats& ss);
};

