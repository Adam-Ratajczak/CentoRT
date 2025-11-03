#pragma once
#include "ITarget.hpp"
#include "ManifestObjects.hpp"

class AutomationTarget : public ITarget {
public:
	static std::string StaticClassName;
	AutomationTarget(const ManifestObjects::ManifestAutomation& automation);

	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
	void Dump() const override;

private:
	std::filesystem::path _script;
	std::map<std::string, std::string> _hooks;
	std::map<std::string, std::string> _actions;
};

template<>
class TargetFactory<ManifestObjects::ManifestAutomation, AutomationTarget> {
public:
	std::unique_ptr<AutomationTarget> Create(const ManifestObjects::ManifestAutomation* automation) const {
		if (automation) {
			return std::make_unique<AutomationTarget>(*automation);
		}
		return nullptr;
	}
};
