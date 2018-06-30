#include <iostream>
#include <string>
using namespace std;

#include "maps.h"
#include "mcts.h"

void assert_is_equal(int a, int b, std::string id) {
	if (a != b) {
		cout << "FAIL: Expected " << a << " to equal " << b << " in " << id << endl;
	}
}

int main() {
	map<int,int> pow_map = build_pow_map(9);
	map<int,int> adjacents_map = build_adjacents_map(9, 3, &pow_map);
	map<int,int> moves_map = build_moves_map(9, 3, &pow_map);
	Staex staex(DEFAULT_STAEX_STATE, &pow_map, &adjacents_map, &moves_map);
	MCTS::Node node(0, nullptr, staex);

	cout << "Tests complete." << endl;
}
