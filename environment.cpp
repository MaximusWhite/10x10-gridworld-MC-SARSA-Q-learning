#include "environment.h"

Environment::Environment(double p1, double p2, int start_state) {
	this->p1 = p1;
	this->p2 = p2;
	p3 = (1 - p1 - p2) / 2;
	off_the_grid_ignore = p1 + p2;
	off_the_grid_adjacent = (1 - p1 - p2) / 2;
	current_state = start_state;
}

int Environment::get_next_state(int a) {
	int next_state = -1;


	last_reward = next_state == 99 ? 100 : -1;
	return 0;
}

int Environment::get_last_reward() {
	return last_reward;
}