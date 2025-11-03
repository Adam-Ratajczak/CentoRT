#pragma once
#include "ITarget.hpp"
#include "ManifestObjects.hpp"

class ExternalDependencyTarget : public ITarget {
public:
	static std::string StaticClassName;
	ExternalDependencyTarget(const ManifestObjects::ManifestExternalDependency& externalDependency);

	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
	void Dump() const override;
};

template<>
class TargetFactory<ManifestObjects::ManifestExternalDependency, ExternalDependencyTarget > {
public:
	std::unique_ptr<ExternalDependencyTarget> Create(const ManifestObjects::ManifestExternalDependency* externalDependency) const {
		if (externalDependency) {
			return std::make_unique<ExternalDependencyTarget>(*externalDependency);
		}
		return nullptr;
	}
};
