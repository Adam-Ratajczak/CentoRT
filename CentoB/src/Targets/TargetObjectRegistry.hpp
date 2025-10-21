#pragma once
#include "ManifestObjects.hpp"
#include "ITargetObject.hpp"
#include <memory>

class ITargetObjectRegistryEntry {
public:
	virtual std::unique_ptr<ITargetObject> Create(const ManifestCommon* manifest) const = 0;
	virtual std::string GetClassName() const = 0;
};

template<typename ManifestType, typename TargetType>
class TargetObjectRegistryEntry : public ITargetObjectRegistryEntry {
	TargetObjectFactory<ManifestType, TargetType> _factory;
public:
	std::unique_ptr<ITargetObject> Create(const ManifestCommon* manifest) const override {
		return _factory.Create(static_cast<const ManifestType*>(manifest));
	}

	std::string GetClassName() const override {
		return TargetType::StaticClassName;
	}
};

class TargetObjectRegistry {
public:
	TargetObjectRegistry();

	std::unique_ptr<ITargetObject> Create(const std::string& className, const ManifestCommon* manifest) const;

private:
	void Init();

	std::vector<std::unique_ptr<ITargetObjectRegistryEntry>> _entries;
};
