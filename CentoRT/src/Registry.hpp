#pragma once
#include <string>
#include <vector>
#include <ffi.h>
#include "CentoCommon.hpp"

class Functor {
public:
	Functor(const std::string& name, void (*func_ptr)(void), _cento_enum_def ret_type, const std::vector<_cento_enum_def>& arg_types);

	void Invoke(const std::vector<_cento_value_def>& args, _cento_result_def* ret);
private:
	static ffi_type* GetTypeFromEnum(_cento_enum_def type);
	static void* GetArgFromStruct(const _cento_value_def& val);

	std::string _name;
	void (*_func_ptr)(void);
	ffi_cif _cif;
};

class Registry {

};
