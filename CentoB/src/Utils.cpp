#include "Utils.hpp"
#include "WildcardsShim.hpp"

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

}
