#include "CsDotnetTargetObject.hpp"

std::string CsDotnetTargetObject::StaticClassName = "cs:dotnet";

CsDotnetTargetObject::CsDotnetTargetObject(const ManifestTarget& target) : CsTargetObject(target) {

}

void CsDotnetTargetObject::FetchTasks(std::vector<ITask>& tasks) const {

}
