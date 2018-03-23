#include "processor.h"
#include "writerfactory.h"
#include "messagequeue.h"
#include "counters.h"
#include <mutex>
#include <iostream>
#include <string>

void console(MessageQueue& q, std::mutex& mtx)
{
    Counters counters;
    Message msg;
    do
    {
        gLogger->debug("{}: pop data", __func__);
        msg = q.pop();
        gLogger->debug("{}: data = {}", __func__, msg.block.data);
        if (msg.id == MessageId::Data) {
            std::cout << msg.block.data;
            counters.commands += msg.block.commands;
            ++counters.blocks;
        }
    } while (msg.id != MessageId::EndOfStream);
    std::lock_guard<std::mutex> g(mtx);
    std::cout << "log поток - "
              << counters.blocks << " блок, "
              << counters.commands << " команд\n";
}

void remote_file(MessageQueue& q, int id, std::mutex& mtx)
{
    Counters counters;
    Message msg;
    do
    {
        gLogger->debug("{}: pop file", __func__);
        msg = q.pop();
        if (msg.id == MessageId::Data) {
            gLogger->debug("{}:{}: filename = {}, data = {}",
                          __func__, __LINE__, msg.filename, msg.block.data);
            std::ofstream file(msg.filename);
            file << msg.block.data;
            file.close();
            counters.commands += msg.block.commands;
            ++counters.blocks;
        }
    } while (msg.id != MessageId::EndOfStream);
    std::lock_guard<std::mutex> g(mtx);
    std::cout << "file" << id << " поток - "
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

        if (argc > 2) {
            gLogger->set_level(spdlog::level::debug);
        }

        int n = std::stoi(argv[1]);

        std::mutex report_mtx;
        MessageQueue console_q;
        std::thread console_thread(console, std::ref(console_q), std::ref(report_mtx));
        MessageQueue file_q;
        std::thread file_thread_1(remote_file, std::ref(file_q), 1, std::ref(report_mtx));
        std::thread file_thread_2(remote_file, std::ref(file_q), 2, std::ref(report_mtx));

        Processor processor(n,
                            std::make_unique<ThreadWriterFactory>(console_q, file_q));
        for (std::string input; std::getline(std::cin, input);) {
            processor.add_token(input);
        }
        gLogger->debug("{}: EOS", __func__);
        processor.end_of_stream();

        Message msg { MessageId::EndOfStream, "", { "", 0 } };
        console_q.push(msg);
        file_q.push(msg);
        file_q.push(msg);

        gLogger->debug("{}: waiting for the threads", __func__);
        console_thread.join();
        file_thread_1.join();
        file_thread_2.join();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
