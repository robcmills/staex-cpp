#include <iostream>
#include "mcts.h"
#include "staex.h"

using namespace std;

void print_move(Staex::Move m) {
	cout << "print_move: " << m.type << m.x << "," << m.y << endl;
}

void _main() {
	BoardState boardState = vector<vector<SquareState>>(
		4, vector<SquareState>(4, INITIAL_SQUARE_STATE));
	boardState[0][0].token = 1;
	boardState[3][3].token = 2;
	Staex staex(4, boardState);

	cout << "Staex" << endl;

	staex.printBoard();

	vector<Staex::Move> moves = staex.get_moves();
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

	MCTS::ComputeOptions compute_options;
	compute_options.max_iterations =  10000;
	compute_options.verbose = true;
	Staex::Move computer_move = MCTS::compute_move(staex, compute_options);
	print_move(computer_move);

	// std::mt19937_64 random_engine;
	// staex.do_random_move(&random_engine);
	// staex.printBoard();
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