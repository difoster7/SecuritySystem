#include <iostream>;
#include "Passenger.h";

using namespace std;

int main()
{

	for (int i = 0; i < 50; i++) {
		Passenger pass = Passenger();
		cout << pass << endl;
	}
}