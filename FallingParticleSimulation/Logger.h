#pragma once
#pragma warning(disable : 4996) // disable warning of localtime
#include <iostream>
class Logger
{
	public:
		void info(std::string message);
		void warn(std::string message);
		void error(std::string message);

		void operator=(const Logger& other) = delete;
		Logger(const Logger& other) = delete;

		static Logger* getInstance();
	private:
		void log(std::string logLevel, std::string message);
		Logger(){
		}

		static Logger* instance;
};

