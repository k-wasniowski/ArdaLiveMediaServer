// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <MediaServer/RtspClient/Details/RtspClientSession.hpp>

#include <boost/bind/bind.hpp>

#include <iostream>

namespace MediaServer
{
    namespace Rtsp
    {
        RtspClientSessionSharedPtr_t RtspClientSession::Create(boost::asio::io_context& ioContext)
        {
            return std::make_shared<RtspClientSession>(ioContext);
        }

        RtspClientSession::RtspClientSession(boost::asio::io_context& ioContext)
            : m_ioContext{ioContext}
            , m_socket{ioContext}
            , m_readStreamBuffer{1024}
        {
            std::cout << "RtspClientSession created!" << std::endl;
        }

        RtspClientSession::~RtspClientSession()
        {
            std::cout << "RtspClientSession destroyed!" << std::endl;
        }

        void RtspClientSession::Connect(std::string address, uint16_t port)
        {
            boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::make_address(address), port};

            m_socket.async_connect(endpoint, std::bind(&RtspClientSession::OnConnect, shared_from_this(), std::placeholders::_1));
        }

        void RtspClientSession::OnConnect(boost::system::error_code errorCode)
        {
            if (errorCode)
            {
                std::cout << "Error: " << errorCode.message() << std::endl;
                return;
            }

            std::cout << "Connected!" << std::endl;

            StartReading_();

            std::ostringstream msg{};
            msg << "OPTIONS rtsp://192.168.0.234:1024/h264_pcm.sdp RTSP/1.0\r\n";
            msg << "CSeq: 2\r\n";
            msg << "User-Agent: Kacper (LIVE555 Streaming Media v2016.11.28)\r\n";
            msg << "\r\n";
            std::string message = msg.str();
            m_socket.send(boost::asio::buffer(message));
        }

        void RtspClientSession::StartReading_()
        {
            boost::asio::async_read_until(m_socket,
                                          m_readStreamBuffer,
                                          "\r\n\r\n",
                                          boost::bind(&RtspClientSession::OnReadComplete,
                                                      shared_from_this(),
                                                      boost::asio::placeholders::error,
                                                      boost::asio::placeholders::bytes_transferred));
        }

        void RtspClientSession::OnReadComplete(const boost::system::error_code& errorCode, size_t bytesTransferred)
        {
            std::cout << "Got response!" << std::endl;

            auto bufs = m_readStreamBuffer.data();
            std::string result(buffers_begin(bufs), buffers_begin(bufs) + m_readStreamBuffer.size());
            std::cout << "Received: \n" << result << std::endl;
            this->m_readStreamBuffer.consume(bytesTransferred);
        }
    }
}