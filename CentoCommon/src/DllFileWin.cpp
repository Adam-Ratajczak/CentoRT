#include "DllFile.hpp"
#include <windows.h>
#include <stdexcept>

struct CentoCommon::DllFile::Impl {
    HMODULE handle;

    Impl(const std::filesystem::path& p) {
        handle = LoadLibraryW(p.wstring().c_str());
        if (!handle)
            throw std::runtime_error("Failed to load DLL");
    }

    ~Impl() {
        if (handle)
            FreeLibrary(handle);
    }

    void* GetFunction(const std::string& name) const {
        auto f = GetProcAddress(handle, name.c_str());
        if (!f)
            throw std::runtime_error("Symbol not found");
        return reinterpret_cast<void*>(f);
    }
};

CentoCommon::DllFile::DllFile(const std::filesystem::path& path)
    : _impl(std::make_unique<Impl>(path)) {
}

CentoCommon::DllFile::~DllFile() = default;

void* CentoCommon::DllFile::GetFunction(const std::string& name) const {
    return _impl->GetFunction(name);
}
