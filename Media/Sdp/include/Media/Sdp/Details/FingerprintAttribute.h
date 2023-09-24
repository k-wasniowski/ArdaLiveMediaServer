#pragma once

#include <Media/Sdp/Details/Attribute.h>

namespace Media
{
    namespace Sdp
    {
        class FingerprintAttribute;
        using FingerprintAttributeSharedPtr_t = std::shared_ptr<FingerprintAttribute>;

        class FingerprintAttribute : public Attribute
        {
        public:
            FingerprintAttribute() = default;
            FingerprintAttribute(const std::string& hashFunc, const std::string& fingerprint)
            {
                this->hashFunc = hashFunc;
                this->fingerprint = fingerprint;
            }
            ~FingerprintAttribute() = default;

            virtual AttributeSharedPtr_t clone() override
            {
                return std::make_shared<FingerprintAttribute>(hashFunc, fingerprint);
            }

            virtual std::string getField() override
            {
                return "fingerprint";
            }

            virtual std::string getValue() override
            {
                return hashFunc + " " + fingerprint;
            }

            virtual std::string toString() override
            {
                // Get value
                std::string value = getValue();
                // Generic attr
                return "a=" + getField() + (!value.empty() ? ":" + value : "") + "\r\n";
            }

            std::string getFingerprint()
            {
                return fingerprint;
            }

            void setFingerprint(const std::string& fingerprint)
            {
                this->fingerprint = fingerprint;
            }

            std::string getHashFunc()
            {
                return hashFunc;
            }

            void setHashFunc(const std::string& hashFunc)
            {
                this->hashFunc = hashFunc;
            }

        private:
            std::string hashFunc;
            std::string fingerprint;
        };
    }
}
