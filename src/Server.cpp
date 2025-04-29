#include "Server.hpp"

#include "Session.hpp"

Server::Server(const std::string address, const std::string port)
    : m_ioContext(1),
      m_acceptor(m_ioContext)
{
    asio::ip::tcp::resolver resolver(this->m_ioContext);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();

    this->m_acceptor.open(endpoint.protocol());
    this->m_acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    this->m_acceptor.bind(endpoint);
    this->m_acceptor.listen();

    this->accept();
}

void Server::accept()
{
    this->m_acceptor.async_accept(
        [this](boost::system::error_code ec, asio::ip::tcp::socket socket)
        {
            if (this->m_acceptor.is_open() == false)
            {
                return;
            }

            if (!ec)
            {
                auto session = std::make_shared<Session>(std::move(socket));

                session->start();
                
                std::cout << "CLIENT CONNECTED" << std::endl;
            }

            this->accept();
        });
}

bool Server::Listen()
{
    this->m_ioContext.run();

    return true;
}