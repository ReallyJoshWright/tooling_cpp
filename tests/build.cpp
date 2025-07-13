#include <vector>

#include "builder.h"

int main(int argc, char *argv[]) {
    Builder builder(argc, argv);

    std::vector<Debug> debug;
    debug.push_back(Debug::G);
    debug.push_back(Debug::Wall);
    debug.push_back(Debug::Wextra);
    debug.push_back(Debug::Pedantic);

    builder.setOptions(Options{
        .name = "test",
        .root_source_file = "./src/main.cpp",
        .version = Version::V23,
        .debug = debug,
        .optimize = Optimize::Debug,
        .target = Targets::Linux,
    });

    builder.addIncludeDir("-I/home/josh/.config/.cppc");

    builder.build();
}
