#include <MediaServer/GenericRtpClientProxy.hpp>

#include <iostream>

namespace MediaServer
{
    GenericRtpClientProxySharedPtr_t GenericRtpClientProxy::Create(boost::asio::io_context& ioContext)
    {
        return std::make_shared<GenericRtpClientProxy>(ioContext);
    }

    GenericRtpClientProxy::GenericRtpClientProxy(boost::asio::io_context& ioContext)
        : m_ioContext{ioContext}
    {
        std::cout << "GenericRtpClientProxy::GenericRtpClientProxy()" << std::endl;
    }

    GenericRtpClientProxy::~GenericRtpClientProxy()
    {
        std::cout << "GenericRtpClientProxy::~GenericRtpClientProxy()" << std::endl;
    }
}