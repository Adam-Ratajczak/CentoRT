#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <figcone/figcone.h>
#include "Utils.hpp"

using OptMapStrStr = std::optional<std::map<std::string, std::string>>;
using OptStr = std::optional<std::string>;
using OptVecStr = std::optional<std::vector<std::string>>;
using OptInt = std::optional<int>;

#define MANIFEST_COMMON														\
FIGCONE_DICT(vars, OptMapStrStr);								\
FIGCONE_PARAM(path, OptStr);							\
FIGCONE_PARAMLIST(envFiles, OptVecStr);

struct ManifestProfile : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_PARAMLIST(defines, OptVecStr);
	FIGCONE_PARAM(optimize, OptStr);
};
using OptVecManifestProfile = std::optional<std::vector<ManifestProfile>>;

struct ManifestExternalDependencies : public figcone::Config {
	FIGCONE_PARAM(toolchain, OptStr);
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_PARAM(version, OptStr);
	FIGCONE_PARAM(url, OptStr);
	FIGCONE_PARAM(branch, OptStr);
	FIGCONE_PARAMLIST(libs, OptVecStr);
	FIGCONE_PARAM(buildsystem, OptStr);
	FIGCONE_PARAMLIST(buildArgs, OptVecStr);
};
using OptVecManifestExternalDependencies = std::optional<std::vector<ManifestExternalDependencies>>;

struct ManifestBridges : public figcone::Config {
	FIGCONE_PARAMLIST(uses, OptVecStr);
	FIGCONE_PARAMLIST(implements, OptVecStr);
};
using OptManifestBridges = std::optional<ManifestBridges>;

struct ManifestTarget : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(type, OptStr);
	FIGCONE_PARAM(language, OptStr);
	FIGCONE_PARAM(toolchain, OptStr);
	FIGCONE_PARAMLIST(sources, OptVecStr);
	FIGCONE_PARAMLIST(includeDirs, OptVecStr);
	FIGCONE_PARAMLIST(link, OptVecStr);
	FIGCONE_PARAM(intDir, OptStr);
	FIGCONE_PARAM(outDir, OptStr);
	FIGCONE_NODE(bridges, OptManifestBridges);
};
using OptVecManifestTarget = std::optional<std::vector<ManifestTarget>>;

struct ManifestProject : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAMLIST(dependsOn, OptVecStr);
	FIGCONE_NODELIST(externalDependencies, OptVecManifestExternalDependencies);
	FIGCONE_PARAM(startupTarget, OptStr);
	FIGCONE_NODELIST(targets, OptVecManifestTarget);
};
using OptVecManifestProject = std::optional<std::vector<ManifestProject>>;

struct ManifestAutomation : public figcone::Config {
	FIGCONE_PARAM(script, OptStr);
	FIGCONE_DICT(hooks, OptMapStrStr);
	FIGCONE_DICT(actions, OptMapStrStr);
};
using OptManifestAutomation = std::optional<ManifestAutomation>;

struct ManifestWorkspace : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAM(startupProject, OptStr);
	FIGCONE_NODELIST(projects, OptVecManifestProject);
	FIGCONE_NODE(automation, OptManifestAutomation);
};
using OptManifestWorkspace = std::optional<ManifestWorkspace>;

struct ManifestRoot : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(schemaVersion, OptInt);
	FIGCONE_PARAMLIST(includes, OptVecStr);
	FIGCONE_NODE(workspace, OptManifestWorkspace);
};

template<typename T>
inline T MergeManifest(const T& lhs, const T& rhs) {
	throw std::runtime_error("Unimplemented merge object");
}

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

template<>
inline OptMapStrStr MergeManifest<OptMapStrStr>(const OptMapStrStr& lhs, const OptMapStrStr& rhs)
{
	GUARD_OPTIONALS

	std::map<std::string, std::string> out = *lhs;
	for (const auto& [key, value] : *rhs) {
		out[key] = value;
	}

	return out;
}

