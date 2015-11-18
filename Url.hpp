#ifndef MY_URL
#define MY_URL

#include <regex>
#include <string>
#include <stdexcept>

class Url {
  std::string m_host;
  std::string m_res;
public:
  explicit Url(const std::string& url) {

    std::regex re{ R"(^(?:http:/+)?([^/]+)(/.*)?$)" };
    std::smatch match;

    if (!std::regex_match(url, match, re)) {
      throw std::runtime_error("Invalid url");
    }
    
    m_host = match[1];
    m_res = match[2].str().empty() ? "/" : match[2].str();
  }
  const std::string& host() const { return m_host; }
  const std::string& resource() const { return m_res; }
};

#endif // MY_URL
