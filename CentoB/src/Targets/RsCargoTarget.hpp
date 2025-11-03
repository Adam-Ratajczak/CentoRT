#pragma once
#include "BuildTarget.hpp"
#include "ManifestObjects.hpp"

class RsCargoTarget : public BuildTarget {
public:
	RsCargoTarget(const ManifestObjects::ManifestTarget& target);
	static std::string StaticClassName;

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetFactory<ManifestObjects::ManifestTarget, RsCargoTarget> {
public:
	std::unique_ptr<RsCargoTarget> Create(const ManifestObjects::ManifestTarget* target) const {
		if (target) {
			return std::make_unique<RsCargoTarget>(*target);
		}
		return nullptr;
	}
};
