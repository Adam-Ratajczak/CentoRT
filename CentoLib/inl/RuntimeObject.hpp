#pragma once
#include <CentoCommon.hpp>

class RuntimeObject {
	CentoCommon::DllFile _dll;
public:
	RuntimeObject();

	void LoadModule(size_t hash);
	void UnloadModule(size_t hash);
};