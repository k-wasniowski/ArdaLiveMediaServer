#pragma once

#include <MediaServer/GenericRtpClient/IGenericRtpClient.hpp>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <memory>
#include <string>

namespace MediaServer
{
    namespace Rtp
    {
        class GenericRtpClient;
        using GenericRtpClientSharedPtr_t = std::shared_ptr<GenericRtpClient>;

        class GenericRtpClient : public IGenericRtpClient
        {
        public:
            static GenericRtpClientSharedPtr_t Create();

            explicit GenericRtpClient();

            virtual ~GenericRtpClient();

            bool InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription);

        private:
            boost::asio::io_context m_ioContext;
            boost::thread_group m_threadPool;
        };
    }
}