template<>
inline OptStr MergeManifest<OptStr>(const OptStr& lhs, const OptStr& rhs)
{
	GUARD_OPTIONALS

	return rhs;
}

template<>
inline OptVecStr MergeManifest<OptVecStr>(const OptVecStr& lhs, const OptVecStr& rhs)
{
	GUARD_OPTIONALS

	std::vector<std::string> out = *lhs;
	out.insert(out.end(), rhs->begin(), rhs->end());

	return out;
}

template<>
inline OptInt MergeManifest<OptInt>(const OptInt& lhs, const OptInt& rhs)
{
	GUARD_OPTIONALS

	return rhs;
}

template<>
inline OptVecManifestProfile MergeManifest<OptVecManifestProfile>(const OptVecManifestProfile& lhs, const OptVecManifestProfile& rhs)
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
			plhs.defines = MergeManifest(plhs.defines, prhs.defines);
			plhs.optimize = MergeManifest(plhs.optimize, prhs.optimize);
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

template<>
inline OptVecManifestExternalDependencies MergeManifest<OptVecManifestExternalDependencies>(const OptVecManifestExternalDependencies& lhs, const OptVecManifestExternalDependencies& rhs)
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

			plhs.toolchain = MergeManifest(plhs.toolchain, prhs.toolchain);
			plhs.name = MergeManifest(plhs.name, prhs.name);
			plhs.version = MergeManifest(plhs.version, prhs.version);
			plhs.url = MergeManifest(plhs.url, prhs.url);
			plhs.branch = MergeManifest(plhs.branch, prhs.branch);
			plhs.libs = MergeManifest(plhs.libs, prhs.libs);
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

template<>
inline OptManifestBridges MergeManifest<OptManifestBridges>(const OptManifestBridges& lhs, const OptManifestBridges& rhs) {
	GUARD_OPTIONALS

	ManifestBridges out;
	out.uses = MergeManifest(lhs->uses, rhs->uses);
	out.implements = MergeManifest(lhs->implements, rhs->implements);

	return out;
}

template<>
inline OptVecManifestTarget MergeManifest<OptVecManifestTarget>(const OptVecManifestTarget& lhs, const OptVecManifestTarget& rhs)
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
			plhs.sources = MergeManifest(plhs.sources, prhs.sources);
			plhs.includeDirs = MergeManifest(plhs.includeDirs, prhs.includeDirs);
			plhs.link = MergeManifest(plhs.link, prhs.link);
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

template<>
inline OptVecManifestProject MergeManifest<OptVecManifestProject>(const OptVecManifestProject& lhs, const OptVecManifestProject& rhs)
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
			plhs.dependsOn = MergeManifest(plhs.dependsOn, prhs.dependsOn);
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

template<>
inline OptManifestAutomation MergeManifest<OptManifestAutomation>(const OptManifestAutomation& lhs, const OptManifestAutomation& rhs) {
	GUARD_OPTIONALS

	ManifestAutomation out;
	out.script = MergeManifest(lhs->script, rhs->script);
	out.hooks = MergeManifest(lhs->hooks, rhs->hooks);
	out.actions = MergeManifest(lhs->actions, rhs->actions);

	return out;
}

template<>
inline OptManifestWorkspace MergeManifest<OptManifestWorkspace>(const OptManifestWorkspace& lhs, const OptManifestWorkspace& rhs) {
	GUARD_OPTIONALS

	ManifestWorkspace out;
	out.vars = MergeManifest(lhs->vars, rhs->vars);
	out.path = MergeManifest(lhs->path, rhs->path);
	out.envFiles = MergeManifest(lhs->envFiles, rhs->envFiles);
	out.profiles = MergeManifest(lhs->profiles, rhs->profiles);
	out.defaultProfile = MergeManifest(lhs->defaultProfile, rhs->defaultProfile);
	out.startupProject = MergeManifest(lhs->startupProject, rhs->startupProject);
	out.projects = MergeManifest(lhs->projects, rhs->projects);
	out.automation = MergeManifest(lhs->automation, rhs->automation);

	return out;
}

