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
const int DEFAULT_VALID_ACTIONS[7] = {-3,6,-6,-7,8,-8,9};

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
	staex.state.player1_squares = staex.pow_map[8];
	staex.build_valid_stacks();
	assert_is_equal(staex.valid_stacks, 160, "test_build_valid_stacks.1");
	// test exclude squares occupied by opponent token
	staex.state.player2_token = staex.pow_map[7];
	staex.build_valid_stacks();
	assert_is_equal(staex.valid_stacks, 32, "test_build_valid_stacks.2");
}

void test_default_valid_moves(int valid_moves) {
	assert_is_equal(valid_moves, 228, "test_default_valid_moves");
}

void test_build_valid_moves(Staex staex) {
	// test exclude squares occupied by opponent token
	staex.state.player2_token = staex.pow_map[7];
	staex.build_valid_moves();
	assert_is_equal(staex.valid_moves, 100, "test_build_valid_moves");
}

void test_default_valid_actions(std::vector<int> valid_actions) {
	for (int i = 0; i < valid_actions.size(); ++i) {
		assert_is_equal(
			valid_actions[i],
			DEFAULT_VALID_ACTIONS[i],
			"test_default_valid_actions"
		);
	}
}

void test_build_valid_actions(Staex staex) {
	staex.state.player1_token = staex.pow_map[4];
	staex.state.player2_token = staex.pow_map[1];
	staex.state.player1_squares = staex.pow_map[4];
	staex.state.player2_squares = 170;
	staex.build_valid_actions();
	const int EXPECTED_VALID_ACTIONS[6] = {4,-4,6,-6,8,-8};
	for (int i = 0; i < staex.valid_actions.size(); ++i) {
		assert_is_equal(
			staex.valid_actions[i],
			EXPECTED_VALID_ACTIONS[i],
			"test_build_valid_actions"
		);
	}
}

void test_perform_stack(Staex staex) {
	staex.perform_stack(8);
	assert_is_equal(
		staex.state.player1_squares,
		staex.pow_map[8],
		"test_perform_stack.1"
	);
	assert_is_equal(
		staex.state.square_heights[8],
		1,
		"test_perform_stack.2"
	);
}

void test_perform_move(Staex staex) {
	staex.perform_move(2);
	assert_is_equal(staex.state.player1_token, staex.pow_map[2], "test_perform_move");
}

void test_default_update_winner(int winner) {
	assert_is_equal(winner, 0, "test_default_update_winner");
}


void test_update_winner(Staex staex) {
	staex.state.square_heights[0] = 10;
	staex.state.player2_squares = staex.pow_map[0];
	staex.update_winner();
	assert_is_equal(staex.winner, 2, "test_update_winner");
}

int main() {
	Staex staex;

	test_adjacents(staex.adjacent_squares_map);
	test_moves(staex.moves_map);
	test_default_valid_stacks(staex.valid_stacks);
	test_build_valid_stacks(staex);
	test_default_valid_moves(staex.valid_moves);
	test_build_valid_moves(staex);
	test_default_valid_actions(staex.valid_actions);
	test_build_valid_actions(staex);
	test_perform_stack(staex);
	test_perform_move(staex);
	test_default_update_winner(staex.winner);
	test_update_winner(staex);

	cout << "Tests complete." << endl;
}
