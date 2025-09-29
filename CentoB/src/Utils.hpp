#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <map>

namespace Utils {

	void ExpandGlob(const std::string& pattern, const std::filesystem::path& dirToSearch, std::vector<std::filesystem::path>& paths);
	std::map<std::string, std::string> ParseEnvFile(const std::filesystem::path& path);

	bool IsWeaklyCanonical(const std::filesystem::path& p);
	bool Match(const std::string& sequence, const std::string& pattern);
}