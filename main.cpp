#include <iostream>

#include "Connection.hpp"

// todo:
// * read complete ?
// * split host addr and path
// * request class
// * NOBLOCK IO
// * http features

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "usage: %s <hostname>\n" << argv[0] << std::endl;
    return -1;
  }

  Connection::Http con(argv[1]);
  Connection::Request req;

  auto recived = con.getRecivedData(req);
  std::cout << recived << std::endl;
  
  return 0;
}
