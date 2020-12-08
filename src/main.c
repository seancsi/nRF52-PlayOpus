// Testbed for ogg_stripper.c
#include <stdio.h>
#include "ogg_stripper.h"

int main (void) {
    FILE *oggFile;
    FILE *outFile;
    oggPacketHeader_t header;
    uint8_t outBuffer[5000];
    size_t bytesPulled;

    printf("Ogg Stripper Testbed starting up...\r\n");
    oggFile = fopen("sample.ogg", "rb");
    outFile = fopen("sample.rawopus", "wb");
    if (oggFile && outFile) {
        printf("Opened file!\r\n");

        if ( OggPrepareFile(oggFile) ) { // Prepare the filehandle to be read.
            printf("DataLength: %d\r\n", OggGetLastPacketHeader()->DataLength);

            while (1) {
                bytesPulled = OggGetNextDataPacket(oggFile, outBuffer, 5000);
                if (bytesPulled > 0)
                    fwrite(outBuffer, 1, bytesPulled, outFile);
                else
                    break;
            }
        } else {
            printf("ERR! Couldn't parse Ogg header.\r\n");
        }
        fclose(oggFile);
    } else {
        printf("ERR! Couldn't open file.\r\n");
    }
    return 0;
}