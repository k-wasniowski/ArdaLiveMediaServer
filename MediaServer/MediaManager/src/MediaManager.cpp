#include <MediaServer/MediaManager/MediaManager.hpp>

#include <iostream>

namespace MediaServer
{
    MediaManagerSharedPtr_t MediaManager::Create()
    {
        return std::make_shared<MediaManager>();
    }

    MediaManager::MediaManager()
    {
        std::cout << "MediaManager Created" << std::endl;
    }

    MediaManager::~MediaManager()
    {
        std::cout << "MediaManager Terminated" << std::endl;
    }

    void MediaManager::AddMediaResourceWithCallback(MediaResourceSharedPtr_t pMediaResource, std::function<void(bool)> callback)
    {
        std::cout << "MediaManager::AddMediaResourceWithCallback" << std::endl;
        if(!pMediaResource)
        {
            std::cout << "MediaManager::AddMediaResourceWithCallback - pMediaResource is null" << std::endl;

            callback(false);
            return;
        }

        auto pExistingMediaResource = GetMediaResource(pMediaResource->ResourceName());
        if (pExistingMediaResource)
        {
            std::cout << "MediaManager::AddMediaResourceWithCallback - pMediaResource already exists" << std::endl;
            callback(false);
            return;
        }

        std::cout << "MediaManager::AddMediaResourceWithCallback - pMediaResource added" << std::endl;

        m_mediaResources.push_back(pMediaResource);

        callback(true);
    }

    bool MediaManager::AddMediaResource(MediaResourceSharedPtr_t pMediaResource)
    {
        if (GetMediaResource(pMediaResource->ResourceName()))
        {
            return false;
        }

        m_mediaResources.push_back(pMediaResource);

        return true;
    }

    MediaResourceSharedPtr_t MediaManager::GetMediaResource(std::string resourceName)
    {
        auto it = std::find_if(
            std::begin(m_mediaResources),
            std::end(m_mediaResources),
            [resourceName = std::move(resourceName)](const auto& resource) -> bool { return resource->ResourceName() == resourceName; });

        if (it == std::end(m_mediaResources))
        {
            return nullptr;
        }

        return *it;
    }

    void MediaManager::GetMediaResourcesWithCallback(std::function<void(std::list<MediaResourceSharedPtr_t>)> callback)
    {
        std::cout << "MediaManager::GetMediaResourcesWithCallback, size: " << m_mediaResources.size() << std::endl;

        callback(m_mediaResources);
    }

    void MediaManager::GetMediaResourceWithCallback(std::string resourceName, std::function<void(MediaResourceSharedPtr_t)> callback)
    {
        auto pMediaResource = GetMediaResource(resourceName);

        callback(pMediaResource);
    }

    void MediaManager::RemoveMediaResource(MediaResourceSharedPtr_t pMediaResource)
    {
        m_mediaResources.remove(pMediaResource);
    }
}