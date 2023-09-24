#include <Media/Sdp/Details/CandidateAttribute.h>

#include <utility>

namespace Media
{
    namespace Sdp
    {
        CandidateAttribute::CandidateAttribute(
            std::string fundation, int componentId, std::string transport, int priority, std::string address, int port, std::string type)
            : m_fundation(std::move(fundation))
            , m_componentId(componentId)
            , m_transport(std::move(transport))
            , m_priority(priority)
            , m_address(std::move(address))
            , m_port(port)
            , m_type(std::move(type))
        {}

        AttributeSharedPtr_t CandidateAttribute::clone()
        {
            return std::make_shared<CandidateAttribute>(m_fundation, m_componentId, m_transport, m_priority, m_address, m_port, m_type);
        }

        std::string CandidateAttribute::toString()
        {
            std::string value = getValue();

            return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
        }

        std::string CandidateAttribute::getField()
        {
            return "candidate";
        }

        std::string CandidateAttribute::getValue()
        {
            std::string value = m_fundation + " " + std::to_string(m_componentId) + " " + m_transport + " " + std::to_string(m_priority) +
                                " " + m_address + " " + std::to_string(m_port) + " typ " + m_type;
            if (!m_relAddr.empty())
                value += " raddr " + m_relAddr;
            if (m_relPort > 0)
                value += " rport " + std::to_string(m_relPort);
            for (const auto& ext : m_extensions)
                value += " " + ext->name + " " + ext->value;
            return value;
        }

        std::string CandidateAttribute::getAddress()
        {
            return m_address;
        }

        void CandidateAttribute::setAddress(const std::string& address)
        {
            m_address = address;
        }

        int CandidateAttribute::getComponentId() const
        {
            return m_componentId;
        }

        void CandidateAttribute::setComponentId(int componentId)
        {
            m_componentId = componentId;
        }

        std::vector<std::shared_ptr<CandidateAttribute::Extension>> CandidateAttribute::getExtensions()
        {
            return m_extensions;
        }

        void CandidateAttribute::setExtensions(const std::vector<std::shared_ptr<Extension>>& extensions)
        {
            m_extensions = extensions;
        }

        std::string CandidateAttribute::getFundation()
        {
            return m_fundation;
        }

        void CandidateAttribute::setFundation(const std::string& fundation)
        {
            m_fundation = fundation;
        }

        int CandidateAttribute::getPort() const
        {
            return m_port;
        }

        void CandidateAttribute::setPort(int port)
        {
            m_port = port;
        }

        int CandidateAttribute::getPriority() const
        {
            return m_priority;
        }

        void CandidateAttribute::setPriority(int priority)
        {
            m_priority = priority;
        }

        std::string CandidateAttribute::getRelAddr()
        {
            return m_relAddr;
        }

        void CandidateAttribute::setRelAddr(const std::string& relAddr)
        {
            m_relAddr = relAddr;
        }

        int CandidateAttribute::getRelPort() const
        {
            return m_relPort;
        }

        void CandidateAttribute::setRelPort(int relPort)
        {
            m_relPort = relPort;
        }

        std::string CandidateAttribute::getTransport()
        {
            return m_transport;
        }

        void CandidateAttribute::setTransport(const std::string& transport)
        {
            m_transport = transport;
        }

        std::string CandidateAttribute::getType()
        {
            return m_type;
        }

        void CandidateAttribute::setType(std::string type)
        {
            m_type = std::move(type);
        }

        void CandidateAttribute::addExtension(const std::string& name, const std::string& value)
        {
            m_extensions.push_back(std::make_shared<Extension>(Extension(name, value)));
        }

        void CandidateAttribute::addExtension(const std::shared_ptr<Extension>& extension)
        {
            m_extensions.push_back(extension);
        }
    }
}