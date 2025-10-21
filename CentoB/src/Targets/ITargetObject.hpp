#pragma once
#include <Tasks/ITask.hpp>
#include <memory>
#include <vector>

class ITargetObject {
public:
	virtual void FetchTasks(std::vector<ITask>& tasks) const = 0;
	virtual void Dump() const = 0;
};