#include "SessionDescription.hpp"
#include "abnf/ParserContext.hpp"
#include "abnf/ParserException.hpp"
#include "abnf/Rule_session_description.hpp"
#include "builders/SessionDescriptionBuilder.h"

#include <memory>

using namespace Media::Sdp;

namespace Media
{
    namespace Sdp
    {
        std::shared_ptr<SessionDescription> SessionDescription::Parse(const std::string& str)
        {
            abnf::ParserContext context(str, false);

            auto rule = abnf::Rule_session_description::parse(context);

            if (!rule)
            {

                std::cout << context.getErrorStack().front() << "\n";
                std::cout << context.text << "\n";
                std::cout << context.getErrorIndex() << "\n";
                std::cout << context.getErrorStack().front() << "\n";

                throw abnf::ParserException("rule \"" + (std::string)context.getErrorStack().front() + "\" failed",
                                            context.text,
                                            context.getErrorIndex(),
                                            context.getErrorStack());
            }

            // Create builder
            SessionDescriptionBuilder builder;
            // And make it visit the object to get the parser object
            auto sdp = (SessionDescription*)builder.visit(rule);

            // Release rules
            delete (rule);

            // Return pointer
            return std::shared_ptr<SessionDescription>(sdp);
        }

        SessionDescription::SessionDescription(int version)
        {
            this->m_version = version;
        }

        std::shared_ptr<SessionDescription> SessionDescription::clone()
        {
            // Create clone
            auto cloned = std::make_shared<SessionDescription>(m_version);

            // Clone data
            if (m_pOrigin)
                cloned->setOrigin(m_pOrigin->clone());
            if (sessionName)
                cloned->setSessionName(sessionName->clone());
            if (information)
                cloned->setInformation(information->clone());
            if (connection)
                cloned->setConnection(connection->clone());
            if (key)
                cloned->setKey(key->clone());
            if (!m_uri.empty())
                cloned->setUri(m_uri);
            // For each email
            for (std::string email : emails)
                // Add it
                cloned->addEmail(email);
            // For each phone
            for (std::string phone : phones)
                // Add it
                cloned->addPhone(phone);
            // For each bandwidth
            for (auto bandwidth : bandwidths)
                // Add it
                cloned->addBandwidth(bandwidth->clone());
            // For each attribute
            for (auto attribute : attributes)
                // Add it
                cloned->addAttribute(attribute->clone());
            // For each time
            for (auto time : times)
                // Add it
                cloned->addTime(time->clone());
            // For each media
            for (auto media : medias)
                // Add it
                cloned->addMedia(media->clone());
            // return it
            return cloned;
        }

        std::string SessionDescription::toString()
        {
            std::string sdp = "v=" + std::to_string(m_version) + "\r\n";
            sdp += m_pOrigin->toString();
            sdp += sessionName->toString();
            if (!m_uri.empty())
                sdp += "u=" + m_uri + "\r\n";
            for (std::string email : emails)
                sdp += "e=" + email + "\r\n";
            for (std::string phone : phones)
                sdp += "p=" + phone + "\r\n";
            if (connection)
                sdp += connection->toString();
            for (auto time : times)
                sdp += time->toString();
            for (auto attr : attributes)
                sdp += attr->toString();
            for (auto media : medias)
                sdp += media->toString();
            return sdp;
        }

        std::vector<std::shared_ptr<Attribute>> SessionDescription::Attributes()
        {
            return attributes;
        }

        void SessionDescription::setAttributes(const std::vector<AttributeSharedPtr_t>& attributes)
        {
            this->attributes = attributes;
        }

        std::shared_ptr<Connection> SessionDescription::Connection()
        {
            return connection;
        }

        void SessionDescription::setConnection(const ConnectionSharedPtr_t& connection)
        {
            this->connection = connection;
        }

        std::vector<std::string> SessionDescription::Emails()
        {
            return emails;
        }

        void SessionDescription::setEmails(const std::vector<std::string>& emails)
        {
            this->emails = emails;
        }

        std::shared_ptr<Information> SessionDescription::Information()
        {
            return information;
        }

        void SessionDescription::setInformation(const InformationSharedPtr_t& information)
        {
            this->information = information;
        }

        std::shared_ptr<Key> SessionDescription::Key()
        {
            return key;
        }

        void SessionDescription::setKey(const KeySharedPtr_t& key)
        {
            this->key = key;
        }

        std::vector<std::shared_ptr<MediaDescription>> SessionDescription::Medias()
        {
            return medias;
        }

        void SessionDescription::setMedias(const std::vector<std::shared_ptr<MediaDescription>>& medias)
        {
            this->medias = medias;
        }

