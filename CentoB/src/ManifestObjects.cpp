#include "ManifestObjects.hpp"
#include <set>
#include <iostream>

#define GUARD_OPTIONALS						\
if (!lhs.has_value() && !rhs.has_value()) {	\
	return std::nullopt;					\
}											\
if (lhs.has_value() && !rhs.has_value()) {	\
	return lhs;								\
}											\
if (!lhs.has_value() && rhs.has_value()) {	\
	return rhs;								\
}

static std::set<std::string> _cento_vars = {
	"CENTO_CURRENT_DIR",
	"CENTO_PROFILE_DIR",
	"CENTO_EXTERNAL_DEPENDENCY_DIR",
	"CENTO_BRIDGE_DIR",
	"CENTO_TARGET_DIR",
	"CENTO_PROJECT_DIR",
	"CENTO_CURRENT_DIR",
	"CENTO_AUTOMATION_DIR",
	"CENTO_WORKSPACE_DIR",
	"CENTO_ROOT_DIR",
	"CENTO_CURRENT_PROFILE",
	"CENTO_CURRENT_WORKSPACE",
	"CENTO_CURRENT_PROJECT",
	"CENTO_CURRENT_TARGET",
};

OptMapStrStr MergeManifest(const OptMapStrStr& lhs, const OptMapStrStr& rhs)
{
	GUARD_OPTIONALS

	std::map<std::string, std::string> out = *lhs;
	for (const auto& [key, value] : *rhs) {
		if (_cento_vars.find(key) == _cento_vars.end() || !value.empty()) {
			out[key] = value;
		}
	}

	return out;
}

OptStr MergeManifest(const OptStr& lhs, const OptStr& rhs)
{
	GUARD_OPTIONALS

	return rhs;
}

OptVecStr MergeManifest(const OptVecStr& lhs, const OptVecStr& rhs)
{
	GUARD_OPTIONALS

	std::vector<std::string> out = *lhs;
	out.insert(out.end(), rhs->begin(), rhs->end());

	return out;
}

OptManifestBridges MergeManifest(const OptManifestBridges& lhs, const OptManifestBridges& rhs) {
	GUARD_OPTIONALS

		ManifestBridges out;
	out.vars = MergeManifest(lhs->vars, rhs->vars);
	out.path = MergeManifest(lhs->path, rhs->path);
	out.envFiles = MergeManifest(lhs->envFiles, rhs->envFiles);
	out.uses = MergeManifest(lhs->uses, rhs->uses);
	out.implements = MergeManifest(lhs->implements, rhs->implements);

	return out;
}

OptVecManifestTargetProfile MergeManifest(const OptVecManifestTargetProfile& lhs, const OptVecManifestTargetProfile& rhs)
{
	GUARD_OPTIONALS

		std::map<std::string, ManifestTargetProfile> profileMap;
	for (auto& plhs : *lhs) {
		profileMap[plhs.name.has_value() ? *plhs.name : ""] = plhs;
	}

	for (const auto& prhs : *rhs) {
		auto name = prhs.name.has_value() ? *prhs.name : "";
		auto it = profileMap.find(name);
		if (it != profileMap.end()) {
			auto& plhs = it->second;

			plhs.vars = MergeManifest(plhs.vars, prhs.vars);
			plhs.path = MergeManifest(plhs.path, prhs.path);
			plhs.envFiles = MergeManifest(plhs.envFiles, prhs.envFiles);
			plhs.name = MergeManifest(plhs.name, prhs.name);
			plhs.sources = MergeManifest(plhs.sources, prhs.sources);
			plhs.includeDirs = MergeManifest(plhs.includeDirs, prhs.includeDirs);
			plhs.compilerOptions = MergeManifest(plhs.compilerOptions, prhs.compilerOptions);
			plhs.intDir = MergeManifest(plhs.intDir, prhs.intDir);
			plhs.outDir = MergeManifest(plhs.outDir, prhs.outDir);
			plhs.bridges = MergeManifest(plhs.bridges, prhs.bridges);
		}
		else {
			profileMap[name] = prhs;
		}
	}

	std::vector<ManifestTargetProfile> out;
	for (const auto& [key, value] : profileMap) {
		out.emplace_back(value);
	}

	return out;
}

OptVecManifestProfile MergeManifest(const OptVecManifestProfile& lhs, const OptVecManifestProfile& rhs)
{
	GUARD_OPTIONALS

		std::map<std::string, ManifestProfile> profileMap;
	for (auto& plhs : *lhs) {
		profileMap[plhs.name.has_value() ? *plhs.name : ""] = plhs;
	}

	for (const auto& prhs : *rhs) {
		auto name = prhs.name.has_value() ? *prhs.name : "";
		auto it = profileMap.find(name);
		if (it != profileMap.end()) {
			auto& plhs = it->second;

			plhs.vars = MergeManifest(plhs.vars, prhs.vars);
			plhs.path = MergeManifest(plhs.path, prhs.path);
			plhs.envFiles = MergeManifest(plhs.envFiles, prhs.envFiles);
			plhs.name = MergeManifest(plhs.name, prhs.name);
		}
		else {
			profileMap[name] = prhs;
		}
	}

	std::vector<ManifestProfile> out;
	for (const auto& [key, value] : profileMap) {
		out.emplace_back(value);
	}

	return out;
}

