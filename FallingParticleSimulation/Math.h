#pragma once
#include <cmath>
#include <random>

struct Vec2 {
	float x;
	float y;
};

class Math
{
	public:
		static int roundToNearestMultiple(int target, int multiple);
		static int getRandomInt(int lower, int upper);
};