template<>
inline ManifestRoot MergeManifest<ManifestRoot>(const ManifestRoot& lhs, const ManifestRoot& rhs)
{
	if (lhs.schemaVersion != rhs.schemaVersion) {
		throw std::runtime_error("Schema version missmatch");
	}

	ManifestRoot out;
	out.vars = MergeManifest(lhs.vars, rhs.vars);
	out.path = MergeManifest(lhs.path, rhs.path);
	out.envFiles = MergeManifest(lhs.envFiles, rhs.envFiles);
	out.profiles = MergeManifest(lhs.profiles, rhs.profiles);
	out.schemaVersion = MergeManifest(lhs.schemaVersion, rhs.schemaVersion);
	out.includes = MergeManifest(lhs.includes, rhs.includes);
	out.workspace = MergeManifest(lhs.workspace, rhs.workspace);

	return out;
}

template<typename T>
inline void CheckAndPostprocessManifest(const std::string& currPath, T& toCheck) {
	throw std::runtime_error("Unimplemented postprocessing object");
}

template<>
inline void CheckAndPostprocessManifest<OptVecManifestProfile>(const std::string& currPath, OptVecManifestProfile& toCheck) {
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

			for (const auto& envFileGlob : *profile.envFiles) {
				std::vector<std::filesystem::path> paths;
				Utils::ExpandGlob(envFileGlob, *profile.path, paths);
				for (const auto& envPathLocal : paths) {
					auto envPath = std::filesystem::path(*profile.path) / envPathLocal;
					if (Utils::Match(envPath.generic_string(), "*.env")) {
						auto envFile = Utils::ParseEnvFile(envPath);
						for (const auto& [key, val] : envFile) {
							vars[key] = val;
						}
					}
				}

				for (const auto& envPathLocal : paths) {
					auto envPath = std::filesystem::path(*profile.path) / envPathLocal;
					if (Utils::Match(envPath.generic_string(), "*.env.local")) {
						auto envFile = Utils::ParseEnvFile(envPath);
						for (const auto& [key, val] : envFile) {
							vars[key] = val;
						}
					}
				}
			}
		}

		vars["CENTO_CURRENT_DIR"] = *profile.path;
		profile.vars = vars;
		profile.envFiles = std::nullopt;
	}
}

template<>
inline void CheckAndPostprocessManifest<OptVecManifestTarget>(const std::string& currPath, OptVecManifestTarget& toCheck) {
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

			for (const auto& envFileGlob : *target.envFiles) {
				std::vector<std::filesystem::path> paths;
				Utils::ExpandGlob(envFileGlob, *target.path, paths);
				for (const auto& envPathLocal : paths) {
					auto envPath = std::filesystem::path(*target.path) / envPathLocal;
					if (Utils::Match(envPath.generic_string(), "*.env")) {
						auto envFile = Utils::ParseEnvFile(envPath);
						for (const auto& [key, val] : envFile) {
							vars[key] = val;
						}
					}
				}

				for (const auto& envPathLocal : paths) {
					auto envPath = std::filesystem::path(*target.path) / envPathLocal;
					if (Utils::Match(envPath.generic_string(), "*.env.local")) {
						auto envFile = Utils::ParseEnvFile(envPath);
						for (const auto& [key, val] : envFile) {
							vars[key] = val;
						}
					}
				}
			}
		}

		vars["CENTO_CURRENT_DIR"] = *target.path;
		target.vars = vars;
		target.envFiles = std::nullopt;

		CheckAndPostprocessManifest(*target.path, target.profiles);
	}
}

