#include <cmath>
#include <ctime>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "staex.h"

using namespace std;

const int C = 2; // Exploration parameter
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
		Node* get_random_child(std::mt19937_64* random_engine);
		std::string to_string() const;
		std::string tree_to_string(int depth = 1) const;
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

Node* Node::get_random_child(std::mt19937_64* engine) {
	std::uniform_int_distribution<std::size_t> distribution(0, children.size() - 1);
	return children[distribution(*engine)];
}

std::string Node::to_string() const {
	std::stringstream ss;
	ss << "m:" << move << " "
		<< "w/v:" << wins << "/" << visits << " "
		<< "p:" << staex.state.active_player << " "
		<< "u:" << ucb;
	return ss.str();
}

std::string Node::tree_to_string(int depth) const {
	std::stringstream ss;
	ss << to_string();
	for (auto child: children) {
		ss << endl;
		for (int i = 0; i < depth; ++i) { ss << "  "; }
		ss << child->tree_to_string(depth + 1);
	}
	return ss.str();
}

class MCTS {
	public:
		int rounds;
		Node root_node;
		Node* current_node;
		std::mt19937_64 random_engine;

		MCTS(int rounds, Staex staex);

		bool should_continue() const;
		void select();
		void expand();
};

MCTS::MCTS(
	int rounds_,
	Staex staex
) :
	rounds(rounds_),
	root_node(*(new Node(0, nullptr, staex)))
{
	root_node.add_children();
	std::mt19937_64 engine(std::time(0));
	random_engine = engine;
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

void MCTS::expand() {
	if(current_node->staex.winner != 0) { return; }
	current_node->add_children();
	current_node = current_node->get_random_child(&random_engine);
}

}