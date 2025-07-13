#include "io_23.h"

using namespace short_names;

int main() {
    expected<fs::path, string> cwd_res = io::getCurrentDirectory();
    if (cwd_res.has_value()) {
        println("{}", cwd_res.value().string());
    } else {
        println("{}", cwd_res.error());
    }

    return 0;
}
