#pragma once
#include "CsTargetObject.hpp"
#include "ManifestObjects.hpp"

class CsDotnetTargetObject : public CsTargetObject {
public:
	CsDotnetTargetObject(const ManifestTarget& target);
	static std::string StaticClassName;

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetObjectFactory<ManifestTarget, CsDotnetTargetObject> {
public:
	std::unique_ptr<CsDotnetTargetObject> Create(const ManifestTarget* target) const {
		if (target) {
			return std::make_unique<CsDotnetTargetObject>(*target);
		}
		return nullptr;
	}
};
