#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class CsTargetObject : public ITargetObject {
public:
	CsTargetObject(const ManifestTarget& automation);

	void Dump() const override;

private:
	std::vector<std::filesystem::path> _sources;
	std::vector<std::filesystem::path> _includeDirs;
	std::vector<std::string> _compilerOptions;
	std::filesystem::path _intDir;
	std::filesystem::path _outDir;
	std::vector<std::filesystem::path> _bridgesImplements;
	std::vector<std::filesystem::path> _bridgesUses;
};
