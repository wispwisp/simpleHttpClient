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


  class Request {
    std::string m_resource;
  public:
    Request(const std::string& resource)
      : m_resource(resource) {};
    const std::string& get() const { return m_resource; }
  };
  // make virtual ?


  class Responce {
    std::string m_responceStr;
  public:
    Responce(const std::string& responce)
      : m_responceStr(responce) {};
    Responce(std::string&& responce)
      : m_responceStr(std::move(responce)) {};
    const std::string& getResponceStr() const { return m_responceStr; }
  };


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

    std::string getResponce(const Request&) const;
  };

}

#endif // CONNECTION_H
