#include <MediaServer/Server.hpp>

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
        {
            std::cout << "Creating Server!" << std::endl;
        }

        ~Impl()
        {
            std::cout << "Destroying Server!" << std::endl;

            if (m_ioContextThread.joinable())
            {
                m_ioContextThread.join();
            }
        }

        void Run()
        {
            std::cout << "Running Server!" << std::endl;
            m_ioContextThread = std::thread([this]() {
                auto work = boost::asio::make_work_guard(m_ioContext);
                m_ioContext.run();
            });
        }

    private:
        boost::asio::io_context m_ioContext;
        std::thread m_ioContextThread;

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
    }
}