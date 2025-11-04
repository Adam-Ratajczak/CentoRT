#pragma once
#include "BuildTarget.hpp"
#include "ManifestObjects.hpp"

class CppNinjaGccTarget : public BuildTarget {
public:
	static std::string StaticClassName;
	CppNinjaGccTarget(const ManifestObjects::ManifestTarget& target);

	void Dump() const override;
	void FetchTasks(std::vector<std::unique_ptr<ITask>>& tasks) const override;
};

template<>
class TargetFactory<ManifestObjects::ManifestTarget, CppNinjaGccTarget> {
public:
	std::unique_ptr<CppNinjaGccTarget> Create(const ManifestObjects::ManifestTarget* target) const {
		if (target) {
			return std::make_unique<CppNinjaGccTarget>(*target);
		}
		return nullptr;
	}
};
