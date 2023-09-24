#pragma once

#include <MediaServer/RtspClient/IRtspClient.hpp>

#include <boost/asio.hpp>

namespace MediaServer
{
    namespace Rtsp
    {
        class RtspClient;
        using RtspClientSharedPtr_t = std::shared_ptr<RtspClient>;

        class RtspClient : public IRtspClient
        {
        public:
            static RtspClientSharedPtr_t Create(boost::asio::io_context& ioContext);

            explicit RtspClient(boost::asio::io_context& ioContext);

            ~RtspClient() override;

            bool InitiateNewStream(std::string address, uint16_t port) override;

        private:
            boost::asio::io_context& m_ioContext;
        };
    }
}