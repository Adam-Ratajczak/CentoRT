#pragma once
#include "ManifestObjects.hpp"

struct BridgesStruct {
	std::vector<std::filesystem::path> Uses;
	std::vector<std::filesystem::path> Implements;
};

struct TargetStruct {
	std::string Name;
	bool Default;
	std::string Type;
	std::string Language;
	std::string Toolchain;
	std::vector<std::string> Link;
	std::vector<std::filesystem::path> Sources;
	std::vector<std::filesystem::path> IncludeDirs;
	std::vector<std::string> CompilerOptions;
	std::filesystem::path IntDir;
	std::filesystem::path OutDir;
	std::vector<BridgesStruct> Bridges;
};

struct ExternalDependenciesStruct {
	std::string Name;
	std::string Toolchain;
	std::vector<std::string> ResolveFirst;
	std::optional<std::string> Version;
	std::optional<std::string> Url;
	std::optional<std::string> Branch;
	std::optional<std::string> BuildSystem;
	std::optional<std::vector<std::string>> BuildArgs;
};

struct ProjectStruct {
	std::string Name;
	bool Default;
	std::vector<TargetStruct> Targets;
	std::vector<ExternalDependenciesStruct> ExternalDependencies;
};

struct AutomationStruct {
	std::filesystem::path Script;
	std::map<std::string, std::string> Hooks;
	std::map<std::string, std::string> Actions;
};

struct WorkspaceStruct {
	std::string Name;
	bool Default;
	std::vector<ProjectStruct> Projects;
	std::optional<AutomationStruct> Automation;
};

void ResolveTargetObjects(const ManifestRoot& root, std::vector<WorkspaceStruct>& resolvedWorkspaces);
