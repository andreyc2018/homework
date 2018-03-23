#include "processor.h"
#include "writerfactory.h"
#include <iostream>
#include <string>

void console(MsgQueue& q)
{
    std::string data;
    do
    {
        data = q.pop();
        if (!data.empty()) {
            std::cout << data;
        }
    } while (!data.empty());
}

void remote_file(MsgQueue& q)
{
    std::string data;
    do
    {
        std::string filename = q.pop();
        data = q.pop();
        if (!data.empty()) {
            std::ofstream file(filename);
            file << data;
            file.close();
        }
    } while (!data.empty());
}

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

        MsgQueue console_q;
        std::thread console_thread(console, std::ref(console_q));
        MsgQueue file_q;
        std::thread file_thread_1(console, std::ref(file_q));
        std::thread file_thread_2(console, std::ref(file_q));


        Processor processor(n,
                            std::make_unique<ThreadWriterFactory>(console_q, file_q));
        for (std::string input; std::getline(std::cin, input);) {
            processor.add_token(input);
        }
        processor.end_of_stream();

        console_thread.join();
        file_thread_1.join();
        file_thread_2.join();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
