#include "Math.h"

int Math::roundToNearestMultiple(int target, int multiple) {
	return (target + 2) / multiple * multiple;
}