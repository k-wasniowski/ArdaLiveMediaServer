#pragma once

#include <MediaServer/MediaManager/MediaManager.hpp>
#include <MediaServer/Server.hpp>

#include <memory>

namespace HttpServer
{
    class Server;
    using ServerUniquePtr_t = std::unique_ptr<Server>;

    /**
     * @brief The Server class
     * @details This class is the main entry point for the HttpServer library.
     * It is responsible for starting the server and handling all incoming requests.
     * It is also responsible for handling all outgoing responses.
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
        static ServerUniquePtr_t Create(MediaServer::MediaManagerSharedPtr_t pMediaManager, MediaServer::ServerSharedPtr_t pMediaServer);

        /**
         * @brief Server
         * @details This constructor will create the server instance.
         *
         */
        Server(MediaServer::MediaManagerSharedPtr_t pMediaManager, MediaServer::ServerSharedPtr_t pMediaServer);

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

    private:
        class Impl;

        /**
         * @brief m_pImpl
         * @details This is the implementation of the server.
         */
        std::unique_ptr<Impl> m_pImpl;
    };
};
