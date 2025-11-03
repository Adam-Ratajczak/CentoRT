#pragma once
#include <filesystem>
#include <optional>
#include "ManifestObjects.hpp"

class ManifestFile {
	std::optional<std::string> _error;

	void ReadManifestTree(const std::filesystem::path& path, figcone::ConfigReader& cfgReader, std::vector<ManifestObjects::ManifestRoot>& manifests);

public:
	void LoadFromFile(const std::filesystem::path& path);

	bool Fail() const;
	std::string GetError() const;
};
