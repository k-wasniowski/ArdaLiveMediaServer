#pragma once

#include <MediaServer/GenericRtpClient/IGenericRtpClient.hpp>

#include <memory>

namespace MediaServer
{
    class Server;
    using ServerSharedPtr_t = std::shared_ptr<Server>;

    /**
     * @brief The Server class
     * @details This class is the main entry point for the MediaServer library.
     */
    class Server
    {
    public:
        /**
         * @brief Create
         * @details This static method will create a new instance of the server.
         *
         * @return ServerUniquePtr_t
         */
        static ServerSharedPtr_t Create();

        /**
         * @brief Server
         * @details This constructor will create the server instance.
         *
         */
        Server();

        /**
         * @brief ~Server
         * @details This destructor will stop the server.
         * It will also wait for all requests to finish before stopping.
         * This means that the destructor will block until all requests are finished.
         * This is to ensure that all requests are handled before the server is stopped.
         */
        ~Server();

        /**
         * @brief Run
         * @details This method will start the server.
         */
        void Run();

        /**
         * @brief Terminate
         * @details This method will stop the server.
         */
        void Terminate();

        MediaServer::Rtp::IGenericRtpClientProxySharedPtr_t MakeGenericRtpClient();

    private:
        class Impl;

        /**
         * @brief m_pImpl
         * @details This is the implementation of the server.
         */
        std::unique_ptr<Impl> m_pImpl;
    };
};
