#pragma once
#include <filesystem>
#include <string>
#include <vector>

class CargoGenerator {
public:
	CargoGenerator() = default;

	void Init(const std::string& name, const std::string& version, const std::string& edition, const std::vector<std::string>& crateType, const std::vector<std::string>& options);
	bool SaveToFile(const std::filesystem::path& path) const;

private:
	std::vector<std::pair<std::string, std::string>> _package;
	std::vector<std::pair<std::string, std::string>> _lib;
	std::vector< std::pair<std::string, std::string>> _build;
};
