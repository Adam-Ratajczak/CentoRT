#pragma once
#include <string>
#include <filesystem>
#include <memory>
#include <utility>
#include "Export.hpp"

namespace CentoCommon {
    class DllFile {
        struct Impl;
        std::unique_ptr<Impl> _impl;

    public:
        explicit DllFile(const std::filesystem::path& path);
        ~DllFile();

        template<typename Ret, typename... Args>
        Ret ExecFunction(const std::string& name, Args&&... args) const {
            using FuncType = Ret(*)(Args...);
            auto f = reinterpret_cast<FuncType>(GetFunction(name));
            if (!f)
                throw std::runtime_error("Function not found");
            return f(std::forward<Args>(args)...);
        }

    private:
        void* GetFunction(const std::string& name) const;
    };
}
