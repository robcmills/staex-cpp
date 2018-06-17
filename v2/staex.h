#include "staex-state.h"

class Staex {
	public:
		StaexState state;

		Staex(
			StaexState state_ = DEFAULT_STAEX_STATE
		) :
			state(state_)
		{}
};
