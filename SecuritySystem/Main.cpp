#include <iostream>;
#include "Passenger.h";
#include "SecurityQueue.h";

using namespace std;

int main()
{
	SecurityQueue secQueue;

	for (int i = 0; i < 50; i++) {
		Passenger pass = Passenger();
		secQueue.enqueue(pass);
		cout << pass << endl;
	}

	while (!secQueue.isEmpty()) {
		secQueue.tic();
		if (rand() % 2 == 0) {
			Passenger pass = secQueue.dequeue();
			cout << pass << " exited the queue.\n";
		}
	}

	cout << "Average wait time: " << secQueue.getAverageWait() << endl;
}