template<>
inline void CheckAndPostprocessManifest<OptVecManifestProject>(const std::string& currPath, OptVecManifestProject& toCheck) {
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

			for (const auto& envFileGlob : *project.envFiles) {
				std::vector<std::filesystem::path> paths;
				Utils::ExpandGlob(envFileGlob, *project.path, paths);
				for (const auto& envPathLocal : paths) {
					auto envPath = std::filesystem::path(*project.path) / envPathLocal;
					if (Utils::Match(envPath.generic_string(), "*.env")) {
						auto envFile = Utils::ParseEnvFile(envPath);
						for (const auto& [key, val] : envFile) {
							vars[key] = val;
						}
					}
				}

				for (const auto& envPathLocal : paths) {
					auto envPath = std::filesystem::path(*project.path) / envPathLocal;
					if (Utils::Match(envPath.generic_string(), "*.env.local")) {
						auto envFile = Utils::ParseEnvFile(envPath);
						for (const auto& [key, val] : envFile) {
							vars[key] = val;
						}
					}
				}
			}
		}

		vars["CENTO_CURRENT_DIR"] = *project.path;
		project.vars = vars;
		project.envFiles = std::nullopt;

		CheckAndPostprocessManifest(*project.path, project.targets);
		CheckAndPostprocessManifest(*project.path, project.profiles);
	}
}

template<>
inline void CheckAndPostprocessManifest<OptManifestWorkspace>(const std::string& currPath, OptManifestWorkspace& toCheck) {
	if (!toCheck.has_value()) {
		return;
	}

	std::filesystem::path base = currPath;
	if (toCheck->path.has_value()) {
		std::filesystem::path path = *toCheck->path;
		if (!Utils::IsWeaklyCanonical(path)) {
			toCheck->path = (base / path).string();
		}
	}
	else {
		toCheck->path = base.string();
	}

	std::map<std::string, std::string> vars;
	if (toCheck->vars.has_value()) {
		vars = *toCheck->vars;
	}

	if (toCheck->envFiles.has_value()) {

		for (const auto& envFileGlob : *toCheck->envFiles) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(envFileGlob, *toCheck->path, paths);
			for (const auto& envPathLocal : paths) {
				auto envPath = std::filesystem::path(*toCheck->path) / envPathLocal;
				if (Utils::Match(envPath.generic_string(), "*.env")) {
					auto envFile = Utils::ParseEnvFile(envPath);
					for (const auto& [key, val] : envFile) {
						vars[key] = val;
					}
				}
			}

			for (const auto& envPathLocal : paths) {
				auto envPath = std::filesystem::path(*toCheck->path) / envPathLocal;
				if (Utils::Match(envPath.generic_string(), "*.env.local")) {
					auto envFile = Utils::ParseEnvFile(envPath);
					for (const auto& [key, val] : envFile) {
						vars[key] = val;
					}
				}
			}
		}
	}

	vars["CENTO_CURRENT_DIR"] = *toCheck->path;
	vars["CENTO_WORKSPACE_DIR"] = *toCheck->path;
	toCheck->vars = vars;
	toCheck->envFiles = std::nullopt;

	CheckAndPostprocessManifest(*toCheck->path, toCheck->projects);
	CheckAndPostprocessManifest(*toCheck->path, toCheck->profiles);
}

