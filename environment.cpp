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

int Environment::next_state(int a) {
	int hypo_state;
	uniform_real_distribution<float> distribution(0.0f, 1.0f);
	double prob = distribution(generator);
	switch (a)
	{
		case 0:  // UP 
			
			if (restricted_by_up.find(current_state) != restricted_by_up.end()) {	// bumping into up
				hypo_state = find_state_along_wall(-1); 
			} else if (restricted_by_left.find(current_state) != restricted_by_left.end()) {  // along left wall
				if (prob < p1) {
					hypo_state = current_state + 10;	// move up
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state + 10 + 1; // move up scewed right
				}
			} else if (restricted_by_right.find(current_state) != restricted_by_right.end()) { // along right wall
				if (prob < p1) {
					hypo_state = current_state + 10;	// move up
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state + 10 - 1; // move up scewed left
				}
			} else {																		// general move
				if (prob < p1) {
					hypo_state = current_state + 10;	// move up
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					hypo_state = current_state + 10 - 1; // move up scewed left
				} else {
					hypo_state = current_state + 10 + 1; // move up scewed right
				}
			}
			break;
		case 1:  // DOWN
			
			if (restricted_by_down.find(current_state) != restricted_by_down.end()) {	// bumping into up
				hypo_state = find_state_along_wall(-2); 
			} else if (restricted_by_left.find(current_state) != restricted_by_left.end()) {  // along left wall
				if (prob < p1) {
					hypo_state = current_state - 10;	// move down
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state - 10 + 1; // move down scewed right
				}
			} else if (restricted_by_right.find(current_state) != restricted_by_right.end()) { // along right wall
				if (prob < p1) {
					hypo_state = current_state - 10;	// move down
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state - 10 - 1; // move down scewed left
				}
			} else {																		// general move
				if (prob < p1) {
					hypo_state = current_state - 10;	// move up
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					hypo_state = current_state - 10 - 1; // move down scewed left
				} else {
					hypo_state = current_state - 10 + 1; // move down scewed right
				}
			}
			break;
		case 2:  // LEFT

			if (restricted_by_left.find(current_state) != restricted_by_left.end()) {	// bumping into left
				hypo_state = find_state_along_wall(-3); 
			} else if (restricted_by_up.find(current_state) != restricted_by_up.end()) {  // along up wall
				if (prob < p1) {
					hypo_state = current_state - 1;	// move left
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state - 10 - 1; // move left scewed down
				}
			} else if (restricted_by_down.find(current_state) != restricted_by_down.end()) { // along down wall
				if (prob < p1) {
					hypo_state = current_state - 1;	// move left
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state + 10 - 1; // move left scewed up
				}
			} else {																		// general move
				if (prob < p1) {
					hypo_state = current_state - 1;	// move left
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					hypo_state = current_state + 10 - 1; // move left scewed up
				} else {
					hypo_state = current_state - 10 - 1; // move left scewed down
				}
			}
			break;
		case 3:  // RIGHT
			hypo_state = current_state + 1;
			if (restricted_by_right.find(current_state) != restricted_by_right.end()) {	// bumping into right
				hypo_state = find_state_along_wall(-4); 
			} else if (restricted_by_up.find(current_state) != restricted_by_up.end()) {  // along up wall
				if (prob < p1) {
					hypo_state = current_state + 1;	// move right
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state - 10 + 1; // move right scewed down
				}
			} else if (restricted_by_down.find(current_state) != restricted_by_down.end()) { // along down wall
				if (prob < p1) {
					hypo_state = current_state + 1;	// move right
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else {
					hypo_state = current_state + 10 + 1; // move right scewed up
				}
			} else {																		// general move
				if (prob < p1) {
					hypo_state = current_state + 1;	// move right
				} else if (prob < p1 + p2) {
					hypo_state = current_state;			// stay
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					hypo_state = current_state + 10 + 1; // move right scewed up
				} else {
					hypo_state = current_state - 10 + 1; // move right scewed down
				}
			}
			break;
		default:
			hypo_state = -5;
			break;
	}

	return hypo_state;
}

int Environment::find_state_along_wall(int hypo_state) {
	int s = -1;

	uniform_real_distribution<float> distribution(0.0f, 1.0f);
	double prob = distribution(generator);

	switch (hypo_state)
	{
		case -1:	{	// bumping into up
			if (restricted_by_right.find(current_state) != restricted_by_right.end()) {  // up and right 

				if (prob < p1 + p2) {
					s = current_state;  // stay
				} else {
					s = current_state - 1; // move left
				}
			} else if (restricted_by_left.find(current_state) != restricted_by_left.end()) {  // up and left
				if (prob < p1 + p2) {
					s = current_state; // stay
				} else {
					s = current_state + 1; // move right
				}
			} else {																		// just up
				if (prob < p1 + p2) {
					s = current_state; // stay
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					s = current_state - 1; // move left
				} else {
					s = current_state + 1; // move right 
				}
			}
			break;
		}
		case -2:	{	// bumping into down
			if (restricted_by_right.find(current_state) != restricted_by_right.end()) {  // down and right 

				if (prob < p1 + p2) {
					s = current_state; // stay
				} else {
					s = current_state - 1; // move left
				}

			} else if (restricted_by_left.find(current_state) != restricted_by_left.end()) {  // down and left
				if (prob < p1 + p2) {
					s = current_state; // stay
				} else {
					s = current_state + 1; // move right
				}
			} else {																		// just down
				if (prob < p1 + p2) {
					s = current_state; // stay
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					s = current_state - 1;  // move left
				} else {
					s = current_state + 1;  // move right
				}
			}
			break;
		}
		case -3:	{	// bumping into left
			if (restricted_by_up.find(current_state) != restricted_by_up.end()) {  // left and up

				if (prob < p1 + p2) {
					s = current_state;
				} else {
					s = current_state - 10;
				}

			} else if (restricted_by_down.find(current_state) != restricted_by_down.end()) {  // left and down
				if (prob < p1 + p2) {
					s = current_state;
				} else {
					s = current_state + 10;
				}
			} else {																		// just up
				if (prob < p1 + p2) {
					s = current_state;
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					s = current_state - 10;
				} else {
					s = current_state + 10;
				}
			}
			break;
		}
		case -4:	{	// bumping into right
			if (restricted_by_up.find(current_state) != restricted_by_up.end()) {  // right and up

				if (prob < p1 + p2) {
					s = current_state;
				} else {
					s = current_state - 10;
				}

			} else if (restricted_by_down.find(current_state) != restricted_by_down.end()) {  // right and down
				if (prob < p1 + p2) {
					s = current_state;
				} else {
					s = current_state + 10;
				}
			} else {																		// just up
				if (prob < p1 + p2) {
					s = current_state;
				} else if (prob < p1 + p2 + off_the_grid_adjacent) {
					s = current_state - 10;
				} else {
					s = current_state + 10;
				}
			}
			break;
		}
		default:
			s = -5;
			break;
	}

	return s;
}

int Environment::get_reward(int a) {
	int next_s = -1;

	next_s = next_state(a);
	
	last_reward = next_s == 99 ? 100 : -1;
	current_state = next_s;
	return last_reward;
}

int Environment::get_last_reward() {
	return last_reward;
}