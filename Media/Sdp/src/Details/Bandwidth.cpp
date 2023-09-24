#include <Media/Sdp/Details/Bandwidth.h>

namespace Media
{
    namespace Sdp
    {
        Bandwidth::Bandwidth(const std::string& type, const std::string& bandwidth)
        {
            this->m_type = type;
            this->m_bandwidth = bandwidth;
        }

        std::string Bandwidth::toString()
        {
            return "b=" + m_type + ":" + m_bandwidth + "\r\n";
        }

        BandwidthSharedPtr_t Bandwidth::clone()
        {
            return std::make_shared<Bandwidth>(m_type, m_bandwidth);
        }

        std::string Bandwidth::getBandwidth()
        {
            return m_bandwidth;
        }

        void Bandwidth::setBandwidth(const std::string& bandwidth)
        {
            this->m_bandwidth = bandwidth;
        }

        std::string Bandwidth::getType()
        {
            return m_type;
        }

        void Bandwidth::setType(const std::string& type)
        {
            this->m_type = type;
        }
    }
}
