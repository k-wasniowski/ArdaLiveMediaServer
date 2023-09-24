#pragma once

#include <Media/Core/MediaBuffer.hpp>

#include <memory>
#include <vector>

namespace Media
{
    namespace Core
    {
        namespace Rtp
        {
#ifdef __WIN32__
    #define PACKED
    #pragma pack(push, 1)
#else
    #define PACKED __attribute__((__packed__))
#endif
            typedef struct _RTPHeader
            {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
                uint32_t csrcCount : 4;  /* CC field */
                uint32_t extensions : 1; /* X field */
                uint32_t padding : 1;    /* padding flag */
                uint32_t version : 2;
#elif G_BYTE_ORDER == G_BIG_ENDIAN
                uint32_t version : 2;
                uint32_t int padding : 1;    /* padding flag */
                uint32_t int extensions : 1; /* X field */
                uint32_t int csrcCount : 4;  /* CC field*/
#else
    #error "G_BYTE_ORDER should be big or little endian."
#endif
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
                uint32_t payloadType : 7; /* PT field */
                uint32_t marker : 1;      /* M field */
#elif G_BYTE_ORDER == G_BIG_ENDIAN
                uint32_t marker : 1;      /* M field */
                uint32_t payloadType : 7; /* PT field */
#else
    #error "G_BYTE_ORDER should be big or little endian."
#endif
                uint16_t sequenceNumber; /* length of the recovery */
                uint32_t timestamp;      /* Timestamp */
                uint32_t ssrc;
            } RtpHeader; // 12 bytes

#ifdef __WIN32__
    #pragma pack(pop)
    #undef PACKED
#else
    #undef PACKED
#endif
        }
    }
}