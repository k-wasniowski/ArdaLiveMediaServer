#pragma once

#include <memory>

#include <MediaServer/MediaManager/IMediaManager.hpp>

#include <Gondor/Execution/CallbackAwaiter.hpp>
#include <Gondor/Execution/ExecutionContext.hpp>

#include <coroutine>
#include <iostream>

namespace MediaServer
{
    class MediaResourceAwaiter : public Gondor::Execution::CallbackAwaiter<MediaResourceSharedPtr_t>
    {
    public:
        MediaResourceAwaiter(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                             IMediaManagerSharedPtr_t pMediaManager,
                             std::string resourceName)
            : m_pExecutionContext{pExecutionContext}
            , m_pMediaManager{pMediaManager}
            , m_resourceName{resourceName}
        {
            std::cout << "MediaResourceAwaiter::MediaResourceAwaiter()" << std::endl;
        }

        ~MediaResourceAwaiter() override
        {
            std::cout << "MediaResourceAwaiter::~MediaResourceAwaiter()" << std::endl;
        }

        void await_suspend(std::coroutine_handle<> handle)
        {
            auto pExecutionContext = m_pExecutionContext.lock();
            if (!pExecutionContext)
            {
                SetValue(nullptr);
                handle.resume();
            }

            auto task = std::bind(&MediaServer::IMediaManager::GetMediaResourceWithCallback,
                                  m_pMediaManager,
                                  m_resourceName,
                                  [this, handle](MediaResourceSharedPtr_t pMediaResource) -> void {
                                      SetValue(pMediaResource);
                                      handle.resume();
                                  });

            auto result = pExecutionContext->PostTask(task);
            if (!result)
            {
                SetValue(nullptr);
                handle.resume();
            }
        }

    private:
        Gondor::Execution::ExecutionContextWeakPtr m_pExecutionContext;
        IMediaManagerSharedPtr_t m_pMediaManager;
        std::string m_resourceName;
    };

    class MediaResourcesAwaiter : public Gondor::Execution::CallbackAwaiter<std::list<MediaResourceSharedPtr_t>>
    {
    public:
        MediaResourcesAwaiter(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext, IMediaManagerSharedPtr_t pMediaManager)
            : m_pExecutionContext{pExecutionContext}
            , m_pMediaManager{pMediaManager}
        {
            std::cout << "MediaResourcesAwaiter::MediaResourcesAwaiter()" << std::endl;
        }

        ~MediaResourcesAwaiter() override
        {
            std::cout << "MediaResourcesAwaiter::~MediaResourcesAwaiter()" << std::endl;
        }

        void await_suspend(std::coroutine_handle<> handle)
        {
            auto pExecutionContext = m_pExecutionContext.lock();
            if (!pExecutionContext)
            {
                SetValue({});
                handle.resume();
            }

            auto task = std::bind(&MediaServer::IMediaManager::GetMediaResourcesWithCallback,
                                  m_pMediaManager,
                                  [this, handle](std::list<MediaResourceSharedPtr_t> pMediaResources) -> void {
                                      SetValue(pMediaResources);
                                      handle.resume();
                                  });

            auto result = pExecutionContext->PostTask(task);
            if (!result)
            {
                SetValue({});
                handle.resume();
            }
        }

    private:
        Gondor::Execution::ExecutionContextWeakPtr m_pExecutionContext;
        IMediaManagerSharedPtr_t m_pMediaManager;
    };

    class MediaResourceAddAwaiter : public Gondor::Execution::CallbackAwaiter<bool>
    {
    public:
        MediaResourceAddAwaiter(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                IMediaManagerSharedPtr_t pMediaManager,
                                MediaResourceSharedPtr_t pMediaResource)
            : m_pExecutionContext{pExecutionContext}
            , m_pMediaManager{pMediaManager}
            , m_pMediaResource{pMediaResource}
        {
            std::cout << "MediaResourceAddAwaiter::MediaResourceAddAwaiter()" << std::endl;
        }

        ~MediaResourceAddAwaiter() override
        {
            std::cout << "MediaResourceAddAwaiter::~MediaResourceAddAwaiter()" << std::endl;
        }

        void await_suspend(std::coroutine_handle<> handle)
        {
            auto pExecutionContext = m_pExecutionContext.lock();
            if (!pExecutionContext)
            {
                SetValue(false);
                handle.resume();
            }

            auto task = std::bind(&MediaServer::IMediaManager::AddMediaResourceWithCallback,
                                  m_pMediaManager,
                                  m_pMediaResource,
                                  [this, handle](bool result) -> void {
                                      SetValue(result);
                                      handle.resume();
                                  });

            auto result = pExecutionContext->PostTask(task);
            if (!result)
            {
                SetValue(false);
                handle.resume();
            }
        }

    private:
        Gondor::Execution::ExecutionContextWeakPtr m_pExecutionContext;
        IMediaManagerSharedPtr_t m_pMediaManager;
        MediaResourceSharedPtr_t m_pMediaResource;
    };

    class MediaManagerProxy;
    using MediaManagerProxySharedPtr_t = std::shared_ptr<MediaManagerProxy>;

    class MediaManagerProxy
    {
    public:
        static MediaManagerProxySharedPtr_t Create(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                                   IMediaManagerSharedPtr_t pMediaManager);
        MediaManagerProxy(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext, IMediaManagerSharedPtr_t pMediaManager);
        ~MediaManagerProxy();

        MediaResourceAddAwaiter AddMediaResource(MediaResourceSharedPtr_t pMediaResource);
        MediaResourceAwaiter GetMediaResource(std::string resourceName);
        MediaResourcesAwaiter GetMediaResources();

    private:
        Gondor::Execution::ExecutionContextWeakPtr m_pExecutionContext;
        IMediaManagerSharedPtr_t m_pMediaManager;
    };
}