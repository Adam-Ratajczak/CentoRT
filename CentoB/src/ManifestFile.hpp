#pragma once
#include <filesystem>
#include <optional>

class ManifestFile {
	std::optional<std::string> _error;
public:
	void LoadFromFile(const std::filesystem::path& path);

	bool Fail() const;
	std::string GetError() const;
};
