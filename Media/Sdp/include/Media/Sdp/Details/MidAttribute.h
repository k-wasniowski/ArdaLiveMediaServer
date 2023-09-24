#pragma once

#include <Media/Sdp/Details/Attribute.h>

namespace Media
{
    namespace Sdp
    {
        class MidAttribute : public Attribute
        {
        public:
            MidAttribute() = default;

            MidAttribute(const std::string& identificationTag)
            {
                this->identificationTag = identificationTag;
            }

            virtual ~MidAttribute() = default;

            virtual AttributeSharedPtr_t clone() override
            {
                return std::make_shared<MidAttribute>(identificationTag);
            }

            virtual std::string toString() override
            {
                // Get value
                std::string value = getValue();
                // Generic attr
                return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
            }

            virtual std::string getField() override
            {
                return "mid";
            }

            virtual std::string getValue() override
            {
                return identificationTag;
            }

            std::string getIdentificationTag()
            {
                return identificationTag;
            }

            void setIdentificationTag(const std::string& identificationTag)
            {
                this->identificationTag = identificationTag;
            }

        private:
            std::string identificationTag;
        };
    }
}
