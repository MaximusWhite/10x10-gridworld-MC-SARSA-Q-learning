#include "agent.h"

random_device r;
default_random_engine generator{ r() };

Agent::Agent() {

}

Agent::initialize_policy() {
	uniform_int_distribution<int> distribution(0, 3);

	for (int cluster = 0; cluster < 4; cluster++) {
		for (int s = 0; s < 25; s++) {
			bool max_used = false;
			int roll = distribution(generator);
			for (int a = 0; a < 4; a++) {
				if (a == roll) {
					policy[cluster][s][a] = max_prob();
				} else {
					policy[cluster][s][a] = non_max_prob();
				}
			}
		}
	}
}