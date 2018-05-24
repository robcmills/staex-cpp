#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int main()
{
	// std::mt19937_64::result_type seed = 1;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 engine(seed);
	std::uniform_int_distribution<int> distribution(0, 1);
	for (int i=0; i<10; ++i) {
		// cout << distribution(engine) << endl;
		cout << (seed % 2 > 0) << endl;
	}
}