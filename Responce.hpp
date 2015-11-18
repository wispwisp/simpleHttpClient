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
    explicit Responce(const std::string& responce);

    int statusCode() const {return m_statusCode; }
    const std::string& statusLine() const { return m_statusLine; }
    const std::string& body() const { return m_body; }

    bool isHeader(const std::string& hdr) const { return m_headers.count(hdr); }
    const std::string& header(const std::string&) const;

    const std::map<std::string, std::string>& headers() const { return m_headers; }
  };
  
}
#endif // RESPONCE_H
