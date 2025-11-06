#pragma once
#include "../ITask.hpp"

class GenCargoTask : public ITask {
public:
	GenCargoTask(const std::filesystem::path& intdir, const std::vector<std::filesystem::path>& sources, const std::string& name, const std::string& version, const std::string& edition, const std::vector<std::string>& crateType, const std::vector<std::string>& options)
		: _intdir{ intdir }
		, _sources{ sources }
		, _name{ name }
		, _version{ version }
		, _edition{ edition }
		, _crateType{ crateType }
		, _options{ options }{ }

	bool Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return EOrder::POSTGEN; }

private:
	std::filesystem::path _intdir;
	std::vector<std::filesystem::path> _sources;
	std::string _name;  
	std::string _version;  
	std::string _edition;  
	std::vector<std::string> _crateType; 
	std::vector<std::string> _options;
};
