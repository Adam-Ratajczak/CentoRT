#include "DllFile.hpp"
#include <dlfcn.h>
#include <stdexcept>

struct CentoCommon::DllFile::Impl {
    void* handle;
    Impl(const std::filesystem::path& p) {
        handle = dlopen(p.c_str(), RTLD_NOW);
        if (!handle) throw std::runtime_error(dlerror());
    }
    ~Impl() { if (handle) dlclose(handle); }

    template<typename Ret, typename... Args>
    Ret ExecFunction(const std::string& name, Args... args) const {
        auto f = reinterpret_cast<Ret(*)(Args...)>(dlsym(handle, name.c_str()));
        if (!f) throw std::runtime_error("Symbol not found");
        return f(std::forward<Args>(args)...);
    }
};

CentoCommon::DllFile::DllFile(const std::filesystem::path& path)
    : _impl(new Impl(path)) {
}

CentoCommon::DllFile::~DllFile() = default;
