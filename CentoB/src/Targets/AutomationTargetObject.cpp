#include "AutomationTargetObject.hpp"
#include "Utils.hpp"
#include <iostream>

std::string AutomationTargetObject::StaticClassName = "automation";

AutomationTargetObject::AutomationTargetObject(const ManifestAutomation& automation) {
	if (automation.script.has_value()) {
		std::vector<std::filesystem::path> paths;
		Utils::ResolvePaths(*automation.script, paths);

		if (!paths.empty()) {
			_script = paths[0];
		}
	}

	if (automation.hooks.has_value()) {
		_hooks = *automation.hooks;
	}

	if (automation.actions.has_value()) {
		_actions = *automation.actions;
	}
}

void AutomationTargetObject::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {

}

void AutomationTargetObject::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	std::cout << "script: " << _script << "\n";

	std::cout << "hooks: {";
	bool first = true;
	for (const auto& [key, value] : _hooks) {
		if (!first) {
			std::cout << ",";
		}
		std::cout << "\"" << key << "\":\"" << value << "\"";
		first = false;
	}
	std::cout << "}\n";

	std::cout << "actions: {";
	first = true;
	for (const auto& [key, value] : _actions) {
		if (!first) {
			std::cout << ",";
		}
		std::cout << "\"" << key << "\":\"" << value << "\"";
		first = false;
	}
	std::cout << "}\n";
}
