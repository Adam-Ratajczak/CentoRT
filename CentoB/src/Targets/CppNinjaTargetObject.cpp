#include "CppNinjaTargetObject.hpp"

std::string CppNinjaTargetObject::StaticClassName = "cpp:ninja";

CppNinjaTargetObject::CppNinjaTargetObject(const ManifestTarget& target) : CppTargetObject(target) {

}

void CppNinjaTargetObject::FetchTasks(std::vector<ITask>& tasks) const {

}
