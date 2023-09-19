// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <MediaServer/RtspClient/RtspClient.hpp>

#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context ioContext{};

    auto pRtspClient = MediaServer::Rtsp::RtspClient::Create(ioContext);

    pRtspClient->InitiateNewStream("192.168.0.234", 1024);

    ioContext.run();

    return 0;
}