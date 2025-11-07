#include "Register.h"
#include "RuntimeObject.hpp"
#include "CentoCommon.hpp"

void libcento_init(size_t hash) {
	CentoCommon::Singleton<RuntimeObject>::GetInstance()->LoadModule(hash);
}

void libcento_exit(size_t hash) {
	CentoCommon::Singleton<RuntimeObject>::GetInstance()->UnloadModule(hash);
}
