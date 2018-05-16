#include <iostream>
#include "mcts.h"
#include "staex.h"

using namespace std;

void _main()
{
	BoardState boardState = vector<vector<SquareState>>(
		4, vector<SquareState>(4, INITIAL_SQUARE_STATE));
	boardState[0][0].token = 1;
	boardState[3][3].token = 2;
	Staex staex(4, boardState);

	cout << "Staex" << endl;

	staex.printBoard();

	vector<Move> moves = staex.get_moves();
	cout << "Valid moves: ";
	for (int i=0; i<moves.size(); ++i) {
		cout << "[" << i << "]:" << moves[i].type << moves[i].x << "," << moves[i].y << " ";
	}
	cout << endl;
	cout << "Your move: ";
	int move_index = -1;
	cin >> move_index;
	staex.do_move(moves[move_index]);

	staex.printBoard();
}

int main()
{
	try {
		_main();
	}
	catch (runtime_error& error) {
		cerr << "ERROR: " << error.what() << endl;
		return 1;
	}
}