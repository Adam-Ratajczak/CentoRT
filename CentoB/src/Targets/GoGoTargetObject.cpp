#include "GoGoTargetObject.hpp"
#include <iostream>

std::string GoGoTargetObject::StaticClassName = "go:go";

GoGoTargetObject::GoGoTargetObject(const ManifestTarget& target) : GoTargetObject(target) {

}

void GoGoTargetObject::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	GoTargetObject::Dump();
}

void GoGoTargetObject::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {

}
