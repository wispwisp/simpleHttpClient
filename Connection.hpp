#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <cstring>
#include <exception>


namespace Connection {

  struct Exception : std::exception {
    std::string m_errMsg;
    Exception(std::string errMsg, int errnum)
      : m_errMsg(errMsg + ": " + strerror(errnum)) {};
    const char* what() const noexcept {
      return m_errMsg.c_str();
    }
  };

  class Request {//TODO
    std::string m_requestStr;
  public:
    const std::string& get() const { return m_requestStr; }
  };

  class Http
  {
    std::string m_url;
    int m_socketFd = -1;
    int m_port = 80;
  public:
    Http(const std::string& url);
    ~Http();
    Http(const Http&) = delete;
    Http& operator= (const Http&) = delete;
    Http(Http&&) = default;
    Http& operator= (Http&&) = default;

    std::string getRecivedData(const Request&) const;
  };
}

#endif // CONNECTION_H
