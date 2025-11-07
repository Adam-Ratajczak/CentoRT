#include "Register.h"
#include "RuntimeObject.hpp"
#include "CentoCommon.hpp"

void libcento_init(const char* id, size_t idsize) {
	_cento_string_def strdef;
	strdef.cData = id;
	strdef.cSize = idsize;
	CentoCommon::Singleton<RuntimeObject>::GetInstance()->LoadModule(&strdef);
}

void libcento_exit(const char* id, size_t idsize) {
	_cento_string_def strdef;
	strdef.cData = id;
	strdef.cSize = idsize;
	CentoCommon::Singleton<RuntimeObject>::GetInstance()->UnloadModule(&strdef);
}
