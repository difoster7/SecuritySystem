#include <iostream>;
#include "SecuritySimulation.h";
#include "SecurityStation.h";

using namespace std;

int main()
{

	SecurityStation foo(150);

	int time = 0;

	while (time < (3600*5) || (time > (3600*5) && !foo.isEmpty())) {
		if (foo.isEmpty()) {
			foo.setPassenger(Passenger());
		}
		time++;
		foo.tic();
		if (foo.getPassengerDone()) {
			foo.getPassenger();
		}
	}

	cout << "Passengers serviced in one hour: " << foo.getPassengersServiced() << endl;
	cout << "Average minutes per passenger: " << (60*5) / (double)foo.getPassengersServiced() << endl;
	cout << "Average minutes per passenger: " << foo.getAverageWaitTime()  << endl;


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// BELOW CODE IS FOR 90 PASSENGERS ARRIVING IN STATIONS EVERY HOUR
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//random_device seeder;
	//const auto seed = seeder.entropy() ? seeder() : time(nullptr);

	//default_random_engine e(seed);
	//exponential_distribution<> expoRandNums(90);

	//double arrivalTime = 0;
	//int numArrivals = 0;
	//double aveArrivals = 0;



	//for (int time = 0; time < 3600; time++) {
	//	if (arrivalTime <= time) {
	//		arrivalTime += expoRandNums(e) * 60 * 60;
	//		cout << "Arrival at: " << time << endl;
	//		numArrivals++;
	//	}
	//}

}