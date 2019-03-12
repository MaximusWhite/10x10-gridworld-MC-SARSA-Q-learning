#pragma once
#include <random>
#include <set>

using namespace std;

class Environment {
	public:
		Environment(double p1, double p2, int start_state);
		int get_current_state();
		int get_reward(int a);
		int get_last_reward();
	private:
		double p1;
		double p2;
		double p3;
		double off_the_grid_ignore;
		double off_the_grid_adjacent;
		int current_state = 0;
		int last_reward = -1;
		int hypothetical_state(int a);
		set<int> restricted_by_up = {40, 41, 43, 44, 45, 46, 48, 49, 90, 91, 92, 93, 94, 95, 96, 97, 98};
		set<int> restricted_by_down = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 50, 51, 53, 54, 55, 56, 58, 59};
		set<int> restricted_by_left = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 5, 15, 35, 45, 55, 65, 85, 95};
		set<int> restricted_by_right = {9, 19, 39, 49, 59, 69, 89, 4, 14, 34, 44, 54, 64, 84, 94};
};
