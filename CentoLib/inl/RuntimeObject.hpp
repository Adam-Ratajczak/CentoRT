#pragma once
#include <CentoCommon.hpp>

class RuntimeObject {
	CentoCommon::DllFile _dll;
public:
	RuntimeObject();

	void LoadModule(int hash);
	void UnloadModule(int hash);
};