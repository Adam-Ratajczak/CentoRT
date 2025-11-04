#pragma once
#include <filesystem>
#include <vector>
#include <map>
#include <string>

enum class EOrder {
	PREGEN = 0,
	GEN,
	POSTGEN,
	PREBUILD,
	BUILD,
	POSTBUILD
};

class ITask {
public:
	virtual bool Execute() const = 0;
	virtual void Dump() const = 0;

	virtual EOrder GetOrder() const = 0;
};
