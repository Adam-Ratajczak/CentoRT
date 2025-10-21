#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class ExternalDependencyTargetObject : public ITargetObject {
public:
	static std::string StaticClassName;
	ExternalDependencyTargetObject(const ManifestExternalDependency& externalDependency);

	void FetchTasks(std::vector<ITask>& tasks) const override;
	void Dump() const override;
};

template<>
class TargetObjectFactory<ManifestExternalDependency, ExternalDependencyTargetObject > {
public:
	std::unique_ptr<ExternalDependencyTargetObject> Create(const ManifestExternalDependency* externalDependency) const {
		if (externalDependency) {
			return std::make_unique<ExternalDependencyTargetObject>(*externalDependency);
		}
		return nullptr;
	}
};
