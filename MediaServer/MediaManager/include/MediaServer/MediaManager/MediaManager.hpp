#pragma once

#include <MediaServer/MediaManager/IMediaManager.hpp>

#include <MediaServer/MediaManager/MediaResource.hpp>

#include <list>
#include <memory>

namespace MediaServer
{
    class MediaManager;
    using MediaManagerSharedPtr_t = std::shared_ptr<MediaManager>;

    class MediaManager : public IMediaManager
    {
    public:
        static MediaManagerSharedPtr_t Create();

        MediaManager();
        ~MediaManager();

        bool AddMediaResource(MediaResourceSharedPtr_t pMediaResource) override;

        void AddMediaResourceWithCallback(MediaResourceSharedPtr_t pMediaResource, std::function<void(bool)> callback) override;

        MediaResourceSharedPtr_t GetMediaResource(std::string resource) override;

        void GetMediaResourceWithCallback(std::string resourceName, std::function<void(MediaResourceSharedPtr_t)> callback) override;

        void GetMediaResourcesWithCallback(std::function<void(std::list<MediaResourceSharedPtr_t>)> callback) override;

        void RemoveMediaResource(MediaResourceSharedPtr_t pMediaResource);

    private:
        std::list<MediaResourceSharedPtr_t> m_mediaResources;
    };
}
