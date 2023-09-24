#pragma once

#include <memory>
#include <string>

namespace Media
{
    namespace Sdp
    {
        class Bandwidth;
        using BandwidthSharedPtr_t = std::shared_ptr<Bandwidth>;

        class Bandwidth
        {
        public:
            Bandwidth() = default;

            Bandwidth(const std::string& type, const std::string& bandwidth);

            virtual ~Bandwidth() = default;

            std::string toString();

            BandwidthSharedPtr_t clone();

            std::string getBandwidth();

            void setBandwidth(const std::string& bandwidth);

            std::string getType();

            void setType(const std::string& type);

        private:
            std::string m_type;
            std::string m_bandwidth;
        };
    }
}
