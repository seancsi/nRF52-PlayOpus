// Ogg Stripper Header File
#include <stdio.h>

#ifndef OGG_STRIPPER_H

#define OGGS_MAGIC 0x4F676753 // "OggS"

typedef struct  {
    uint32_t Signature;
    uint8_t Version;
    uint8_t Flags;
    uint64_t GranulePosition;
    uint32_t SerialNumber;
    uint32_t SequenceNumber;
    uint32_t Checksum;
    uint8_t TotalSegments;
    uint32_t DataLength;
} oggPacketHeader_t;

typedef struct {
    uint64_t Signature;
    uint8_t Version;
    uint8_t ChannelCount;
    uint16_t PreSkip;
    uint32_t InputSampleRate;
    uint16_t OutputGain;
    uint8_t MappingFamily;
    uint32_t ChannelMappingOffset; 
} oggIDHeader_t;

typedef struct {
    uint64_t Signature;
    uint32_t VendorStringLength;
    uint32_t UserCommentListLength;
    uint32_t UserComment0StringLength;
} oggCommentHeader_t;


oggIDHeader_t OggGetIDHeader (FILE * oggFile);

enum {
    OGG_STRIP_ERR_UNKNOWN = -1,
    OGG_STRIP_ERR_EOF = -2,
    OGG_STRIP_BAD_MAGIC = -3,
    OGG_STRIP_NO_SEGS = -4
};

#endif