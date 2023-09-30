#include <MediaServer/Server.hpp>

#include <gtest/gtest.h>

TEST(MediaServerTests, Creation)
{
    auto pMediaServer = MediaServer::Server::Create();
    ASSERT_TRUE(pMediaServer != nullptr);
}

TEST(MediaServerTests, MakingGenericRtpClient)
{
    auto pMediaServer = MediaServer::Server::Create();
    ASSERT_TRUE(pMediaServer != nullptr);

    auto pGenericRtpClient = pMediaServer->MakeGenericRtpClient();
    ASSERT_TRUE(pGenericRtpClient != nullptr);
}
