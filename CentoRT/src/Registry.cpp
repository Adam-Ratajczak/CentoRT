#include "Registry.hpp"

Functor::Functor(const std::string& name, void (*func_ptr)(void), _cento_enum_def ret_type, const std::vector<_cento_enum_def>& arg_types) {
	_name = name;
	_func_ptr = func_ptr;

	ffi_type** atypes = NULL;

	ffi_type* rtype = GetTypeFromEnum(ret_type);

	if (!arg_types.empty()) {
		atypes = new ffi_type * [arg_types.size()];
		for (size_t i = 0; i < arg_types.size(); i++) {
			atypes[i] = GetTypeFromEnum(arg_types[i]);
		}
	}

	ffi_prep_cif(&_cif, FFI_DEFAULT_ABI, arg_types.size(), rtype, atypes);
}

void Functor::Invoke(const std::vector<_cento_value_def>& args, _cento_result_def* ret) {
	void** avalue = NULL;
	void* rvalue = GetArgFromStruct(ret->cResult);

	if (!args.empty()) {
		avalue = new void*[args.size()];
		for (size_t i = 0; i < args.size(); i++) {
			avalue[i] = GetArgFromStruct(args[i]);
		}
	}

	ffi_call(&_cif, _func_ptr, rvalue, avalue);
	switch (ret->cResult.cType) {
	case CENTO_U8:
		ret->cResult.cValue.cU8 = *(uint8_t*)rvalue;
		break;
	case CENTO_S8:
		ret->cResult.cValue.cS8 = *(int8_t*)rvalue;
		break;
	case CENTO_U16:
		ret->cResult.cValue.cU16 = *(uint16_t*)rvalue;
		break;
	case CENTO_S16:
		ret->cResult.cValue.cS16 = *(int16_t*)rvalue;
		break;
	case CENTO_U32:
		ret->cResult.cValue.cU32 = *(uint32_t*)rvalue;
		break;
	case CENTO_S32:
		ret->cResult.cValue.cS32 = *(int32_t*)rvalue;
		break;
	case CENTO_U64:
		ret->cResult.cValue.cU64 = *(int64_t*)rvalue;
		break;
	case CENTO_S64:
		ret->cResult.cValue.cS64 = *(int64_t*)rvalue;
		break;
	case CENTO_F32:
		ret->cResult.cValue.cF32 = *(float*)rvalue;
		break;
	case CENTO_F64:
		ret->cResult.cValue.cF64 = *(double*)rvalue;
		break;
	case CENTO_PTR:
		ret->cResult.cValue.cPtr = (void*)*(size_t*)rvalue;
		break;
	default:
		break;
	}
	delete rvalue;

	for (size_t i = 0; i < args.size(); i++) {
		delete avalue[i];
	}
	delete[] avalue;


}

ffi_type* Functor::GetTypeFromEnum(_cento_enum_def type) {
	switch (type) {
	case CENTO_VOID:
		return &ffi_type_void;
	case CENTO_U8:
		return &ffi_type_uint8;
	case CENTO_S8:
		return &ffi_type_sint8;
	case CENTO_U16:
		return &ffi_type_uint16;
	case CENTO_S16:
		return &ffi_type_sint16;
	case CENTO_U32:
		return &ffi_type_uint32;
	case CENTO_S32:
		return &ffi_type_sint32;
	case CENTO_U64:
		return &ffi_type_uint64;
	case CENTO_S64:
		return &ffi_type_sint64;
	case CENTO_F32:
		return &ffi_type_float;
	case CENTO_F64:
		return &ffi_type_double;
	case CENTO_PTR:
		return &ffi_type_pointer;
	}
}

void* Functor::GetArgFromStruct(const _cento_value_def& val) {
	void* data = NULL;
	switch (val.cType) {
	case CENTO_U8: {
		auto* u8 = new uint8_t;
		*u8 = val.cValue.cU8;
		data = u8;
		break;
	}
	case CENTO_S8: {
		auto* s8 = new int8_t;
		*s8 = val.cValue.cS8;
		data = s8;
		break;
	}
	case CENTO_U16: {
		auto* u16 = new uint16_t;
		*u16 = val.cValue.cU16;
		data = u16;
		break;
	}
	case CENTO_S16: {
		auto* s16 = new int16_t;
		*s16 = val.cValue.cS16;
		data = s16;
		break;
	}
	case CENTO_U32: {
		auto* u32 = new uint32_t;
		*u32 = val.cValue.cU32;
		data = u32;
		break;
	}
	case CENTO_S32: {
		auto* s32 = new int32_t;
		*s32 = val.cValue.cS32;
		data = s32;
		break;
	}
	case CENTO_U64: {
		auto* u64 = new uint64_t;
		*u64 = val.cValue.cU64;
		data = u64;
		break;
	}
	case CENTO_S64: {
		auto* s64 = new int64_t;
		*s64 = val.cValue.cS64;
		data = s64;
		break;
	}
	case CENTO_F32: {
		auto* f32 = new float;
		*f32 = val.cValue.cF32;
		data = f32;
		break;
	}
	case CENTO_F64: {
		auto* f64 = new double;
		*f64 = val.cValue.cF64;
		data = f64;
		break;
	}
	case CENTO_PTR: {
		auto* ptr = new void*;
		*ptr = val.cValue.cPtr;
		data = ptr;
		break;
	}
	default:
		break;
	}

	return data;
}
