#include <iostream>
using namespace std;

struct State {
	int activePlayer;
	int player1Squares;
	int player2Squares;
	int player1Token;
	int player2Token;
	int heights [16];
};

class Staex {
	public:
		Staex(State _state) : state(_state) {}
		State state;

		void print(ostream& out) const {
			out << "Player to move: " << state.activePlayer << endl;
			for (int i=0; i<4; ++i) {
				for (int j=0; j<4; ++j) {
			    out << " " << state.heights[4*i+j];
			  }
			  out << endl;
			}
		}
};

ostream& operator << (ostream& out, const Staex& staex)
{
	staex.print(out);
	return out;
}
