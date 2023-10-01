#pragma once

#include <MediaServer/MediaManager/MediaResource.hpp>

#include <functional>
#include <list>
#include <memory>

namespace MediaServer
{
    class IMediaManager
    {
    public:
        virtual ~IMediaManager() = default;

        virtual bool AddMediaResource(MediaResourceSharedPtr_t pMediaResource) = 0;

        virtual void AddMediaResourceWithCallback(MediaResourceSharedPtr_t pMediaResource, std::function<void(bool)> callback) = 0;

        virtual MediaResourceSharedPtr_t GetMediaResource(std::string resource) = 0;

        virtual void GetMediaResourceWithCallback(std::string resourceName, std::function<void(MediaResourceSharedPtr_t)> callback) = 0;

        virtual void GetMediaResourcesWithCallback(std::function<void(std::list<MediaResourceSharedPtr_t>)> callback) = 0;
    };

    using IMediaManagerSharedPtr_t = std::shared_ptr<IMediaManager>;
}
