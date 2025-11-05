#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <optional>

class NinjaGenerator {
public:
	NinjaGenerator() = default;

	void Init(const std::string& name, const std::string& compiler, const std::vector<std::filesystem::path>& sources, const std::vector<std::string>& compilerOptions, const std::vector<std::string>& linkerOptions, bool staticlib);
	bool SaveToFile(const std::filesystem::path& path) const;

private:
	struct Rule {
		std::string name;
		std::string command;
		std::string description;
		std::string depfile;
		std::string deps;
		std::string rspfile;
		std::string rspfile_content;
		std::string pool;
		bool restat = false;
		bool generator = false;
	};

	struct BuildEdge {
		std::vector<std::string> outputs;
		std::string rule_name;
		std::vector<std::string> explicit_inputs;
		std::vector<std::string> implicit_inputs;
		std::vector<std::string> order_only_inputs;
		std::vector<std::pair<std::string, std::string>> variables;
	};

	std::map<std::string, std::string> _vars;
	std::vector<Rule> _rules;
	std::vector<BuildEdge> _buildEdges;

};
