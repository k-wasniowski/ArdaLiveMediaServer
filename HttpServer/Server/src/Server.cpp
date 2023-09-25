#include <HttpServer/Server.hpp>

#include <HealthCheck/HealthCheckController.hpp>
#include <HttpServer/Resources/WebRtcController.hpp>
#include <HttpServer/Resources/GenericRtpController.hpp>

#include <MediaServer/MediaManager/MediaManager.hpp>

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
        static std::unique_ptr<Impl> Create(MediaServer::MediaManagerSharedPtr_t pMediaManager)
        {
            return std::make_unique<Impl>(std::move(pMediaManager));
        }

        /**
         * @brief Impl
         * @details This constructor will create the server instance.
         */
        Impl(MediaServer::MediaManagerSharedPtr_t pMediaManager)
            : m_pMediaManager{std::move(pMediaManager)}
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
            auto pHealthCheckController = Http::HealthCheckController::Create();
            auto pWebRtcController = HttpServer::Resources::WebRtcController::Create(m_pMediaManager);
            auto pGenericRtpController = HttpServer::Resources::GenericRtpController::Create();

            drogon::app()
                .addListener("127.0.0.1", 80)
                .registerController(pHealthCheckController)
                .registerController(pWebRtcController)
                .run();
        }

    private:
        MediaServer::MediaManagerSharedPtr_t m_pMediaManager;
    };

    ServerUniquePtr_t Server::Create(MediaServer::MediaManagerSharedPtr_t pMediaManager)
    {
        return std::make_unique<Server>(std::move(pMediaManager));
    }

    Server::Server(MediaServer::MediaManagerSharedPtr_t pMediaManager)
        : m_pImpl(Impl::Create(std::move(pMediaManager)))
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
