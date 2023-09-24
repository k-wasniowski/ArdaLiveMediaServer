#include <Media/Sdp/Details/CNameAttribute.h>

#include <utility>

namespace Media
{
    namespace Sdp
    {
        CNameAttributeSharedPtr_t CNameAttribute::Create(const std::string& cname)
        {
            return std::make_shared<CNameAttribute>(cname);
        }

        CNameAttribute::CNameAttribute(std::string cname)
            : m_cname{std::move(cname)}
        {}

        AttributeSharedPtr_t CNameAttribute::clone()
        {
            return Create(m_cname);
        }

        std::string CNameAttribute::toString()
        {
            std::string value = getValue();

            return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
        }

        std::string CNameAttribute::getField()
        {
            return "cname";
        }

        std::string CNameAttribute::getValue()
        {
            return m_cname;
        }

        std::string CNameAttribute::getCName()
        {
            return m_cname;
        }

        void CNameAttribute::setCName(const std::string& cname)
        {
            this->m_cname = cname;
        }
    }
}