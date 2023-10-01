#include <MediaServer/MediaManagerProxy.hpp>

namespace MediaServer
{
    MediaManagerProxySharedPtr_t MediaManagerProxy::Create(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                                           IMediaManagerSharedPtr_t pMediaManager)
    {
        return std::make_shared<MediaManagerProxy>(pExecutionContext, pMediaManager);
    }

    MediaManagerProxy::MediaManagerProxy(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                         IMediaManagerSharedPtr_t pMediaManager)
        : m_pExecutionContext{pExecutionContext}
        , m_pMediaManager{pMediaManager}
    {}

    MediaManagerProxy::~MediaManagerProxy() {}

    MediaResourceAddAwaiter MediaManagerProxy::AddMediaResource(MediaResourceSharedPtr_t pMediaResource)
    {
        return MediaResourceAddAwaiter{m_pExecutionContext, m_pMediaManager, pMediaResource};
    }

    MediaResourceAwaiter MediaManagerProxy::GetMediaResource(std::string resourceName)
    {
        return MediaResourceAwaiter{m_pExecutionContext, m_pMediaManager, resourceName};
    }

    MediaResourcesAwaiter MediaManagerProxy::GetMediaResources()
    {
        return MediaResourcesAwaiter{m_pExecutionContext, m_pMediaManager};
    }
}