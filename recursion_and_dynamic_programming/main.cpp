#include <catch2/catch_all.hpp>
#include <iostream>

// 8.1 triple step
int num_ways(int num_steps) {
	// impossible option - don't count it
	if (num_steps < 0) {
		return 0;
	}
	// base case - at the top
	else if (num_steps == 0) {
		return 1;
	}

	int count = 0;
	for (int steps = 1; steps <= 3; steps++) {
		count += num_ways(num_steps - steps);
	}

	return count;
}

TEST_CASE("triple step")
{
	/* for three steps, the child could:
		- take 1 step at a time   (1)
		- 2 steps and then 1 step (1)
		- 1 step and then 2 steps (1)
		- all three               (1)
		==============================
		total:					   4
	 */
	REQUIRE(num_ways(3) == 4);
}

//todo all the rest :)