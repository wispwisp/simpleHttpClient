#include "Connection.hpp"

#include <cstdio>
#include <cstdlib>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

#include <string>

namespace Tools {
  void writeToSocket(int sockFd, const std::string& str) {

    ssize_t nwrite = write(sockFd, str.c_str(), str.size());

    if (nwrite == -1) {
      throw Connection::Exception("write()", errno);
    }
    else if (str.size() != nwrite) {
      throw Connection::Exception("write incomplete", EAGAIN);
    }
  }
  
  std::string readFromSocket(int sockFd) {
    
    const int BUF_SIZE = 4096;
    char buf[BUF_SIZE];
    char *p = buf;

    ssize_t nread;
    size_t nleft = BUF_SIZE - 1;
    while(nleft > 0) {
      if ((nread = read(sockFd, p, nleft) < 0)) {
	if (errno == EINTR)//The call was interrupted by a signal before any data was read(W. R. Stevens)
	  nread = 0; // call read() again
	else {
	  throw Connection::Exception("read()", errno);
	}
      } else if (nread == 0)
	break; // EOF

      nleft -= nread;
      p += nread;
    }

    buf[BUF_SIZE] = 0;
    return { buf };
  }
}

namespace Connection {
  Http::Http(const std::string& host)
    : m_host(host)
  {
    // socket fd
    m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFd == -1) {
      throw Exception("socket()", errno);
    }

    // host init
    struct hostent* server = gethostbyname(m_host.c_str());
    if (server == NULL) {
      throw Exception("Host not found", EFAULT);
    }

    // sockaddr:
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length); // simplier ?
    serv_addr.sin_port = htons(m_port);

    // connect
    if (connect(m_socketFd, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
      throw Exception("connect()", errno);
    }
  }

  Http::~Http() {
    if (m_socketFd != -1)
      close(m_socketFd);
  }

  std::string Http::getResponce(const Request&) const {

    // todo: change info from request
    std::string resource = "/";
    std::string request("GET " +
			resource +
			" HTTP/1.1\nHOST:" +
			m_host +
			"\n\n");

    Tools::writeToSocket(m_socketFd, request);
    return Tools::readFromSocket(m_socketFd);
  }
}
