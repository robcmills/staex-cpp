#include <bitset>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "staex-state.h"

using namespace std;

class Staex {
	public:
		StaexState state;
		int board_length;
		int board_size;
		std::map<int,int>* pow_map;
		std::map<int,int>* adjacents_map;
		std::map<int,int>* moves_map;
		int valid_stacks;
		int valid_moves;
		std::vector<int> valid_stack_actions;
		std::vector<int> valid_move_actions;
		std::vector<int> valid_actions;
		int winner;
		// Note that state.square_heights and action indexes are descending
		// to reflect binary power conversions.
		/*
			876
			543
			210
		*/

		Staex(
			StaexState state_,
			std::map<int,int>* pow_map_,
			std::map<int,int>* adjacents_map_,
			std::map<int,int>* moves_map_
		) :
			state(state_),
			pow_map(pow_map_),
			adjacents_map(adjacents_map_),
			moves_map(moves_map_)
		{
			board_length = state.square_heights.size();
			board_size = int(sqrt(board_length));
			// reserve enough for max num actions
			valid_stack_actions.reserve(5);
			valid_move_actions.reserve((board_size - 1) * 2);
			valid_actions.reserve((board_size - 1) * 2 + 5);
			build_valid_actions();
			update_winner();
		}

		void build_valid_stacks() {
			int active_player_token = state.active_player == 1
				? state.player1_token
				: state.player2_token;
			int adjacents = (*adjacents_map)[active_player_token];
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
			valid_moves = (*moves_map)[active_player_token];
			// Exclude squares occupied by opponent
			int non_active_player_token = state.active_player == 1
				? state.player2_token
				: state.player1_token;
			valid_moves &= ~non_active_player_token;
		}

		void build_valid_actions() {
			build_valid_stacks();
			build_valid_moves();
			valid_stack_actions.clear();
			valid_move_actions.clear();
			valid_actions.clear();
			for (int i = 0; i < board_length; ++i) {
				if ((*pow_map)[i] & valid_stacks) {
					valid_stack_actions.push_back(i + 1);
					valid_actions.push_back(i + 1);
				}
				if ((*pow_map)[i] & valid_moves) {
					valid_move_actions.push_back((i + 1) * -1);
					valid_actions.push_back((i + 1) * -1);
				}
			}
		}

		void perform_stack(int stack_index) {
			int mask = (*pow_map)[stack_index];
			if (state.active_player == 1) {
			  state.player1_squares |= mask;
			  state.player2_squares &= ~mask;
			} else {
			  state.player2_squares |= mask;
			  state.player1_squares &= ~mask;
			}
			state.square_heights[stack_index]++;
		}

		void perform_move(int move_index) {
			int token = (*pow_map)[move_index];
			state.active_player == 1
				? state.player1_token = token
				: state.player2_token = token;
		}

		void perform_action(int action) {
			action > 0
				? perform_stack(action - 1)
				: perform_move(action * -1 - 1);
			state.active_player = 3 - state.active_player;
			update_winner();
			build_valid_actions();
		}

		void perform_playout_action(std::mt19937_64* engine) {
			// Prefer stack actions
			if (valid_stack_actions.size() > 0) {
				uniform_int_distribution<std::size_t> stack_dist(0, valid_stack_actions.size() - 1);
				int random_stack_action = valid_stack_actions[stack_dist(*engine)];
				perform_action(random_stack_action);
				return;
			}
			uniform_int_distribution<std::size_t> move_dist(0, valid_move_actions.size() - 1);
			int random_move_action = valid_move_actions[move_dist(*engine)];
			perform_action(random_move_action);
		}

		void update_winner() {
			int player1_score = 0;
			int player2_score = 0;
			for (int i = 0; i < board_length; ++i) {
				if (state.player1_squares & (*pow_map)[i]) {
					player1_score += state.square_heights[i];
				} else if (state.player2_squares & (*pow_map)[i]) {
					player2_score += state.square_heights[i];
				}
			}
			if (player1_score > state.game_end_score) {
				winner = 1;
			} else if (player2_score > state.game_end_score) {
				winner = 2;
			} else {
				winner = 0;
			}
		}

		Staex clone() {
			Staex staex_clone(state, pow_map, adjacents_map, moves_map);
			return staex_clone;
		}
};
