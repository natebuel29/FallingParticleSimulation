#include "Colors.h"
#include "Logger.h"


// Either have a function like this ORRR 
//have a struct of enum COLOR to an RGB value
// memory or speed efficent?!
RGB getRGBFromColor(Color color) {
	RGB rgb = {};

	//COULD THIS BE BASED OFF OF PARTICLE NAME INSTEAD OF STORING A COLOR ENUM IN PARTICLE STRUCT??
	switch (color) {
		case Color::GRAY:
			rgb.r = 50;
			rgb.g = 50;
			rgb.b = 50;
			rgb.a = 1;
			break;
		case Color::LIGHT_BROWN:
			rgb.r = 194;
			rgb.g = 178;
			rgb.g = 178;
			rgb.b = 128;
			rgb.a = 1;
			break;
		default:
			Logger::getInstance()->warn("WHAAT WE DONT HAVE THAT COLOR?!"); \
			break;
	}

	return rgb;
}