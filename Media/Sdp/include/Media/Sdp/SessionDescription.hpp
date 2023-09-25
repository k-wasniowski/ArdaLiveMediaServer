#pragma once

#include <Media/Sdp/Details/Attribute.h>
#include <Media/Sdp/Details/Bandwidth.h>
#include <Media/Sdp/Details/Connection.h>
#include <Media/Sdp/Details/Information.h>
#include <Media/Sdp/Details/Key.h>
#include <Media/Sdp/Details/MediaDescription.h>
#include <Media/Sdp/Details/Origin.h>
#include <Media/Sdp/Details/SessionName.h>
#include <Media/Sdp/Details/Timing.h>

#include <memory>

namespace Media
{
    namespace Sdp
    {
        class SessionDescription;
        using SessionDescriptionSharedPtr_t = std::shared_ptr<SessionDescription>;

        class SessionDescription
        {
        public:
            static SessionDescriptionSharedPtr_t Parse(const std::string& string);

            explicit SessionDescription(int version = 0);
            ~SessionDescription() = default;

            SessionDescriptionSharedPtr_t clone();

            std::string toString();

            template <typename T = Attribute>
            std::shared_ptr<T> Attribute(const std::string& key)
            {
                // For each attribute
                for (auto attr : attributes)
                    // Check if the one searhced
                    if (strcasecmp(attr->getField().c_str(), key.c_str()) == 0)
                        // Try to convert it
                        return std::dynamic_pointer_cast<T>(attr);
                // Not found
                return std::shared_ptr<T>();
            }

            template <typename T>
            std::shared_ptr<T> Attribute()
            {
                // For each attribute
                for (auto attr : attributes)
                {
                    // Try to convert it
                    auto t = std::dynamic_pointer_cast<T>(attr);
                    // If it is from this type
                    if (t)
                        // Found
                        return t;
                }
                // Not found
                return std::shared_ptr<T>();
            }

            template <typename T = Attribute>
            std::vector<std::shared_ptr<T>> Attributes(const std::string& key)
            {
                // Create list
                auto attrs = std::vector<std::shared_ptr<T>>();
                // For each attribute
                for (auto attr : attributes)
                    // Check if the one searhced
                    if (strcasecmp(attr->getField().c_str(), key.c_str()) == 0)
                    {
                        // Try to convert it
                        auto t = std::dynamic_pointer_cast<T>(attr);
                        // If it was that type
                        if (t)
                            // Add it
                            attrs.push_back(t);
                    }
                // Done
                return attrs;
            }

            template <typename T = Attribute>
            std::vector<std::shared_ptr<T>> Attributes()
            {
                // Create list
                auto attrs = std::vector<std::shared_ptr<T>>();
                // For each attribute
                for (auto attr : attributes)
                {
                    // Try to convert it
                    auto t = std::dynamic_pointer_cast<T>(attr);
                    // If it was that type
                    if (t)
                        // Add it
                        attrs.push_back(t);
                }
                // Done
                return attrs;
            }

            template <typename Type, class... Args>
            void addAttribute(Args... args)
            {
                // Add attribute
                addAttribute(std::make_shared<Type>(Type{std::forward<Args>(args)...}));
            }

            std::vector<AttributeSharedPtr_t> Attributes();

            [[nodiscard]] int Version() const;
            ConnectionSharedPtr_t Connection();
            std::vector<std::string> Emails();
            InformationSharedPtr_t Information();
            KeySharedPtr_t Key();
            std::vector<MediaDescriptionSharedPtr_t> Medias();
            OriginSharedPtr_t Origin();
            std::vector<std::string> Phones();
            SessionNameSharedPtr_t SessionName();
            std::vector<TimeSharedPtr_t> Times();
            std::string Uri();
            std::vector<BandwidthSharedPtr_t> Bandwidths();

            void setVersion(int version);
            void setOrigin(const OriginSharedPtr_t& origin);
            void setOrigin(const std::string& username,
                           uint64_t sessId,
                           uint64_t sessVersion,
                           const std::string& nettype,
                           const std::string& addrtype,
                           const std::string& address);
            void setOrigin(const std::string& username,
                           int sessId,
                           uint64_t sessVersion,
                           const std::string& nettype,
                           const std::string& addrtype,
                           const std::string& address);
            void setOrigin(const std::string& username,
                           int sessId,
                           int sessVersion,
                           const std::string& nettype,
                           const std::string& addrtype,
                           const std::string& address);
            void setUri(const std::string& uri);
            void setSessionName(std::string sessionName);
            void setSessionName(const SessionNameSharedPtr_t& sessionName);
            void setInformation(const InformationSharedPtr_t& information);
            void setConnection(const ConnectionSharedPtr_t& connection);
            void setEmails(const std::vector<std::string>& emails);
            void addEmail(const std::string& email);
            void setPhones(const std::vector<std::string>& phones);
            void addPhone(const std::string& email);
            void setConnection(const std::string& netType, const std::string& addrType, const std::string& address);
            void addBandwidth(const std::string& type, int bandwidth);
            void addBandwidth(const std::string& type, const std::string& bandwidth);
            void addBandwidth(const BandwidthSharedPtr_t& bandwidth);
            void addAttribute(const AttributeSharedPtr_t& attr);
            void setAttributes(const std::vector<AttributeSharedPtr_t>& attributes);
            void addAttribute(const std::string& attr);
            void addAttribute(const std::string& attr, const std::string& value);
            void setTimes(const std::vector<TimeSharedPtr_t>& times);
            void addTime(int start, int stop);
            void addTime(const TimeSharedPtr_t& time);
            void setKey(const KeySharedPtr_t& key);
            void setMedias(const std::vector<MediaDescriptionSharedPtr_t>& medias);
            void addMedia(const MediaDescriptionSharedPtr_t& media);
            MediaDescriptionSharedPtr_t Media(const std::string& media);
            MediaDescriptionSharedPtr_t MediaById(const std::string& id);

        private:
            int m_version;
            OriginSharedPtr_t m_pOrigin;
            std::string m_uri;
            SessionNameSharedPtr_t sessionName;
            InformationSharedPtr_t information;
            std::vector<std::string> emails;
            std::vector<std::string> phones;
            ConnectionSharedPtr_t connection;
            std::vector<BandwidthSharedPtr_t> bandwidths;
            std::vector<AttributeSharedPtr_t> attributes;
            KeySharedPtr_t key;
            std::vector<TimeSharedPtr_t> times;
            std::vector<MediaDescriptionSharedPtr_t> medias;
        };
    }
}