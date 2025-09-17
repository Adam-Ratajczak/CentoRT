#include "ArgsResolver.hpp"
#include <iostream>
#include <string>
#include <vector>

struct CommandDef {
	std::string Name;
	size_t MaxArgCount;

	CommandDef(const std::string& name, size_t maxArgCount) : Name{ name }, MaxArgCount{ maxArgCount } {}
};

static std::vector<CommandDef> _commandDefs = {
	CommandDef("Help", {0}),
	CommandDef("Dump", {0, 1}),
};

void ArgsResolver::resolve(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv + argc);

	if (args.size() == 0) {

	}

	for (int i = 1; i < args.size();) {

	}
}

void ArgsResolver::display_help() {

}

void ArgsResolver::resolve_dump(std::optional<std::string> localFolder) {

}
