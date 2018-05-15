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
	cout << "Winner:" << staex.get_winner() << endl;
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