        std::shared_ptr<Origin> SessionDescription::Origin()
        {
            return m_pOrigin;
        }

        void SessionDescription::setOrigin(const OriginSharedPtr_t& origin)
        {
            this->m_pOrigin = origin;
        }

        std::vector<std::string> SessionDescription::Phones()
        {
            return phones;
        }

        void SessionDescription::setPhones(const std::vector<std::string>& phones)
        {
            this->phones = phones;
        }

        std::shared_ptr<SessionName> SessionDescription::SessionName()
        {
            return sessionName;
        }

        void SessionDescription::setSessionName(std::string sessionName)
        {
            this->sessionName = SessionName::Create(sessionName);
        }

        void SessionDescription::setSessionName(const SessionNameSharedPtr_t& sessionName)
        {
            this->sessionName = sessionName;
        }

        std::vector<TimeSharedPtr_t> SessionDescription::Times()
        {
            return times;
        }

        void SessionDescription::setTimes(const std::vector<TimeSharedPtr_t>& times)
        {
            this->times = times;
        }

        std::string SessionDescription::Uri()
        {
            return m_uri;
        }

        void SessionDescription::setUri(const std::string& uri)
        {
            this->m_uri = uri;
        }

        int SessionDescription::Version() const
        {
            return m_version;
        }

        void SessionDescription::setVersion(int version)
        {
            this->m_version = version;
        }

        void SessionDescription::addEmail(const std::string& email)
        {
            emails.push_back(email);
        }

        void SessionDescription::addPhone(const std::string& email)
        {
            emails.push_back(email);
        }

        void SessionDescription::addBandwidth(const std::string& type, const std::string& bandwidth)
        {
            addBandwidth(std::make_shared<Bandwidth>(type, bandwidth));
        }

        void SessionDescription::addBandwidth(const BandwidthSharedPtr_t& bandwidth)
        {
            bandwidths.push_back(bandwidth);
        }

        void SessionDescription::addMedia(const MediaDescriptionSharedPtr_t& media)
        {
            medias.push_back(media);
        }

        void SessionDescription::addTime(const TimeSharedPtr_t& time)
        {
            times.push_back(time);
        }

        void SessionDescription::addAttribute(const AttributeSharedPtr_t& attr)
        {
            attributes.push_back(attr);
        }

        std::vector<BandwidthSharedPtr_t> SessionDescription::Bandwidths()
        {
            return bandwidths;
        }

        void SessionDescription::setOrigin(const std::string& username,
                                           uint64_t sessId,
                                           uint64_t sessVersion,
                                           const std::string& nettype,
                                           const std::string& addrtype,
                                           const std::string& address)
        {
            auto pNewOrigin = Origin::Create(username, sessId, sessVersion, nettype, addrtype, address);
            setOrigin(pNewOrigin);
        }

        void SessionDescription::setOrigin(const std::string& username,
                                           int sessId,
                                           uint64_t sessVersion,
                                           const std::string& nettype,
                                           const std::string& addrtype,
                                           const std::string& address)
        {
            auto pNewOrigin = Origin::Create(username, sessId, sessVersion, nettype, addrtype, address);
            setOrigin(pNewOrigin);
        }

        void SessionDescription::setOrigin(const std::string& username,
                                           int sessId,
                                           int sessVersion,
                                           const std::string& nettype,
                                           const std::string& addrtype,
                                           const std::string& address)
        {
            auto pNewOrigin = Origin::Create(username, sessId, sessVersion, nettype, addrtype, address);
            setOrigin(pNewOrigin);
        }

        void SessionDescription::setConnection(const std::string& netType, const std::string& addrType, const std::string& address)
        {
            auto pNewConnection = Connection::Create(netType, addrType, address);
            setConnection(pNewConnection);
        }

        void SessionDescription::addTime(int start, int stop)
        {
            addTime(std::make_shared<Time>(start, stop));
        }

        void SessionDescription::addAttribute(const std::string& attr)
        {
            addAttribute(std::make_shared<BaseAttribute>(attr));
        }

        void SessionDescription::addAttribute(const std::string& attr, const std::string& value)
        {
            addAttribute(std::make_shared<BaseAttribute>(attr, value));
        }

        MediaDescriptionSharedPtr_t SessionDescription::Media(const std::string& type)
        {
            for (auto media : medias)
                if (type == media->getMedia())
                    return media;
            return nullptr;
        }

        MediaDescriptionSharedPtr_t SessionDescription::MediaById(const std::string& id)
        {
            for (auto media : medias)
            {
                // Get mid attribute
                auto mid = media->getAttribute("mid");
                if (mid && id == mid->getValue())
                    return media;
            }

            return nullptr;
        }
    }
}