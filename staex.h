#include <iostream>
#include <vector>
using namespace std;

struct SquareState {
	int owner;
	int token;
	int height;
};

SquareState const INITIAL_SQUARE_STATE = {0,0,0};

typedef vector<vector<SquareState>> BoardState;

static const int DEFAULT_GAME_END_SCORE = 16;
static const int DEFAULT_BOARD_SIZE = 4;
BoardState const INITIAL_BOARD_STATE = BoardState(
	DEFAULT_BOARD_SIZE, vector<SquareState>(DEFAULT_BOARD_SIZE, INITIAL_SQUARE_STATE)
);

void printSquare(SquareState s) {
	stringstream state;
	state << "H" << s.height;
	if (s.owner > 0) {
		state << "O" << s.owner;
	}
	if (s.token > 0) {
		state << "T" << s.token;
	}
	cout << setw(8) << state.str();
}

struct Move {
	char type;
	int x;
	int y;
};

class Staex {
	public:
		static const int no_move = -1;
		int player_to_move;
		int game_end_score;

		Staex(
			int board_size_ = DEFAULT_BOARD_SIZE,
			BoardState board_ = INITIAL_BOARD_STATE,
			int game_end_score_ = DEFAULT_GAME_END_SCORE
		) :
			player_to_move(1),
		  board_size(board_size_),
		  board(board_),
		  game_end_score(game_end_score_)
		{}

		void printBoard() const {
			cout << " ";
			for (int i=0; i<board_size; ++i) {
				cout << setw(8) << i;
			}
			cout << endl;
			for (int y=0; y<board_size; ++y) {
				cout << y;
				for (int x=0; x<board_size; ++x) {
					printSquare(board[y][x]);
				}
				cout << endl;
			}
		}

		int get_winner() const {
			int player_1_score = 0;
			int player_2_score = 0;
			for (int y=0; y<board_size; ++y) {
				for (int x=0; x<board_size; ++x) {
					if (board[y][x].owner == 1) {
						player_1_score += board[y][x].height;
					} else if (board[y][x].owner == 2) {
						player_2_score += board[y][x].height;
					}
				}
			}
			if (player_1_score >= game_end_score) {
				return 1;
			} else if (player_2_score >= game_end_score) {
				return 2;
			}
			return 0;
		}

		bool is_valid_coord(int x, int y) const {
			if (x < 0 || x >= board_size) {
				return false;
			}
			if (y < 0 || y >= board_size) {
				return false;
			}
			return true;
		}

		bool is_valid_stack_target(SquareState target) const {
			return target.owner != player_to_move;
		}

		bool is_valid_token_target(SquareState target) const {
			return target.token != 3 - player_to_move;
		}

		vector<Move> get_moves() const {
			check_invariant();

			vector<Move> moves;
			if (get_winner() != 0) {
				return moves;
			}

			int max_num_moves = (board_size - 1) * 2 + 5;
			moves.reserve(max_num_moves);

			// Find current player token
			int token_x, token_y;
			for (int y=0; y<board_size; ++y) {
				for (int x=0; x<board_size; ++x) {
					if (board[y][x].token == player_to_move) {
						token_x = x;
						token_y = y;
					}
				}
			}

			int target_x, target_y;
			// Find stack targets
			const int targets[5][2] = { {-1,0}, {1,0}, {0,0}, {0,1}, {0,-1} };
			for (int t=0; t<5; ++t) {
				target_x = token_x + targets[t][0];
				target_y = token_y + targets[t][1];
				if (is_valid_coord(target_x, target_y)) {
					SquareState target = board[target_y][target_x];
					if (is_valid_stack_target(target)) {
						const Move move = { 'S', target_x, target_y };
						moves.push_back(move);
					}
				}
			}

			// Find token targets
			const int directions[4][2] = { {-1,0}, {1,0}, {0,1}, {0,-1} };
			for (int d=0; d<4; ++d) {
				target_x = token_x + directions[d][0];
				target_y = token_y + directions[d][1];
				while (is_valid_coord(target_x, target_y)) {
					SquareState target = board[target_y][target_x];
					if (is_valid_token_target(target)) {
						const Move move = { 'M', target_x, target_y };
						moves.push_back(move);
					}
					target_x += directions[d][0];
					target_y += directions[d][1];
				}
			}

			cout << "Valid moves: ";
			for (int i=0; i<moves.size(); ++i) {
				cout << "[" << i << "]:" << moves[i].type << moves[i].x << "," << moves[i].y << " ";
			}
			cout << endl;
			return moves;
		}

	private:
		void check_invariant() const {
			attest(player_to_move == 1 || player_to_move == 2);
		}

		int board_size;
		vector<vector<SquareState>> board;
};
