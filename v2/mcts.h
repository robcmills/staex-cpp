#include <vector>
#include <limits>
#include <cmath>
#include <sstream>
#include <string>

#include "staex.h"

using namespace std;

// Exploration parameter
const int C = 2;
const float FLOAT_INFINITY = std::numeric_limits<float>::infinity();

namespace MCTS {

class Node {
	public:
		Staex staex;
		const int move;
		Node* const parent;
		int depth;
		int visits;
		int wins;
		std::vector<Node*> children;
		float ucb;

		Node(int move, Node* parent, Staex staex);

		void update_ucb();
		void add_children();
		std::string to_string() const;
		std::string tree_to_string() const;
};

Node::Node(
	int move_,
	Node* parent_,
	Staex staex_
) :
	move(move_),
	parent(parent_),
	staex(staex_),
	visits(0),
	wins(0)
{
	update_ucb();
}

void Node::update_ucb() {
	if (visits == 0) {
		ucb = FLOAT_INFINITY;
		return;
	}
	if (parent == nullptr || parent->visits == 0) {
		ucb = 0;
		return;
	}
	float exploitation = wins / visits;
	float exploration = sqrt(C * log(parent->visits) / visits);
	ucb = exploitation + exploration;
}

void Node::add_children() {
	for (auto action: staex.valid_actions) {
		auto child = new Node(action, this, staex);
		child->staex.perform_action(action);
		children.push_back(child);
	}
}

std::string Node::to_string() const {
	std::stringstream ss;
	ss << "m:" << move << " "
		<< "w/v:" << wins << "/" << visits << " "
		<< "u:" << ucb;
	return ss.str();
}

std::string Node::tree_to_string() const {
	std::stringstream ss;
	ss << to_string();
	for (auto child: children) {
		ss << endl << "  " << child->tree_to_string();
	}
	return ss.str();
}

class MCTS {
	public:
		int rounds;
		Node root_node;
		Node* current_node;

		MCTS(int rounds, Staex staex);

		bool should_continue() const;
		void select();
};

MCTS::MCTS(
	int rounds_,
	Staex staex
) :
	rounds(rounds_),
	root_node(*(new Node(0, nullptr, staex)))
{
	root_node.add_children();
}

bool MCTS::should_continue() const {
	return rounds > 0;
}

void MCTS::select() {
	current_node = &root_node;
	while (current_node->children.size() > 0 && should_continue()) {
		current_node = *std::max_element(
			current_node->children.begin(),
			current_node->children.end(),
			[](Node* a, Node* b) {
				return a->ucb < b->ucb;
			}
		);
	}
}

}