template<>
inline void CheckAndPostprocessManifest<ManifestRoot>(const std::string& currPath, ManifestRoot& toCheck) {
	if (!toCheck.schemaVersion.has_value() || *toCheck.schemaVersion <= 0) {
		throw std::runtime_error("Schema version must exist and be a positive number");
	}

	std::filesystem::path base = currPath;
	if (toCheck.path.has_value()) {
		std::filesystem::path path = *toCheck.path;
		if (!Utils::IsWeaklyCanonical(path)) {
			toCheck.path = (base / path).string();
		}
	}
	else {
		toCheck.path = base.string();
	}

	std::map<std::string, std::string> vars;
	if (toCheck.vars.has_value()) {
		vars = *toCheck.vars;
	}

	if (toCheck.envFiles.has_value()) {

		for (const auto& envFileGlob : *toCheck.envFiles) {
			std::vector<std::filesystem::path> paths;
			Utils::ExpandGlob(envFileGlob, *toCheck.path, paths);
			for (const auto& envPathLocal : paths) {
				auto envPath = std::filesystem::path(*toCheck.path) / envPathLocal;
				if (Utils::Match(envPath.generic_string(), "*.env")) {
					auto envFile = Utils::ParseEnvFile(envPath);
					for (const auto& [key, val] : envFile) {
						vars[key] = val;
					}
				}
			}

			for (const auto& envPathLocal : paths) {
				auto envPath = std::filesystem::path(*toCheck.path) / envPathLocal;
				if (Utils::Match(envPath.generic_string(), "*.env.local")) {
					auto envFile = Utils::ParseEnvFile(envPath);
					for (const auto& [key, val] : envFile) {
						vars[key] = val;
					}
				}
			}
		}
	}

	vars["CENTO_CURRENT_DIR"] = *toCheck.path;
	toCheck.vars = vars;
	toCheck.envFiles = std::nullopt;

	CheckAndPostprocessManifest(*toCheck.path, toCheck.workspace);
	CheckAndPostprocessManifest(*toCheck.path, toCheck.profiles);
}

template<typename T, typename U>
inline void PropagateVarsAndProfiles(const T& parent, U& child) {
	throw std::runtime_error("Unimplemented propagation object");
}

template<>
inline void PropagateVarsAndProfiles<OptMapStrStr, OptVecManifestProfile>(const OptMapStrStr& parent, OptVecManifestProfile& child) {
	if (!child.has_value() || !parent.has_value()) {
		return;
	}

	for (auto& prhs : *child) {
		prhs.vars = MergeManifest(parent, prhs.vars);
	}
}

template<>
inline void PropagateVarsAndProfiles<OptVecManifestProfile, OptVecManifestProfile>(const OptVecManifestProfile& parent, OptVecManifestProfile& child) {
	if (!parent.has_value()) {
		return;
	}

	if (!child.has_value()) {
		child = parent;
		return;
	}

	for (const auto& plhs : *parent) {
		bool found = false;
		for (auto& prhs : *child) {
			if (plhs.name == prhs.name) {
				found = true;
				prhs = MergeManifest(plhs, prhs);
				break;
			}
		}
		if (!found) {
			child->emplace_back(plhs);
		}
	}
}

template<>
inline void PropagateVarsAndProfiles<ManifestProject, OptVecManifestTarget>(const ManifestProject& parent, OptVecManifestTarget& child) {
	if (!child.has_value()) {
		return;
	}
	for (auto& target : *child) {
		target.vars = MergeManifest(parent.vars, target.vars);

		PropagateVarsAndProfiles(parent.profiles, target.profiles);
		PropagateVarsAndProfiles(target.vars, target.profiles);
	}
}

template<>
inline void PropagateVarsAndProfiles<ManifestWorkspace, OptVecManifestProject>(const ManifestWorkspace& parent, OptVecManifestProject& child) {
	if (!child.has_value()) {
		return;
	}
	for (auto& project : *child) {
		project.vars = MergeManifest(parent.vars, project.vars);

		PropagateVarsAndProfiles(parent.profiles, project.profiles);
		PropagateVarsAndProfiles(project.vars, project.profiles);
		PropagateVarsAndProfiles(project, project.targets);
	}
}

template<>
inline void PropagateVarsAndProfiles<ManifestRoot, OptManifestWorkspace>(const ManifestRoot& parent, OptManifestWorkspace& child) {
	if (!child.has_value()) {
		return;
	}
	child->vars = MergeManifest(parent.vars, child->vars);

	PropagateVarsAndProfiles(parent.profiles, child->profiles);
	PropagateVarsAndProfiles(child->vars, child->profiles);
	PropagateVarsAndProfiles(*child, child->projects);
}

template<>
inline void PropagateVarsAndProfiles<ManifestRoot, ManifestRoot>(const ManifestRoot& parent, ManifestRoot& child) {
	PropagateVarsAndProfiles(child.vars, child.profiles);
	PropagateVarsAndProfiles(child, child.workspace);
}
