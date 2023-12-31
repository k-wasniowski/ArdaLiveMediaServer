#pragma once

#include <string>

#include "Attribute.h"

namespace Media
{
    namespace Sdp
    {
        class ExtMapAttribute;
        using ExtMapAttributeSharedPtr_t = std::shared_ptr<ExtMapAttribute>;

        class ExtMapAttribute : public Attribute
        {
        public:
            ExtMapAttribute() = default;

            ExtMapAttribute(int id, const std::string& uri)
            {
                this->id = id;
                this->uri = uri;
            }

            ExtMapAttribute(int id, const std::string& direction, const std::string& uri, const std::string& attributes)
            {
                this->id = id;
                this->direction = direction;
                this->uri = uri;
                this->attributes = attributes;
            }

            virtual AttributeSharedPtr_t clone() override
            {
                return std::make_shared<ExtMapAttribute>(id, direction, uri, attributes);
            }

            virtual std::string getField() override
            {
                return "extmap";
            }

            virtual std::string getValue() override
            {
                return std::to_string(id) + (!direction.empty() ? "/" + direction : "") + " " + uri +
                       (!attributes.empty() ? " " + attributes : "");
            }

            virtual std::string toString() override
            {
                // Get value
                std::string value = getValue();
                // Generic attr
                return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
            }

            std::string getDirection()
            {
                return direction;
            }

            void setDirection(const std::string& direction)
            {
                this->direction = direction;
            }

            int getId()
            {
                return id;
            }

            void setId(int id)
            {
                this->id = id;
            }

            std::string getUri()
            {
                return uri;
            }

            void setUri(const std::string& uri)
            {
                this->uri = uri;
            }

            std::string getAttributes()
            {
                return attributes;
            }

            void setAttributes(const std::string& attributes)
            {
                this->attributes = attributes;
            }

        private:
            int id = 0;
            std::string direction;
            std::string uri;
            std::string attributes;
        };
    }
}
