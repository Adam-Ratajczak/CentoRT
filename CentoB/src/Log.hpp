#pragma once
#include <string>

class Log {
public:
	static void LogInfo(const std::string& msg);
	static void LogWarning(const std::string& msg);
	static void LogError(const std::string& msg);
};
