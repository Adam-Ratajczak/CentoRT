#include "RsCargoTargetObject.hpp"
#include <iostream>

std::string RsCargoTargetObject::StaticClassName = "rs:cargo";

RsCargoTargetObject::RsCargoTargetObject(const ManifestTarget& target) : RsTargetObject(target) {

}

void RsCargoTargetObject::Dump() const {
	std::cout << "=== " << StaticClassName << " ===\n";
	RsTargetObject::Dump();
}

void RsCargoTargetObject::FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const {

}
