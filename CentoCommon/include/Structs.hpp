#pragma once

typedef struct _cento_string_def {
	const char* cData;
	size_t cSize;
} _cento_string_def;

typedef enum _cento_enum_def {
	CENTO_VOID = 0,
	CENTO_U8,
	CENTO_S8,
	CENTO_U16,
	CENTO_S16,
	CENTO_U32,
	CENTO_S32,
	CENTO_U64,
	CENTO_S64,
	CENTO_F32,
	CENTO_F64,
	CENTO_PTR,
};

typedef struct _cento_value_def {
	union {
		uint8_t cU8;
		int8_t cS8;
		uint16_t cU16;
		int16_t cS16;
		uint32_t cU32;
		int32_t cS32;
		uint64_t cU64;
		int64_t cS64;
		float cF32;
		double cF64;
		void* cPtr;
	} cValue;

	_cento_enum_def cType;
} _cento_value_def;

typedef struct _cento_result_def {
	_cento_value_def cResult;
	int cErrorCode;
	_cento_string_def cErrorMsg;
} _cento_result_def;
