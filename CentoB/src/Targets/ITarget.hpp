#pragma once
#include <Tasks/ITask.hpp>
#include <memory>
#include <vector>
#include <exception>

class ITarget {
public:
	virtual void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const = 0;
	virtual void Dump() const = 0;
};

template<typename ManifestType, typename TargetType>
class TargetFactory {
public:
	std::unique_ptr<TargetType> Create(const ManifestType* manifest) const {
		//throw std::runtime_error("Unimplemented TargetFactory");

		return nullptr;
	}
};
