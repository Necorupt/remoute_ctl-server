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
                std::cout<<"[SESSION] async_read_some"<<ec.what() << std::endl;
            }

            for(const auto c: this->m_buffer){
                std::cout<< c;
            }

            do_write();
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
                std::cout<<"[SESSION] async_write"<<ec.what() << std::endl;
            }
        });
}