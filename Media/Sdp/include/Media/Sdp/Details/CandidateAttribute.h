#pragma once

#include <Media/Sdp/Details/Attribute.h>

#include <string>
#include <vector>

namespace Media
{
    namespace Sdp
    {
        class CandidateAttribute;
        using CandidateAttributeSharedPtr_t = std::shared_ptr<CandidateAttribute>;

        class CandidateAttribute : public Attribute
        {
        public:
            class Extension
            {
            public:
                Extension() = default;

                Extension(const std::string& name, const std::string& value)
                {
                    this->name = name;
                    this->value = value;
                }

                void setName(const std::string& name)
                {
                    this->name = name;
                }

                void setValue(const std::string& value)
                {
                    this->value = value;
                }

            private:
                friend class CandidateAttribute;
                std::string name;
                std::string value;
            };

        public:
            CandidateAttribute() = default;
            ~CandidateAttribute() override = default;

            CandidateAttribute(std::string fundation,
                               int componentId,
                               std::string transport,
                               int priority,
                               std::string address,
                               int port,
                               std::string type);

            [[nodiscard]] AttributeSharedPtr_t clone() override;

            [[nodiscard]] std::string toString() override;

            [[nodiscard]] std::string getField() override;

            [[nodiscard]] std::string getValue() override;

            [[nodiscard]] std::string getAddress();

            void setAddress(const std::string& address);

            [[nodiscard]] int getComponentId() const;

            void setComponentId(int componentId);

            [[nodiscard]] std::vector<std::shared_ptr<Extension>> getExtensions();

            void setExtensions(const std::vector<std::shared_ptr<Extension>>& extensions);

            [[nodiscard]] std::string getFundation();

            void setFundation(const std::string& fundation);

            [[nodiscard]] int getPort() const;

            void setPort(int port);

            [[nodiscard]] int getPriority() const;

            void setPriority(int priority);

            std::string getRelAddr();

            void setRelAddr(const std::string& relAddr);

            [[nodiscard]] int getRelPort() const;

            void setRelPort(int relPort);

            [[nodiscard]] std::string getTransport();

            void setTransport(const std::string& transport);

            [[nodiscard]] std::string getType();

            void setType(std::string type);

            void addExtension(const std::string& name, const std::string& value);

            void addExtension(const std::shared_ptr<Extension>& extension);

        private:
            std::string m_fundation;
            int m_componentId = 0;
            std::string m_transport;
            int m_priority = 0;
            std::string m_address;
            int m_port = 0;
            std::string m_type;
            std::string m_relAddr;
            int m_relPort = 0;
            std::vector<std::shared_ptr<Extension>> m_extensions;
        };
    }
}
