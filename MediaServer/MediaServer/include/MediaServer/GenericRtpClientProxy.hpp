#pragma once

#include <boost/asio.hpp>

#include <memory>

namespace MediaServer
{
    class GenericRtpClientProxy;
    using GenericRtpClientProxySharedPtr_t = std::shared_ptr<GenericRtpClientProxy>;

    class GenericRtpClientProxy
    {
    public:
        static GenericRtpClientProxySharedPtr_t Create(boost::asio::io_context& ioContext);

        GenericRtpClientProxy(boost::asio::io_context& ioContext);
        ~GenericRtpClientProxy();

    private:
        boost::asio::io_context& m_ioContext;
    };
}