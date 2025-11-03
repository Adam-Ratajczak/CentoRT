#pragma once
#include "BuildTarget.hpp"
#include "ManifestObjects.hpp"

class CppNinjaTarget : public BuildTarget {
public:
	static std::string StaticClassName;
	CppNinjaTarget(const ManifestObjects::ManifestTarget& target);

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetFactory<ManifestObjects::ManifestTarget, CppNinjaTarget> {
public:
	std::unique_ptr<CppNinjaTarget> Create(const ManifestObjects::ManifestTarget* target) const {
		if (target) {
			return std::make_unique<CppNinjaTarget>(*target);
		}
		return nullptr;
	}
};
