#include <iostream>
#include <map>
#include <cmath>

using namespace std;

void assert_is_equal(int a, int b, std::string id) {
	if (a != b) {
		cout << "FAIL: Expected " << a << " to equal " << b << " in " << id << endl;
	}
}

std::map<int, int> build_pow_map(int length) {
	std::map<int, int> pow_map;
	for (int i = 0; i < length; ++i) {
		pow_map[i] = int(pow(2, i));
	}
	return pow_map;
}

int DEFAULT_BOARD_LENGTH = 9;

class Staex {
	public:
		int board_length;
		std::map<int,int>* pow_map;

		Staex(
			int board_length_,
			std::map<int,int>* pow_map_
		) :
			board_length(board_length_),
			pow_map(pow_map_)
		{
			// init
		}
};

int main() {
	std::map<int, int> pow_map = build_pow_map(9);
	assert_is_equal(pow_map[0], 1, "pow_map");
	Staex staex(9, &pow_map);
	assert_is_equal((*staex.pow_map)[0], 1, "pow_map");
	cout << "Tests complete." << endl;
}
