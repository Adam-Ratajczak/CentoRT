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

#define MANIFEST_COMMON									\
FIGCONE_DICT(vars, OptMapStrStr);						\
FIGCONE_PARAM(path, OptStr);							\
FIGCONE_PARAMLIST(envFiles, OptVecStr);

#define MANIFEST_COMMON_FOR_TARGET						\
FIGCONE_PARAMLIST(sources, OptVecStr);					\
FIGCONE_PARAMLIST(includeDirs, OptVecStr);				\
FIGCONE_PARAMLIST(compilerOptions, OptVecStr);			\
FIGCONE_PARAM(intDir, OptStr);							\
FIGCONE_PARAM(outDir, OptStr);							\
FIGCONE_NODE(bridges, OptManifestBridges);				

struct ManifestProfile : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	MANIFEST_COMMON_FOR_TARGET
};
using OptVecManifestProfile = std::optional<std::vector<ManifestProfile>>;

struct ManifestBridges : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAMLIST(uses, OptVecStr);
	FIGCONE_PARAMLIST(implements, OptVecStr);
};
using OptManifestBridges = std::optional<ManifestBridges>;

struct ManifestTarget : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAM(type, OptStr);
	FIGCONE_PARAM(language, OptStr);
	FIGCONE_PARAM(toolchain, OptStr);
	FIGCONE_PARAMLIST(link, OptVecStr);
	MANIFEST_COMMON_FOR_TARGET
};
using OptVecManifestTarget = std::optional<std::vector<ManifestTarget>>;

struct ManifestExternalDependencies : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(toolchain, OptStr);
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_PARAM(version, OptStr);
	FIGCONE_PARAM(url, OptStr);
	FIGCONE_PARAM(branch, OptStr);
	FIGCONE_PARAMLIST(resolveFirst, OptVecStr);
	FIGCONE_PARAM(buildsystem, OptStr);
	FIGCONE_PARAMLIST(buildArgs, OptVecStr);
};
using OptVecManifestExternalDependencies = std::optional<std::vector<ManifestExternalDependencies>>;

struct ManifestProject : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAMLIST(dependsOn, OptVecStr);
	FIGCONE_NODELIST(externalDependencies, OptVecManifestExternalDependencies);
	FIGCONE_PARAM(startupTarget, OptStr);
	FIGCONE_NODELIST(targets, OptVecManifestTarget);
};
using OptVecManifestProject = std::optional<std::vector<ManifestProject>>;

struct ManifestAutomation : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(script, OptStr);
	FIGCONE_DICT(hooks, OptMapStrStr);
	FIGCONE_DICT(actions, OptMapStrStr);
};
using OptManifestAutomation = std::optional<ManifestAutomation>;

struct ManifestWorkspace : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAM(startupProject, OptStr);
	FIGCONE_NODELIST(projects, OptVecManifestProject);
	FIGCONE_NODE(automation, OptManifestAutomation);
};
using OptVecManifestWorkspace = std::optional<std::vector<ManifestWorkspace>>;

struct ManifestRoot : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAMLIST(includes, OptVecStr);
	FIGCONE_NODE(workspaces, OptVecManifestWorkspace);
	FIGCONE_PARAM(startupWorkspace, OptStr);
};

template<typename T>
inline T MergeManifest(const T& lhs, const T& rhs) {
	throw std::runtime_error("Unimplemented merge object");
}
template<>
OptMapStrStr MergeManifest<OptMapStrStr>(const OptMapStrStr& lhs, const OptMapStrStr& rhs);

template<>
OptStr MergeManifest<OptStr>(const OptStr& lhs, const OptStr& rhs);

template<>
OptVecStr MergeManifest<OptVecStr>(const OptVecStr& lhs, const OptVecStr& rhs);

template<>
OptVecManifestProfile MergeManifest<OptVecManifestProfile>(const OptVecManifestProfile& lhs, const OptVecManifestProfile& rhs);

template<>
OptVecManifestExternalDependencies MergeManifest<OptVecManifestExternalDependencies>(const OptVecManifestExternalDependencies& lhs, const OptVecManifestExternalDependencies& rhs);

template<>
OptManifestBridges MergeManifest<OptManifestBridges>(const OptManifestBridges& lhs, const OptManifestBridges& rhs);

template<>
OptVecManifestTarget MergeManifest<OptVecManifestTarget>(const OptVecManifestTarget& lhs, const OptVecManifestTarget& rhs);

template<>
OptVecManifestProject MergeManifest<OptVecManifestProject>(const OptVecManifestProject& lhs, const OptVecManifestProject& rhs);

