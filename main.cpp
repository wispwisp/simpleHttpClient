#include <iostream>

#include "Connection.hpp"
#include "Responce.hpp"
#include "Request.hpp"
#include "Url.hpp"

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "usage: %s [url]\n" << argv[0] << std::endl;
    return -1;
  }

  Url url(argv[1]);

  auto simpleGet = Connection::Request::Type::SimpleGet;
  auto request = Connection::Request::createRequest(simpleGet, url);

  Connection::Http connection(url.host());
  auto responce = connection.getResponce(request);

  /* TODO: redirect; operator= overload; Request::Type::SimpleGetWithRedirect; getHeader;
     while (responce.status() >= 300 && responce.status() < 308) {
     url = responce.getHeader("Location");
     connection = url.host();
     request = Connection::Request::createRequest(simpleGet, url);
     responce = connection.getResponce(request);
     }
  */

#define MY_RESPONCE_DEBUG
#ifdef MY_RESPONCE_DEBUG
  std::cout << "Status line: " << responce.statusLine() << "\n"
	    << "Status code: " << responce.statusCode() << "\n";

  std::cout << "Headers:\n";
  for (const auto& header : responce.headers()) {
    std::cout << header.first << ": " << header.second << "\n";
  }

  std::cout << "Body:\n" << responce.body()
	    << std::endl;
#endif

  return 0;
}
