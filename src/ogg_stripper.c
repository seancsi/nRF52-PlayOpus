#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ogg_stripper.h"

static oggPacketHeader_t currentPacketHeader;
static oggIDHeader_t currentIDHeader;
static oggCommentHeader_t currentCommentHeader;

// Parse the packet header into a struct.
// Expect to be at the beginning of the packet.
// Return the length of the data in the packet.
// Seek to the beginning of the data when finished.
size_t OggReadPacketHeader (FILE * oggFile, oggPacketHeader_t * header) {
    size_t i;
    if ( fread(header, 1, 27, oggFile) == 27) {
        if (header->Signature == OGGS_MAGIC) {
            // Our magic signature is good, and we don't care about everything else.
            // Let's figure out how big our data payload is.
            if (header->TotalSegments) {
                header->DataLength = 0;
                for (i = 0; i < header->TotalSegments; i++)
                    header->DataLength += fgetc(oggFile);

                return header->DataLength;
            } else {
                return OGG_STRIP_NO_SEGS;
            }
        } else {
            return OGG_STRIP_BAD_MAGIC;
        }
    } else {
        return OGG_STRIP_EOF;
    }
}

size_t OggGetNextDataPacket (FILE * oggFile, uint8_t * destination, size_t maxLength) {
    return 0;
}

oggPacketHeader_t* OggGetLastPacketHeader(void) {
    return &currentPacketHeader;
}

// We should be at the start of the ID header data section.  Read it in.
// At the end of this thing, we should have advanced dataLen.
size_t OggGetIDHeader (FILE * oggFile, oggIDHeader_t * destination, size_t dataLen) {
    size_t extraBytes = dataLen - 19;
    // If dataLen exceeds the length of the ID header (like if there's a channel mapping table)
    // just read in the ID stuff, and skip to the end.
    if (dataLen >= 19) {
        if ( fread(destination, 1, 19, oggFile) == 19 ) {
            // Advance any excess bytes.
            if (extraBytes > 0)
                fseek(oggFile, extraBytes, SEEK_CUR);
            
            if (destination->Signature == OPUSHEAD_MAGIC)
                return OGG_STRIP_OK;
            else {
                printf("ERR! Bad magic string.\r\n");
                return OGG_STRIP_BAD_MAGIC;
            }
        } else {
            printf("ERR! Couldn't read enough bytes.\r\n");
            return OGG_STRIP_EOF;
        }
    } else {
        printf("ERR! ID Header Data length too short.\r\n");
        return OGG_STRIP_LEN_SHORT;
    }
}

// We should be at the start of the comment header data section.
// As of now, we don't need to parse this crap.  Just skip it all for now.
size_t OggGetCommentHeader (FILE * oggFile, oggCommentHeader_t * destination, size_t dataLen) {
    size_t extraBytes = dataLen - 12;
    // If dataLen exceeds the length of the comment header (like if there's a custom comment)
    // just read in the fixed comment stuff, and skip to the end.
    if (dataLen >= 12) {
        if ( fread(destination, 1, 12, oggFile) == 12 ) {
            // Advance any excess bytes.
            if (extraBytes > 0)
                fseek(oggFile, extraBytes, SEEK_CUR);
            
            if (destination->Signature == OPUSTAGS_MAGIC)
                return OGG_STRIP_OK;
            else {
                printf("ERR! Bad magic string.\r\n");
                return OGG_STRIP_BAD_MAGIC;
            }
        } else {
            printf("ERR! Couldn't read enough bytes.\r\n");
            return OGG_STRIP_EOF;
        }
    } else {
        printf("ERR! Comment Header Data length too short.\r\n");
        return OGG_STRIP_LEN_SHORT;
    }
}

// Start the file at the beginning.  If it's valid, read the info.
// Finally, seek to the beginning of the first data packet.
// This function should be called first, before GetNextDataPacket.
// Return the data length pulled from the packet header.
bool OggPrepareFile (FILE * oggFile) {
    size_t dataLen;
    fseek(oggFile, 0, SEEK_SET); // Seek to the beginning.

    // Read in the ID header.
    dataLen = OggReadPacketHeader(oggFile, &currentPacketHeader);
    if ( OggGetIDHeader(oggFile, &currentIDHeader, dataLen) == OGG_STRIP_OK ) {
        printf("Got ID Header!\r\n");
    }

    // Read in the comment header.
    dataLen = OggReadPacketHeader(oggFile, &currentPacketHeader);
    if ( OggGetCommentHeader(oggFile, &currentCommentHeader, dataLen) == OGG_STRIP_OK ) {
        printf("Got Comment Header!\r\n");
    }

    if (dataLen > 0)
        return true;
    else
        return false;
}
