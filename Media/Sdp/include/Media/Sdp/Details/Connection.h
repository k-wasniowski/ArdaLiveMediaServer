#pragma once

#include <string>
#include <memory>

namespace Media
{
    namespace Sdp
    {
        class Connection;
        using ConnectionSharedPtr_t = std::shared_ptr<Connection>;

        class Connection
        {
        public:
            static ConnectionSharedPtr_t Create(const std::string& netType, const std::string& addrType, const std::string& address);

            Connection() = default;

            Connection(const std::string& netType, const std::string& addrType, const std::string& address);

            ConnectionSharedPtr_t clone();

            std::string toString();

            void setAddrType(const std::string& addrType);
            void setAddress(const std::string& address);
            void setNetType(const std::string& netType);

            std::string getAddrType();
            std::string getAddress();
            std::string getNetType();

        private:
            std::string m_netType;
            std::string m_addrType;
            std::string m_address;
        };
    }

}
