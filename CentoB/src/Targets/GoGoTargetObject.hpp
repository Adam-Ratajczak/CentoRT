#pragma once
#include "GoTargetObject.hpp"
#include "ManifestObjects.hpp"

class GoGoTargetObject : public GoTargetObject {
public:
	GoGoTargetObject(const ManifestTarget& target);
	static std::string StaticClassName;

	void FetchTasks(std::vector<ITask>& tasks) const override;
};

template<>
class TargetObjectFactory<ManifestTarget, GoGoTargetObject> {
public:
	std::unique_ptr<GoGoTargetObject> Create(const ManifestTarget* target) const {
		if (target) {
			return std::make_unique<GoGoTargetObject>(*target);
		}
		return nullptr;
	}
};
