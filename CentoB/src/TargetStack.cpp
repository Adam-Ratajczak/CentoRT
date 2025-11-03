#include "TargetStack.hpp"
#include "Targets/TargetRegistry.hpp"
#include "Tasks/ITask.hpp"
#include <iostream>
#include <queue>
#include <set>

void TargetStack::BuildTargetsAndTasks() {
	if (!ResolveStartupTarget()) {
		throw std::runtime_error("Could not resolve startup target");
	}

	ResolveTargets();
	ResolveExternalDependencies();
	ResolveAutomation();
	
	ResolvePromises();
	OrderPromises();
	OptimizePromises();

	ResolveFinalTargets();
	ResolveFinalTasks();
}

void TargetStack::DumpTargets() const {
	for (const auto& target : _targets) {
		std::cout << "=================================\n";
		target->Dump();
	}
	std::cout << "=================================\n";
}

void TargetStack::DumpTasks() const {
	for (const auto& task : _tasks) {
		std::cout << "=================================\n";
		task->Dump();
	}
	std::cout << "=================================\n";
}

bool TargetStack::ResolveStartupTarget() {
	_startupTarget.clear();
	if (_manifestRoot.workspaces.has_value()) {
		auto startupWorkspace = _manifestRoot.startupWorkspace.has_value() ? *_manifestRoot.startupWorkspace : "";
		for (const auto& workspace : *_manifestRoot.workspaces) {
			auto workspaceName = workspace.name.has_value() ? *workspace.name : "";
			if (!startupWorkspace.empty()) {
				if(startupWorkspace == workspaceName)
					return ResolveStartupTarget(workspace);
			}
			else {
				if (ResolveStartupTarget(workspace))
					return true;
			}
		}
	}

	return false;
}

bool TargetStack::ResolveStartupTarget(const ManifestObjects::ManifestWorkspace& workspace) {
	if (workspace.projects.has_value()) {
		auto workspaceName = workspace.name.has_value() ? *workspace.name : "";
		auto startupProject = workspace.startupProject.has_value() ? *workspace.startupProject : "";
		for (const auto& project : *workspace.projects) {
			auto projectName = project.name.has_value() ? *project.name : "";
			if (!startupProject.empty()) {
				if (startupProject == projectName)
					return ResolveStartupTarget(project, workspaceName);
			}
			else {
				if (ResolveStartupTarget(project, workspaceName))
					return true;
			}
		}
	}

	return false;
}

bool TargetStack::ResolveStartupTarget(const ManifestObjects::ManifestProject& project, const std::string& workspaceName) {
	if (project.targets.has_value()) {
		auto projectName = project.name.has_value() ? *project.name : "";
		auto startupTarget = project.startupTarget.has_value() ? *project.startupTarget : "";
		for (const auto& target : *project.targets) {
			auto targetName = target.name.has_value() ? *target.name : "";
			if (!startupTarget.empty() && startupTarget == targetName || startupTarget.empty()) {
				_startupTarget = workspaceName + ":" + projectName + ":" + targetName;
				return true;
			}
		}
	}

	return false;
}

void TargetStack::ResolveTargets() {
	_manifestTargets.clear();
	if (_manifestRoot.workspaces.has_value()) {
		for (const auto& workspace : *_manifestRoot.workspaces) {
			ResolveTargets(workspace);
		}
	}
}

void TargetStack::ResolveTargets(const ManifestObjects::ManifestWorkspace& workspace) {
	if (workspace.projects.has_value()) {
		for (const auto& project : *workspace.projects) {
			ResolveTargets(project, workspace.name.has_value() ? *workspace.name : "");
		}
	}
}

void TargetStack::ResolveTargets(const ManifestObjects::ManifestProject& project, const std::string& workspaceName) {
	std::string projectName = project.name.has_value() ? *project.name : "";
	if (project.targets.has_value()) {
		for (const auto& target : *project.targets) {
			std::string targetName = target.name.has_value() ? *target.name : "";
			_manifestTargets[workspaceName + ":" + projectName + ":" + targetName] = &target;
		}
	}
}

