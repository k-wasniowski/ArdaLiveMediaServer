// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>

#include <Media/Core/MediaBuffer.hpp>
#include <Media/Core/Rtp/RtpPacket.hpp>
#include <Media/Core/VideoFrame.hpp>

#include <boost/bind/bind.hpp>

#include <iostream>

namespace MediaServer
{
    namespace Rtp
    {
        RtpClientSessionSharedPtr_t RtpClientSession::Create(boost::asio::io_context& ioContext, boost::asio::ip::udp::endpoint endpoint)
        {
            return std::make_shared<RtpClientSession>(ioContext, endpoint);
        }

        RtpClientSession::RtpClientSession(boost::asio::io_context& ioContext, boost::asio::ip::udp::endpoint endpoint)
            : m_ioContext{ioContext}
            , m_socket{ioContext, endpoint}
        {
            std::cout << "RtpClientSession::RtpClientSession()" << std::endl;
        }

        RtpClientSession::~RtpClientSession()
        {
            std::cout << "RtpClientSession::~RtpClientSession()" << std::endl;
        }

        void RtpClientSession::Initiate()
        {
            std::cout << "RtpClientSession::Initiate()" << std::endl;

            StartReading_();
        }

        void RtpClientSession::StartReading_()
        {
            m_socket.async_receive(boost::asio::buffer(m_readStreamBuffer),
                                   boost::bind(&RtpClientSession::OnMessage_,
                                               shared_from_this(),
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
        }

        void RtpClientSession::OnMessage_(const boost::system::error_code& errorCode, size_t bytesTransferred)
        {
            std::cout << "RtpClientSession::OnMessage_()" << std::endl;

            if (errorCode)
            {
                std::cout << "Error: " << errorCode.message() << std::endl;

                return;
            }

            std::vector<std::byte> data{};
            data.resize(bytesTransferred);
            std::copy(m_readStreamBuffer.begin(), m_readStreamBuffer.begin() + bytesTransferred, data.begin());

            auto pRtpHeader = reinterpret_cast<Media::Core::Rtp::RtpHeader*>(m_readStreamBuffer.data());
            std::cout << "Payload: " << pRtpHeader->payloadType << std::endl;

            auto pMediaBuffer = Media::Core::MediaBuffer::Create(std::move(data));

            auto pFrame = Media::Core::VideoFrame::Create(pMediaBuffer);

            StartReading_();
        }
    }
}