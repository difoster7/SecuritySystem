#include <iostream>;
#include "SecuritySimulation.h";

using namespace std;

int main()
{
	int numSimDays = 5;

	SecuritySimulation secSim(90, 20);

	for (int i = 0; i < numSimDays; i++) {
		secSim.simulateDay();
	}

	cout << secSim.getStats();
}