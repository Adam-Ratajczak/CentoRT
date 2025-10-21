#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class GoTargetObject : public ITargetObject {
public:
	GoTargetObject(const ManifestTarget& target);

	void Dump() const override;
};
