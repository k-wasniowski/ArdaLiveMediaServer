#pragma once

#include <boost/asio.hpp>

#include <memory>
#include <string>

namespace MediaServer
{
    namespace Rtp
    {
        class GenericRtpClient;
        using GenericRtpClientSharedPtr_t = std::shared_ptr<GenericRtpClient>;

        class GenericRtpClient
        {
        public:
            static GenericRtpClientSharedPtr_t Create(boost::asio::io_context& ioContext);

            explicit GenericRtpClient(boost::asio::io_context& ioContext);

            virtual ~GenericRtpClient();

            bool InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription);

        private:
            boost::asio::io_context& m_ioContext;
        };
    }
}
