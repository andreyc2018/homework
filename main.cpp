#include "processor.h"
#include "writerfactory.h"
#include "messagequeue.h"
#include "counters.h"
#include "listeners.h"
#include <mutex>
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

        int n = std::stoi(argv[1]);

        MessageQueue console_q;
        ConsoleListener console(console_q);
        MessageQueue file_q;
        FileListener file_1(file_q, 1);
        FileListener file_2(file_q, 2);

        console.run();
        file_1.run();
        file_2.run();

        Processor processor(n,
                            std::make_unique<ThreadWriterFactory>(console_q, file_q));
        for (std::string input; std::getline(std::cin, input);) {
            processor.add_token(input);
        }
        processor.end_of_stream();

        Message msg { MessageId::EndOfStream, "", { "", 0 } };
        console.queue().push(msg);
        file_1.queue().push(msg);
        file_2.queue().push(msg);

        console.wait();
        file_1.wait();
        file_2.wait();

        std::cout << "\n";
        processor.report(std::cout);
        console.report(std::cout);
        file_1.report(std::cout);
        file_2.report(std::cout);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
