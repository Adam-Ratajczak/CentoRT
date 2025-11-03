#pragma once
#include "BuildTarget.hpp"
#include "ManifestObjects.hpp"

class CsDotnetTarget : public BuildTarget {
public:
	CsDotnetTarget(const ManifestObjects::ManifestTarget& target);
	static std::string StaticClassName;

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetFactory<ManifestObjects::ManifestTarget, CsDotnetTarget> {
public:
	std::unique_ptr<CsDotnetTarget> Create(const ManifestObjects::ManifestTarget* target) const {
		if (target) {
			return std::make_unique<CsDotnetTarget>(*target);
		}
		return nullptr;
	}
};
