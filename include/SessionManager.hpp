#ifndef __SESSION_MANAGER_HPP__
#define __SESSION_MANAGER_HPP__

#include "Session.hpp"

class SessionManager
{
public:
    SessionManager();
    ~SessionManager();

    void startSession(std::shared_ptr<Session> session_ptr);
};

#endif //! __SESSION_MANAGER_HPP__