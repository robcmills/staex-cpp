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
const int DEFAULT_MOVES[9][2] = {
	{1,78},
	{2,149},
	{4,291},
	{8,113},
	{16,170},
	{32,284},
	{64,393},
	{128,338},
	{256,228},
};

bool test_adjacents(map<int,int> adjacents) {
	// adjacent squares map
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_ADJACENTS[i][0];
		int value = DEFAULT_ADJACENTS[i][1];
		if (adjacents[key] != value) {
			cout << "FAIL: Expected staex.adjacent_squares_map[" << key << "] ";
			cout << "to equal " << value << " but instead got ";
			cout << adjacents[key] << endl;
			return false;
		}
	}
	return true;
}

bool test_moves(map<int,int> moves) {
	// rook movements
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_MOVES[i][0];
		int value = DEFAULT_MOVES[i][1];
		if (moves[key] != value) {
			cout << "FAIL: Expected staex.moves_map[" << key << "] ";
			cout << "to equal " << value << " but instead got ";
			cout << moves[key] << endl;
			return false;
		}
	}
	return true;
}

int main() {
	bool didPass = true;
	Staex staex;

	didPass = test_adjacents(staex.adjacent_squares_map);
	didPass = test_moves(staex.moves_map);

	if (didPass) {
		cout << "All tests passed." << endl;
	}
}
