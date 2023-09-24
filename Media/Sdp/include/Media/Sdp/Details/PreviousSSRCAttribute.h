#pragma once

#include <Media/Sdp/Details/Attribute.h>

#include <vector>

namespace Media
{
    namespace Sdp
    {
        class PreviousSSRCAttribute;
        using PreviousSSRCAttributeSharedPtr_t = std::shared_ptr<PreviousSSRCAttribute>;

        class PreviousSSRCAttribute : public Attribute
        {
        public:
            PreviousSSRCAttribute() = default;
            ~PreviousSSRCAttribute() = default;

            virtual AttributeSharedPtr_t clone() override
            {
                // Clone
                auto cloned = std::make_shared<PreviousSSRCAttribute>();
                // For each ssrc
                for (auto ssrc : SSRCs)
                    // Add it
                    cloned->addSSRC(ssrc);
                // REturn cloned
                return cloned;
            }

            virtual std::string toString()
            {
                // Get value
                std::string value = getValue();
                // Generic attr
                return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
            }

            virtual std::string getField()
            {
                return "previous-ssrc";
            }

            virtual std::string getValue()
            {
                std::string value;
                for (std::string SSRC : SSRCs)
                    if (value.empty())
                        value = SSRC;
                    else
                        value += " " + SSRC;
                return value;
            }

            void addSSRC(std::string SSRC)
            {
                SSRCs.push_back(SSRC);
            }

            std::vector<std::string> getSSRCs()
            {
                return SSRCs;
            }

            void setSSRCs(const std::vector<std::string>& SSRCs)
            {
                this->SSRCs.clear();
                this->SSRCs.insert(SSRCs.cbegin(), SSRCs.cend(), this->SSRCs.cbegin());
            }

        private:
            std::vector<std::string> SSRCs;
        };
    }

}