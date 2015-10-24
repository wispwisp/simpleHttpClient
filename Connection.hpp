#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
using std::string;

namespace Connection {

  class Request {//TODO
    string m_requestStr;
  public:
    const string& get() const { return m_requestStr; }
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
