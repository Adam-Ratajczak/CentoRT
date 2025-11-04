#include "NinjaGenerator.hpp"
#include <fstream>

void NinjaGenerator::Init(const std::string& compiler,
    const std::vector<std::filesystem::path>& sources,
    const std::vector<std::string>& compilerOptions,
    const std::vector<std::string>& linkerOptions, 
    const std::string& name)
{
    _vars.clear();
    _rules.clear();
    _buildEdges.clear();

    _vars["cc"] = compiler;
    _vars["srcs"] = "";
    _vars["objs"] = "";
    _vars["cflags"] = "";
    _vars["ldflags"] = "";

    std::vector<std::string> objectPaths;
    for (const auto& source : sources) {
        std::string src = source.string();
        std::string base = src.substr(0, src.rfind("."));
        std::string obj = base + ".o";
        objectPaths.push_back(obj);

        _vars["srcs"] += "\"" + src + "\" ";
        _vars["objs"] += "\"" + obj + "\" ";
    }

    for (const auto& compilerOption : compilerOptions)
        _vars["cflags"] += compilerOption + " ";

    for (const auto& linkerOption : linkerOptions)
        _vars["ldflags"] += linkerOption + " ";

    _rules.emplace_back(Rule{
        .name = "cc",
        .command = "$cc -MMD -MF $out.d $cflags -fPIC -c $in -o $out",
        .description = "CC $out",
        .depfile = "$out.d",
        .deps = "gcc",
        });

    _rules.emplace_back(Rule{
        .name = "link",
        .command = "$cc $in -o $out $ldflags",
        .description = "LINK $out",
        });

    _rules.emplace_back(Rule{
        .name = "mkdir",
        .command = "mkdir -p $out",
        .description = "MKDIR $out",
        });

    _buildEdges.push_back(BuildEdge{
        .outputs = {"obj/"},
        .rule_name = "mkdir"
        });

    for (size_t i = 0; i < sources.size(); ++i) {
        BuildEdge edge;
        edge.outputs = { objectPaths[i] };
        edge.rule_name = "cc";
        edge.explicit_inputs = { sources[i].string() };
        edge.order_only_inputs = { "obj/" };
        _buildEdges.push_back(std::move(edge));
    }

    BuildEdge linkEdge;
    linkEdge.outputs = { name };
    linkEdge.rule_name = "link";
    linkEdge.explicit_inputs = objectPaths;
    _buildEdges.push_back(std::move(linkEdge));
}

bool NinjaGenerator::SaveToFile(const std::filesystem::path& path) const {
	std::ofstream f_out(path);
    if (!f_out.is_open())
        return false;

    for (const auto& [key, value] : _vars) {
        f_out << key << " = " << value << "\n";
    }
    f_out << "\n";

    for (const auto& rule : _rules) {
        if(!rule.name.empty())
            f_out << "rule " << rule.name << "\n";

        if (!rule.command.empty())
            f_out << "\tcommand = " << rule.command << "\n";

        if (!rule.description.empty())
            f_out << "\tdescription = " << rule.description << "\n";

        if (!rule.depfile.empty())
            f_out << "\tdepfile = " << rule.depfile << "\n";

        if (!rule.deps.empty())
            f_out << "\tdeps = " << rule.deps << "\n";

        if (!rule.rspfile.empty())
            f_out << "\trspfile = " << rule.rspfile << "\n";

        if (!rule.rspfile_content.empty())
            f_out << "\trspfile_content = " << rule.rspfile_content << "\n";

        if (!rule.pool.empty())
            f_out << "\tpool = " << rule.pool << "\n";

        if (rule.restat)
            f_out << "\trestat = 1\n";

        if (rule.generator)
            f_out << "\tgenerator = 1\n";

        f_out << "\n";
    }

    for (const auto& edge : _buildEdges) {
        f_out << "build ";
        for (const auto& out : edge.outputs)
            f_out << out << " ";
        f_out << ": " << edge.rule_name << " ";

        for (const auto& in : edge.explicit_inputs)
            f_out << in << " ";

        if (!edge.implicit_inputs.empty()) {
            f_out << "| ";
            for (const auto& imp : edge.implicit_inputs)
                f_out << imp << " ";
        }

        if (!edge.order_only_inputs.empty()) {
            f_out << "|| ";
            for (const auto& ord : edge.order_only_inputs)
                f_out << ord << " ";
        }

        f_out << "\n";

        for (const auto& [var, val] : edge.variables)
            f_out << "  " << var << " = " << val << "\n";

        f_out << "\n";
    }

    f_out.close();

    return true;
}
