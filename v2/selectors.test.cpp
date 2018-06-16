#include <iostream>
#include <cmath>

#include "selectors.h"

using namespace std;

int main() {
	std::vector<int> square_heights = {0,0,0,0,0,0,0,0,0};
	Staex_State const state = {
		1, // active_player;
		0, // player1_squares;
		int(pow(2, 8)), // player1_token;
		0, // player2_squares;
		1, // player2_token;
		square_heights
	};
	std::vector<int> moves = possible_moves_selector(state);
}