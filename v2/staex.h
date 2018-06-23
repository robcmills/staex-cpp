#include <bitset>
#include <iostream>
#include <map>
#include <vector>

#include "staex-state.h"

using namespace std;

class Staex {
	public:
		StaexState state;
		int board_length;
		int board_size;
		std::map<int,int> pow_map;
		std::map<int,int> adjacent_squares_map;
		std::map<int,int> ranks_map;
		std::map<int,int> files_map;
		std::map<int,int> moves_map;
		int valid_stacks;
		int valid_moves;

		Staex(
			StaexState state_ = DEFAULT_STAEX_STATE
		) :
			state(state_)
		{
			build_move_maps();
		}

		void build_pow_map() {
			for (int i = 0; i < board_length; ++i) {
				pow_map[i] = int(pow(2, i));
			}
		}

		void build_adjacents_map() {
			// Adjacents squares for stack targets
			const int adjacents[5][2] = { {-1,0}, {1,0}, {0,0}, {0,1}, {0,-1} };
			int length_mask = 1;
			for (int i = 0; i < board_length; ++i) {
				length_mask = length_mask | pow_map[i];
			}
			for (int i = 0; i < board_length; ++i) {
				int target_y = int((board_length - 1 - i) / board_size);
				int target_x = (board_length - 1 - i) % board_size;
				int adjacent_squares = 0;
				for (int a=0; a<5; ++a) {
					int target_index = (adjacents[a][0] + target_x) +
						((adjacents[a][1] + target_y) * board_size);
					adjacent_squares = adjacent_squares | pow_map[target_index];
				}
				int key = pow_map[board_length - i - 1];
				int value = adjacent_squares & length_mask;
				adjacent_squares_map[key] = value;
			}
		}

		void build_ranks_map() {
			for (int y = 0; y < board_size; ++y) {
				int rank_mask = 0;
				for (int x = 0; x < board_size; ++x) {
					int target_index = x + (board_size - y - 1) * board_size;
					rank_mask = rank_mask | pow_map[target_index];
				}
				ranks_map[y] = rank_mask;
			}
		}

		void build_files_map() {
			for (int x = 0; x < board_size; ++x) {
				int file_mask = 0;
				for (int y = 0; y < board_size; ++y) {
					int target_index = (board_size - x - 1) + y * board_size;
					file_mask = file_mask | pow_map[target_index];
				}
				files_map[x] = file_mask;
			}
		}

		void build_moves_map() {
			for (int i = 0; i < board_length; ++i) {
				int x = (board_length - 1 - i) % board_size;
				int y = int((board_length - 1 - i) / board_size);
				int key = pow_map[i];
				int value = files_map[x] ^ ranks_map[y];
				moves_map[key] = value;
			}
		}

		void build_valid_stacks() {
			int active_player_token = state.active_player == 1
				? state.player1_token
				: state.player2_token;
			int adjacents = adjacent_squares_map[active_player_token];
			// Exclude squares already owned by player
			int active_player_squares = state.active_player == 1
				? state.player1_squares
				: state.player2_squares;
			int owned_intersection = adjacents & active_player_squares;
			valid_stacks = adjacents ^ owned_intersection;
			// Exclude squares occupied by opponent
			int non_active_player_token = state.active_player == 1
				? state.player2_token
				: state.player1_token;
			valid_stacks &= ~non_active_player_token;
		}

		void build_valid_moves() {
			int active_player_token = state.active_player == 1
				? state.player1_token
				: state.player2_token;
			valid_moves = moves_map[active_player_token];
			// Exclude squares occupied by opponent
			int non_active_player_token = state.active_player == 1
				? state.player2_token
				: state.player1_token;
			valid_moves &= ~non_active_player_token;
		}

		void build_move_maps() {
			board_length = state.square_heights.size();
			board_size = int(sqrt(board_length));
			build_pow_map();
			build_adjacents_map();
			build_ranks_map();
			build_files_map();
			build_moves_map();
			build_valid_stacks();
			build_valid_moves();
		}
};
