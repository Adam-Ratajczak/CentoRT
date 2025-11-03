#pragma once
#include "ManifestObjects.hpp"
#include "ITarget.hpp"
#include <memory>

class ITargetRegistryEntry {
public:
	virtual std::unique_ptr<ITarget> Create(const ManifestObjects::ManifestCommon* manifest) const = 0;
	virtual std::string GetClassName() const = 0;
};

template<typename ManifestType, typename TargetType>
class TargetRegistryEntry : public ITargetRegistryEntry {
	TargetFactory<ManifestType, TargetType> _factory;
public:
	std::unique_ptr<ITarget> Create(const ManifestObjects::ManifestCommon* manifest) const override {
		return _factory.Create(static_cast<const ManifestType*>(manifest));
	}

	std::string GetClassName() const override {
		return TargetType::StaticClassName;
	}
};

class TargetRegistry {
public:
	TargetRegistry();

	std::unique_ptr<ITarget> Create(const std::string& className, const ManifestObjects::ManifestCommon* manifest) const;

private:
	void Init();

	std::vector<std::unique_ptr<ITargetRegistryEntry>> _entries;
};
