#include <iostream>

#include "Connection.hpp"


#include <regex>
#include <tuple>
#include <string>
std::tuple<std::string, std::string>
parseUrl(const std::string& url) {

  // todo: correct regex. now only "aaa.com/bbb"
  std::regex re{ R"((?:http://|)([^/]+)(/.+))" };
  std::smatch match;

  if (!std::regex_match(url, match, re)) {
    throw std::exception();
  }

  //host, path
  return std::make_tuple(match[1], match[2]);
}


int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "usage: %s [url]\n" << argv[0] << std::endl;
    return -1;
  }

  auto hostAndPath = parseUrl(argv[1]);

  //debug:
  std::cout << std::get<0>(hostAndPath) << std::endl;
  std::cout << std::get<1>(hostAndPath) << std::endl;

  Connection::Http con(std::get<0>(hostAndPath));
  Connection::Request req(std::get<1>(hostAndPath));

  auto recived = con.getRecivedData(req);
  std::cout << recived << std::endl;

  return 0;
}
