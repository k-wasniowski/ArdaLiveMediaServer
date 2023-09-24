#pragma once

#include <string>

#include <Media/Sdp/Details/Attribute.h>

namespace Media
{
    namespace Sdp
    {
        class CNameAttribute;
        using CNameAttributeSharedPtr_t = std::shared_ptr<CNameAttribute>;

        class CNameAttribute : public Attribute
        {
        public:
            static CNameAttributeSharedPtr_t Create(const std::string& cname);

            CNameAttribute() = default;
            ~CNameAttribute() override = default;

            explicit CNameAttribute(std::string  cname);

            AttributeSharedPtr_t clone() override;

            std::string toString() override;

            std::string getField() override;

            std::string getValue() override;

            std::string getCName();

            void setCName(const std::string& cname);

        private:
            std::string m_cname;
        };
    }
}