void TargetStack::ResolveExternalDependencies() {
	_manifestExternalDependencies.clear();
	if (_manifestRoot.workspaces.has_value()) {
		for (const auto& workspace : *_manifestRoot.workspaces) {
			ResolveExternalDependencies(workspace);
		}
	}
}

void TargetStack::ResolveExternalDependencies(const ManifestObjects::ManifestWorkspace& workspace) {
	if (workspace.projects.has_value()) {
		for (const auto& project : *workspace.projects) {
			ResolveExternalDependencies(project, workspace.name.has_value() ? *workspace.name : "");
		}
	}
}

void TargetStack::ResolveExternalDependencies(const ManifestObjects::ManifestProject& project, const std::string& workspaceName) {
	std::string projectName = project.name.has_value() ? *project.name : "";
	if (project.externalDependencies.has_value()) {
		for (const auto& externalDependency : *project.externalDependencies) {
			std::string externalDependencyName = externalDependency.name.has_value() ? *externalDependency.name : "";
			_manifestExternalDependencies[workspaceName + ":" + projectName + ":" + externalDependencyName] = &externalDependency;
		}
	}
}

void TargetStack::ResolveAutomation() {
	_manifestAutomation.clear();
	if (_manifestRoot.workspaces.has_value()) {
		for (const auto& workspace : *_manifestRoot.workspaces) {
			ResolveAutomation(workspace);
		}
	}
}

void TargetStack::ResolveAutomation(const ManifestObjects::ManifestWorkspace& workspace) {
	if (workspace.automation.has_value()) {
		_manifestAutomation[workspace.name.has_value() ? *workspace.name : ""] = &*workspace.automation;
	}
}

std::string TargetStack::ResolveFullName(const std::string& partialName) {
	for (const auto& [key, _] : _manifestTargets) {
		auto pos = key.rfind(partialName);
		if (pos != std::string::npos && pos == key.size() - partialName.size()) {
			return key;
		}
	}
	for (const auto& [key, _] : _manifestExternalDependencies) {
		auto pos = key.rfind(partialName);
		if (pos != std::string::npos && pos == key.size() - partialName.size()) {
			return key;
		}
	}

	return partialName;
}

void TargetStack::ResolvePromises() {
	_unorderedPromises.clear();
	for (const auto& [key, target] : _manifestTargets) {
		TargetPromise promise;
		promise.Key = key;
		promise.Type = ETargetType::TARGET;
		if (target->link.has_value()) {
			for (const auto& dependency : *target->link) {
				promise.DependsOn.emplace_back(ResolveFullName(dependency));
			}
		}
		promise.DependsOn.emplace_back(promise.Key.substr(0, promise.Key.find(":")));

		_unorderedPromises.emplace_back(promise);
	}

	for (const auto& [key, externalDependency] : _manifestExternalDependencies) {
		TargetPromise promise;
		promise.Key = key;
		promise.Type = ETargetType::EXTERNAL_DEPENDENCY;
		if (externalDependency->resolveFirst.has_value()) {
			for (const auto& dependency : *externalDependency->resolveFirst) {
				promise.DependsOn.emplace_back(ResolveFullName(dependency));
			}
		}
		promise.DependsOn.emplace_back(promise.Key.substr(0, promise.Key.find(":")));

		_unorderedPromises.emplace_back(promise);
	}

	for (const auto& [key, automation] : _manifestAutomation) {
		TargetPromise promise;
		promise.Key = key;
		promise.Type = ETargetType::AUTOMATION;

		_unorderedPromises.emplace_back(promise);
	}
}

