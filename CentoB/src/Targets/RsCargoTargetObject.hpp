#pragma once
#include "RsTargetObject.hpp"
#include "ManifestObjects.hpp"

class RsCargoTargetObject : public RsTargetObject {
public:
	RsCargoTargetObject(const ManifestTarget& target);
	static std::string StaticClassName;

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetObjectFactory<ManifestTarget, RsCargoTargetObject> {
public:
	std::unique_ptr<RsCargoTargetObject> Create(const ManifestTarget* target) const {
		if (target) {
			return std::make_unique<RsCargoTargetObject>(*target);
		}
		return nullptr;
	}
};
