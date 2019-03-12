#include "environment.h"

random_device r;
default_random_engine generator{ r() };

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

int Environment::hypothetical_state(int a) {
	int hypo_state;
	switch (a)
	{
		case 0:  // UP 
			hypo_state = current_state + 10;
			if (restricted_by_up.find(hypo_state) == restricted_by_up.end()) hypo_state = -1;
			break;
		case 1:  // DOWN
			hypo_state = current_state - 10;
			if (restricted_by_up.find(hypo_state) == restricted_by_down.end()) hypo_state = -1;
			break;
		case 2:  // LEFT
			hypo_state = current_state - 1;
			if (restricted_by_up.find(hypo_state) == restricted_by_left.end()) hypo_state = -1;
			break;
		case 3:  // RIGHT
			hypo_state = current_state + 1;
			if (restricted_by_up.find(hypo_state) == restricted_by_right.end()) hypo_state = -1;
			break;
		default:
			hypo_state = -1;
			break;
	}

	return hypo_state;
}



int Environment::get_reward(int a) {
	int next_state = -1;



	uniform_real_distribution<float> distribution(0.0f, 1.0f);
	float chance = distribution(generator);
	if (chance < p1) {    // chance happened to go where intended

	} else if (chance < p1 + p2){ // chance of stay in place

	} else if (chance < p1 + p2 + off_the_grid_adjacent){  // adjacent left

	} else {	// adjacent right 

	}

	// TODO: finish actual state

	last_reward = next_state == 99 ? 100 : -1;
	current_state = next_state;
	return last_reward;
}

int Environment::get_last_reward() {
	return last_reward;
}