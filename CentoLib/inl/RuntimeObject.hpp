#pragma once
#include <CentoCommon.hpp>

class RuntimeObject {
	CentoCommon::DllFile _dll;
public:
	RuntimeObject();
	~RuntimeObject();

	void LoadModule(_cento_string_def* identifier);
	void UnloadModule(_cento_string_def* identifier);
};