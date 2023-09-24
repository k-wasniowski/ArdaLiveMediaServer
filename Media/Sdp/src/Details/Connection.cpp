#include <Media/Sdp/Details/Connection.h>

namespace Media
{
    namespace Sdp
    {
        ConnectionSharedPtr_t Connection::Create(const std::string& netType, const std::string& addrType, const std::string& address)
        {
            return std::make_shared<Connection>(netType, addrType, address);
        }

        Connection::Connection(const std::string& netType, const std::string& addrType, const std::string& address)
            : m_netType{netType}
            , m_addrType{addrType}
            , m_address{address}
        {}

        ConnectionSharedPtr_t Connection::clone()
        {
            return Create(m_netType, m_addrType, m_address);
        }

        std::string Connection::toString()
        {
            return "c=" + m_netType + " " + m_addrType + " " + m_address + "\r\n";
        }

        std::string Connection::getAddrType()
        {
            return m_addrType;
        }

        void Connection::setAddrType(const std::string& addrType)
        {
            m_addrType = addrType;
        }

        std::string Connection::getAddress()
        {
            return m_address;
        }

        void Connection::setAddress(const std::string& address)
        {
            m_address = address;
        }

        std::string Connection::getNetType()
        {
            return m_netType;
        }

        void Connection::setNetType(const std::string& netType)
        {
            m_netType = netType;
        }
    }
}