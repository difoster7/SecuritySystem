#pragma once
#include <string>;

using namespace std;

class Passenger
{
private:
	string firstName;
	string lastName;
	int waiting;

	void generateFirstName();
	void generateLastName();

public:
	Passenger();
	Passenger(string firstName, string lastName) : firstName(firstName), lastName(lastName), waiting(0) {};
	void tic();
	void resetWait();
	int getWaitingTime() const;
	string getFirstName() const;
	string getLastName() const;
	friend ostream& operator<<(ostream& os, const Passenger &pass);
};