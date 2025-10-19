#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <figcone/figcone.h>
#include "Utils.hpp"

struct ManifestProfile;
struct ManifestBridges;
struct ManifestTarget;
struct ManifestExternalDependencies;
struct ManifestProject;
struct ManifestAutomation;
struct ManifestWorkspace;

using OptMapStrStr = std::optional<std::map<std::string, std::string>>;
using OptStr = std::optional<std::string>;
using OptVecStr = std::optional<std::vector<std::string>>;
using OptVecManifestProfile = std::optional<std::vector<ManifestProfile>>;
using OptManifestBridges = std::optional<ManifestBridges>;
using OptVecManifestTarget = std::optional<std::vector<ManifestTarget>>;
using OptVecManifestExternalDependencies = std::optional<std::vector<ManifestExternalDependencies>>;
using OptVecManifestProject = std::optional<std::vector<ManifestProject>>;
using OptManifestAutomation = std::optional<ManifestAutomation>;
using OptVecManifestWorkspace = std::optional<std::vector<ManifestWorkspace>>;

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

struct ManifestBridges : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAMLIST(uses, OptVecStr);
	FIGCONE_PARAMLIST(implements, OptVecStr);
};

struct ManifestProfile : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	MANIFEST_COMMON_FOR_TARGET
};

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

struct ManifestAutomation : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(script, OptStr);
	FIGCONE_DICT(hooks, OptMapStrStr);
	FIGCONE_DICT(actions, OptMapStrStr);
};

struct ManifestWorkspace : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, OptStr);
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAM(startupProject, OptStr);
	FIGCONE_NODELIST(projects, OptVecManifestProject);
	FIGCONE_NODE(automation, OptManifestAutomation);
};

struct ManifestRoot : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_NODELIST(profiles, OptVecManifestProfile);
	FIGCONE_PARAM(defaultProfile, OptStr);
	FIGCONE_PARAMLIST(includes, OptVecStr);
	FIGCONE_NODELIST(workspaces, OptVecManifestWorkspace);
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

template<typename T>
inline void EvaluateCentoVars(T& toEvaluate) {
	throw std::runtime_error("Unimplemented evaluation object");
}

template<>
void EvaluateCentoVars<OptVecManifestProfile>(OptVecManifestProfile& toEvaluate);

template<>
void EvaluateCentoVars<OptVecManifestExternalDependencies>(OptVecManifestExternalDependencies& toEvaluate);

template<>
void EvaluateCentoVars<OptManifestBridges>(OptManifestBridges& toEvaluate);

template<>
void EvaluateCentoVars<OptVecManifestTarget>(OptVecManifestTarget& toEvaluate);

template<>
void EvaluateCentoVars<OptVecManifestProject>(OptVecManifestProject& toEvaluate);

template<>
void EvaluateCentoVars<OptManifestAutomation>(OptManifestAutomation& toEvaluate);

template<>
void EvaluateCentoVars<OptVecManifestWorkspace>(OptVecManifestWorkspace& toEvaluate);

template<>
void EvaluateCentoVars<ManifestRoot>(ManifestRoot& toEvaluate);

template<typename T>
inline void CollapseProfiles(T& toCollapse) {
	throw std::runtime_error("Unimplemented collapse object");
}

template<>
void CollapseProfiles<OptVecManifestTarget>(OptVecManifestTarget& toCollapse);

template<>
void CollapseProfiles<OptVecManifestProject>(OptVecManifestProject& toCollapse);

template<>
void CollapseProfiles<OptVecManifestWorkspace>(OptVecManifestWorkspace& toCollapse);

template<>
void CollapseProfiles<ManifestRoot>(ManifestRoot& toCollapse);

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
