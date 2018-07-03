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

template<typename T>
void assert_not_equal(T a, T b, std::string id) {
	if (a == b) {
		cout << "FAIL: Expected " << a << " to equal " << b << " in " << id << endl;
	}
}

void test_default_root_node(MCTS::Node* node) {
	assert_equal<int>(node->move, 0, "root node move is zero");
	assert_equal<int>(node->wins, 0, "root node wins is zero");
	assert_equal<int>(node->visits, 0, "root node visits is zero");
	assert_equal<float>(node->ucb, FLOAT_INFINITY, "root node ucb is infinity");
}

void test_add_children(MCTS::Node* node) {
	node->add_children();
	assert_equal<int>(node->children.size(), 7, "root node has 7 children");
	assert_equal<int>(node->staex.state.player1_token, 256, "root node state is unchanged");
	assert_equal<int>(
		node->children[0]->staex.state.player1_token,
		4, "first child state is changed"
	);
}

void test_default_mcts(MCTS::MCTS* mcts) {
	assert_equal<int>(mcts->rounds, 10, "rounds set");
	assert_equal<bool>(mcts->should_continue(), true, "should continue");
}

void test_mcts_select(MCTS::MCTS* mcts) {
	mcts->select();
	assert_equal<int>(mcts->current_node->move, -3, "current_node selected");
}

void test_mcts_expand(MCTS::MCTS* mcts) {
	mcts->expand();
}

void test_mcts_playout(MCTS::MCTS* mcts) {
	mcts->playout();
	assert_not_equal<int>(mcts->current_winner, 0, "playout");
}

void test_mcts_propagate(MCTS::MCTS* mcts) {
	mcts->propagate();
	MCTS::Node* updated_child = nullptr;
	for (int i = 0; i < mcts->root_node.children.size(); ++i) {
		if (mcts->root_node.children[i]->visits == 1) {
			updated_child = mcts->root_node.children[i];
		}
	}
	assert_equal<int>(updated_child->ucb, 0, "propagate updated a child");
}

int main() {
	map<int,int> pow_map = build_pow_map(9);
	map<int,int> adjacents_map = build_adjacents_map(9, 3, &pow_map);
	map<int,int> moves_map = build_moves_map(9, 3, &pow_map);
	Staex staex(DEFAULT_STAEX_STATE, &pow_map, &adjacents_map, &moves_map);
	MCTS::Node node(0, nullptr, staex);

	test_default_root_node(&node);
	test_add_children(&node);

	MCTS::MCTS mcts(10, staex);
	test_default_mcts(&mcts);
	test_mcts_select(&mcts);
	test_mcts_expand(&mcts);
	test_mcts_playout(&mcts);
	test_mcts_propagate(&mcts);

	cout << mcts.root_node.tree_to_string() << endl;

	cout << "Tests complete." << endl;
}
