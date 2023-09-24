#pragma once

#include <string>

namespace Media
{
    namespace Sdp
    {
        class Connection;
        using ConnectionSharedPtr_t = std::shared_ptr<Connection>;

        class Connection
        {
        public:
            static ConnectionSharedPtr_t Create(const std::string& netType, const std::string& addrType, const std::string& address)
            {
                return std::make_shared<Connection>(netType, addrType, address);
            }
            
            Connection() = default;

            Connection(const std::string& netType, const std::string& addrType, const std::string& address)
            {
                this->netType = netType;
                this->addrType = addrType;
                this->address = address;
            }

            ConnectionSharedPtr_t clone()
            {
                return std::make_shared<Connection>(netType, addrType, address);
            }

            std::string toString()
            {
                return "c=" + netType + " " + addrType + " " + address + "\r\n";
            }

            std::string getAddrType()
            {
                return addrType;
            }

            void setAddrType(const std::string& addrType)
            {
                this->addrType = addrType;
            }

            std::string getAddress()
            {
                return address;
            }

            void setAddress(const std::string& address)
            {
                this->address = address;
            }

            std::string getNetType()
            {
                return netType;
            }

            void setNetType(const std::string& netType)
            {
                this->netType = netType;
            }

        private:
            std::string netType;
            std::string addrType;
            std::string address;
        };
    }

}
