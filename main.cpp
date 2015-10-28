#include <iostream>

#include "Connection.hpp"


#include <regex>
#include <string>

class ParsedUrl {
  std::string m_host;
  std::string m_res;
public:
  ParsedUrl(const std::string& url) {

    std::regex re{ R"(^(?:http:/+)?([^/]+)(/.*)?$)" };
    std::smatch match;

    if (!std::regex_match(url, match, re)) {
      throw std::exception();
    }

    m_host = match[1];
    m_res = match[2].str().empty() ? "/" : match[2].str();
  }
  const std::string& host() const { return m_host; }
  const std::string& resource() const { return m_res; }
};


int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "usage: %s [url]\n" << argv[0] << std::endl;
    return -1;
  }

  ParsedUrl parsedUrl(argv[1]);

#ifdef MY_DEBUG_PARSE_URL
  std::cout << parsedUrl.host() << std::endl;
  std::cout << parsedUrl.resource() << std::endl;
#endif

  Connection::Http con(parsedUrl.host());
  Connection::Request req(parsedUrl.resource());

  auto recived = con.getResponce(req);
  std::cout << recived << std::endl;

  return 0;
}
