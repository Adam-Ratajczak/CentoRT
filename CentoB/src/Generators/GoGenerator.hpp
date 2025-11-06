#pragma once
#include <filesystem>
#include <string>
#include <vector>

class GoGenerator {
public:
	GoGenerator() = default;

	void Init(const std::string& name, const std::string& version, const std::string& buildmode, const std::vector<std::string>& compilerOptions, const std::vector<std::string>& linkerOptions);
	bool SaveToFile(const std::filesystem::path& goPath, const std::filesystem::path& makefilePath);

private:
	std::string _name;
	std::string _version;
	std::string _buildCommand;
};
