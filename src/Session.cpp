#include "Session.hpp"

#include <iostream>

Session::Session(asio::ip::tcp::socket socket) : m_socket(std::move(socket))
{
    this->m_reply = asio::buffer("Hello world");
}

void Session::start()
{
    this->do_read();
}

void Session::do_read()
{
    auto self(this->shared_from_this());

    this->m_socket.async_read_some(
        asio::buffer(this->m_buffer),
        [this, self](boost::system::error_code ec, size_t bytesTransfered)
        {
            if (!ec)
            {
                std::cout << "[SESSION] async_read_some" << ec.what() << std::endl;

                PROTO_MESSAGE_T msg;

                memcpy(&msg, this->m_buffer.data(), sizeof(msg));

                std::cout << "MESSAGE TYPE " << (uint32_t)msg.msgType << std::endl;
                std::cout << "PROTO VERSION " << (uint32_t)msg.versionMaj << "." << (uint32_t)msg.versionMin << std::endl;

                this->execMessage(msg);
            }
        });
}

void Session::do_write()
{
    auto self(this->shared_from_this());

    asio::async_write(
        this->m_socket, this->m_reply,
        [this, self](boost::system::error_code ec, size_t len)
        {
            if (!ec)
            {
                std::cout << "[SESSION] async_write" << ec.what() << std::endl;
            }
        });
}

void Session::execMessage(PROTO_MESSAGE_T message)
{
    switch (message.msgType)
    {
    case PROTO_MSG_TYPE_HELLO:
        this->sendHandshake();
        break;
    }
}

int counter = 0;

void Session::sendHandshake()
{
    std::vector<char> msgBuffer;
    PROTO_MESSAGE msg;
    PROTO_HANDSHAKE_PAYLOAD handshake;

    msg.endian = PROTO_LITTLE_ENDIAN;
    memcpy(&msg.magic, PROTO_MAGIC, sizeof(msg.magic));
    msg.msgType = PROTO_MSG_TYPE_HANDSHAKE;
    msg.versionMaj = 1;
    msg.versionMin = 0;

    handshake.clientId = counter++;
    handshake.versionMaj = 1;
    handshake.versionMin = 0;

    msgBuffer.resize(sizeof(msg) + sizeof(handshake));

    memcpy(msgBuffer.data(), (char *)&msg, sizeof(msg));
    memcpy(&msgBuffer[sizeof(msg)], (char *)&handshake, sizeof(msg));

    auto self(this->shared_from_this());

    this->m_reply = asio::const_buffer(msgBuffer.data(), sizeof(msgBuffer));

    asio::async_write(
        this->m_socket, this->m_reply,
        [this, self](boost::system::error_code ec, size_t len)
        {
            if (!ec)
            {
                std::cout << "[SESSION] async_write" << ec.message() << std::endl;
                this->do_read();
            }
        });
}