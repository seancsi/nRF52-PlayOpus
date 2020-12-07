#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ogg_stripper.h"

static oggPacketHeader_t currentPacketHeader;

// Parse the packet header into a struct.
// Expect to be at the beginning of the packet.
// Return the length of the data in the packet.
// Seek to the beginning of the data when finished.
size_t OggReadPacketHeader (FILE * oggFile, oggPacketHeader_t * header) {
    size_t i;
    if ( fread(header, 1, 27, oggFile) == 27) {
        if (header->Signature == OGGS_MAGIC) {
            // Our magic signature is good, and we don't care about everything else.
            // Let's figure out how big out data payload is.
            if (header->TotalSegments) {
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
        return OGG_STRIP_ERR_EOF;
    }
}

size_t OggGetNextDataPacket (FILE * oggFile, uint8_t * destination, size_t maxLength) {

}

// Start the file at the beginning.  If it's valid, read the info.
// Finally, seek to the beginning of the first data packet.
// This function should be called first, before GetNextDataPacket.
bool OggPrepareFile (FILE * oggFile) {
    size_t dataLen;
    fseek(oggFile, 0, SEEK_SET); // Seek to the beginning.
    dataLen = OggReadPacketHeader(oggFile, &currentPacketHeader);
    
}