#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <boost/asio.hpp>
#include <optional>
#include <iostream>

namespace asio = boost::asio;

class Server
{
public:
    Server(const std::string address,const std::string port);

    bool Listen();

private:
    asio::io_context m_ioContext;
    asio::ip::tcp::acceptor m_acceptor;

    void accept();
};

#endif //! __SERVER_HPP__