template<>
OptManifestAutomation MergeManifest<OptManifestAutomation>(const OptManifestAutomation& lhs, const OptManifestAutomation& rhs);

template<>
OptVecManifestWorkspace MergeManifest<OptVecManifestWorkspace>(const OptVecManifestWorkspace& lhs, const OptVecManifestWorkspace& rhs);

template<>
ManifestRoot MergeManifest<ManifestRoot>(const ManifestRoot& lhs, const ManifestRoot& rhs);

template<typename T>
inline void CheckAndPostprocessManifest(const std::string& currPath, T& toCheck) {
	throw std::runtime_error("Unimplemented postprocessing object");
}

template<>
void CheckAndPostprocessManifest<OptVecManifestProfile>(const std::string& currPath, OptVecManifestProfile& toCheck);

template<>
void CheckAndPostprocessManifest<OptVecManifestExternalDependencies>(const std::string& currPath, OptVecManifestExternalDependencies& toCheck);

template<>
void CheckAndPostprocessManifest<OptManifestBridges>(const std::string& currPath, OptManifestBridges& toCheck);

template<>
void CheckAndPostprocessManifest<OptVecManifestTarget>(const std::string& currPath, OptVecManifestTarget& toCheck);

template<>
void CheckAndPostprocessManifest<OptVecManifestProject>(const std::string& currPath, OptVecManifestProject& toCheck);

template<>
void CheckAndPostprocessManifest<OptManifestAutomation>(const std::string& currPath, OptManifestAutomation& toCheck);

template<>
void CheckAndPostprocessManifest<OptVecManifestWorkspace>(const std::string& currPath, OptVecManifestWorkspace& toCheck);

template<>
void CheckAndPostprocessManifest<ManifestRoot>(const std::string& currPath, ManifestRoot& toCheck);

template<typename T, typename U>
void PropagateVarsAndProfiles(const T& parent, U& child) {
	throw std::runtime_error("Unimplemented propagation object");
}

template<>
void PropagateVarsAndProfiles<ManifestTarget, OptVecManifestProfile>(const ManifestTarget& parent, OptVecManifestProfile& child);

template<>
void PropagateVarsAndProfiles<ManifestTarget, OptManifestBridges>(const ManifestTarget& parent, OptManifestBridges& child);

template<>
void PropagateVarsAndProfiles<ManifestProject, OptVecManifestProfile>(const ManifestProject& parent, OptVecManifestProfile& child);

template<>
void PropagateVarsAndProfiles<ManifestProject, OptVecManifestExternalDependencies>(const ManifestProject& parent, OptVecManifestExternalDependencies& child);

template<>
void PropagateVarsAndProfiles<ManifestProject, OptVecManifestTarget>(const ManifestProject& parent, OptVecManifestTarget& child);

template<>
void PropagateVarsAndProfiles<ManifestWorkspace, OptVecManifestProfile>(const ManifestWorkspace& parent, OptVecManifestProfile& child);

template<>
void PropagateVarsAndProfiles<ManifestWorkspace, OptManifestAutomation>(const ManifestWorkspace& parent, OptManifestAutomation& child);

template<>
void PropagateVarsAndProfiles<ManifestWorkspace, OptVecManifestProject>(const ManifestWorkspace& parent, OptVecManifestProject& child);

template<>
void PropagateVarsAndProfiles<ManifestRoot, OptVecManifestProfile>(const ManifestRoot& parent, OptVecManifestProfile& child);

template<>
void PropagateVarsAndProfiles<ManifestRoot, OptVecManifestWorkspace>(const ManifestRoot& parent, OptVecManifestWorkspace& child);

void PropagateVarsAndProfiles(ManifestRoot& child);

template<typename T>
inline void ManifestExpandVars(T& toExpand) {
	throw std::runtime_error("Unimplemented variables expansion object");
}

template<>
void ManifestExpandVars<OptVecManifestProfile>(OptVecManifestProfile& toExpand);

template<>
void ManifestExpandVars<OptVecManifestExternalDependencies>(OptVecManifestExternalDependencies& toExpand);

template<>
void ManifestExpandVars<OptManifestBridges>(OptManifestBridges& toExpand);

template<>
void ManifestExpandVars<OptVecManifestTarget>(OptVecManifestTarget& toExpand);

template<>
void ManifestExpandVars<OptVecManifestProject>(OptVecManifestProject& toExpand);

template<>
void ManifestExpandVars<OptManifestAutomation>(OptManifestAutomation& toExpand);

template<>
void ManifestExpandVars<OptVecManifestWorkspace>(OptVecManifestWorkspace& toExpand);

template<>
void ManifestExpandVars<ManifestRoot>(ManifestRoot& toExpand);
