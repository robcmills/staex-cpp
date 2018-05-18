#include <iostream>
#include "mcts.h"
#include "staex.h"

using namespace std;

const Staex::Move Staex::no_move = { '0',0,0 };

void print_move(Staex::Move m) {
	cout << "print_move: " << m.type << m.x << "," << m.y;
}

void _main() {
	BoardState boardState = vector<vector<SquareState>>(
		4, vector<SquareState>(4, INITIAL_SQUARE_STATE));
	boardState[0][0].token = 1;
	boardState[3][3].token = 2;
	Staex staex(4, boardState);

	MCTS::ComputeOptions compute_options;
	compute_options.max_iterations = 10000;
	compute_options.verbose = false;
	compute_options.number_of_threads = 4;

	cout << "Staex" << endl;

	int winner = staex.get_winner();
	while (winner == 0) {
		staex.printBoard();
		vector<Staex::Move> moves = staex.get_moves();
		cout << "Valid moves: ";
		for (int i=0; i<moves.size(); ++i) {
			cout << "[" << i << "]:" << moves[i] << " ";
		}
		cout << endl << "Your move: ";
		int move_index = -1;
		cin >> move_index;
		Staex::Move player_move = moves[move_index];
		cout << "Player move: " << player_move << endl;
		staex.do_move(player_move);
		winner = staex.get_winner();
		if (winner > 0) {
			break;
		}

		Staex::Move computer_move = MCTS::compute_move(staex, compute_options);
		cout << "Computer move: " << computer_move << endl;
		staex.do_move(computer_move);
		winner = staex.get_winner();
	}

	cout << endl << "Final state:" << endl;
	staex.printBoard();

	if (winner == 1) {
		cout << "Player 1 wins!" << endl;
	} else {
		cout << "Player 2 wins!" << endl;
	}

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