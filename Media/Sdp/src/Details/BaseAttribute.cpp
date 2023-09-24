#include <Media/Sdp/Details/BaseAttribute.h>

#include <utility>

namespace Media
{
    namespace Sdp
    {
        BaseAttribute::BaseAttribute(std::string field)
            : m_field(std::move(field))
        {}

        BaseAttribute::BaseAttribute(std::string field, std::string value)
            : m_field(std::move(field))
            , m_value(std::move(value))
        {}

        BaseAttribute::BaseAttribute(std::string field, int value)
            : m_field{std::move(field)}
            , m_value{std::to_string(value)}
        {}

        AttributeSharedPtr_t BaseAttribute::clone()
        {
            return std::make_shared<BaseAttribute>(m_field, m_value);
        }

        std::string BaseAttribute::toString()
        {
            std::string value = getValue();

            return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
        }

        std::string BaseAttribute::getField()
        {
            return m_field;
        }

        void BaseAttribute::setField(const std::string& field)
        {
            this->m_field = field;
        }

        std::string BaseAttribute::getValue()
        {
            return m_value;
        }

        void BaseAttribute::setValue(const std::string& value)
        {
            this->m_value = value;
        }
    }
}