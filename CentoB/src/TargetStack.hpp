#pragma once
#include "Targets/ITarget.hpp"
#include "ManifestObjects.hpp"
#include <map>
#include <set>

class TargetStack {
public:
	TargetStack(const ManifestObjects::ManifestRoot& root) : _manifestRoot{ root } {}

	void BuildTargetsAndTasks();

	void DumpTargets() const;
	void DumpTasks() const;

	bool ExecuteAllTasks() const;
private:
	struct TargetPromise;

	bool ResolveStartupTarget();
	bool ResolveStartupTarget(const ManifestObjects::ManifestWorkspace& workspace);
	bool ResolveStartupTarget(const ManifestObjects::ManifestProject& project, const std::string& workspaceName);

	void ResolveTargets();
	void ResolveTargets(const ManifestObjects::ManifestWorkspace& workspace);
	void ResolveTargets(const ManifestObjects::ManifestProject& project, const std::string& workspaceName);

	void ResolveExternalDependencies();
	void ResolveExternalDependencies(const ManifestObjects::ManifestWorkspace& workspace);
	void ResolveExternalDependencies(const ManifestObjects::ManifestProject& project, const std::string& workspaceName);

	void ResolveAutomation();
	void ResolveAutomation(const ManifestObjects::ManifestWorkspace& workspace);

	std::string ResolveFullName(const std::string& partialName);

	void ResolvePromises();
	void OrderPromises();
	void OptimizePromises();
	void FetchDependencyKeys(const TargetPromise& promise, std::set<std::string>& keys);

	void ResolveFinalTargets();
	void ResolveFinalTasks();

	enum class ETargetType {
		TARGET = 0,
		EXTERNAL_DEPENDENCY,
		AUTOMATION
	};

	struct TargetPromise {
		ETargetType Type;
		std::string Key;
		std::vector<std::string> DependsOn;
	};

	const ManifestObjects::ManifestRoot& _manifestRoot;

	std::map<std::string, const ManifestObjects::ManifestTarget*> _manifestTargets; // list of targets fetched from root, key: workspace:project:target
	std::map<std::string, const ManifestObjects::ManifestExternalDependency*> _manifestExternalDependencies; // list of external dependencies fetched from root, key: workspace:project:name
	std::map<std::string, const ManifestObjects::ManifestAutomation*> _manifestAutomation; // list of automations fetched from root, key: workspace

	std::string _startupTarget; // key of startup target

	std::vector<TargetPromise> _unorderedPromises; // list of targets, external dependencies and automations converted to promises directly
	std::vector<TargetPromise> _orderedPromises; // list of promises ordered in the way they should be resolved
	std::vector<TargetPromise> _optimizedPromises; // list of only necessary promises

	std::vector<std::unique_ptr<ITarget>> _targets; // list of targets converted from promises
	std::vector<std::unique_ptr<ITask>> _tasks; // list of tasks fetched from targets
};