void TargetStack::OrderPromises() {
	std::unordered_map<std::string, std::vector<std::string>> dependencyGraph;
	std::unordered_map<std::string, int> inDegree;

	for (const auto& promise : _unorderedPromises) {
		if (inDegree.find(promise.Key) == inDegree.end()) {
			inDegree[promise.Key] = 0;
		}

		for (const auto& dep : promise.DependsOn) {
			dependencyGraph[dep].push_back(promise.Key);
			inDegree[promise.Key]++;
		}
	}

	std::queue<std::string> zeroInDegreeQueue;
	for (const auto& [target, degree] : inDegree) {
		if (degree == 0) {
			zeroInDegreeQueue.push(target);
		}
	}

	_orderedPromises.clear();
	while (!zeroInDegreeQueue.empty()) {
		std::string currentTarget = zeroInDegreeQueue.front();
		zeroInDegreeQueue.pop();

		auto it = std::find_if(_unorderedPromises.begin(), _unorderedPromises.end(), [&](const TargetPromise& promise) -> bool {
			return promise.Key == currentTarget;
			});
		if (it != _unorderedPromises.end()) {
			_orderedPromises.emplace_back(*it);
		}

		for (const auto& dependentTarget : dependencyGraph[currentTarget]) {
			inDegree[dependentTarget]--;
			if (inDegree[dependentTarget] == 0) {
				zeroInDegreeQueue.push(dependentTarget);
			}
		}
	}

	if (_orderedPromises.size() != inDegree.size()) {
		throw std::runtime_error("Cyclic dependency detected");
	}
}

void TargetStack::OptimizePromises() {
	auto it = std::find_if(_orderedPromises.begin(), _orderedPromises.end(), [&](const TargetPromise& promise) -> bool {
		return promise.Key == _startupTarget;
		});

	std::set<std::string> keys;
	if (it != _orderedPromises.end()) {
		FetchDependencyKeys(*it, keys);
	}

	_optimizedPromises.clear();
	for (const auto& promise : _orderedPromises) {
		if (keys.find(promise.Key) != keys.end()) {
			_optimizedPromises.emplace_back(promise);
		}
	}
}

void TargetStack::FetchDependencyKeys(const TargetPromise& promise, std::set<std::string>& keys) {
	for (const auto& dependency : promise.DependsOn) {
		auto it = std::find_if(_orderedPromises.begin(), _orderedPromises.end(), [&](const TargetPromise& promise) -> bool {
			return promise.Key == dependency;
			});
		if (it != _orderedPromises.end()) {
			FetchDependencyKeys(*it, keys);
		}
	}
	keys.insert(promise.Key);
}

void TargetStack::ResolveFinalTargets() {
	TargetRegistry registry;

	for (const auto& promise : _optimizedPromises) {
		std::unique_ptr<ITarget> target;
		switch (promise.Type) {
		case ETargetType::TARGET: {
			auto it = _manifestTargets.find(promise.Key);
			if (it != _manifestTargets.end()) {
				const auto* manifestTarget = it->second;
				std::string identifier = (manifestTarget->language.has_value() ? *manifestTarget->language : "") + ":" + (manifestTarget->toolchain.has_value() ? *manifestTarget->toolchain : "");
				target = registry.Create(identifier, manifestTarget);
			}
			break;
		}
		case ETargetType::EXTERNAL_DEPENDENCY: {
			auto it = _manifestExternalDependencies.find(promise.Key);
			if (it != _manifestExternalDependencies.end()) {
				const auto* manifestExternalDependency = it->second;
				std::string identifier = "external";
				target = registry.Create(identifier, manifestExternalDependency);
			}
			break;
		}
		case ETargetType::AUTOMATION: {
			auto it = _manifestAutomation.find(promise.Key);
			if (it != _manifestAutomation.end()) {
				const auto* manifestAutomation = it->second;
				std::string identifier = "automation";
				target = registry.Create(identifier, manifestAutomation);
			}
			break;
		}
		}

		if (target) {
			_targets.emplace_back(std::move(target));
		}
	}
}

void TargetStack::ResolveFinalTasks() {
	std::vector<std::unique_ptr<ITask>> allTasks;
	for (const auto& target : _targets) {
		target->FetchTasks(allTasks);
	}
	
	std::stable_sort(allTasks.begin(), allTasks.end(),
		[](const std::unique_ptr<ITask>& a, const std::unique_ptr<ITask>& b) {
			return a->GetOrder() < b->GetOrder();
		});

	std::move(allTasks.begin(), allTasks.end(), std::back_inserter(_tasks));
}
