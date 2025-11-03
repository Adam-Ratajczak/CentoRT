#pragma once
#include "ITask.hpp"

class AutomationTask : public ITask {
public:
	AutomationTask(const std::filesystem::path& script, const std::string& funcName, EOrder order)
		: _script{ script }
		, _funcName{ funcName }
		, _order{ order } { }

	void Execute() const override;
	void Dump() const override;
	EOrder GetOrder() const override { return _order; }

private:
	std::string GetOrderString() const;

	std::filesystem::path _script;
	std::string _funcName;
	EOrder _order;
};
