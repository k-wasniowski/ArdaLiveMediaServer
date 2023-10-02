#include <MediaServer/MediaManager/MediaResource.hpp>

#include <iostream>

namespace MediaServer
{
    MediaResourceSharedPtr_t MediaResource::Create(std::string resourceName)
    {
        return std::make_shared<Gondor::Concurrency::Mutex<MediaResource>>(std::move(resourceName));
    }

    MediaResource::MediaResource(std::string resourceName)
        : m_resourceName{std::move(resourceName)}
    {
        std::cout << "MediaResource Created" << std::endl;
    }

    MediaResource::~MediaResource()
    {
        std::cout << "MediaResource Terminated" << std::endl;
    }

    void MediaResource::AddTrack(std::shared_ptr<IMediaTrack> pMediaTrack)
    {
        m_mediaTracks.push_back(pMediaTrack);
    }
}