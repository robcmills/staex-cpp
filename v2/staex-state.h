#include <vector>
#include <cmath>

struct StaexState {
	int active_player;
	int game_end_score;
	int player1_squares;
	int player1_token;
	int player2_squares;
	int player2_token;
	std::vector<int> square_heights;
};

std::vector<int> DEFAULT_SQUARE_HEIGHTS = {0,0,0,0,0,0,0,0,0};
StaexState const DEFAULT_STAEX_STATE = {
	1, // active_player
	9, // game_end_score
	0, // player1_squares
	int(pow(2, 8)), // player1_token
	0, // player2_squares
	1, // player2_token
	DEFAULT_SQUARE_HEIGHTS
};