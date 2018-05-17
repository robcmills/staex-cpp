#include <iostream>

using namespace std;

struct Move {
	char type;
	int x;
	int y;
};

// template<typename T>
std::ostream& operator << (std::ostream &o, const Move &m) {
	o << "m: " << m.type << m.x << "," << m.y << std::endl;
	return o;
}

int main() {
	Move m = { 'S', 0, 0 };
	std::cout << m << endl;
}