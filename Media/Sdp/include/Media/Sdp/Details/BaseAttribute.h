#pragma once

#include <string>

#include <Media/Sdp/Details/Attribute.h>

namespace Media
{
    namespace Sdp
    {
        class BaseAttribute;
        using BaseAttributeSharedPtr_t = std::shared_ptr<BaseAttribute>;

        class BaseAttribute : public Attribute
        {
        public:
            BaseAttribute() = default;
            virtual ~BaseAttribute() = default;

            explicit BaseAttribute(std::string  field);

            BaseAttribute(std::string  field, std::string  value);

            BaseAttribute(std::string  field, int value);

            AttributeSharedPtr_t clone() override;

            std::string toString() override;

            std::string getField() override;

            void setField(const std::string& field);

            std::string getValue() override;

            void setValue(const std::string& value);

        private:
            std::string m_field;
            std::string m_value;
        };
    }

}