#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class CppTargetObject : public ITargetObject {
public:
	CppTargetObject(const ManifestTarget& target);

	void Dump() const override;
};
