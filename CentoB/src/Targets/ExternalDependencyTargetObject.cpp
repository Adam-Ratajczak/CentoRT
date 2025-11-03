#include "ExternalDependencyTargetObject.hpp"
#include <iostream>

std::string ExternalDependencyTargetObject::StaticClassName = "external";

ExternalDependencyTargetObject::ExternalDependencyTargetObject(const ManifestExternalDependency& externalDependency) {

}

void ExternalDependencyTargetObject::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::cout << "=== " << StaticClassName << " ===\n";
}

void ExternalDependencyTargetObject::Dump() const {

}
