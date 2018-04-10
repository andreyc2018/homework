#include "async.h"
#include "logger.h"
#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

class chat_session
  : public chat_participant,
    public std::enable_shared_from_this<chat_session>
{
public:
  chat_session(tcp::socket socket, chat_room& room)
    : socket_(std::move(socket)),
      room_(room)
  {
  }

  void start()
  {
    room_.join(shared_from_this());
    do_read_header();
  }

  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
  }

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_read_body()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            room_.deliver(read_msg_);
            do_read_header();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_write()
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  tcp::socket socket_;
  chat_room& room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

class BulkServer
{
    public:
        BulkServer(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
            : acceptor_(io_service, endpoint)
            , socket_(io_service)
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            acceptor_.async_accept(socket_,
                                   [this](boost::system::error_code ec)
            {
                if (!ec)
                {
                    std::make_shared<chat_session>(std::move(socket_), room_)->start();
                }

                do_accept();
            });
        }

        tcp::acceptor acceptor_;
        tcp::socket socket_;
};

void full_session(int size)
{
    auto h = async::connect(size);
    async::receive(h, "1", 1);
    async::receive(h, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
}

int main(int argc, char const** argv)
{
    try {
        if (argc < 3) {
            std::cout << "usage: "
                      << std::string(argv[0]).substr(std::string(argv[0]).rfind("/")+1)
                      << " <port> <N>\n"
                         "where:\n"
                         "  port - tcp port for incomming connections\n"
                         "  N    - command block size\n";
            exit(1);
        }

        if (argc > 3) {
            gLogger->set_level(spdlog::level::debug);
        }

        std::size_t bulk = std::stoul(argv[1]);
        std::thread t1(full_session, bulk);
        std::thread t2(full_session, bulk+3);
        auto h = async::connect(bulk+4);
        auto h2 = async::connect(bulk);
        async::receive(h, "1", 1);
        async::receive(h2, "1\n", 2);
        async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
        async::receive(h, "b\nc\nd\n}\n89\n", 11);
        async::disconnect(h);
        async::disconnect(h2);
        t2.join();
        t1.join();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
