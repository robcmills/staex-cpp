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
	cout << "H" << s.height;
	if (s.owner > 0) {
		cout << "O" << s.owner;
	}
	if (s.token > 0) {
		cout << "T" << s.token;
	}
}

struct Move {
	char type;
	int x;
	int y;
};

class Staex {
	public:
		typedef int Move;
		static const Move no_move = -1;
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
			for (int y=0; y<4; ++y) {
				for (int x=0; x<4; ++x) {
					cout << " ";
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

	private:
		void check_invariant() const {
			attest(player_to_move == 1 || player_to_move == 2);
		}

		int board_size;
		vector<vector<SquareState>> board;
};
