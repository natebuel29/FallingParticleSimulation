#pragma once
#pragma warning(disable : 4996)
#include <iostream>
class Logger
{
	public:
		Logger() {

		};
		void info(std::string message);
		void warn(std::string message);
		void error(std::string message);
	private:
		void log(std::string logLevel, std::string message);
};

