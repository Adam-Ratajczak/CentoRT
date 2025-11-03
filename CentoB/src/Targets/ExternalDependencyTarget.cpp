#include "ExternalDependencyTarget.hpp"
#include <iostream>

std::string ExternalDependencyTarget::StaticClassName = "external";

ExternalDependencyTarget::ExternalDependencyTarget(const ManifestObjects::ManifestExternalDependency& externalDependency) {

}

void ExternalDependencyTarget::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {
	std::cout << "=== " << StaticClassName << " ===\n";
}

void ExternalDependencyTarget::Dump() const {

}
