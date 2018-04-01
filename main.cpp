#include "async.h"
#include "logger.h"
#include <iostream>
#include <string>

int main(int argc, char const** argv)
{
    try {
        if (argc < 2) {
            std::cout << "usage: "
                      << std::string(argv[0]).substr(std::string(argv[0]).rfind("/")+1)
                      << " <N>\nwhere:\n  N - command block size\n";
            exit(1);
        }

        if (argc > 2) {
            gLogger->set_level(spdlog::level::debug);
        }

        std::size_t bulk = std::stoul(argv[1]);
        auto h = async::connect(bulk+4);
        auto h2 = async::connect(bulk);
        async::receive(h, "1", 1);
        async::receive(h2, "1\n", 2);
        async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
        async::receive(h, "b\nc\nd\n}\n89\n", 11);
        async::disconnect(h);
        async::disconnect(h2);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
