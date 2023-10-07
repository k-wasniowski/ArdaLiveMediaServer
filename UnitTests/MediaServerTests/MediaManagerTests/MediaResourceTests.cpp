#include <Gondor/Concurrency/Mutex.hpp>

#include <MediaServer/MediaManager/MediaResource.hpp>

#include <gtest/gtest.h>

#include <algorithm>

TEST(MediaResourceTests, Creation)
{
    MediaServer::MediaResourceSharedPtr_t pMediaResource = MediaServer::MediaResource::Create("TestResource");
    ASSERT_TRUE(pMediaResource != nullptr);
}

TEST(MediaResourceTests, MultiThreadAccessAnother)
{
    auto pLockableMediaResource = std::make_shared<Gondor::Concurrency::Mutex<MediaServer::MediaResource>>("TestResource");
    ASSERT_TRUE(pLockableMediaResource != nullptr);

    std::vector<std::thread> threads{};
    for (int i = 0; i < 20; ++i)
    {
        threads.emplace_back([pLockableMediaResource]() {
            for (int j = 0; j < 100; j++)
            {
                auto pLockedMediaResource = pLockableMediaResource->Lock();

                pLockedMediaResource->AddTrack(nullptr);
            }
        });
    }

    std::ranges::for_each(threads, &std::thread::join);

    auto pLockedMediaResource = pLockableMediaResource->Lock();
    ASSERT_TRUE(pLockedMediaResource->TracksCount() == 20 * 100);
}