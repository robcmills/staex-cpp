#include <iostream>
using namespace std;

#include "staex.h"

const int DEFAULT_ADJACENTS[9][2] = {
	{256,416},
	{128,464},
	{64,232},
	{32,372},
	{16,186},
	{8,93},
	{4,46},
	{2,23},
	{1,11},
};

int main() {
	bool didPass = true;
	Staex staex;

	// adjacent squares map
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_ADJACENTS[i][0];
		int value = DEFAULT_ADJACENTS[i][1];
		if (staex.adjacent_squares_map[key] != value) {
			cout << "FAIL: Expected staex.adjacent_squares_map[" << key << "] ";
			cout << "to equal " << value << " but instead got ";
			cout << staex.adjacent_squares_map[key] << endl;
			didPass = false;
		}
	}

	if (didPass) {
		cout << "All tests passed." << endl;
	}
}