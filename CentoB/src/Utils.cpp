#include "Utils.hpp"
#include "WildcardsShim.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <windows.h>

namespace Utils {
    namespace detail {
        inline bool has_wild(const std::string& s) {
            return s.find_first_of("*?[") != std::string::npos;
        }

        inline std::pair<std::filesystem::path, std::filesystem::path> split_at_first_wildcard(const std::filesystem::path& p) {
            std::filesystem::path fixed, tail;
            bool in_tail = false;

            for (const auto& comp : p) {
                if (!in_tail && has_wild(comp.generic_string())) {
                    in_tail = true;
                }
                if (in_tail) {
                    tail /= comp;
                }
                else {
                    fixed /= comp;
                }
            }
            return { fixed, tail };
        }

    } // namespace detail

    void ExpandGlob(const std::string& pattern,
        const std::filesystem::path& dirToSearch,
        std::vector<std::filesystem::path>& paths)
    {
        paths.clear();

        auto has_any_wild = pattern.find_first_of("*?[") != std::string::npos;

        std::filesystem::path pat{ pattern };

        if (!has_any_wild) {
            std::filesystem::path candidate = pat.is_absolute() ? pat : (dirToSearch / pat);
            std::error_code ec;
            auto canon = std::filesystem::weakly_canonical(candidate, ec);
            if (!ec && std::filesystem::exists(canon)) {
                paths.emplace_back(canon);
            }
            return;
        }

        const auto [fixedPrefix, globTail] = detail::split_at_first_wildcard(pat);

        std::filesystem::path searchRoot = pat.is_absolute() ? fixedPrefix : (dirToSearch / fixedPrefix);

        std::error_code ec;
        searchRoot = std::filesystem::weakly_canonical(searchRoot, ec);
        if (ec || !std::filesystem::exists(searchRoot)) {
            return;
        }

        const std::string tailPattern = globTail.generic_string();

        std::filesystem::recursive_directory_iterator it{ searchRoot,
                                             std::filesystem::directory_options::skip_permission_denied,
                                             ec };
        std::filesystem::recursive_directory_iterator end;

        for (; !ec && it != end; ++it) {
            const std::filesystem::directory_entry& de = *it;

            const std::filesystem::path p = de.path();

            std::error_code ecRel;
            std::filesystem::path rel = std::filesystem::relative(p, searchRoot, ecRel);
            if (ecRel) {
                continue;
            }

            const std::string relStr = rel.generic_string();
            if (wildcards::match(relStr, tailPattern)) {
                std::error_code ecCan;
                std::filesystem::path canon = std::filesystem::weakly_canonical(p, ecCan);
                paths.emplace_back(ecCan ? p : canon);
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

    std::string ExpandVarsOnce(const std::string& s, const std::map<std::string, std::string>& vars)
    {
        std::string out;
        out.reserve(s.size());

        std::size_t pos = 0;
        while (pos < s.size()) {
            std::size_t start = s.find("${", pos);
            if (start == std::string::npos) {
                out.append(s, pos, std::string::npos);
                break;
            }

            if (start > 0 && s[start - 1] == '\\') {
                out.append(s, pos, start - 1 - pos);
                out += "${";
                pos = start + 2;
                continue;
            }

            out.append(s, pos, start - pos);

            std::size_t end = s.find('}', start + 2);
            if (end == std::string::npos) {
                out.append(s, start, std::string::npos);
                break;
            }

            std::string key = s.substr(start + 2, end - (start + 2));
            auto it = vars.find(key);
            if (it != vars.end()) {
                out += it->second;
            }
            else {
                out.append(s, start, end - start + 1);
            }

            pos = end + 1;
        }

        return out;
    }

    std::string ExpandVars(std::string s, const std::map<std::string, std::string>& vars, int max_passes)
    {
        for (int i = 0; i < max_passes; ++i) {
            std::string t = ExpandVarsOnce(s, vars);
            if (t == s) break;
            s = std::move(t);
        }
        return s;
    }

    std::filesystem::path GetShellDirectory() {
        char buffer[MAX_PATH];
        DWORD ret = GetCurrentDirectoryA(MAX_PATH, buffer);

        return buffer;
    }

    void ResolvePaths(const std::string& pattern, std::vector<std::filesystem::path>& paths) {
        ExpandGlob(pattern, GetShellDirectory(), paths);
    }
}
