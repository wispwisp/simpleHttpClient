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
#endif

  Connection::Http con(parsedUrl.host());
  Connection::Request req(parsedUrl);

  auto recived = con.getResponce(req);
  std::cout << recived << std::endl;

  return 0;
}
