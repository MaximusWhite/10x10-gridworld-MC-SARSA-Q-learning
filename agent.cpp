#include "agent.h"

const double epsilon = 0.1;

double non_max_prob() {
	return (epsilon / 4.0);
}

double max_prob() {
	return 1 - epsilon + non_max_prob();
}

Agent::Agent() : policy(vector<vector<double>>(100, vector<double>(4, 0.0))) {
	initialize_policy();
}

Agent::Agent(vector<vector<double>> q_generated, double a, double gamma_c) : policy(vector<vector<double>>(100, vector<double>(4, 0.0))), 
	Q(q_generated), 
	alpha(a), 
	gamma_constant(gamma_c) {
}

void Agent::initialize_policy() {
	uniform_int_distribution<int> distribution(0, 3);
		for (int s = 0; s < 100; s++) {
			bool max_used = false;
			int roll = distribution(generator);
			for (int a = 0; a < 4; a++) {
				if (a == roll) {
					policy[s][a] = max_prob();
				} else {
					policy[s][a] = non_max_prob();
				}
			}
		}
}

void Agent::readjust_policy(int state, int optimal_action) {
		for (int a = 0; a < 4; a++) {
				if (a == optimal_action) {
					policy[state][a] = max_prob();
				} else {
					policy[state][a] = non_max_prob();
				}
		}
}

void Agent::adjust_q_sarsa(int s, int a, int s_prime, int a_prime, int r) {
		Q[s][a] = Q[s][a] + alpha * (r + gamma_constant * Q[s_prime][a_prime] - Q[s][a]);
}

void Agent::adjust_q_q_learning(int s, int a, int s_prime, int r) {
		vector<double> q_s_prime = Q[s_prime];

		int max_index = 0;
		double max_q = q_s_prime[0];

		for (int a = 1; a < 4; a++) {
			if (q_s_prime[a] > max_q) {
				max_index = a;
				max_q = q_s_prime[a];
			}
		}

		Q[s][a] = Q[s][a] + alpha * (r + gamma_constant * max_q - Q[s][a]);
}


int Agent::pick_action(int s) {
	vector<double> options = policy[s];

	uniform_real_distribution<double> distribution(0.0f, 1.0f);
	double dice_roll = distribution(generator);
	double cum_sum = 0;
	for (int i = 0; i < 4; i++) {
		cum_sum += options[i];
		if (dice_roll <= cum_sum) {
			return i;
		}
	}

	return 0;
}

int Agent::pick_eplison_greedy_action(int s) {
	vector<double> options = policy[s];

	uniform_real_distribution<double> distribution(0.0f, 1.0f);
	uniform_int_distribution<double> roll(0, 3);
	double chance = distribution(generator);
	int dice_roll = roll(generator);
	vector<double> q_for_state = Q[s];
	int max_index = 0;
	double max = q_for_state[0];
	for (int i = 1; i < 4; i++) {
		if (q_for_state[i] > max) {
			max_index = i;
			max = q_for_state[i];
		}
	}

	if (chance < epsilon) {
		return dice_roll;
	} else {
		return max_index;
	}

	return -5;
}

void Agent::greedify_policy() {
	for (int s = 0; s < 99; s++) {
		
		//cout << "greedifying: " << s;

		vector<double> q = Q[s];
		int max_index = 0;
		double max_q = q[0];
		for (int action = 1; action < 4; action++) {
			if (q[action] > max_q) {
				max_index = action;
				max_q = q[action];
			}
		}

		//cout << " ; q_max = " << max_index << endl;

		for (int a = 0; a < 4; a++) {
			if (a == max_index) {
				policy[s][a] = 1.0;
			} else {
				policy[s][a] = 0.0;
			}
		}
	}
}

void Agent::show_policy() {
	cout << "|";
	for (int i = 0; i < 11; i++) {
		cout << "-";
	}
	cout << "|" << endl;
	
	for (int row = 9; row >= 0; row--) {
		cout << "|";

		for (int col = 0; col < 10; col++) {

			int index = row * 10 + col;
			
			if (index == 99) {
				cout << "G";
			} else {

				int max_index = 0;
				double max_a = policy[index][0];
				for (int action = 1; action < 4; action++) {
					if (policy[index][action] > max_a) {
						max_index = action;
						max_a = policy[index][action];
					}
				}

				switch (max_index)
				{
					case 0:
						cout << "\u2191";
						break;
					case 1:
						cout << "\u2193";
						break;
					case 2:
						cout << "\u2190";
						break;
					case 3:
						cout << "\u2192";
						break;
					default:
						cout << "?";
						break;
				}
			}

			if (col == 4) { 
				if (row != 7 && row != 2) { 
					cout << "|";
				} else {
					cout << " ";
				}

			}

		}

		cout << "|" << endl;

		if (row == 5) {
			cout << "|";
			for (int i = 0; i < 11; i++) {
				if (i == 2 || i== 8) {
					cout << " ";
				} else {
					cout << "-";
				}
			}
			cout << "|" << endl;
		}
	}

	cout << "|";
	for (int i = 0; i < 11; i++) {
		cout << "-";
	}
	cout << "|" << endl;

}