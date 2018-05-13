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

class Staex {
	public:
		typedef int Move;
		static const Move no_move = -1;
		int player_to_move;

		Staex(int board_size_ = DEFAULT_BOARD_SIZE, BoardState board_ = INITIAL_BOARD_STATE) :
			player_to_move(1),
		  board_size(board_size_),
		  board(board_)
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

	private:
		void check_invariant() const
		{
			attest(player_to_move == 1 || player_to_move == 2);
		}

		int board_size;
		vector<vector<SquareState>> board;
};
