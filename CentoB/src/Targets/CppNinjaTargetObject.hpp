#pragma once
#include "CppTargetObject.hpp"
#include "ManifestObjects.hpp"

class CppNinjaTargetObject : public CppTargetObject {
public:
	static std::string StaticClassName;
	CppNinjaTargetObject(const ManifestTarget& target);

	void FetchTasks(std::vector<ITask>& tasks) const override;
};

template<>
class TargetObjectFactory<ManifestTarget, CppNinjaTargetObject> {
public:
	std::unique_ptr<CppNinjaTargetObject> Create(const ManifestTarget* target) const {
		if (target) {
			return std::make_unique<CppNinjaTargetObject>(*target);
		}
		return nullptr;
	}
};
