#include "CargoGenerator.hpp"
#include <fstream>

void CargoGenerator::Init(const std::string& name, const std::string& version, const std::string& edition, const std::vector<std::string>& crateType, const std::vector<std::string>& options) {
	_package.clear();
	_lib.clear();
	_build.clear();

	_package.emplace_back(std::make_pair("name", "\"" + name + "\""));
	_package.emplace_back(std::make_pair("version", "\"" + version + "\""));
	_package.emplace_back(std::make_pair("edition", "\"" + edition + "\""));

	if (!crateType.empty()) {
		std::string crates = "[";
		bool first = false;
		for (const auto& crate : crateType) {
			if (first) {
				crates += ", ";
			}
			crates += "\"" + crate + "\"";
			first = true;
		}
		crates += "]";

		_lib.emplace_back(std::make_pair("crate-type", crates));
	}

	if (!options.empty()) {
		std::string optionStr = "[";
		bool first = false;
		for (const auto& option : options) {
			if (first) {
				optionStr += ", ";
			}
			optionStr += "\"-C\", \"" + option + "\"";
			first = true;
		}
		optionStr += "]";

		_build.emplace_back(std::make_pair("rustflags", optionStr));
	}
}

bool CargoGenerator::SaveToFile(const std::filesystem::path& path) const {
	std::ofstream file(path);
	if (!_package.empty()) {
		file << "[package]\n";
		for (const auto& [option, value] : _package) {
			file << option << " = " << value << "\n";
		}
	}
	if (!_lib.empty()) {
		file << "\n[lib]\n";
		for (const auto& [option, value] : _lib) {
			file << option << " = " << value << "\n";
		}
	}
	if (!_build.empty()) {
		file << "\n[lib]\n";
		for (const auto& [option, value] : _build) {
			file << option << " = " << value << "\n";
		}
	}

	file.close();

	return true;
}
