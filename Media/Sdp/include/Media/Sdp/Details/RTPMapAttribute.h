#pragma once

#include <Media/Sdp/Details/Attribute.h>

#include <string>

namespace Media
{
    namespace Sdp
    {
        class RTPMapAttribute;
        using RTPMapAttributeSharedPtr_t = std::shared_ptr<RTPMapAttribute>;

        class RTPMapAttribute : public Attribute
        {
        public:
            RTPMapAttribute() = default;

            RTPMapAttribute(int format, std::string name, int rate, std::string parameters)
            {
                this->format = format;
                this->name = name;
                this->rate = rate;
                this->parameters = parameters;
            }

            RTPMapAttribute(int format, const std::string& name, int rate)
            {
                this->format = format;
                this->name = name;
                this->rate = rate;
            }
            virtual ~RTPMapAttribute() = default;

            virtual AttributeSharedPtr_t clone() override
            {
                return std::make_shared<RTPMapAttribute>(format, name, rate, parameters);
            }

            virtual std::string getField() override
            {
                return "rtpmap";
            }

            virtual std::string getValue() override
            {
                return std::to_string(format) + " " + name + "/" + std::to_string(rate) + (!parameters.empty() ? "/" + parameters : "");
            }

            virtual std::string toString() override
            {
                // Get value
                std::string value = getValue();
                // Generic attr
                return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
            }

            int getFormat()
            {
                return format;
            }

            void setFormat(int format)
            {
                this->format = format;
            }

            std::string getName()
            {
                return name;
            }

            void setName(const std::string& name)
            {
                this->name = name;
            }

            std::string getParameters()
            {
                return parameters;
            }

            void setParameters(const std::string& parameters)
            {
                this->parameters = parameters;
            }

            int getRate()
            {
                return rate;
            }

            void setRate(int rate)
            {
                this->rate = rate;
            }

        private:
            int format = 0;
            std::string name;
            int rate = 0;
            std::string parameters;
        };
    }
}
