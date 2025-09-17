#include "ManifestFile.hpp"
#include "ManifestObjects.hpp"

void ManifestFile::LoadFromFile(const std::filesystem::path& path) {
    _error = std::nullopt;
    try {
        auto cfgReader = figcone::ConfigReader{};
        auto cfg = cfgReader.readYamlFile<ManifestRoot>(path);
    }
    catch (std::exception& e) {
        _error = e.what();
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
