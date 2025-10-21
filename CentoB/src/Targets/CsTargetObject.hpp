#pragma once
#include "ITargetObject.hpp"
#include "ManifestObjects.hpp"

class CsTargetObject : public ITargetObject {
public:
	CsTargetObject(const ManifestTarget& automation);

	void Dump() const override;
};
