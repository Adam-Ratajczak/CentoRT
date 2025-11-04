#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <figcone/figcone.h>
#include "Utils.hpp"

namespace ManifestObjects {

	struct ManifestTargetProfile;
	struct ManifestProfile;
	struct ManifestBridges;
	struct ManifestTarget;
	struct ManifestExternalDependency;
	struct ManifestProject;
	struct ManifestAutomation;
	struct ManifestWorkspace;

	using OptMapStrStr = std::optional<std::map<std::string, std::string>>;
	using OptStr = std::optional<std::string>;
	using OptVecStr = std::optional<std::vector<std::string>>;
	using OptVecManifestTargetProfile = std::optional<std::vector<ManifestTargetProfile>>;
	using OptVecManifestProfile = std::optional<std::vector<ManifestProfile>>;
	using OptManifestBridges = std::optional<ManifestBridges>;
	using OptVecManifestTarget = std::optional<std::vector<ManifestTarget>>;
	using OptVecManifestExternalDependency = std::optional<std::vector<ManifestExternalDependency>>;
	using OptVecManifestProject = std::optional<std::vector<ManifestProject>>;
	using OptManifestAutomation = std::optional<ManifestAutomation>;
	using OptVecManifestWorkspace = std::optional<std::vector<ManifestWorkspace>>;

#define MANIFEST_COMMON									\
FIGCONE_DICT(vars, OptMapStrStr);						\
FIGCONE_PARAM(path, OptStr);							\
FIGCONE_PARAMLIST(envFiles, OptVecStr);

#define MANIFEST_COMMON_FOR_TARGET						\
FIGCONE_PARAMLIST(sources, OptVecStr);					\
FIGCONE_PARAMLIST(compilerOptions, OptVecStr);			\
FIGCONE_PARAMLIST(linkerOptions, OptVecStr);			\
FIGCONE_PARAM(intDir, OptStr);							\
FIGCONE_PARAM(outDir, OptStr);							\
FIGCONE_NODE(bridges, OptManifestBridges);				

	struct ManifestCommon {
	};

	struct ManifestBridges : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAMLIST(uses, OptVecStr);
		FIGCONE_PARAMLIST(implements, OptVecStr);
	};

	struct ManifestTargetProfile : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAM(name, OptStr);
		MANIFEST_COMMON_FOR_TARGET
	};

	struct ManifestProfile : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAM(name, OptStr);
	};

	struct ManifestTarget : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAM(name, OptStr);
		FIGCONE_NODELIST(profiles, OptVecManifestTargetProfile);
		FIGCONE_PARAM(defaultProfile, OptStr);
		FIGCONE_PARAM(type, OptStr);
		FIGCONE_PARAM(language, OptStr);
		FIGCONE_PARAM(toolchain, OptStr);
		FIGCONE_PARAMLIST(link, OptVecStr);
		MANIFEST_COMMON_FOR_TARGET
	};

	struct ManifestExternalDependency : public figcone::Config, public ManifestCommon {
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

	struct ManifestProject : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAM(name, OptStr);
		FIGCONE_NODELIST(profiles, OptVecManifestProfile);
		FIGCONE_PARAM(defaultProfile, OptStr);
		FIGCONE_NODELIST(externalDependencies, OptVecManifestExternalDependency);
		FIGCONE_PARAM(startupTarget, OptStr);
		FIGCONE_NODELIST(targets, OptVecManifestTarget);
	};

	struct ManifestAutomation : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAM(script, OptStr);
		FIGCONE_DICT(hooks, OptMapStrStr);
		FIGCONE_DICT(actions, OptMapStrStr);
	};

	struct ManifestWorkspace : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_PARAM(name, OptStr);
		FIGCONE_NODELIST(profiles, OptVecManifestProfile);
		FIGCONE_PARAM(defaultProfile, OptStr);
		FIGCONE_PARAM(startupProject, OptStr);
		FIGCONE_NODELIST(projects, OptVecManifestProject);
		FIGCONE_NODE(automation, OptManifestAutomation);
	};

	struct ManifestRoot : public figcone::Config, public ManifestCommon {
		MANIFEST_COMMON;
		FIGCONE_NODELIST(profiles, OptVecManifestProfile);
		FIGCONE_PARAM(defaultProfile, OptStr);
		FIGCONE_PARAMLIST(includes, OptVecStr);
		FIGCONE_NODELIST(workspaces, OptVecManifestWorkspace);
		FIGCONE_PARAM(startupWorkspace, OptStr);
	};

	ManifestRoot MergeManifest(const ManifestRoot& lhs, const ManifestRoot& rhs);

	void CheckAndPostprocessManifest(const std::string& currPath, ManifestRoot& toCheck);

	void EvaluateCentoVars(ManifestRoot& toEvaluate);

	void PropagateVars(ManifestRoot& child);

	void ManifestExpandVars(ManifestRoot& toExpand);

	void DumpManifest(int offset, const ManifestRoot& toExpand);

}
