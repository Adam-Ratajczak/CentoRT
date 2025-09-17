#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <figcone/figcone.h>

using MapStrStr = std::map<std::string, std::string>;
struct PathObject : public figcone::Config {
	FIGCONE_PARAM(path, std::optional<std::string>);
	FIGCONE_PARAM(required, bool);
};

#define MANIFEST_COMMON														\
FIGCONE_DICT(vars, std::optional<MapStrStr>);								\
FIGCONE_PARAM(path, std::optional<std::string>);							\
FIGCONE_NODELIST(envFiles, std::optional<std::vector<PathObject>>);

struct ManifestProfile : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, std::optional<std::string>);
	FIGCONE_PARAMLIST(defines, std::optional<std::vector<std::string>>);
	FIGCONE_PARAM(optimize, std::optional<std::string>);
};

struct ManifestExternalDependencies : public figcone::Config {
	FIGCONE_PARAM(toolchain, std::optional<std::string>);
	FIGCONE_PARAM(name, std::optional<std::string>);
	FIGCONE_PARAM(version, std::optional<std::string>);
	FIGCONE_PARAM(url, std::optional<std::string>);
	FIGCONE_PARAM(branch, std::optional<std::string>);
	FIGCONE_PARAMLIST(libs, std::optional<std::vector<std::string>>);
	FIGCONE_PARAM(buildsystem, std::optional<std::string>);
	FIGCONE_PARAMLIST(buildArgs, std::optional<std::vector<std::string>>);
};

struct ManifestBridges : public figcone::Config {
	FIGCONE_PARAMLIST(uses, std::optional<std::vector<std::string>>);
	FIGCONE_PARAMLIST(implements, std::optional<std::vector<std::string>>);
};

struct ManifestTarget : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, std::optional<std::string>);
	FIGCONE_NODELIST(profiles, std::optional<std::vector<ManifestProfile>>);
	FIGCONE_PARAM(type, std::optional<std::string>);
	FIGCONE_PARAM(language, std::optional<std::string>);
	FIGCONE_PARAM(toolchain, std::optional<std::string>);
	FIGCONE_PARAMLIST(sources, std::optional<std::vector<std::string>>);
	FIGCONE_PARAMLIST(includeDirs, std::optional<std::vector<std::string>>);
	FIGCONE_PARAMLIST(link, std::optional<std::vector<std::string>>);
	FIGCONE_PARAM(intDir, std::optional<std::string>);
	FIGCONE_PARAM(outDir, std::optional<std::string>);
	FIGCONE_NODE(bridges, std::optional<ManifestBridges>);
};

struct ManifestProject : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, std::optional<std::string>);
	FIGCONE_NODELIST(profiles, std::optional<std::vector<ManifestProfile>>);
	FIGCONE_PARAMLIST(dependsOn, std::optional<std::vector<std::string>>);
	FIGCONE_NODELIST(externalDependencies, std::optional<std::vector<ManifestExternalDependencies>>);
	FIGCONE_PARAM(startupTarget, std::optional<std::string>);
	FIGCONE_NODELIST(targets, std::optional<std::vector<ManifestTarget>>);
};

struct ManifestAutomation : public figcone::Config {
	FIGCONE_PARAM(script, std::optional<std::string>);
	FIGCONE_DICT(hooks, std::optional<MapStrStr>);
	FIGCONE_DICT(actions, std::optional<MapStrStr>);
};

struct ManifestWorkspace : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_PARAM(name, std::optional<std::string>);
	FIGCONE_NODELIST(profiles, std::optional<std::vector<ManifestProfile>>);
	FIGCONE_PARAM(defaultProfile, std::optional<std::string>);
	FIGCONE_PARAM(startupProject, std::optional<std::string>);
	FIGCONE_NODELIST(projects, std::vector<ManifestProject>);
	FIGCONE_NODE(automation, std::optional<ManifestAutomation>);
};

struct ManifestRoot : public figcone::Config {
	MANIFEST_COMMON;
	FIGCONE_NODELIST(profiles, std::optional<std::vector<ManifestProfile>>);
	FIGCONE_PARAM(schemaVersion, std::optional<int>);
	FIGCONE_PARAMLIST(includes, std::optional<std::vector<std::string>>);
	FIGCONE_NODE(workspace, std::optional<ManifestWorkspace>);
};
