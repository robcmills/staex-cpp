#include <iostream>
#include <string>
using namespace std;

#include "maps.h"
#include "mcts.h"

template<typename T>
void assert_equal(T a, T b, std::string id) {
	if (a != b) {
		cout << "FAIL: Expected " << a << " to equal " << b << " in " << id << endl;
	}
}

void test_default_root_node(MCTS::Node* node) {
	assert_equal<int>(node->move, 0, "root node move is zero");
	assert_equal<int>(node->wins, 0, "root node wins is zero");
	assert_equal<int>(node->visits, 0, "root node visits is zero");
	assert_equal<float>(node->ucb, FLOAT_INFINITY, "root node ucb is infinity");
}

int main() {
	map<int,int> pow_map = build_pow_map(9);
	map<int,int> adjacents_map = build_adjacents_map(9, 3, &pow_map);
	map<int,int> moves_map = build_moves_map(9, 3, &pow_map);
	Staex staex(DEFAULT_STAEX_STATE, &pow_map, &adjacents_map, &moves_map);
	MCTS::Node node(0, nullptr, staex);

	cout << node.to_string() << endl;

	test_default_root_node(&node);

	cout << "Tests complete." << endl;
}
