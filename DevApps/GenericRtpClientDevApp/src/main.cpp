// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>

#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context ioContext{};

    boost::asio::ip::udp::endpoint mediaEndpoint{boost::asio::ip::address::from_string("127.0.0.1"), 5004};
    auto pRtpClientSession = MediaServer::Rtp::RtpClientSession::Create(ioContext, mediaEndpoint);

    pRtpClientSession->Initiate();

    ioContext.run();

    return 0;
}