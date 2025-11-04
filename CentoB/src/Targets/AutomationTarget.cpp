#include "AutomationTarget.hpp"
#include "Utils.hpp"
#include <iostream>

#include <Tasks/AutomationTask.hpp>

std::string AutomationTarget::StaticClassName = "automation";

AutomationTarget::AutomationTarget(const ManifestObjects::ManifestAutomation& automation) {
	std::filesystem::path path = automation.path.has_value() ? *automation.path : "";
	if (automation.script.has_value()) {
		_script = *automation.script;
		if (!Utils::IsWeaklyCanonical(_script)) {
			_script = path / _script;
		}
		_script = Utils::NormalizePath(_script);
	}

	if (automation.hooks.has_value()) {
		_hooks = *automation.hooks;
	}

	if (automation.actions.has_value()) {
		_actions = *automation.actions;
	}
}

void AutomationTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	for (const auto& [hook, funcName] : _hooks) {
		EOrder order = EOrder::POSTBUILD;
		if (hook == "pregen") {
			order = EOrder::PREGEN;
		}
		else if (hook == "postgen") {
			order = EOrder::POSTGEN;
		}
		else if (hook == "prebuild") {
			order = EOrder::PREBUILD;
		}
		else if (hook == "postbuild") {
			order = EOrder::POSTBUILD;
		}
		else {
			continue;
		}
		tasks.emplace_back(std::make_unique<AutomationTask>(_script, funcName, order));
	}
}

void AutomationTarget::Dump() const {
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
