#include "DotnetGenerator.hpp"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <fstream>

void DotnetGenerator::Init(const std::vector<std::filesystem::path>& sources, const std::vector<std::string>& options) {
	for (const auto& source : sources) {
		_items.emplace_back(std::make_pair("Compile", source.string()));
	}
	for (const auto& option : options) {
		auto loc = option.find("=");
		if (loc == std::string::npos) {
			continue;
		}
        _properties.emplace_back(std::make_pair(option.substr(0, loc), option.substr(loc + 1)));
	}
}

bool DotnetGenerator::SaveToFile(const std::filesystem::path& path) const {
    rapidxml::xml_document<> doc;

    auto* decl = doc.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

    auto* project = doc.allocate_node(rapidxml::node_element, "Project");
    project->append_attribute(doc.allocate_attribute("Sdk", "Microsoft.NET.Sdk"));
    doc.append_node(project);

    auto* propGroup = doc.allocate_node(rapidxml::node_element, "PropertyGroup");
    project->append_node(propGroup);

    for (const auto& [prop, val] : _properties) {
        auto* name = doc.allocate_string(prop.c_str());
        auto* value = doc.allocate_string(val.c_str());

        propGroup->append_node(doc.allocate_node(rapidxml::node_element, name, value));
    }

    auto* itemGroup = doc.allocate_node(rapidxml::node_element, "ItemGroup");
    project->append_node(itemGroup);

    for (const auto& [prop, filePath] : _items) {
        auto* name = doc.allocate_string(prop.c_str());
        auto* include = doc.allocate_string(filePath.c_str());

        auto* compileNode = doc.allocate_node(rapidxml::node_element, name);
        compileNode->append_attribute(doc.allocate_attribute("Include", include));
        itemGroup->append_node(compileNode);
    }

    std::string s;
    rapidxml::print(std::back_inserter(s), doc, 0);

    std::ofstream file(path);
    file << s;
    file.close();

    return true;
}
