#ifndef MY_REQUEST
#define MY_REQUEST

#include <string>
#include <memory>
#include <stdexcept>

#include "Url.hpp"

namespace Connection
{
  struct RequestImplInterface {
    virtual const std::string& getRequestStr() const = 0;
    virtual ~RequestImplInterface() = default;
  };


  class RequestImplSimpleGet : public RequestImplInterface {
    std::string m_request;
  public:
    RequestImplSimpleGet(const Url& url) {
      m_request = "GET " +
	url.resource() +
	" HTTP/1.1\nHOST:" +
	url.host() +
	"\n\n";
    }
    ~RequestImplSimpleGet() = default;
    const std::string& getRequestStr() const {
      return m_request;
    }
  };


  class Request
  {
    std::unique_ptr<RequestImplInterface> m_reqImpl;
    explicit Request(std::unique_ptr<RequestImplInterface> reqImpl)
      : m_reqImpl(std::move(reqImpl)) {};
  public:
    enum class Type { SimpleGet };
    static Request createRequest(const Request::Type& type, const Url& url) {
      std::unique_ptr<RequestImplInterface> reqImpl;

      switch (type) {
      case Type::SimpleGet:
	reqImpl.reset(new RequestImplSimpleGet(url));
	break;
      default:
	throw std::runtime_error("Unspecified request");
      }

      return Request(std::move(reqImpl));
    }
    const std::string& requestStr() const {
      return m_reqImpl->getRequestStr();
    }

    ~Request() = default;
    Request(const Request&) = delete;
    Request& operator= (const Request&) = delete;
    Request(Request&&) = default;
    Request& operator= (Request&&) = default;
  };
}
#endif //MY_REQUEST
