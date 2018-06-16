#include <vector>

struct Staex_State {
	int active_player;
	int player1_squares;
	int player1_token;
	int player2_squares;
	int player2_token;
	std::vector<int> square_heights;
};