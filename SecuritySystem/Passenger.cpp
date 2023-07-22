#include "Passenger.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

void Passenger::generateFirstName()
{
	string name = "default";

	switch (rand() % 20) {
	case 0: name = "Wade"; break;
	case 1: name = "Dave"; break;
	case 2: name = "Seth"; break;
	case 3: name = "Ivan"; break;
	case 4: name = "Riley"; break;
	case 5: name = "Gilbert"; break;
	case 6: name = "Jorge"; break;
	case 7: name = "Dan"; break;
	case 8: name = "Brian"; break;
	case 9: name = "Roberto"; break;
	case 10: name = "Daisy"; break;
	case 11: name = "Deborah"; break;
	case 12: name = "Isabel"; break;
	case 13: name = "Stella"; break;
	case 14: name = "Debra"; break;
	case 15: name = "Beverly"; break;
	case 16: name = "Vera"; break;
	case 17: name = "Angela"; break;
	case 18: name = "Lucy"; break;
	case 19: name = "Lauren"; break;
	}

	this->firstName = name;
}

void Passenger::generateLastName()
{
	string name = "default";
	
	switch (rand() % 20) {
	case 0: name = "Williams"; break;
	case 1: name = "Harris"; break;
	case 2: name = "Thomas"; break;
	case 3: name = "Robinson"; break;
	case 4: name = "Walker"; break;
	case 5: name = "Scott"; break;
	case 6: name = "Nelson"; break;
	case 7: name = "Mitchell"; break;
	case 8: name = "Morgan"; break;
	case 9: name = "Cooper"; break;
	case 10: name = "Howard"; break;
	case 11: name = "Davis"; break;
	case 12: name = "Miller"; break;
	case 13: name = "Martin"; break;
	case 14: name = "Smith"; break;
	case 15: name = "Anderson"; break;
	case 16: name = "White"; break;
	case 17: name = "Perry"; break;
	case 18: name = "Clark"; break;
	case 19: name = "Richards"; break;
	}

	this->lastName = name;
}

Passenger::Passenger()
{
	generateFirstName();
	generateLastName();
	this->waiting = 0;
}

void Passenger::tic()
{
	this->waiting++;
}

void Passenger::resetWait()
{
	this->waiting = 0;
}

int Passenger::getWaitingTime() const
{
	return this->waiting;
}

string Passenger::getFirstName() const
{
	return this->firstName;
}

string Passenger::getLastName() const
{
	return this->lastName;
}

ostream& operator<<(ostream& os, const Passenger& pass)
{
	return os << pass.firstName << " " << pass.lastName;
}
