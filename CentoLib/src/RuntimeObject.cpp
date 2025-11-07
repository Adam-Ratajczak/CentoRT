#include "RuntimeObject.hpp"

RuntimeObject::RuntimeObject() : _dll{ "CentoRT.dll" } {

}

void RuntimeObject::LoadModule(size_t hash) {
	_dll.ExecFunction<void>("LoadModule", hash);
}

void RuntimeObject::UnloadModule(size_t hash) {
	_dll.ExecFunction<void>("UnloadModule", hash);
}
