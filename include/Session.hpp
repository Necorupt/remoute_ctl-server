#ifndef __SESSION_HPP__
#define __SESSION_HPP__
#define BOOST_SPIRIT_DEBUG

#include <memory>
#include <array>
#include <boost/asio.hpp>

namespace asio = boost::asio;

#include "Protocol.hpp"

class Session
    : public std::enable_shared_from_this<Session>
{
public:
    Session(asio::ip::tcp::socket socket);

    void start();
    void stop();

private:
    void do_read();
    void do_write();

    void execMessage(PROTO_MESSAGE_T message);
    void sendHandshake();

    asio::ip::tcp::socket m_socket;
    std::array<char, 8192> m_buffer;
    boost::asio::const_buffer m_reply;
};

#endif //! __SESSION_HPP__