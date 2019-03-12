#include "environment.h"

Environment::Environment(double p1, double p2, int start_state) {
	this->p1 = p1;
	this->p2 = p2;
	p3 = (1 - p1 - p2) / 2;
	off_the_grid_ignore = p1 + p2;
	off_the_grid_adjacent = (1 - p1 - p2) / 2;
	current_state = start_state;
}

int Environment::get_current_state() {
	return current_state;
}

int Environment::get_reward(int a) {
	int next_state = -1;

	// TODO: finish actual state

	last_reward = next_state == 99 ? 100 : -1;
	current_state = next_state;
	return last_reward;
}

int Environment::get_last_reward() {
	return last_reward;
}