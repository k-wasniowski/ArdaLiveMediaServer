#include <Media/Sdp/SessionDescription.hpp>

#include <gtest/gtest.h>

TEST(SessionDescriptionTests, SampleFfmpegGeneratedSdpForH264)
{
    std::cout << "----------------------------------------------------" << std::endl;
    std::string sdp = "v=0\r\n"
                      "o=- 0 0 IN IP4 127.0.0.1\r\n"
                      "s=No Name\r\n"
                      "c=IN IP4 127.0.0.1\r\n"
                      "t=0 0\r\n"
                      "a=tool:libavformat 60.4.101\r\n"
                      "m=video 5004 RTP/AVP 96\r\n"
                      "a=rtpmap:96 H264/90000\r\n"
                      "a=fmtp:96 packetization-mode=1\r\n";

    auto pSessionDescription = Media::Sdp::SessionDescription::Parse(sdp);

    auto medias = pSessionDescription->Medias();
    ASSERT_EQ(medias.size(), 1);

    auto pMedia = medias.front();
    auto attributes = pMedia->getAttributes();
    for(auto& attr: attributes)
    {
        std::cout << attr->toString() << std::endl;
    }

    auto formats = pMedia->getFormats();
    ASSERT_EQ(formats.size(), 1);
    ASSERT_EQ(formats.front(), "96");

    auto pRtpMap = pMedia->getAttribute<Media::Sdp::RTPMapAttribute>("rtpmap");
    ASSERT_EQ(pRtpMap->getName(), "H264");
    std::cout << "----------------------------------------------------" << std::endl;
}

TEST(SessionDescriptionTests, SampleFfmpegGeneratedSdpForVP8)
{
    std::cout << "----------------------------------------------------" << std::endl;
    std::string sdp = "v=0\r\n"
                      "o=- 0 0 IN IP4 127.0.0.1\r\n"
                      "s=No Name\r\n"
                      "c=IN IP4 127.0.0.1\r\n"
                      "t=0 0\r\n"
                      "a=tool:libavformat 60.4.101\r\n"
                      "m=video 5004 RTP/AVP 96\r\n"
                      "i=My Title\r\n"
                      "b=AS:256\r\n"
                      "a=rtpmap:96 VP8/90000\r\n";

    auto pSessionDescription = Media::Sdp::SessionDescription::Parse(sdp);

    auto medias = pSessionDescription->Medias();
    ASSERT_EQ(medias.size(), 1);

    auto pMedia = medias.front();
    auto formats = pMedia->getFormats();
    ASSERT_EQ(formats.size(), 1);
    ASSERT_EQ(formats.front(), "96");

    std::cout << "Text: " << pMedia->getInformation()->getText() << std::endl;

    auto attributes = pMedia->getAttributes();
    for(auto& attr: attributes)
    {
        std::cout << attr->toString() << std::endl;
    }

    auto pRtpMap = pMedia->getAttribute<Media::Sdp::RTPMapAttribute>("rtpmap");
    ASSERT_EQ(pRtpMap->getName(), "VP8");
    std::cout << "----------------------------------------------------" << std::endl;
}