#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <optional>

class DotnetGenerator {
public:
	DotnetGenerator() = default;

	void Init(const std::vector<std::filesystem::path>& sources, const std::vector<std::string>& options);
	bool SaveToFile(const std::filesystem::path& path) const;

private:
	std::vector<std::pair<std::string, std::string>> _properties;
	std::vector<std::pair<std::string, std::string>> _items;
};
