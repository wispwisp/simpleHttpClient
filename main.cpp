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

  auto simpleGet = Connection::Request::Type::SimpleGet;
  auto request = Connection::Request::createRequest(simpleGet, parsedUrl);

  Connection::Http connect(parsedUrl.host());
  auto recived = connect.getResponce(request);
  std::cout << recived << std::endl;

  return 0;
}
