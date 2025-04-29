#include "Root.hpp"

Root *Root::m_instance = nullptr;

Root *Root::getPtr()
{
    if (m_instance == nullptr)
    {
        m_instance = new Root();
    }

    return m_instance;
}

bool Root::Init(int listen_port)
{
    return true;
}

bool Root::startListning()
{
    this->m_server.Listen();

    return true;
}

int Root::Run()
{
    this->startListning();

    return 1;
}