OptVecManifestExternalDependencies MergeManifest(const OptVecManifestExternalDependencies& lhs, const OptVecManifestExternalDependencies& rhs)
{
	GUARD_OPTIONALS

	std::map<std::string, ManifestExternalDependencies> externalDependenciesMap;
	for (auto& plhs : *lhs) {
		externalDependenciesMap[plhs.name.has_value() ? *plhs.name : ""] = plhs;
	}

	for (const auto& prhs : *rhs) {
		auto name = prhs.name.has_value() ? *prhs.name : "";
		auto it = externalDependenciesMap.find(name);
		if (it != externalDependenciesMap.end()) {
			auto& plhs = it->second;

			plhs.vars = MergeManifest(plhs.vars, prhs.vars);
			plhs.path = MergeManifest(plhs.path, prhs.path);
			plhs.envFiles = MergeManifest(plhs.envFiles, prhs.envFiles);
			plhs.toolchain = MergeManifest(plhs.toolchain, prhs.toolchain);
			plhs.name = MergeManifest(plhs.name, prhs.name);
			plhs.version = MergeManifest(plhs.version, prhs.version);
			plhs.url = MergeManifest(plhs.url, prhs.url);
			plhs.branch = MergeManifest(plhs.branch, prhs.branch);
			plhs.resolveFirst = MergeManifest(plhs.resolveFirst, prhs.resolveFirst);
			plhs.buildsystem = MergeManifest(plhs.buildsystem, prhs.buildsystem);
			plhs.buildArgs = MergeManifest(plhs.buildArgs, prhs.buildArgs);
		}
		else {
			externalDependenciesMap[name] = prhs;
		}
	}

	std::vector<ManifestExternalDependencies> out;
	for (const auto& [key, value] : externalDependenciesMap) {
		out.emplace_back(value);
	}

	return out;
}

OptVecManifestTarget MergeManifest(const OptVecManifestTarget& lhs, const OptVecManifestTarget& rhs)
{
	GUARD_OPTIONALS

	std::map<std::string, ManifestTarget> targetMap;
	for (auto& plhs : *lhs) {
		targetMap[plhs.name.has_value() ? *plhs.name : ""] = plhs;
	}

	for (const auto& prhs : *rhs) {
		auto name = prhs.name.has_value() ? *prhs.name : "";
		auto it = targetMap.find(name);
		if (it != targetMap.end()) {
			auto& plhs = it->second;

			plhs.vars = MergeManifest(plhs.vars, prhs.vars);
			plhs.path = MergeManifest(plhs.path, prhs.path);
			plhs.envFiles = MergeManifest(plhs.envFiles, prhs.envFiles);
			plhs.name = MergeManifest(plhs.name, prhs.name);
			plhs.profiles = MergeManifest(plhs.profiles, prhs.profiles);
			plhs.type = MergeManifest(plhs.type, prhs.type);
			plhs.language = MergeManifest(plhs.language, prhs.language);
			plhs.toolchain = MergeManifest(plhs.toolchain, prhs.toolchain);
			plhs.link = MergeManifest(plhs.link, prhs.link);
			plhs.sources = MergeManifest(plhs.sources, prhs.sources);
			plhs.includeDirs = MergeManifest(plhs.includeDirs, prhs.includeDirs);
			plhs.compilerOptions = MergeManifest(plhs.compilerOptions, prhs.compilerOptions);
			plhs.intDir = MergeManifest(plhs.intDir, prhs.intDir);
			plhs.outDir = MergeManifest(plhs.outDir, prhs.outDir);
			plhs.bridges = MergeManifest(plhs.bridges, prhs.bridges);
		}
		else {
			targetMap[name] = prhs;
		}
	}

	std::vector<ManifestTarget> out;
	for (const auto& [key, value] : targetMap) {
		out.emplace_back(value);
	}

	return out;
}

OptVecManifestProject MergeManifest(const OptVecManifestProject& lhs, const OptVecManifestProject& rhs)
{
	GUARD_OPTIONALS

	std::map<std::string, ManifestProject> projectMap;
	for (auto& plhs : *lhs) {
		projectMap[plhs.name.has_value() ? *plhs.name : ""] = plhs;
	}

	for (const auto& prhs : *rhs) {
		auto name = prhs.name.has_value() ? *prhs.name : "";
		auto it = projectMap.find(name);
		if (it != projectMap.end()) {
			auto& plhs = it->second;

			plhs.vars = MergeManifest(plhs.vars, prhs.vars);
			plhs.path = MergeManifest(plhs.path, prhs.path);
			plhs.envFiles = MergeManifest(plhs.envFiles, prhs.envFiles);
			plhs.name = MergeManifest(plhs.name, prhs.name);
			plhs.profiles = MergeManifest(plhs.profiles, prhs.profiles);
			plhs.externalDependencies = MergeManifest(plhs.externalDependencies, prhs.externalDependencies);
			plhs.startupTarget = MergeManifest(plhs.startupTarget, prhs.startupTarget);
			plhs.targets = MergeManifest(plhs.targets, prhs.targets);
		}
		else {
			projectMap[name] = prhs;
		}
	}

	std::vector<ManifestProject> out;
	for (const auto& [key, value] : projectMap) {
		out.emplace_back(value);
	}

	return out;
}

OptManifestAutomation MergeManifest(const OptManifestAutomation& lhs, const OptManifestAutomation& rhs) {
	GUARD_OPTIONALS

	ManifestAutomation out;
	out.vars = MergeManifest(lhs->vars, rhs->vars);
	out.path = MergeManifest(lhs->path, rhs->path);
	out.envFiles = MergeManifest(lhs->envFiles, rhs->envFiles);
	out.script = MergeManifest(lhs->script, rhs->script);
	out.hooks = MergeManifest(lhs->hooks, rhs->hooks);
	out.actions = MergeManifest(lhs->actions, rhs->actions);

	return out;
}

OptVecManifestWorkspace MergeManifest(const OptVecManifestWorkspace& lhs, const OptVecManifestWorkspace& rhs) {
	GUARD_OPTIONALS

	std::map<std::string, ManifestWorkspace> workspaceMap;
	for (auto& plhs : *lhs) {
		workspaceMap[plhs.name.has_value() ? *plhs.name : ""] = plhs;
	}

	for (const auto& prhs : *rhs) {
		auto name = prhs.name.has_value() ? *prhs.name : "";
		auto it = workspaceMap.find(name);
		if (it != workspaceMap.end()) {
			auto& plhs = it->second;
			plhs.vars = MergeManifest(plhs.vars, prhs.vars);
			plhs.path = MergeManifest(plhs.path, prhs.path);
			plhs.envFiles = MergeManifest(plhs.envFiles, prhs.envFiles);
			plhs.profiles = MergeManifest(plhs.profiles, prhs.profiles);
			plhs.defaultProfile = MergeManifest(plhs.defaultProfile, prhs.defaultProfile);
			plhs.startupProject = MergeManifest(plhs.startupProject, prhs.startupProject);
			plhs.projects = MergeManifest(plhs.projects, prhs.projects);
			plhs.automation = MergeManifest(plhs.automation, prhs.automation);
		}
		else {
			workspaceMap[name] = prhs;
		}
	}

	std::vector<ManifestWorkspace> out;
	for (const auto& [key, value] : workspaceMap) {
		out.emplace_back(value);
	}

	return out;
}

