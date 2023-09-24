#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

namespace MediaServer
{
    namespace Rtp
    {
        GenericRtpClientSharedPtr_t GenericRtpClient::Create()
        {
            return std::make_shared<GenericRtpClient>();
        }

        GenericRtpClient::GenericRtpClient()
        {}

        GenericRtpClient::~GenericRtpClient()
        {}
    }
}
