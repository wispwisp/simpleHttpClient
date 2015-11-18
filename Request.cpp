#include "Request.hpp"

#include <string>
#include <memory>
#include <stdexcept>

#include "Url.hpp"

namespace Connection
{
  // Impl

  RequestImplSimpleGet::RequestImplSimpleGet(const Url& url)
    : m_request("GET " +
		url.resource() +
		" HTTP/1.1\nHOST:" +
		url.host() +
		"\n\n")
  { }

  
  // Request
  
  Request Request::createRequest(const Request::Type& type, const Url& url) {

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
}
