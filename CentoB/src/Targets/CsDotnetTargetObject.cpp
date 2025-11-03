#include "CsDotnetTargetObject.hpp"
#include <iostream>

std::string CsDotnetTargetObject::StaticClassName = "cs:dotnet";

CsDotnetTargetObject::CsDotnetTargetObject(const ManifestTarget& target) : CsTargetObject(target) {

}

void CsDotnetTargetObject::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	CsTargetObject::Dump();
}

void CsDotnetTargetObject::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {

}
