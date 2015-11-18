#ifndef MY_REQUEST
#define MY_REQUEST

#include <string>
#include <memory>
#include <stdexcept>

#include "Url.hpp"

namespace Connection {

  struct RequestImplInterface {
    virtual const std::string& getRequestStr() const = 0;
    virtual ~RequestImplInterface() = default;
  };


  class RequestImplSimpleGet final : public RequestImplInterface {
    std::string m_request;
  public:
    explicit RequestImplSimpleGet(const Url&);
    ~RequestImplSimpleGet() = default;
    const std::string& getRequestStr() const { return m_request; }
  };


  class Request
  {
    std::unique_ptr<RequestImplInterface> m_reqImpl;
    explicit Request(std::unique_ptr<RequestImplInterface> reqImpl)
      : m_reqImpl(std::move(reqImpl)) {};
  public:
    ~Request() = default;
    Request(const Request&) = delete;
    Request& operator= (const Request&) = delete;
    Request(Request&&) = default;
    Request& operator= (Request&&) = default;

    enum class Type { SimpleGet };
    static Request createRequest(const Request::Type&, const Url&);
    const std::string& requestStr() const { return m_reqImpl->getRequestStr(); }
  };
}
#endif //MY_REQUEST
