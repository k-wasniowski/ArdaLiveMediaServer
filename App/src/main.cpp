// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <HttpServer/Server.hpp>
#include <MediaServer/MediaManager/MediaManager.hpp>
#include <MediaServer/RtspClient/RtspClient.hpp>

#include <Gondor/Execution/TasksContext.hpp>

#include <iostream>

int main()
{
    std::cout << "Initializing!" << std::endl;

    auto pTasksContext = Gondor::Execution::TasksContext::Create();
    if (!pTasksContext)
    {
        std::cout << "Failed to create TasksContext!" << std::endl;
        return -1;
    }

    boost::asio::io_context ioContext{};

    auto pRtspClient = MediaServer::Rtsp::RtspClient::Create(ioContext);

    auto pMediaManager = MediaServer::MediaManager::Create();

    auto pHttpServer = HttpServer::Server::Create(pMediaManager);
    if (!pHttpServer)
    {
        return -1;
    }

    pHttpServer->Run();

    return 0;
}
