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

std::string b(int integer) {
	return std::bitset<9>(integer).to_string();
}

void assert_is_equal(int a, int b, std::string id) {
	if (a != b) {
		cout << "FAIL: Expected " << a << " to equal " << b << " in " << id << endl;
	}
}

void test_adjacents(map<int,int> adjacents) {
	// adjacent squares map
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_ADJACENTS[i][0];
		int value = DEFAULT_ADJACENTS[i][1];
		assert_is_equal(adjacents[key], value, "test_adjacents");
	}
}

void test_moves(map<int,int> moves) {
	// rook movements
	for (int i = 0; i < 9; ++i) {
		int key = DEFAULT_MOVES[i][0];
		int value = DEFAULT_MOVES[i][1];
		assert_is_equal(moves[key], value, "test_moves");
	}
}

void test_default_valid_stacks(int valid_stacks) {
	assert_is_equal(valid_stacks, 416, "test_default_valid_stacks");
}

void test_build_valid_stacks(Staex staex) {
	// test exclude squares already occupied by current player
	staex.state.player1_squares = int(pow(2, 8));
	staex.build_valid_stacks();
	assert_is_equal(staex.valid_stacks, 160, "test_build_valid_stacks.1");
	// test exclude squares occupied by opponent token
	staex.state.player2_token = int(pow(2, 7));
	staex.build_valid_stacks();
	assert_is_equal(staex.valid_stacks, 32, "test_build_valid_stacks.2");
}

void test_default_valid_moves(int valid_moves) {
	assert_is_equal(valid_moves, 228, "test_default_valid_moves");
}

void test_build_valid_moves(Staex staex) {
	// test exclude squares occupied by opponent token
	staex.state.player2_token = int(pow(2, 7));
	staex.build_valid_moves();
	assert_is_equal(staex.valid_moves, 100, "test_build_valid_moves");
}

int main() {
	Staex staex;
	test_adjacents(staex.adjacent_squares_map);
	test_moves(staex.moves_map);
	test_default_valid_stacks(staex.valid_stacks);
	test_build_valid_stacks(staex);
	test_default_valid_moves(staex.valid_moves);
	test_build_valid_moves(staex);

	cout << "Tests complete." << endl;
}
