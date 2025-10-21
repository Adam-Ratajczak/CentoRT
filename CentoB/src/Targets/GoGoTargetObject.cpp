#include "GoGoTargetObject.hpp"

std::string GoGoTargetObject::StaticClassName = "go:go";

GoGoTargetObject::GoGoTargetObject(const ManifestTarget& target) : GoTargetObject(target) {

}

void GoGoTargetObject::FetchTasks(std::vector<ITask>& tasks) const {

}
