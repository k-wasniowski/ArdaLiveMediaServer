// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

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

    void MediaManager::AddMediaResource(MediaResourceSharedPtr_t pMediaResource)
    {
        m_mediaResources.push_back(pMediaResource);
    }

    MediaResourceSharedPtr_t MediaManager::GetMediaResource(std::string resourceName)
    {
//        auto it = std::find_if(std::begin(m_mediaResources), std::end(m_mediaResources), [resourceName = std::move(resourceName)](const auto& resource) -> bool {
//            return resource->ResourceName() == resourceName;
//        });
//
//        if(it == std::end(m_mediaResources))
//        {
//            return nullptr;
//        }

        return m_mediaResources.front();
    }

    void MediaManager::RemoveMediaResource(MediaResourceSharedPtr_t pMediaResource)
    {
        m_mediaResources.remove(pMediaResource);
    }
}