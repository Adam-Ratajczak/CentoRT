#include "Register.h"
#include "RuntimeObject.hpp"
#include "CentoCommon.hpp"

void libcento_init(int hash) {
	CentoCommon::Singleton<RuntimeObject>::GetInstance()->LoadModule(hash);
}

void libcento_exit(int hash) {
	CentoCommon::Singleton<RuntimeObject>::GetInstance()->UnloadModule(hash);
}
