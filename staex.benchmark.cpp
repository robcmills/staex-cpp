#include <iostream>
#include <chrono>
#include "mcts.h"
#include "staex.h"

using namespace std;

class Timer {
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

const Staex::Move Staex::no_move = { '0',0,0 };

void _main() {
	BoardState boardState = vector<vector<SquareState>>(
		4, vector<SquareState>(4, INITIAL_SQUARE_STATE));
	boardState[0][0].token = 1;
	boardState[3][3].token = 2;
	Staex staex(4, boardState);

	MCTS::ComputeOptions compute_options;
	compute_options.max_iterations = 1000;
	compute_options.verbose = false;
	compute_options.number_of_threads = 8;

	Timer tmr;
	Staex::Move computer_move = MCTS::compute_move(staex, compute_options);
	double t = tmr.elapsed();
	cout << "Computer move: " << computer_move << endl;
	cout << "Elapsed: " << t << endl;
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