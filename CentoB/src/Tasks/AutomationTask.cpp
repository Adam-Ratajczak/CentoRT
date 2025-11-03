#include "AutomationTask.hpp"
#include <iostream>

void AutomationTask::Execute() const {

}

void AutomationTask::Dump() const {
	std::cout << "=== AutomationTask ===\n";
	std::cout << "script: " << _script << "\n";
	std::cout << "funcName: " << _funcName << "\n";
	std::cout << "order: " << GetOrderString() << "\n";
}

std::string AutomationTask::GetOrderString() const {
	switch (_order)
	{
	case EOrder::PREGEN:
		return "PREGEN";
	case EOrder::GEN:
		return "GEN";
	case EOrder::POSTGEN:
		return "POSTGEN";
	case EOrder::PREBUILD:
		return "PREBUILD";
	case EOrder::BUILD:
		return "BUILD";
	case EOrder::POSTBUILD:
		return "POSTBUILD";
	default:
		return "";
	}
	return "";
}
