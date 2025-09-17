#include "Log.hpp"
#include <iostream>

void Log::LogInfo(const std::string& msg) {
	std::cerr << "[INFO]\t" << msg << "\n";
}

void Log::LogWarning(const std::string& msg) {
	std::cerr << "[WARN]\t" << msg << "\n";
}

void Log::LogError(const std::string& msg) {
	std::cerr << "[ERROR]\t" << msg << "\n";
}
