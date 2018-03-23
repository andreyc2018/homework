#include "processor.h"
#include "writerfactory.h"
#include "messagequeue.h"
#include "counters.h"
#include <iostream>
#include <string>

void console(MessageQueue& q)
{
    TRACE();
    Counters counters;
    Message msg;
    do
    {
        gLogger->info("{}: pop data", __func__);
        msg = q.pop();
        gLogger->info("{}: data = {}", __func__, msg.data);
        if (msg.id == MessageId::Data) {
            std::cout << msg.data;
            ++counters.blocks;
        }
    } while (msg.id != MessageId::EndOfStream);
    std::cout << "log поток - "
              << counters.blocks << " блок, "
              << counters.commands << " команд\n";
}

void remote_file(MessageQueue& q)
{
    TRACE();
    Counters counters;
    Message msg;
    do
    {
        gLogger->info("{}: pop file", __func__);
        msg = q.pop();
        if (msg.id == MessageId::Data) {
            gLogger->info("{}:{}: filename = {}, data = {}",
                          __func__, __LINE__, msg.filename, msg.data);
            std::ofstream file(msg.filename);
            file << msg.data;
            file.close();
            ++counters.blocks;
        }
    } while (msg.id != MessageId::EndOfStream);
    std::cout << "file" << 1 << " поток - "
              << counters.blocks << " блок, "
              << counters.commands << " команд\n";
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

        MessageQueue console_q;
        std::thread console_thread(console, std::ref(console_q));
        MessageQueue file_q;
        std::thread file_thread_1(remote_file, std::ref(file_q));
        std::thread file_thread_2(remote_file, std::ref(file_q));

        Processor processor(n,
                            std::make_unique<ThreadWriterFactory>(console_q, file_q));
        for (std::string input; std::getline(std::cin, input);) {
            processor.add_token(input);
        }
        gLogger->info("{}: EOS", __func__);
        processor.end_of_stream();

        Message msg { MessageId::EndOfStream, "", "", 0 };
        console_q.push(msg);
        file_q.push(msg);
        file_q.push(msg);

        gLogger->info("{}: waiting for the threads", __func__);
        console_thread.join();
        file_thread_1.join();
        file_thread_2.join();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
