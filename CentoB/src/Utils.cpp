#include "Utils.hpp"
#include "WildcardsShim.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

namespace Utils {
    void ExpandGlob(const std::string& pattern,
        const std::filesystem::path& dirToSearch,
        std::vector<std::filesystem::path>& paths)
    {
        paths.clear();

        const auto base = std::filesystem::weakly_canonical(dirToSearch);
        for (const auto& de : std::filesystem::recursive_directory_iterator(base)) {
            const auto p = de.path();

            const auto rel = std::filesystem::relative(p, base);
            if (wildcards::match(rel.generic_string(), pattern)) {
                paths.emplace_back(rel);
            }
        }
    }

    static inline void TrimInPlace(std::string& s) {
        auto not_space = [](unsigned char ch) { return !std::isspace(ch); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
        s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    }

    std::map<std::string, std::string> ParseEnvFile(const std::filesystem::path& path) {
        std::map<std::string, std::string> out;

        std::ifstream in(path);
        if (!in) return out;

        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();

            std::string view = line;
            TrimInPlace(view);
            if (view.empty() || view.front() == '#') continue;

            auto pos = view.find('=');
            if (pos == std::string::npos) continue;

            std::string key = view.substr(0, pos);
            std::string val = view.substr(pos + 1);

            TrimInPlace(key);
            TrimInPlace(val);

            if (!key.empty()) out[key] = val;
        }

        return out;
    }

    bool IsWeaklyCanonical(const std::filesystem::path& p) {
        std::error_code ec;
        std::filesystem::path c = std::filesystem::weakly_canonical(p, ec);
        if (ec) return false;
        return p == c;
    }
    
    bool Match(const std::string& sequence, const std::string& pattern) {
        return wildcards::match(sequence, pattern);
    }

}
