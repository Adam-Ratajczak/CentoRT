#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class AutomationTargetObject : public ITargetObject {
public:
	static std::string StaticClassName;
	AutomationTargetObject(const ManifestAutomation& automation);

	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
	void Dump() const override;

private:
	std::filesystem::path _script;
	std::map<std::string, std::string> _hooks;
	std::map<std::string, std::string> _actions;
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
