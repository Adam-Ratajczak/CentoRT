#include "ManifestFile.hpp"
#include "Utils.hpp"

void ManifestFile::LoadFromFile(const std::filesystem::path& path) {
    _error = std::nullopt;
    try {
        figcone::ConfigReader cfgReader;
        std::vector<ManifestRoot> manifests;

        ReadManifestTree(path, cfgReader, manifests);
        if (manifests.empty()) {
            throw std::runtime_error("Empty manifest");
        }

        ManifestRoot mergedManifest = manifests[0];
        for (int i = 1; i < manifests.size(); i++) {
            mergedManifest = MergeManifest(mergedManifest, manifests[i]);
        }

        PropagateVarsAndProfiles(mergedManifest);
        EvaluateCentoVars(mergedManifest);
        ManifestExpandVars(mergedManifest);
    }
    catch (std::exception& e) {
        _error = e.what();
    }
}

void ManifestFile::ReadManifestTree(const std::filesystem::path& filePath, figcone::ConfigReader& cfgReader, std::vector<ManifestRoot>& manifests) {
    try {
        ManifestRoot cfg = cfgReader.readYamlFile<ManifestRoot>(filePath);

        std::filesystem::path curr_path = filePath.parent_path();
        if (cfg.includes.has_value()) {
            std::vector<std::filesystem::path> paths;
            for (const auto& includeGlob : *cfg.includes) {
                std::vector<std::filesystem::path> intermediatePaths;
                Utils::ExpandGlob(includeGlob, curr_path, intermediatePaths);
                paths.insert(paths.end(), intermediatePaths.begin(), intermediatePaths.end());
            }

            for (const auto& path : paths) {
                ReadManifestTree(curr_path / path, cfgReader, manifests);
            }

            cfg.includes = std::nullopt;
        }

        CheckAndPostprocessManifest(curr_path.generic_string(), cfg);
        manifests.emplace_back(cfg);
    }
    catch (std::exception& e) {
        std::string errMsg = "Error in file \"" + filePath.string() + "\": " + e.what();
        
        throw std::runtime_error(errMsg);
    }
}

bool ManifestFile::Fail() const {
    return _error.has_value();
}

std::string ManifestFile::GetError() const {
    if (_error.has_value()) {
        return *_error;
    }

    return "";
}
