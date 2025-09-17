#pragma once
#include <string>
#include <set>
#include <filesystem>

class ArgsResolver {
	static void display_help();
	static void resolve_dump(const std::filesystem::path& localFolder);
public:
	static void resolve(int argc, char* argv[]);
};
