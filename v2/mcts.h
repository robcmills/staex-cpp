#include <vector>
#include <limits>
#include <cmath>

#include "staex.h"

using namespace std;

// Exploration parameter
const int C = 2;

namespace MCTS {

class Node {
	public:
		const Staex staex;
		const int move;
		Node* const parent;
		int depth;
		int visits;
		int wins;
		std::vector<Node*> children;
		float ucb;

		Node(int move, Node* parent, const Staex& staex);

		void update_ucb();
};

Node::Node(
	int move_,
	Node* parent_,
	const Staex& staex_
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
		ucb = std::numeric_limits<float>::infinity();
		return;
	}
	if (!parent || parent->visits == 0) {
		ucb = 0;
		return;
	}
	float exploitation = wins / visits;
	float exploration = sqrt(C * log(parent->visits) / visits);
	ucb = exploitation + exploration;
}

}