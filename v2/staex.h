#include <iostream>
#include <map>

#include "staex-state.h"

using namespace std;

class Staex {
	public:
		StaexState state;
		std::map<int,int> adjacent_squares_map;

		Staex(
			StaexState state_ = DEFAULT_STAEX_STATE
		) :
			state(state_)
		{
			cout << "Staex constructor" << endl;
			build_move_maps();
		}

		void build_move_maps() {
			cout << "build_move_maps" << endl;
			// Adjacents squares for stack targets
			const int adjacents[5][2] = { {-1,0}, {1,0}, {0,0}, {0,1}, {0,-1} };
			int length = state.square_heights.size();
			int length_mask = 1;
			for (int i = 0; i < length; ++i) {
				length_mask = length_mask | int(pow(2,i));
			}
			for (int i = 0; i < length; ++i) {
				int board_size = int(sqrt(length));
				int target_y = int((length - 1 - i) / board_size);
				int target_x = (length - 1 - i) % board_size;
				int adjacent_squares = 0;
				for (int a=0; a<5; ++a) {
					int target_index = (adjacents[a][0] + target_x) +
						((adjacents[a][1] + target_y) * board_size);
					adjacent_squares = adjacent_squares | int(pow(2,target_index));
				}
				int key = int(pow(2,length - i - 1));
				int value = adjacent_squares & length_mask;
				adjacent_squares_map[key] = value;
			}
		}
};
