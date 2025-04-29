#ifndef __ROOT_HPP__
#define __ROOT_HPP__

#define LISTEN_PORT "8000"

#include "Server.hpp"
#include <iostream>

class Root
{
public:
    int Run();
    bool Init(int listen_port);

    static Root *getPtr();

private:
    Server m_server = Server("192.168.1.200", LISTEN_PORT);
    static Root *m_instance;

    int port = 0;
    std::string m_host = "";

    bool startListning();
};

#endif //! __ROOT_HPP__