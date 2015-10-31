#ifndef RESPONCE_H
#define RESPONCE_H

#include <map>
#include <string>

namespace Connection {
  
  class Responce {
    std::string m_statusLine;
    int m_statusCode;
    std::map<std::string, std::string> m_headers;
    std::string m_body;
  public:
    Responce(const std::string& responce);
    ~Responce() = default;

    int statusCode() const {return m_statusCode; }
    const std::string& statusLine() const { return m_statusLine; }
    const std::string& body() const { return m_body; }
    
    const std::map<std::string, std::string>& headers() const { return m_headers; }
  };
  
}
#endif // RESPONCE_H
