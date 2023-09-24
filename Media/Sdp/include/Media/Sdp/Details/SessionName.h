#pragma once

#include <memory>
#include <string>

namespace Media
{
    namespace Sdp
    {
        class SessionName;
        using SessionNameSharedPtr_t = std::shared_ptr<SessionName>;

        class SessionName
        {
        public:
            static SessionNameSharedPtr_t Create(const std::string& name)
            {
                return std::make_shared<SessionName>(name);
            }

            SessionName() {}

            SessionName(const std::string& name)
            {
                this->name = name;
            }

            SessionNameSharedPtr_t clone()
            {
                return std::make_shared<SessionName>(name);
            }

            std::string toString()
            {
                return "s=" + name + "\r\n";
            }

            std::string getName()
            {
                return name;
            }

            void setName(const std::string& name)
            {
                this->name = name;
            }

        private:
            std::string name;
        };
    }
}
