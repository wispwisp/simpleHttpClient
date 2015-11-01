#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

#include "Responce.hpp"
#include "Request.hpp"

namespace Connection {
  class Http
  {
    std::string m_host;
    int m_socketFd = -1;
    int m_port = 80;
  public:
    Http(const std::string& host);
    ~Http();
    Http(const Http&) = delete;
    Http& operator= (const Http&) = delete;
    Http(Http&&) = default;
    Http& operator= (Http&&) = default;

    Responce getResponce(const Request&) const;
  };
}

#endif // CONNECTION_H
