#include <map>
#include <cmath>

using namespace std;

std::map<int,int> build_pow_map(int length) {
	std::map<int, int> pow_map;
	for (int i = 0; i < length; ++i) {
		pow_map[i] = int(pow(2, i));
	}
	return pow_map;
}

std::map<int,int> build_adjacents_map(int length, int size, std::map<int,int>* pow_map) {
	std::map<int,int> adjacents_map;
	// Adjacents squares for stack targets
	const int adjacents[5][2] = { {-1,0}, {1,0}, {0,0}, {0,1}, {0,-1} };
	int length_mask = 1;
	for (int i = 0; i < length; ++i) {
		length_mask = length_mask | (*pow_map)[i];
	}
	for (int i = 0; i < length; ++i) {
		int target_y = int((length - 1 - i) / size);
		int target_x = (length - 1 - i) % size;
		int adjacent_squares = 0;
		for (int a=0; a<5; ++a) {
			int target_index = (adjacents[a][0] + target_x) +
				((adjacents[a][1] + target_y) * size);
			adjacent_squares |= (*pow_map)[target_index];
		}
		int key = (*pow_map)[length - i - 1];
		int value = adjacent_squares & length_mask;
		adjacents_map[key] = value;
	}
	return adjacents_map;
}

std::map<int,int> build_ranks_map(int size, std::map<int,int>* pow_map) {
	std::map<int,int> ranks_map;
	for (int y = 0; y < size; ++y) {
		int rank_mask = 0;
		for (int x = 0; x < size; ++x) {
			int target_index = x + (size - y - 1) * size;
			rank_mask |= (*pow_map)[target_index];
		}
		ranks_map[y] = rank_mask;
	}
	return ranks_map;
}

std::map<int,int> build_files_map(int size, std::map<int,int>* pow_map) {
	std::map<int,int> files_map;
	for (int x = 0; x < size; ++x) {
		int file_mask = 0;
		for (int y = 0; y < size; ++y) {
			int target_index = (size - x - 1) + y * size;
			file_mask |= (*pow_map)[target_index];
		}
		files_map[x] = file_mask;
	}
	return files_map;
}

std::map<int,int> build_moves_map(int length, int size, std::map<int,int>* pow_map) {
	std::map<int,int> ranks_map = build_ranks_map(size, pow_map);
	std::map<int,int> files_map = build_files_map(size, pow_map);
	std::map<int,int> moves_map;
	for (int i = 0; i < length; ++i) {
		int x = (length - 1 - i) % size;
		int y = int((length - 1 - i) / size);
		int key = (*pow_map)[i];
		int value = files_map[x] ^ ranks_map[y];
		moves_map[key] = value;
	}
	return moves_map;
}

