#pragma once

#include <memory>
#include <string>

namespace Media
{
    namespace Sdp
    {
        class Information;
        using InformationSharedPtr_t = std::shared_ptr<Information>;

        class Information
        {
        public:
            Information() = default;

            Information(const std::string& text)
            {
                this->text = text;
            }

            InformationSharedPtr_t clone()
            {
                return std::make_shared<Information>(text);
            }

            std::string toString()
            {
                return "i=" + text + "\r\n";
            }

            std::string getText()
            {
                return text;
            }

            void setText(std::string text)
            {
                this->text = text;
            }

        private:
            std::string text;
        };
    }
}
