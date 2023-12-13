#pragma once
#include <stdint.h>

// Not sure if this enum will be needed
enum Color : uint8_t {
	GRAY,
	LIGHT_BROWN
};

struct RGB {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

RGB getRGBFromColor(Color color);