#include "GoGenerator.hpp"
#include <fstream>

void GoGenerator::Init(const std::string& name, const std::string& version, const std::string& buildmode, const std::vector<std::string>& compilerOptions, const std::vector<std::string>& linkerOptions) {
	_name = name;
	_version = version;

	std::string copt, ldopt;
	for (const auto& option : compilerOptions) {
		if (!copt.empty()) {
			copt += " ";
		}

		copt += option;
	}
	for (const auto& option : linkerOptions) {
		if (!ldopt.empty()) {
			ldopt += " ";
		}

		ldopt += option;
	}

	_buildCommand = "go build";
	if (!buildmode.empty()) {
		_buildCommand += " -buildmode=\"" + buildmode + "\"";
	}
	if (!copt.empty()) {
		_buildCommand += " -gcflags=\"" + copt + "\"";
	}
	if (!ldopt.empty()) {
		_buildCommand += " -ldflags=\"" + ldopt + "\"";
	}

	_buildCommand += " -o $(APP)";
}

bool GoGenerator::SaveToFile(const std::filesystem::path& goPath, const std::filesystem::path& makefilePath) {
	std::ofstream gomod(goPath), makefile(makefilePath);

	gomod << "module " << _name << "\n";
	gomod << "go " << _version << "\n";
	gomod.close();

	makefile << "# Makefile\n";
	makefile << "APP = " << _name << "\n\n";
	makefile << "build:\n";
	makefile << "\t" << _buildCommand << "\n";
	makefile.close();

	return true;
}