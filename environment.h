#pragma once

class Environment {
	public:
		Environment(double p1, double p2, int start_state);
		int get_next_state(int a);
		int get_last_reward();
	private:
		double p1;
		double p2;
		double p3;
		double off_the_grid_ignore;
		double off_the_grid_adjacent;
		int current_state = 0;
		int last_reward = -1;
};
