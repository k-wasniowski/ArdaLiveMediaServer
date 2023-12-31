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

    MediaServer::Rtp::GenericRtpStreamAwaiter GenericRtpClientProxy::Initiate(std::string ip, uint16_t port)
    {
        std::cout << "GenericRtpClient::Initiate()" << std::endl;

        return MediaServer::Rtp::GenericRtpStreamAwaiter(m_pExecutionContext, m_pGenericRtpClient, ip, port);
    }
}