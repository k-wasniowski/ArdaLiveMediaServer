#include <MediaServer/GenericRtpClientProxy.hpp>

#include <iostream>

namespace MediaServer
{
    GenericRtpClientProxySharedPtr_t GenericRtpClientProxy::Create(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                                                   MediaServer::Rtp::GenericRtpClientSharedPtr_t pGenericRtpClient)
    {
        return std::make_shared<GenericRtpClientProxy>(pExecutionContext, pGenericRtpClient);
    }

    GenericRtpClientProxy::GenericRtpClientProxy(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                                 MediaServer::Rtp::GenericRtpClientSharedPtr_t pGenericRtpClient)
        : m_pExecutionContext{pExecutionContext}
        , m_pGenericRtpClient{pGenericRtpClient}
    {
        std::cout << "GenericRtpClientProxy::GenericRtpClientProxy()" << std::endl;
    }

    GenericRtpClientProxy::~GenericRtpClientProxy()
    {
        std::cout << "GenericRtpClientProxy::~GenericRtpClientProxy()" << std::endl;
    }

    bool GenericRtpClientProxy::InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription)
    {
        return true;
//        std::cout << "GenericRtpClientProxy::InitiateNewSession()" << std::endl;
//
//        auto pExecutionContext = m_pExecutionContext.lock();
//        if (!pExecutionContext)
//        {
//            std::cout << "GenericRtpClientProxy::InitiateNewSession() - pExecutionContext is null!" << std::endl;
//            return false;
//        }
//
//        auto task = std::bind(&MediaServer::Rtp::GenericRtpClient::InitiateNewSession, m_pGenericRtpClient, ip, port, sessionDescription);
//
//        return pExecutionContext->PostTask(task);
    }

    MediaServer::Rtp::GenericRtpStreamAwaiter GenericRtpClientProxy::Initiate(std::string ip, uint16_t port, std::string sessionDescription)
    {
        std::cout << "GenericRtpClient::Initiate()" << std::endl;

        return MediaServer::Rtp::GenericRtpStreamAwaiter(m_pExecutionContext, m_pGenericRtpClient, ip, port, sessionDescription);
    }
}