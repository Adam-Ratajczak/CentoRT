#include "TargetObjectStack.hpp"
#include <iostream>
#include <queue>
#include <set>

void TargetObjectStack::BuildTargetsAndTasks() {
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

void TargetObjectStack::DumpTargets() const {
	for (const auto& target : _targets) {
		std::cout << "=================================\n";
		target->Dump();
	}
	std::cout << "=================================\n";
}

void TargetObjectStack::DumpTasks() const {
	for (const auto& task : _tasks) {
		std::cout << "=================================\n";
		task->Dump();
	}
	std::cout << "=================================\n";
}

bool TargetObjectStack::ResolveStartupTarget() {
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

bool TargetObjectStack::ResolveStartupTarget(const ManifestWorkspace& workspace) {
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

bool TargetObjectStack::ResolveStartupTarget(const ManifestProject& project, const std::string& workspaceName) {
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

void TargetObjectStack::ResolveTargets() {
	_manifestTargets.clear();
	if (_manifestRoot.workspaces.has_value()) {
		for (const auto& workspace : *_manifestRoot.workspaces) {
			ResolveTargets(workspace);
		}
	}
}

void TargetObjectStack::ResolveTargets(const ManifestWorkspace& workspace) {
	if (workspace.projects.has_value()) {
		for (const auto& project : *workspace.projects) {
			ResolveTargets(project, workspace.name.has_value() ? *workspace.name : "");
		}
	}
}

void TargetObjectStack::ResolveTargets(const ManifestProject& project, const std::string& workspaceName) {
	std::string projectName = project.name.has_value() ? *project.name : "";
	if (project.targets.has_value()) {
		for (const auto& target : *project.targets) {
			std::string targetName = target.name.has_value() ? *target.name : "";
			_manifestTargets[workspaceName + ":" + projectName + ":" + targetName] = &target;
		}
	}
}

void TargetObjectStack::ResolveExternalDependencies() {
	_manifestExternalDependencies.clear();
	if (_manifestRoot.workspaces.has_value()) {
		for (const auto& workspace : *_manifestRoot.workspaces) {
			ResolveExternalDependencies(workspace);
		}
	}
}

void TargetObjectStack::ResolveExternalDependencies(const ManifestWorkspace& workspace) {
	if (workspace.projects.has_value()) {
		for (const auto& project : *workspace.projects) {
			ResolveExternalDependencies(project, workspace.name.has_value() ? *workspace.name : "");
		}
	}
}

void TargetObjectStack::ResolveExternalDependencies(const ManifestProject& project, const std::string& workspaceName) {
	std::string projectName = project.name.has_value() ? *project.name : "";
	if (project.externalDependencies.has_value()) {
		for (const auto& externalDependency : *project.externalDependencies) {
			std::string externalDependencyName = externalDependency.name.has_value() ? *externalDependency.name : "";
			_manifestExternalDependencies[workspaceName + ":" + projectName + ":" + externalDependencyName] = &externalDependency;
		}
	}
}

void TargetObjectStack::ResolveAutomation() {
	_manifestAutomation.clear();
	if (_manifestRoot.workspaces.has_value()) {
		for (const auto& workspace : *_manifestRoot.workspaces) {
			ResolveAutomation(workspace);
		}
	}
}

void TargetObjectStack::ResolveAutomation(const ManifestWorkspace& workspace) {
	if (workspace.automation.has_value()) {
		_manifestAutomation[workspace.name.has_value() ? *workspace.name : ""] = &*workspace.automation;
	}
}

std::string TargetObjectStack::ResolveFullName(const std::string& partialName) {
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

void TargetObjectStack::ResolvePromises() {
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

void TargetObjectStack::OrderPromises() {
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

void TargetObjectStack::OptimizePromises() {
	auto it = std::find_if(_orderedPromises.begin(), _orderedPromises.end(), [&](const TargetPromise& promise) -> bool {
		return promise.Key == _startupTarget;
		});

	std::set<std::string> keys;
	if (it != _orderedPromises.end()) {
		FetchDependencies(*it, keys);
	}

	_optimizedPromises.clear();
	for (const auto& promise : _orderedPromises) {
		if (keys.find(promise.Key) != keys.end()) {
			_optimizedPromises.emplace_back(promise);
		}
	}
}

void TargetObjectStack::FetchDependencies(const TargetPromise& promise, std::set<std::string>& keys) {
	for (const auto& dependency : promise.DependsOn) {
		auto it = std::find_if(_orderedPromises.begin(), _orderedPromises.end(), [&](const TargetPromise& promise) -> bool {
			return promise.Key == dependency;
			});
		if (it != _orderedPromises.end()) {
			FetchDependencies(*it, keys);
		}
	}
	keys.insert(promise.Key);
}

void TargetObjectStack::ResolveFinalTargets() {

}

void TargetObjectStack::ResolveFinalTasks() {

}

