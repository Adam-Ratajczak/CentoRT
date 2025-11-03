#pragma once
#include "BuildTarget.hpp"
#include "ManifestObjects.hpp"

class GoGoTarget : public BuildTarget {
public:
	GoGoTarget(const ManifestObjects::ManifestTarget& target);
	static std::string StaticClassName;

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetFactory<ManifestObjects::ManifestTarget, GoGoTarget> {
public:
	std::unique_ptr<GoGoTarget> Create(const ManifestObjects::ManifestTarget* target) const {
		if (target) {
			return std::make_unique<GoGoTarget>(*target);
		}
		return nullptr;
	}
};
