#pragma once

#include <memory>
#include <string>

namespace Media
{
    namespace Sdp
    {
        class Attribute;
        using AttributeSharedPtr_t = std::shared_ptr<Attribute>;

        class Attribute
        {
        public:
            virtual std::string toString() = 0;
            virtual AttributeSharedPtr_t clone() = 0;
            virtual std::string getField() = 0;
            virtual std::string getValue() = 0;
            virtual ~Attribute() = default;
        };
    }
}
