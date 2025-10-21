#include "RsCargoTargetObject.hpp"

std::string RsCargoTargetObject::StaticClassName = "rs:cargo";

RsCargoTargetObject::RsCargoTargetObject(const ManifestTarget& target) : RsTargetObject(target) {

}

void RsCargoTargetObject::FetchTasks(std::vector<ITask>& tasks) const {

}
