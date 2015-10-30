#include <iostream>

#include "Connection.hpp"
#include "Request.hpp"
#include "Url.hpp"

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "usage: %s [url]\n" << argv[0] << std::endl;
    return -1;
  }

  Url parsedUrl(argv[1]);

#ifdef MY_DEBUG_PARSE_URL
  std::cout << parsedUrl.host() << std::endl;
  std::cout << parsedUrl.resource() << std::endl;
  return 0;
#endif

  Connection::Http connect(parsedUrl.host());

  auto simpleGet = Connection::Request::Type::SimpleGet;
  auto request = Connection::Request::createRequest(simpleGet, parsedUrl);

  auto recived = connect.getResponce(request);
  std::cout << recived << std::endl;

  return 0;
}
