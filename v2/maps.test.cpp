#include <iostream>

using namespace std;

#include "maps.h"

const int POWERS[9] = {1,2,4,8,16,32,64,128,256};
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

std::string b(int integer) {
	return std::bitset<9>(integer).to_string();
}

void assert_is_equal(int a, int b, std::string id) {
	if (a != b) {
		cout << "FAIL: Expected " << a << " to equal " << b << " in " << id << endl;
	}
}

void test_powers(map<int,int>* powers) {
	for (int i = 0; i < 9; ++i) {
		assert_is_equal((*powers)[i], POWERS[i], "test_powers");
	}
}

void test_adjacents(map<int,int>* adjacents) {
	// adjacent squares map
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_ADJACENTS[i][0];
		int value = DEFAULT_ADJACENTS[i][1];
		assert_is_equal((*adjacents)[key], value, "test_adjacents");
	}
}

void test_moves(map<int,int>* moves) {
	// rook movements
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_MOVES[i][0];
		int value = DEFAULT_MOVES[i][1];
		assert_is_equal((*moves)[key], value, "test_moves");
	}
}

int main() {
	map<int,int> pow_map = build_pow_map(9);
	test_powers(&pow_map);

	map<int,int> adjacents_map = build_adjacents_map(9, 3, &pow_map);
	test_adjacents(&adjacents_map);

	map<int,int> moves_map = build_moves_map(9, 3, &pow_map);
	test_moves(&moves_map);

	cout << "Tests complete." << endl;
}
