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

            bool InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription, std::function<void()> callback) override;

        private:
            boost::asio::io_context m_ioContext;
            boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;
            boost::thread_group m_threadPool;
        };
    }
}
