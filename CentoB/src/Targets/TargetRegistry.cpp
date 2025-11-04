#include "TargetRegistry.hpp"
#include "ManifestObjects.hpp"

#include "AutomationTarget.hpp"
#include "CppNinjaGccTarget.hpp"
#include "CsDotnetTarget.hpp"
#include "ExternalDependencyTarget.hpp"
#include "GoGoTarget.hpp"
#include "RsCargoTarget.hpp"

TargetRegistry::TargetRegistry() {
	Init();
}

std::unique_ptr<ITarget> TargetRegistry::Create(const std::string& className, const ManifestObjects::ManifestCommon* manifest) const {
	for (const auto& entry : _entries) {
		if (entry->GetClassName() == className) {
			return entry->Create(manifest);
		}
	}

	return nullptr;
}

void TargetRegistry::Init() {
	_entries.emplace_back(std::make_unique<TargetRegistryEntry<ManifestObjects::ManifestAutomation, AutomationTarget>>());
	_entries.emplace_back(std::make_unique<TargetRegistryEntry<ManifestObjects::ManifestTarget, CppNinjaGccTarget>>());
	_entries.emplace_back(std::make_unique<TargetRegistryEntry<ManifestObjects::ManifestTarget, CsDotnetTarget>>());
	_entries.emplace_back(std::make_unique<TargetRegistryEntry<ManifestObjects::ManifestExternalDependency, ExternalDependencyTarget>>());
	_entries.emplace_back(std::make_unique<TargetRegistryEntry<ManifestObjects::ManifestTarget, GoGoTarget>>());
	_entries.emplace_back(std::make_unique<TargetRegistryEntry<ManifestObjects::ManifestTarget, RsCargoTarget>>());
}
