#include <iostream>
#include <string>
using namespace std;

#include "maps.h"
#include "mcts.h"
#include "timer.h"

int main() {
	int const BOARD_SIZE = 4;
	int const BOARD_LENGTH = BOARD_SIZE * BOARD_SIZE;
	std::vector<int> const SQUARE_HEIGHTS(BOARD_LENGTH, 0);
	StaexState const STAEX_STATE = {
		1, // active_player
		9, // game_end_score
		0, // player1_squares
		int(pow(2, BOARD_LENGTH - 1)), // player1_token
		0, // player2_squares
		1, // player2_token
		SQUARE_HEIGHTS
	};

	map<int,int> pow_map = build_pow_map(BOARD_LENGTH);
	map<int,int> adjacents_map = build_adjacents_map(BOARD_LENGTH, BOARD_SIZE, &pow_map);
	map<int,int> moves_map = build_moves_map(BOARD_LENGTH, BOARD_SIZE, &pow_map);
	Staex staex(STAEX_STATE, &pow_map, &adjacents_map, &moves_map);
	MCTS::MCTS mcts(1000, staex);

	Timer tmr;
	int const move = mcts.get_move();
	double t = tmr.elapsed();
	cout << "Move: " << move << endl;
	cout << "Elapsed: " << t << endl;

	cout << mcts.root_node.tree_to_string() << endl;

	cout << "Tests complete." << endl;
}
