#pragma once
#include "ITarget.hpp"
#include "ManifestObjects.hpp"

class BuildTarget : public ITarget {
public:
	BuildTarget(const ManifestObjects::ManifestTarget& target);

	void Dump() const override;

protected:

	std::vector<std::filesystem::path> _sources;
	std::vector<std::filesystem::path> _includeDirs;
	std::vector<std::string> _compilerOptions;
	std::filesystem::path _intDir;
	std::filesystem::path _outDir;
	std::vector<std::filesystem::path> _bridgesImplements;
	std::vector<std::filesystem::path> _bridgesUses;
};
