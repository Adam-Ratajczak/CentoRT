#include "RuntimeObject.hpp"

RuntimeObject::RuntimeObject() : _dll{ "CentoRT.dll" } {

}

void RuntimeObject::LoadModule(int hash) {
	_dll.ExecFunction<void>("LoadModule", hash);
}

void RuntimeObject::UnloadModule(int hash) {
	_dll.ExecFunction<void>("UnloadModule", hash);
}
