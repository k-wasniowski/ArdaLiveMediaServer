#include <HttpServer/Server.hpp>

#include <HttpServer/HealthCheck/HealthCheckController.hpp>
#include <HttpServer/Resources/GenericRtpController.hpp>
#include <HttpServer/Resources/WebRtcController.hpp>

#include <iostream>

namespace HttpServer
{
    class Server::Impl
    {
    public:
        /**
         * @brief Create
         * @details This static method will create a new instance of the server implementation.
         *
         * @return std::unique_ptr<Impl>
         */
        static std::unique_ptr<Impl> Create(MediaServer::ServerSharedPtr_t pMediaServer)
        {
            return std::make_unique<Impl>(std::move(pMediaServer));
        }

        /**
         * @brief Impl
         * @details This constructor will create the server instance.
         */
        Impl(MediaServer::ServerSharedPtr_t pMediaServer)
            : m_pMediaServer{std::move(pMediaServer)}
        {
            std::cout << "Creating Server Impl" << std::endl;
        }

        /**
         * @brief ~Impl
         * @details This destructor will stop the server.
         */
        ~Impl()
        {
            std::cout << "Destroying Server Impl" << std::endl;
        }

        void Run()
        {
            std::cout << "Running Server Impl" << std::endl;
            auto pHealthCheckController = HttpServer::HealthCheckController::Create();
            // auto pWebRtcController = HttpServer::Resources::WebRtcController::Create(m_pMediaManager);
            auto pGenericRtpController = HttpServer::Resources::GenericRtpController::Create(m_pMediaServer);

            drogon::app()
                .addListener("127.0.0.1", 80)
                .registerController(pHealthCheckController)
                //.registerController(pWebRtcController)
                .registerController(pGenericRtpController)
                .run();
        }

    private:
        MediaServer::ServerSharedPtr_t m_pMediaServer;
    };

    ServerUniquePtr_t Server::Create(MediaServer::ServerSharedPtr_t pMediaServer)
    {
        return std::make_unique<Server>(std::move(pMediaServer));
    }

    Server::Server(MediaServer::ServerSharedPtr_t pMediaServer)
        : m_pImpl(Impl::Create(std::move(pMediaServer)))
    {
        std::cout << "Creating Server" << std::endl;
    }

    Server::~Server()
    {
        std::cout << "Destroying Server" << std::endl;

        m_pImpl = nullptr;
    }

    void Server::Run()
    {
        std::cout << "Running Server" << std::endl;

        if (!m_pImpl)
        {
            std::cout << "Server implementation is not initialized" << std::endl;

            return;
        }

        m_pImpl->Run();
    }
};
