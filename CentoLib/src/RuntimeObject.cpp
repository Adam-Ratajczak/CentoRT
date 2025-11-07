#include "RuntimeObject.hpp"

RuntimeObject::RuntimeObject() : _dll{ "CentoRT.dll" } {
	_dll.ExecFunction<void>("Initialize");
}

RuntimeObject::~RuntimeObject() {
	_dll.ExecFunction<void>("Shutdown");
}

void RuntimeObject::LoadModule(_cento_string_def* identifier) {
	_dll.ExecFunction<void>("LoadModule", identifier);
}

void RuntimeObject::UnloadModule(_cento_string_def* identifier) {
	_dll.ExecFunction<void>("UnloadModule", identifier);
}
