#include "Logger.h"
#include <ctime>


// Public

void Logger::info(std::string message) {
	log("INFO", message);
}

void Logger::warn(std::string message) {
	log("WARN", message);
}

void Logger::error(std::string message) {
	log("ERROR", message);
}

// Private

void Logger::log(std::string logLevel, std::string message) {
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	std::cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " [" << logLevel << "] " << message << std::endl;
}