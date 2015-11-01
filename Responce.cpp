#include "Responce.hpp"

#include <string>
#include <stdexcept>

namespace Tools {
  void makeEntry(std::map<std::string, std::string>& headers,
		 const std::string& responce, size_t rb, size_t len) {

    std::string headerEntry = responce.substr(rb, len);

    size_t pos = headerEntry.find(":");
    if (pos != std::string::npos) {
      // whitespace after ':'
      size_t afterPos = headerEntry[pos + 1] == ' ' ? pos + 2 : pos + 1;
      headers[headerEntry.substr(0, pos)] = headerEntry.substr(afterPos);
    }    
  }

  int makeStatus(const std::string& statusStr) {
    //HTTP/1.1 200 OK

    size_t rb, re = 0;
    rb = statusStr.find(" ");
    if (rb == std::string::npos)
      throw std::runtime_error("Bad status line");

    re = statusStr.find(" ", rb + 1);
    if (re == std::string::npos)
      throw std::runtime_error("Bad status line");

    return std::stoi(statusStr.substr(rb, re - rb));
  }
}

namespace Connection {

  Responce::Responce(const std::string& responce) {

    size_t rangeBegin = 0;
    size_t rangeEnd = 0;

    // status str:
    rangeEnd = responce.find("\r\n");
    if (rangeEnd == std::string::npos)
      throw std::runtime_error("Bad responce:\n" + responce);

    m_statusLine = responce.substr(0, rangeEnd);
    m_statusCode = Tools::makeStatus(m_statusLine);

    // headers:
    rangeBegin = rangeEnd + 2;
    size_t len = 0;
    do {
      rangeEnd = responce.find("\r\n", rangeBegin);
      if (rangeEnd == std::string::npos) {
	break;
      }
      
      len = rangeEnd - rangeBegin;
      if (len)
	Tools::makeEntry(m_headers, responce, rangeBegin, len);

      rangeBegin = rangeEnd + 2;
    } while (len);

    // body:
    m_body = responce.substr(rangeBegin);
  }

  const std::string& Responce::header(const std::string& hdr) const {
    auto header_it = m_headers.find(hdr);
    if (header_it == m_headers.cend())
      throw std::runtime_error("No such header: " + hdr);
    
    return header_it->second;
  }

}
