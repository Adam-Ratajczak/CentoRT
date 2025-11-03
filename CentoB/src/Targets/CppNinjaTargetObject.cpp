#include "CppNinjaTargetObject.hpp"
#include <iostream>

std::string CppNinjaTargetObject::StaticClassName = "cpp:ninja";

CppNinjaTargetObject::CppNinjaTargetObject(const ManifestTarget& target) : CppTargetObject(target) {

}

void CppNinjaTargetObject::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	CppTargetObject::Dump();
}

void CppNinjaTargetObject::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {

}
