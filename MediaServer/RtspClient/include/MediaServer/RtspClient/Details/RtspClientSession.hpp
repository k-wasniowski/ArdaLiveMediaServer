// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <boost/asio.hpp>

namespace MediaServer
{
    namespace Rtsp
    {
        class RtspClientSession;
        using RtspClientSessionSharedPtr_t = std::shared_ptr<RtspClientSession>;

        class RtspClientSession : public std::enable_shared_from_this<RtspClientSession>
        {
        public:
            static RtspClientSessionSharedPtr_t Create(boost::asio::io_context& ioContext);

            explicit RtspClientSession(boost::asio::io_context& ioContext);

            virtual ~RtspClientSession();

            void Connect(std::string address, uint16_t port);

        private:
            void OnConnect(boost::system::error_code errorCode);

            void StartReading_();

            void OnReadComplete(const boost::system::error_code& errorCode, size_t bytesTransferred);

        private:
            boost::asio::io_context& m_ioContext;
            boost::asio::ip::tcp::socket m_socket;
            boost::asio::streambuf m_readStreamBuffer;
        };
    }
}