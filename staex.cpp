#include <iostream>
#include "mcts.h"
#include "staex.h"

using namespace std;

void _main()
{
	State state;
	state.activePlayer = 1;
	state.player1Squares = 0;
	state.player2Squares = 0;
	state.player1Token = 32768;
	state.player2Token = 1;
	for (int i=0; i<16; ++i) {
    state.heights[i] = 0;
	}
	Staex staex(state);
	cout << "Staex" << endl;
	cout << staex << endl;
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