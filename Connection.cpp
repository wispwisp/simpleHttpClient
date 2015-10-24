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
#include <exception>

namespace Connection {
  Http::Http(const std::string& url)
    : m_url(url)
  {
    // socket fd
    m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFd == -1) {
      perror("socket() failed");
      throw std::exception();
    }

    // url init
    struct hostent* server = gethostbyname(m_url.c_str());
    if (server == NULL) {
      errno = 14;
      perror("Host not found");
      throw std::exception();
    }

    // sockaddr:
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length); // simplier ?
    serv_addr.sin_port = htons(m_port);

    // connect
    if (connect(m_socketFd, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
      perror("connect() failed");
      throw std::exception();
    }
  }

  Http::~Http() {
    if (m_socketFd != -1)
      close(m_socketFd);
  }

  std::string Http::getRecivedData(const Request&) const {

    // todo: change info from request
    std::string request("GET / HTTP/1.1\nHOST:");
    request += m_url + "\n\n";

    // make request
    ssize_t nwrite = write(m_socketFd, request.c_str(), request.size());
    if (nwrite == -1) {
      perror("write()");
      throw std::exception();      
    }
    else if (request.size() != nwrite) {
      printf("write incomplete\n");
      throw std::exception();
    }

    // get responce
#ifdef MY_DONE
    const int BUF_SIZE = 4096;
    char buf[BUF_SIZE];
    char *p = buf;
    ssize_t nread;
    size_t nleft = BUF_SIZE - 1;
    while(nleft > 0) {
      if ((nread = read(m_socketFd, p, nleft) < 0)) {
	if (errno == EINTR)//The call was interrupted by a signal before any data was read(R.)
	  nread = 0; // call read() again
	else {
	  perror("read from socket");
	  throw std::exception();
	}
      } else if (nread == 0)
	break; // EOF

      nleft -= nread;
      p += nread;
    }

    buf[BUF_SIZE] = 0;
    return { buf };
#else
    const int BUF_SIZE = 4096;
    char buf[BUF_SIZE];
    buf[BUF_SIZE] = 0;
    
    read(m_socketFd, buf, BUF_SIZE - 1);
    return { buf };
#endif
  }
}
