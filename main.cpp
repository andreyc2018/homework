#include "processor.h"
#include "writerfactory.h"
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
        int n = std::stoi(argv[1]);

        Processor processor(n,
                            std::make_unique<LocalWriterFactory>());
        for (std::string input; std::getline(std::cin, input);) {
            processor.add_token(input);
        }
        processor.end_of_stream();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
