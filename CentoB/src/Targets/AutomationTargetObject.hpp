#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class AutomationTargetObject : public ITargetObject {
public:
	static std::string StaticClassName;
	AutomationTargetObject(const ManifestAutomation& automation);

	void FetchTasks(std::vector<ITask>& tasks) const override;
	void Dump() const override;
};

template<>
class TargetObjectFactory<ManifestAutomation, AutomationTargetObject> {
public:
	std::unique_ptr<AutomationTargetObject> Create(const ManifestAutomation* automation) const {
		if (automation) {
			return std::make_unique<AutomationTargetObject>(*automation);
		}
		return nullptr;
	}
};
