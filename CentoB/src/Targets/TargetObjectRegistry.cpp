#include "TargetObjectRegistry.hpp"
#include "ManifestObjects.hpp"

#include "AutomationTargetObject.hpp"
#include "CppNinjaTargetObject.hpp"
#include "CsDotnetTargetObject.hpp"
#include "ExternalDependencyTargetObject.hpp"
#include "GoGoTargetObject.hpp"
#include "RsCargoTargetObject.hpp"

TargetObjectRegistry::TargetObjectRegistry() {
	Init();
}

std::unique_ptr<ITargetObject> TargetObjectRegistry::Create(const std::string& className, const ManifestCommon* manifest) const {
	for (const auto& entry : _entries) {
		if (entry->GetClassName() == className) {
			return entry->Create(manifest);
		}
	}

	return nullptr;
}

void TargetObjectRegistry::Init() {
	_entries.emplace_back(std::make_unique<TargetObjectRegistryEntry<ManifestAutomation, AutomationTargetObject>>());
	_entries.emplace_back(std::make_unique<TargetObjectRegistryEntry<ManifestTarget, CppNinjaTargetObject>>());
	_entries.emplace_back(std::make_unique<TargetObjectRegistryEntry<ManifestTarget, CsDotnetTargetObject>>());
	_entries.emplace_back(std::make_unique<TargetObjectRegistryEntry<ManifestExternalDependency, ExternalDependencyTargetObject>>());
	_entries.emplace_back(std::make_unique<TargetObjectRegistryEntry<ManifestTarget, GoGoTargetObject>>());
	_entries.emplace_back(std::make_unique<TargetObjectRegistryEntry<ManifestTarget, RsCargoTargetObject>>());
}