ManifestRoot MergeManifest(const ManifestRoot& lhs, const ManifestRoot& rhs)
{
	ManifestRoot out;
	out.vars = MergeManifest(lhs.vars, rhs.vars);
	out.path = MergeManifest(lhs.path, rhs.path);
	out.envFiles = MergeManifest(lhs.envFiles, rhs.envFiles);
	out.profiles = MergeManifest(lhs.profiles, rhs.profiles);
	out.includes = MergeManifest(lhs.includes, rhs.includes);
	out.workspaces = MergeManifest(lhs.workspaces, rhs.workspaces);
	out.defaultProfile = MergeManifest(lhs.defaultProfile, rhs.defaultProfile);
	out.startupWorkspace = MergeManifest(lhs.startupWorkspace, rhs.startupWorkspace);

	return out;
}

void VerifyIfOverridesCentoVars(const std::map<std::string, std::string>& vars, std::optional<std::string>& violatedVar) {
	for (const auto& [key, _] : vars) {
		if (_cento_vars.find(key) != _cento_vars.end()) {
			violatedVar = key;
			return;
		}
	}

	violatedVar = std::nullopt;
}

void ParseEnvFiles(const std::vector<std::string>& envFiles, const std::string& path, std::map<std::string, std::string>& vars) {
	for (const auto& envFileGlob : envFiles) {
		std::vector<std::filesystem::path> paths;
		Utils::ExpandGlob(envFileGlob, path, paths);
		for (const auto& envPathLocal : paths) {
			auto envPath = std::filesystem::path(path) / envPathLocal;
			if (Utils::Match(envPath.generic_string(), "*.env")) {
				auto envFile = Utils::ParseEnvFile(envPath);
				for (const auto& [key, val] : envFile) {
					vars[key] = val;
				}
			}
		}

		for (const auto& envPathLocal : paths) {
			auto envPath = std::filesystem::path(path) / envPathLocal;
			if (Utils::Match(envPath.generic_string(), "*.env.local")) {
				auto envFile = Utils::ParseEnvFile(envPath);
				for (const auto& [key, val] : envFile) {
					vars[key] = val;
				}
			}
		}
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptVecManifestTargetProfile& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	for (auto& profile : *toCheck) {
		if (!profile.name.has_value() || profile.name->empty()) {
			throw std::runtime_error("Profile name cannot be empty");
		}

		std::filesystem::path base = currPath;
		if (profile.path.has_value()) {
			std::filesystem::path path = *profile.path;
			if (!Utils::IsWeaklyCanonical(path)) {
				profile.path = (base / path).string();
			}
		}
		else {
			profile.path = base.string();
		}

		std::map<std::string, std::string> vars;
		if (profile.vars.has_value()) {
			vars = *profile.vars;
		}

		if (profile.envFiles.has_value()) {
			ParseEnvFiles(*profile.envFiles, *profile.path, vars);
			profile.envFiles = std::nullopt;
		}
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptVecManifestProfile& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	for (auto& profile : *toCheck) {
		if (!profile.name.has_value() || profile.name->empty()) {
			throw std::runtime_error("Profile name cannot be empty");
		}

		std::filesystem::path base = currPath;
		if (profile.path.has_value()) {
			std::filesystem::path path = *profile.path;
			if (!Utils::IsWeaklyCanonical(path)) {
				profile.path = (base / path).string();
			}
		}
		else {
			profile.path = base.string();
		}

		std::map<std::string, std::string> vars;
		if (profile.vars.has_value()) {
			vars = *profile.vars;
		}

		if (profile.envFiles.has_value()) {
			ParseEnvFiles(*profile.envFiles, *profile.path, vars);
			profile.envFiles = std::nullopt;
		}
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptVecManifestExternalDependencies& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	for (auto& externalDependency : *toCheck) {
		if (!externalDependency.name.has_value() || externalDependency.name->empty()) {
			throw std::runtime_error("Target name cannot be empty");
		}

		std::filesystem::path base = currPath;
		if (externalDependency.path.has_value()) {
			std::filesystem::path path = *externalDependency.path;
			if (!Utils::IsWeaklyCanonical(path)) {
				externalDependency.path = (base / path).string();
			}
		}
		else {
			externalDependency.path = base.string();
		}

		std::map<std::string, std::string> vars;
		if (externalDependency.vars.has_value()) {
			vars = *externalDependency.vars;
		}

		if (externalDependency.envFiles.has_value()) {
			ParseEnvFiles(*externalDependency.envFiles, *externalDependency.path, vars);
			externalDependency.envFiles = std::nullopt;
		}
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptManifestBridges& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	auto& bridge = *toCheck;

	std::filesystem::path base = currPath;
	if (bridge.path.has_value()) {
		std::filesystem::path path = *bridge.path;
		if (!Utils::IsWeaklyCanonical(path)) {
			bridge.path = (base / path).string();
		}
	}
	else {
		bridge.path = base.string();
	}

	std::map<std::string, std::string> vars;
	if (bridge.vars.has_value()) {
		vars = *bridge.vars;
	}

	if (bridge.envFiles.has_value()) {
		ParseEnvFiles(*bridge.envFiles, *bridge.path, vars);
		bridge.envFiles = std::nullopt;
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptVecManifestTarget& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	for (auto& target : *toCheck) {
		if (!target.name.has_value() || target.name->empty()) {
			throw std::runtime_error("Target name cannot be empty");
		}

		std::filesystem::path base = currPath;
		if (target.path.has_value()) {
			std::filesystem::path path = *target.path;
			if (!Utils::IsWeaklyCanonical(path)) {
				target.path = (base / path).string();
			}
		}
		else {
			target.path = base.string();
		}

		std::map<std::string, std::string> vars;
		if (target.vars.has_value()) {
			vars = *target.vars;
		}

		if (target.envFiles.has_value()) {
			ParseEnvFiles(*target.envFiles, *target.path, vars);
			target.envFiles = std::nullopt;
		}

		CheckAndPostprocessManifest(*target.path, target.profiles);
		CheckAndPostprocessManifest(*target.path, target.bridges);
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptVecManifestProject& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	for (auto& project : *toCheck) {
		if (!project.name.has_value() || project.name->empty()) {
			throw std::runtime_error("Project name cannot be empty");
		}

		std::filesystem::path base = currPath;
		if (project.path.has_value()) {
			std::filesystem::path path = *project.path;
			if (!Utils::IsWeaklyCanonical(path)) {
				project.path = (base / path).string();
			}
		}
		else {
			project.path = base.string();
		}

		std::map<std::string, std::string> vars;
		if (project.vars.has_value()) {
			vars = *project.vars;
		}

		if (project.envFiles.has_value()) {
			ParseEnvFiles(*project.envFiles, *project.path, vars);
			project.envFiles = std::nullopt;
		}

		CheckAndPostprocessManifest(*project.path, project.targets);
		CheckAndPostprocessManifest(*project.path, project.profiles);
		CheckAndPostprocessManifest(*project.path, project.externalDependencies);
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptManifestAutomation& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	auto& automation = *toCheck;

	std::filesystem::path base = currPath;
	if (automation.path.has_value()) {
		std::filesystem::path path = *automation.path;
		if (!Utils::IsWeaklyCanonical(path)) {
			automation.path = (base / path).string();
		}
	}
	else {
		automation.path = base.string();
	}

	std::map<std::string, std::string> vars;
	if (automation.vars.has_value()) {
		vars = *automation.vars;
	}

	if (automation.envFiles.has_value()) {
		ParseEnvFiles(*automation.envFiles, *automation.path, vars);
		automation.envFiles = std::nullopt;
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, OptVecManifestWorkspace& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	for (auto& workspace : *toCheck) {
		if (!workspace.name.has_value() || workspace.name->empty()) {
			throw std::runtime_error("Project name cannot be empty");
		}

		std::filesystem::path base = currPath;
		if (workspace.path.has_value()) {
			std::filesystem::path path = *workspace.path;
			if (!Utils::IsWeaklyCanonical(path)) {
				workspace.path = (base / path).string();
			}
		}
		else {
			workspace.path = base.string();
		}

		std::map<std::string, std::string> vars;
		if (workspace.vars.has_value()) {
			vars = *workspace.vars;
		}

		if (workspace.envFiles.has_value()) {
			ParseEnvFiles(*workspace.envFiles, *workspace.path, vars);
			workspace.envFiles = std::nullopt;
		}

		CheckAndPostprocessManifest(*workspace.path, workspace.projects);
		CheckAndPostprocessManifest(*workspace.path, workspace.profiles);
		CheckAndPostprocessManifest(*workspace.path, workspace.automation);
	}
}

void CheckAndPostprocessManifest(const std::string& currPath, ManifestRoot& toCheck) {
	auto& root = toCheck;

	std::filesystem::path base = currPath;
	if (root.path.has_value()) {
		std::filesystem::path path = *root.path;
		if (!Utils::IsWeaklyCanonical(path)) {
			root.path = (base / path).string();
		}
	}
	else {
		root.path = base.string();
	}

	std::map<std::string, std::string> vars;
	if (root.vars.has_value()) {
		vars = *root.vars;
	}

	if (root.envFiles.has_value()) {
		ParseEnvFiles(*root.envFiles, *root.path, vars);
		root.envFiles = std::nullopt;
	}

	CheckAndPostprocessManifest(*root.path, root.workspaces);
	CheckAndPostprocessManifest(*root.path, root.profiles);

	root.vars = vars;
}

void EvaluateCentoVars(OptVecManifestTargetProfile& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	for (auto& profile : *toEvaluate) {
		std::map<std::string, std::string> vars;
		if (profile.vars.has_value()) {
			vars = *profile.vars;
		}

		std::optional<std::string> violatedVar = std::nullopt;
		VerifyIfOverridesCentoVars(vars, violatedVar);
		if (violatedVar.has_value()) {
			throw std::runtime_error("Violated Cento variable: " + *violatedVar);
		}

		vars["CENTO_CURRENT_DIR"] = *profile.path;
		vars["CENTO_PROFILE_DIR"] = *profile.path;
		profile.vars = vars;
	}
}

void EvaluateCentoVars(OptVecManifestProfile& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	for (auto& profile : *toEvaluate) {
		std::map<std::string, std::string> vars;
		if (profile.vars.has_value()) {
			vars = *profile.vars;
		}

		std::optional<std::string> violatedVar = std::nullopt;
		VerifyIfOverridesCentoVars(vars, violatedVar);
		if (violatedVar.has_value()) {
			throw std::runtime_error("Violated Cento variable: " + *violatedVar);
		}

		vars["CENTO_CURRENT_DIR"] = *profile.path;
		vars["CENTO_PROFILE_DIR"] = *profile.path;
		profile.vars = vars;
	}
}

void EvaluateCentoVars(OptVecManifestExternalDependencies& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	for (auto& externalDependency : *toEvaluate) {
		std::map<std::string, std::string> vars;
		if (externalDependency.vars.has_value()) {
			vars = *externalDependency.vars;
		}

		std::optional<std::string> violatedVar = std::nullopt;
		VerifyIfOverridesCentoVars(vars, violatedVar);
		if (violatedVar.has_value()) {
			throw std::runtime_error("Violated Cento variable: " + *violatedVar);
		}

		vars["CENTO_CURRENT_DIR"] = *externalDependency.path;
		vars["CENTO_EXTERNAL_DEPENDENCY_DIR"] = *externalDependency.path;
		externalDependency.vars = vars;
	}
}

void EvaluateCentoVars(OptManifestBridges& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	auto& bridge = *toEvaluate;

	std::map<std::string, std::string> vars;
	if (bridge.vars.has_value()) {
		vars = *bridge.vars;
	}

	std::optional<std::string> violatedVar = std::nullopt;
	VerifyIfOverridesCentoVars(vars, violatedVar);
	if (violatedVar.has_value()) {
		throw std::runtime_error("Violated Cento variable: " + *violatedVar);
	}

	vars["CENTO_CURRENT_DIR"] = *bridge.path;
	vars["CENTO_BRIDGE_DIR"] = *bridge.path;
	bridge.vars = vars;
}

void EvaluateCentoVars(OptVecManifestTarget& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	for (auto& target : *toEvaluate) {
		std::map<std::string, std::string> vars;
		if (target.vars.has_value()) {
			vars = *target.vars;
		}

		std::optional<std::string> violatedVar = std::nullopt;
		VerifyIfOverridesCentoVars(vars, violatedVar);
		if (violatedVar.has_value()) {
			throw std::runtime_error("Violated Cento variable: " + *violatedVar);
		}

		vars["CENTO_CURRENT_DIR"] = *target.path;
		vars["CENTO_TARGET_DIR"] = *target.path;
		vars["CENTO_CURRENT_PROFILE"] = target.defaultProfile.has_value() ? *target.defaultProfile : "";
		target.vars = vars;

		EvaluateCentoVars(target.profiles);
		EvaluateCentoVars(target.bridges);
	}
}

void EvaluateCentoVars(OptVecManifestProject& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	for (auto& project : *toEvaluate) {
		std::map<std::string, std::string> vars;
		if (project.vars.has_value()) {
			vars = *project.vars;
		}

		std::optional<std::string> violatedVar = std::nullopt;
		VerifyIfOverridesCentoVars(vars, violatedVar);
		if (violatedVar.has_value()) {
			throw std::runtime_error("Violated Cento variable: " + *violatedVar);
		}

		vars["CENTO_CURRENT_DIR"] = *project.path;
		vars["CENTO_PROJECT_DIR"] = *project.path;
		vars["CENTO_CURRENT_PROFILE"] = project.defaultProfile.has_value() ? *project.defaultProfile : "";
		vars["CENTO_CURRENT_TARGET"] = project.startupTarget.has_value() ? *project.startupTarget : "";
		project.vars = vars;

		EvaluateCentoVars(project.profiles);
		EvaluateCentoVars(project.targets);
		EvaluateCentoVars(project.externalDependencies);
	}
}

void EvaluateCentoVars(OptManifestAutomation& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	auto& automation = *toEvaluate;

	std::map<std::string, std::string> vars;
	if (automation.vars.has_value()) {
		vars = *automation.vars;
	}

	std::optional<std::string> violatedVar = std::nullopt;
	VerifyIfOverridesCentoVars(vars, violatedVar);
	if (violatedVar.has_value()) {
		throw std::runtime_error("Violated Cento variable: " + *violatedVar);
	}

	vars["CENTO_CURRENT_DIR"] = *automation.path;
	vars["CENTO_AUTOMATION_DIR"] = *automation.path;
	automation.vars = vars;
}

void EvaluateCentoVars(OptVecManifestWorkspace& toEvaluate) {
	if (!toEvaluate.has_value()) {
		return;
	}

	for (auto& workspace : *toEvaluate) {
		std::map<std::string, std::string> vars;
		if (workspace.vars.has_value()) {
			vars = *workspace.vars;
		}

		std::optional<std::string> violatedVar = std::nullopt;
		VerifyIfOverridesCentoVars(vars, violatedVar);
		if (violatedVar.has_value()) {
			throw std::runtime_error("Violated Cento variable: " + *violatedVar);
		}

		vars["CENTO_CURRENT_DIR"] = *workspace.path;
		vars["CENTO_WORKSPACE_DIR"] = *workspace.path;
		vars["CENTO_CURRENT_PROFILE"] = workspace.defaultProfile.has_value() ? *workspace.defaultProfile : "";
		vars["CENTO_CURRENT_PROJECT"] = workspace.startupProject.has_value() ? *workspace.startupProject : "";
		workspace.vars = vars;

		EvaluateCentoVars(workspace.profiles);
		EvaluateCentoVars(workspace.projects);
		EvaluateCentoVars(workspace.automation);
	}
}

void EvaluateCentoVars(ManifestRoot& toEvaluate) {
	auto& root = toEvaluate;

	std::map<std::string, std::string> vars;
	if (root.vars.has_value()) {
		vars = *root.vars;
	}

	std::optional<std::string> violatedVar = std::nullopt;
	VerifyIfOverridesCentoVars(vars, violatedVar);
	if (violatedVar.has_value()) {
		throw std::runtime_error("Violated Cento variable: " + *violatedVar);
	}

	vars["CENTO_CURRENT_DIR"] = *root.path;
	vars["CENTO_ROOT_DIR"] = *root.path;
	vars["CENTO_CURRENT_PROFILE"] = root.defaultProfile.has_value() ? *root.defaultProfile : "";
	vars["CENTO_CURRENT_WORKSPACE"] = root.startupWorkspace.has_value() ? *root.startupWorkspace : "";

	root.vars = vars;

	EvaluateCentoVars(root.profiles);
	EvaluateCentoVars(root.workspaces);
}

OptMapStrStr ManifestExpandVars(const OptMapStrStr vars, const OptMapStrStr& toExpand)
{
	if (!vars.has_value() || !toExpand.has_value()) {
		return toExpand;
	}

	std::map<std::string, std::string> out = *toExpand;
	for (const auto& [key, value] : out) {
		out[key] = Utils::ExpandVars(value, *vars);
	}

	return out;
}

OptStr ManifestExpandVars(const OptMapStrStr& vars, const OptStr& toExpand)
{
	if (!vars.has_value() || !toExpand.has_value()) {
		return toExpand;
	}

	return Utils::ExpandVars(*toExpand, *vars);
}

OptVecStr ManifestExpandVars(const OptMapStrStr& vars, const OptVecStr& toExpand)
{
	if (!vars.has_value() || !toExpand.has_value()) {
		return toExpand;
	}

	std::vector<std::string> out = *toExpand;
	for (auto& value : out) {
		value = Utils::ExpandVars(value, *vars);
	}

	return out;
}

void ManifestExpandVars(OptManifestBridges& toExpand) {
	if (!toExpand.has_value()) {
		return;
	}

	toExpand->vars = ManifestExpandVars(toExpand->vars, toExpand->vars);
	toExpand->path = ManifestExpandVars(toExpand->vars, toExpand->path);
	toExpand->uses = ManifestExpandVars(toExpand->vars, toExpand->uses);
	toExpand->implements = ManifestExpandVars(toExpand->vars, toExpand->implements);

	toExpand->vars = std::nullopt;
}

void ManifestExpandVars(OptVecManifestTargetProfile& toExpand)
{
	if (!toExpand.has_value()) {
		return;
	}

	for (auto& profile : *toExpand) {
		profile.vars = ManifestExpandVars(profile.vars, profile.vars);
		profile.path = ManifestExpandVars(profile.vars, profile.path);
		profile.name = ManifestExpandVars(profile.vars, profile.name);
		profile.sources = ManifestExpandVars(profile.vars, profile.sources);
		profile.includeDirs = ManifestExpandVars(profile.vars, profile.includeDirs);
		profile.compilerOptions = ManifestExpandVars(profile.vars, profile.compilerOptions);
		profile.intDir = ManifestExpandVars(profile.vars, profile.intDir);
		profile.outDir = ManifestExpandVars(profile.vars, profile.outDir);
		ManifestExpandVars(profile.bridges);

		profile.vars = std::nullopt;
	}
}

void ManifestExpandVars(OptVecManifestProfile& toExpand)
{
	if (!toExpand.has_value()) {
		return;
	}

	for (auto& profile : *toExpand) {
		profile.vars = ManifestExpandVars(profile.vars, profile.vars);
		profile.path = ManifestExpandVars(profile.vars, profile.path);
		profile.name = ManifestExpandVars(profile.vars, profile.name);

		profile.vars = std::nullopt;
	}
}

void ManifestExpandVars(OptVecManifestExternalDependencies& toExpand)
{
	if (!toExpand.has_value()) {
		return;
	}

	for (auto& externalDependency : *toExpand) {
		externalDependency.vars = ManifestExpandVars(externalDependency.vars, externalDependency.vars);
		externalDependency.path = ManifestExpandVars(externalDependency.vars, externalDependency.path);
		externalDependency.toolchain = ManifestExpandVars(externalDependency.vars, externalDependency.toolchain);
		externalDependency.name = ManifestExpandVars(externalDependency.vars, externalDependency.name);
		externalDependency.version = ManifestExpandVars(externalDependency.vars, externalDependency.version);
		externalDependency.url = ManifestExpandVars(externalDependency.vars, externalDependency.url);
		externalDependency.branch = ManifestExpandVars(externalDependency.vars, externalDependency.branch);
		externalDependency.resolveFirst = ManifestExpandVars(externalDependency.vars, externalDependency.resolveFirst);
		externalDependency.buildsystem = ManifestExpandVars(externalDependency.vars, externalDependency.buildsystem);
		externalDependency.buildArgs = ManifestExpandVars(externalDependency.vars, externalDependency.buildArgs);

		externalDependency.vars = std::nullopt;
	}
}

void ManifestExpandVars(OptVecManifestTarget& toExpand)
{
	if (!toExpand.has_value()) {
		return;
	}

	for (auto& target : *toExpand) {
		target.vars = ManifestExpandVars(target.vars, target.vars);
		target.path = ManifestExpandVars(target.vars, target.path);
		target.name = ManifestExpandVars(target.vars, target.name);
		ManifestExpandVars(target.profiles);
		target.type = ManifestExpandVars(target.vars, target.type);
		target.language = ManifestExpandVars(target.vars, target.language);
		target.toolchain = ManifestExpandVars(target.vars, target.toolchain);
		target.link = ManifestExpandVars(target.vars, target.link);
		target.sources = ManifestExpandVars(target.vars, target.sources);
		target.includeDirs = ManifestExpandVars(target.vars, target.includeDirs);
		target.compilerOptions = ManifestExpandVars(target.vars, target.compilerOptions);
		target.intDir = ManifestExpandVars(target.vars, target.intDir);
		target.outDir = ManifestExpandVars(target.vars, target.outDir);
		ManifestExpandVars(target.bridges);

		target.vars = std::nullopt;
	}
}

void ManifestExpandVars(OptVecManifestProject& toExpand)
{
	if (!toExpand.has_value()) {
		return;
	}

	for (auto& project : *toExpand) {
		project.vars = ManifestExpandVars(project.vars, project.vars);
		project.path = ManifestExpandVars(project.vars, project.path);
		project.name = ManifestExpandVars(project.vars, project.name);
		ManifestExpandVars(project.profiles);
		ManifestExpandVars(project.externalDependencies);
		project.startupTarget = ManifestExpandVars(project.vars, project.startupTarget);
		ManifestExpandVars(project.targets);

		project.vars = std::nullopt;
	}
}

void ManifestExpandVars(OptManifestAutomation& toExpand) {
	if (!toExpand.has_value()) {
		return;
	}

	toExpand->vars = ManifestExpandVars(toExpand->vars, toExpand->vars);
	toExpand->path = ManifestExpandVars(toExpand->vars, toExpand->path);
	toExpand->script = ManifestExpandVars(toExpand->vars, toExpand->script);
	toExpand->hooks = ManifestExpandVars(toExpand->vars, toExpand->hooks);
	toExpand->actions = ManifestExpandVars(toExpand->vars, toExpand->actions);

	toExpand->vars = std::nullopt;
}

void ManifestExpandVars(OptVecManifestWorkspace& toExpand) {
	if (!toExpand.has_value()) {
		return;
	}

	for (auto& workspace : *toExpand) {
		workspace.vars = ManifestExpandVars(workspace.vars, workspace.vars);
		workspace.path = ManifestExpandVars(workspace.vars, workspace.path);
		ManifestExpandVars(workspace.profiles);
		workspace.defaultProfile = ManifestExpandVars(workspace.vars, workspace.defaultProfile);
		workspace.startupProject = ManifestExpandVars(workspace.vars, workspace.startupProject);
		ManifestExpandVars(workspace.projects);
		ManifestExpandVars(workspace.automation);

		workspace.vars = std::nullopt;
	}
}

void ManifestExpandVars(ManifestRoot& toExpand) {
	toExpand.vars = ManifestExpandVars(toExpand.vars, toExpand.vars);
	toExpand.path = ManifestExpandVars(toExpand.vars, toExpand.path);
	ManifestExpandVars(toExpand.profiles);
	toExpand.includes = ManifestExpandVars(toExpand.vars, toExpand.includes);
	ManifestExpandVars(toExpand.workspaces);
	toExpand.startupWorkspace = ManifestExpandVars(toExpand.vars, toExpand.startupWorkspace);

	toExpand.vars = std::nullopt;
}

void CollapseProfiles(ManifestTarget& toCollapse) {
	if (toCollapse.profiles.has_value() && toCollapse.defaultProfile.has_value()) {
		auto defaultProfile = ManifestExpandVars(toCollapse.vars, toCollapse.defaultProfile);
		for (const auto& profile : *toCollapse.profiles) {
			if (*profile.name == defaultProfile) {
				toCollapse.vars = MergeManifest(toCollapse.vars, profile.vars);
				toCollapse.sources = MergeManifest(toCollapse.sources, profile.sources);
				toCollapse.includeDirs = MergeManifest(toCollapse.includeDirs, profile.includeDirs);
				toCollapse.compilerOptions = MergeManifest(toCollapse.compilerOptions, profile.compilerOptions);
				toCollapse.intDir = MergeManifest(toCollapse.intDir, profile.intDir);
				toCollapse.outDir = MergeManifest(toCollapse.outDir, profile.outDir);
				toCollapse.bridges = MergeManifest(toCollapse.bridges, profile.bridges);
				break;
			}
		}
	}

	toCollapse.profiles = std::nullopt;
}

void CollapseProfiles(ManifestProject& toCollapse) {
	if (toCollapse.profiles.has_value() && toCollapse.defaultProfile.has_value()) {
		auto defaultProfile = ManifestExpandVars(toCollapse.vars, toCollapse.defaultProfile);
		for (const auto& profile : *toCollapse.profiles) {
			if (*profile.name == defaultProfile) {
				toCollapse.vars = MergeManifest(toCollapse.vars, profile.vars);
				break;
			}
		}
	}

	toCollapse.profiles = std::nullopt;
}

void CollapseProfiles(ManifestWorkspace& toCollapse) {
	if (toCollapse.profiles.has_value() && toCollapse.defaultProfile.has_value()) {
		auto defaultProfile = ManifestExpandVars(toCollapse.vars, toCollapse.defaultProfile);
		for (const auto& profile : *toCollapse.profiles) {
			if (*profile.name == defaultProfile) {
				toCollapse.vars = MergeManifest(toCollapse.vars, profile.vars);
				break;
			}
		}
	}

	toCollapse.profiles = std::nullopt;
}

void CollapseProfiles(ManifestRoot& toCollapse) {
	if (toCollapse.profiles.has_value() && toCollapse.defaultProfile.has_value()) {
		auto defaultProfile = ManifestExpandVars(toCollapse.vars, toCollapse.defaultProfile);
		for (const auto& profile : *toCollapse.profiles) {
			if (*profile.name == defaultProfile) {
				toCollapse.vars = MergeManifest(toCollapse.vars, profile.vars);
				break;
			}
		}
	}

	toCollapse.profiles = std::nullopt;
}

void PropagateVars(const ManifestTarget& parent, OptManifestBridges& child) {
	if (!child.has_value()) {
		return;
	}
	child->vars = MergeManifest(parent.vars, child->vars);
}

void PropagateVars(const ManifestProject& parent, OptVecManifestExternalDependencies& child) {
	if (!child.has_value()) {
		return;
	}
	for (auto& externalDependencies : *child) {
		externalDependencies.vars = MergeManifest(parent.vars, externalDependencies.vars);
	}
}

void PropagateVars(const ManifestProject& parent, OptVecManifestTarget& child) {
	if (!child.has_value()) {
		return;
	}
	for (auto& target : *child) {
		target.vars = MergeManifest(parent.vars, target.vars);
		target.defaultProfile = MergeManifest(parent.defaultProfile, target.defaultProfile);

		CollapseProfiles(target);
		PropagateVars(target, target.bridges);
	}
}

void PropagateVars(const ManifestWorkspace& parent, OptManifestAutomation& child) {
	if (!child.has_value()) {
		return;
	}
	child->vars = MergeManifest(parent.vars, child->vars);
}

void PropagateVars(const ManifestWorkspace& parent, OptVecManifestProject& child) {
	if (!child.has_value()) {
		return;
	}
	for (auto& project : *child) {
		project.vars = MergeManifest(parent.vars, project.vars);
		project.defaultProfile = MergeManifest(parent.defaultProfile, project.defaultProfile);

		CollapseProfiles(project);
		PropagateVars(project, project.externalDependencies);
		PropagateVars(project, project.targets);
	}
}

void PropagateVars(const ManifestRoot& parent, OptVecManifestWorkspace& child) {
	if (!child.has_value()) {
		return;
	}

	for (auto& workspace : *child) {
		workspace.vars = MergeManifest(parent.vars, workspace.vars);
		workspace.defaultProfile = MergeManifest(parent.defaultProfile, workspace.defaultProfile);

		CollapseProfiles(workspace);
		PropagateVars(workspace, workspace.automation);
		PropagateVars(workspace, workspace.projects);
	}
}

void PropagateVars(ManifestRoot& child) {
	CollapseProfiles(child);
	PropagateVars(child, child.workspaces);
}

void DumpManifest(int offset, const OptMapStrStr& toExpand) {
	if (!toExpand.has_value()) {
		std::cout << "{}";
		return;
	}
	int i = 0;
	std::cout << "{ ";
	for (const auto& [key, val] : *toExpand) {
		if (i != 0) {
			std::cout << ", ";
		}
		std::cout << key << " : \"" << val + "\"";
		i++;
	}
	std::cout << " }";
}

void DumpManifest(int offset, const OptStr& toExpand) {
	if (!toExpand.has_value()) {
		std::cout << "\"\"";
		return;
	}
	std::cout << "\"" << *toExpand << "\"";
}

void DumpManifest(int offset, const OptVecStr& toExpand) {
	if (!toExpand.has_value()) {
		std::cout << "[]";
		return;
	}
	int i = 0;
	std::cout << "[";
	for (const auto& val : *toExpand) {
		if (i != 0) {
			std::cout << ", ";
		}
		std::cout << "\"" << val << "\"";
		i++;
	}
	std::cout << "]";
}
inline std::string Indent(int levels, int spacesPerLevel = 2) {
	if (levels <= 0) return {};
	return std::string(static_cast<size_t>(levels) * spacesPerLevel, ' ');
}

#define DUMP(LABEL, FIELD)						\
	std::cout << Indent(offset) << LABEL ": ";	\
    DumpManifest(offset + 1, FIELD);			\
    std::cout << '\n'; 

void DumpManifest(int offset, const OptManifestBridges& toExpand) {
	if (!toExpand.has_value()) return;
	auto& bridge = *toExpand;
	std::cout << "{\n";
	DUMP("vars", bridge.vars);
	DUMP("path", bridge.path);
	DUMP("envFiles", bridge.envFiles);
	DUMP("uses", bridge.uses);
	DUMP("implements", bridge.implements);
	std::cout << Indent(offset) <<  "}";
}

void DumpManifest(int offset, const OptVecManifestTargetProfile& toExpand) {
	if (!toExpand.has_value()) return;
	std::cout << "{\n";
	for (const auto& profile : *toExpand) {
		DUMP("vars", profile.vars);
		DUMP("path", profile.path);
		DUMP("envFiles", profile.envFiles);
		DUMP("name", profile.name);
		DUMP("sources", profile.sources);
		DUMP("includeDirs", profile.includeDirs);
		DUMP("compilerOptions", profile.compilerOptions);
		DUMP("intDir", profile.intDir);
		DUMP("outDir", profile.outDir);
		DUMP("bridges", profile.bridges);
	}
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const OptVecManifestProfile& toExpand) {
	if (!toExpand.has_value()) return;
	std::cout << "{\n";
	for (const auto& profile : *toExpand) {
		DUMP("vars", profile.vars);
		DUMP("path", profile.path);
		DUMP("envFiles", profile.envFiles);
		DUMP("name", profile.name);
	}
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const OptVecManifestTarget& toExpand) {
	if (!toExpand.has_value()) return;
	std::cout << "{\n";
	for (const auto& target : *toExpand) {
		DUMP("vars", target.vars);
		DUMP("path", target.path);
		DUMP("envFiles", target.envFiles);
		DUMP("name", target.name);
		DUMP("profiles", target.profiles);
		DUMP("defaultProfile", target.defaultProfile);
		DUMP("type", target.type);
		DUMP("language", target.language);
		DUMP("toolchain", target.toolchain);
		DUMP("link", target.link);
		DUMP("sources", target.sources);
		DUMP("includeDirs", target.includeDirs);
		DUMP("compilerOptions", target.compilerOptions);
		DUMP("intDir", target.intDir);
		DUMP("outDir", target.outDir);
		DUMP("bridges", target.bridges);
	}
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const OptVecManifestExternalDependencies& toExpand) {
	if (!toExpand.has_value()) return;
	std::cout << "{\n";
	for (const auto& externalDependency : *toExpand) {
		DUMP("vars", externalDependency.vars);
		DUMP("path", externalDependency.path);
		DUMP("envFiles", externalDependency.envFiles);
		DUMP("toolchain", externalDependency.toolchain);
		DUMP("name", externalDependency.name);
		DUMP("version", externalDependency.version);
		DUMP("url", externalDependency.url);
		DUMP("branch", externalDependency.branch);
		DUMP("resolveFirst", externalDependency.resolveFirst);
		DUMP("buildsystem", externalDependency.buildsystem);
		DUMP("buildArgs", externalDependency.buildArgs);
	}
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const OptVecManifestProject& toExpand) {
	if (!toExpand.has_value()) return;
	std::cout << "{\n";
	for (const auto& project : *toExpand) {
		DUMP("vars", project.vars);
		DUMP("path", project.path);
		DUMP("envFiles", project.envFiles);
		DUMP("name", project.name);
		DUMP("profiles", project.profiles);
		DUMP("defaultProfile", project.defaultProfile);
		DUMP("externalDependencies", project.externalDependencies);
		DUMP("startupTarget", project.startupTarget);
		DUMP("targets", project.targets);
	}
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const OptManifestAutomation& toExpand) {
	if (!toExpand.has_value()) return;
	auto& automation = *toExpand;
	std::cout << "{\n";
	DUMP("vars", automation.vars);
	DUMP("path", automation.path);
	DUMP("envFiles", automation.envFiles);
	DUMP("script", automation.script);
	DUMP("hooks", automation.hooks);
	DUMP("actions", automation.actions);
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const OptVecManifestWorkspace& toExpand) {
	if (!toExpand.has_value()) return;
	std::cout << "{\n";
	for (const auto& workspace : *toExpand) {
		DUMP("vars", workspace.vars);
		DUMP("path", workspace.path);
		DUMP("envFiles", workspace.envFiles);
		DUMP("name", workspace.name);
		DUMP("profiles", workspace.profiles);
		DUMP("defaultProfile", workspace.defaultProfile);
		DUMP("startupProject", workspace.startupProject);
		DUMP("projects", workspace.projects);
		DUMP("automation", workspace.automation);
	}
	std::cout << Indent(offset) << "}";
}

void DumpManifest(int offset, const ManifestRoot& toExpand) {
	DUMP("vars", toExpand.vars);
	DUMP("path", toExpand.path);
	DUMP("envFiles", toExpand.envFiles);
	DUMP("profiles", toExpand.profiles);
	DUMP("defaultProfile", toExpand.defaultProfile);
	DUMP("includes", toExpand.includes);
	DUMP("startupWorkspace", toExpand.startupWorkspace);
	DUMP("workspaces", toExpand.workspaces);
}
