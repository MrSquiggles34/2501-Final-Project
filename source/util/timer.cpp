#include <GLFW/glfw3.h>
#include <iostream>

#include "timer.h"

namespace game {
	
	Timer::Timer(void) {
		end_time_ = 0;
	}
	Timer::~Timer(void) {}
	
	void Timer::Start(double duration) {
		end_time_ = duration;
	}
	
	// Make sure the timer doesn't run faster than the game.
	void Timer::Update(double delta_time) {
		if (end_time_ > 0) end_time_ -= delta_time;
	}
	
	bool Timer::Finished(void) const {
		return end_time_ <= 0;
	}
} // namespace game
