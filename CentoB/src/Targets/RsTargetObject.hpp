#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class RsTargetObject : public ITargetObject {
public:
	RsTargetObject(const ManifestTarget& target);

	void Dump() const override;
};
