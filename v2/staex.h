#include <iostream>
#include <bitset>
#include <map>

#include "staex-state.h"

using namespace std;

class Staex {
	public:
		StaexState state;
		int board_length;
		int board_size;
		std::map<int,int> adjacent_squares_map;
		std::map<int,int> ranks_map;
		std::map<int,int> files_map;
		std::map<int,int> moves_map;

		Staex(
			StaexState state_ = DEFAULT_STAEX_STATE
		) :
			state(state_)
		{
			build_move_maps();
		}

		void build_adjacents_map() {
			// Adjacents squares for stack targets
			const int adjacents[5][2] = { {-1,0}, {1,0}, {0,0}, {0,1}, {0,-1} };
			board_length = state.square_heights.size();
			board_size = int(sqrt(board_length));
			int length_mask = 1;
			for (int i = 0; i < board_length; ++i) {
				length_mask = length_mask | int(pow(2,i));
			}
			for (int i = 0; i < board_length; ++i) {
				int target_y = int((board_length - 1 - i) / board_size);
				int target_x = (board_length - 1 - i) % board_size;
				int adjacent_squares = 0;
				for (int a=0; a<5; ++a) {
					int target_index = (adjacents[a][0] + target_x) +
						((adjacents[a][1] + target_y) * board_size);
					adjacent_squares = adjacent_squares | int(pow(2, target_index));
				}
				int key = int(pow(2,board_length - i - 1));
				int value = adjacent_squares & length_mask;
				adjacent_squares_map[key] = value;
			}
		}

		void build_ranks_map() {
			for (int y = 0; y < board_size; ++y) {
				int rank_mask = 0;
				for (int x = 0; x < board_size; ++x) {
					int target_index = x + (board_size - y - 1) * board_size;
					rank_mask = rank_mask | int(pow(2, target_index));
				}
				ranks_map[y] = rank_mask;
			}
		}

		void build_files_map() {
			for (int x = 0; x < board_size; ++x) {
				int file_mask = 0;
				for (int y = 0; y < board_size; ++y) {
					int target_index = (board_size - x - 1) + y * board_size;
					file_mask = file_mask | int(pow(2, target_index));
				}
				files_map[x] = file_mask;
			}
		}

		void build_moves_map() {
			for (int i = 0; i < board_length; ++i) {
				int x = (board_length - 1 - i) % board_size;
				int y = int((board_length - 1 - i) / board_size);
				int key = int(pow(2, i));
				int value = files_map[x] ^ ranks_map[y];
				moves_map[key] = value;
			}
		}

		void build_move_maps() {
			build_adjacents_map();
			build_ranks_map();
			build_files_map();
			build_moves_map();
		}
};
