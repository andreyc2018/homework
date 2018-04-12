#include "async.h"
#include "logger.h"
#include <asio.hpp>

#include <iostream>
#include <string>
#include <thread>

using asio::ip::tcp;

class session
    : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket)
            : socket_(std::move(socket))
        {
        }

        void start()
        {
            do_read();
        }

    private:
        void do_read()
        {
            auto self(shared_from_this());
            socket_.async_read_some(asio::buffer(data_, max_length),
                                    [this, self](std::error_code ec, std::size_t length)
            {
                if (!ec) {
                    std::cout << std::this_thread::get_id() << " " << (void*)this << " " << length << "\n";
                    do_read();
                }
            });
        }

        void do_write(std::size_t length)
        {
            auto self(shared_from_this());
            asio::async_write(socket_, asio::buffer(data_, length),
                                     [this, self](std::error_code ec, std::size_t /*length*/)
            {
                if (!ec) {
                    do_read();
                }
            });
        }

        tcp::socket socket_;
        enum { max_length = 1024 };

        char data_[max_length];
};

class server
{
    public:
        server(asio::io_service& io_service, short port)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
            , socket_(io_service)
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            acceptor_.async_accept(socket_,
                                   [this](std::error_code ec)
            {
                if (!ec) {
                    std::make_shared<session>(std::move(socket_))->start();
                }

                do_accept();
            });
        }

        tcp::acceptor acceptor_;
        tcp::socket socket_;
};

int main(int argc, char const** argv)
{
    try {
        if (argc < 3) {
            std::cout << "usage: "
                      << std::string(argv[0]).substr(std::string(argv[0]).rfind("/") + 1)
                      << " <port> <N>\n"
                         "where:\n"
                         "  port - tcp port for incomming connections\n"
                         "  N    - command block size\n";
            exit(1);
        }

        if (argc > 3) {
            gLogger->set_level(spdlog::level::debug);
        }

        asio::io_service io_service;

        server s(io_service, std::atoi(argv[1]));

        io_service.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

