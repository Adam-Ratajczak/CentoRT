#include "RuntimeObject.hpp"

RuntimeObject::RuntimeObject() : _dll{ "CentoRT.dll" } {

}

void RuntimeObject::LoadModule(size_t hash) {
	_dll.ExecFunction<void>("LoadModule", (int)hash);
}

void RuntimeObject::UnloadModule(size_t hash) {
	_dll.ExecFunction<void>("UnloadModule", (int)hash);
}
