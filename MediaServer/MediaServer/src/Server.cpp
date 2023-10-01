#include <MediaServer/GenericRtpClientProxy.hpp>
#include <MediaServer/Server.hpp>

#include <Gondor/Execution/ExecutionContext.hpp>

#include <boost/asio.hpp>

#include <iostream>

namespace MediaServer
{
    class Server::Impl
    {
    public:
        static std::unique_ptr<Server::Impl> Create()
        {
            return std::make_unique<Impl>();
        }

        Impl()
            : m_pExecutionContext{Gondor::Execution::ExecutionContext::Create()}
            , m_pGenericRtpClient{MediaServer::Rtp::GenericRtpClient::Create()}
        {
            std::cout << "Creating Server!" << std::endl;
        }

        ~Impl()
        {
            std::cout << "Destroying Server!" << std::endl;
        }

        void Run()
        {
            std::cout << "Running Server!" << std::endl;
            if (m_pExecutionContext)
            {
                m_pExecutionContext->Run();
            }
        }

        void Terminate()
        {
            std::cout << "Terminating Server!" << std::endl;
            if (m_pExecutionContext)
            {
                m_pExecutionContext->Terminate();
            }
        }

        MediaServer::Rtp::IGenericRtpClientProxySharedPtr_t MakeGenericRtpClient()
        {
            return GenericRtpClientProxy::Create(m_pExecutionContext, m_pGenericRtpClient);
        }

    private:
        Gondor::Execution::ExecutionContextSharedPtr m_pExecutionContext;
        MediaServer::Rtp::GenericRtpClientSharedPtr_t m_pGenericRtpClient;
    };

    ServerSharedPtr_t Server::Create()
    {
        return std::make_shared<Server>();
    }

    Server::Server()
        : m_pImpl{Impl::Create()}
    {
        std::cout << "Creating Server!" << std::endl;
    }

    Server::~Server()
    {
        std::cout << "Destroying Server!" << std::endl;
    }

    void Server::Run()
    {
        std::cout << "Running Server!" << std::endl;
        if (m_pImpl)
        {
            m_pImpl->Run();
        }
    }

    void Server::Terminate()
    {
        std::cout << "Terminating Server!" << std::endl;
        if (m_pImpl)
        {
            m_pImpl->Terminate();
        }
    }

    MediaServer::Rtp::IGenericRtpClientProxySharedPtr_t Server::MakeGenericRtpClient()
    {
        if (!m_pImpl)
        {
            return nullptr;
        }

        return m_pImpl->MakeGenericRtpClient();
    }
}