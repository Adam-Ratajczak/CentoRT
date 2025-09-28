#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace Utils {

	void ExpandGlob(const std::string& pattern, const std::filesystem::path& dirToSearch, std::vector<std::filesystem::path>& paths);

}