#pragma once
#include <string>
#include <set>
#include <optional>

class ArgsResolver {
	static void display_help();
	static void resolve_dump(std::optional<std::string> localFolder);
public:
	static void resolve(int argc, char* argv[]);
};
