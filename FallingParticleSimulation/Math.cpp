#include "Math.h"

int Math::roundToNearestMultiple(int target, int multiple) {
	return (target + 2) / multiple * multiple;
}

std::random_device seed;
std::mt19937 gen{ seed() };

int Math::getRandomInt(int lower, int upper) {
	std::uniform_int_distribution<> dist{ lower, upper }; // set min and max
	int ran = dist(gen); // generate number
	return ran;
}