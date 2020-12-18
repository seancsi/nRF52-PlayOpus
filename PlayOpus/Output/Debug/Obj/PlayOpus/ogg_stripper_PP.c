# 1 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
# 1 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 1 3 4
# 44 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
# 1 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/__crossworks.h" 1 3 4
# 70 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/__crossworks.h" 3 4

# 70 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/__crossworks.h" 3 4
typedef __builtin_va_list __va_list;
# 124 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/__crossworks.h" 3 4
struct __mbstate_s {
  int __state;
  long __wchar;
};

typedef int (__RAL_mb_encode_t)(char *s, unsigned int wc, struct __mbstate_s *codec);
typedef int (__RAL_mb_decode_t)(unsigned int *pwc, const char *s, unsigned len, struct __mbstate_s *codec);

typedef struct {

  const char *decimal_point;
  const char *thousands_sep;
  const char *grouping;

  const char *int_curr_symbol;
  const char *currency_symbol;
  const char *mon_decimal_point;
  const char *mon_thousands_sep;
  const char *mon_grouping;
  const char *positive_sign;
  const char *negative_sign;

  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_p_cs_precedes;
  char int_n_cs_precedes;
  char int_p_sep_by_space;
  char int_n_sep_by_space;
  char int_p_sign_posn;
  char int_n_sign_posn;




  const char *day_names;
  const char *abbrev_day_names;
  const char *month_names;
  const char *abbrev_month_names;
  const char *am_pm_indicator;
  const char *date_format;
  const char *time_format;
  const char *date_time_format;
} __RAL_locale_data_t;

enum {
  __RAL_WC_ALNUM = 1,
  __RAL_WC_ALPHA,
  __RAL_WC_CNTRL,
  __RAL_WC_DIGIT,
  __RAL_WC_GRAPH,
  __RAL_WC_LOWER,
  __RAL_WC_UPPER,
  __RAL_WC_SPACE,
  __RAL_WC_PRINT,
  __RAL_WC_PUNCT,
  __RAL_WC_BLANK,
  __RAL_WC_XDIGIT
};

enum {
  __RAL_WT_TOLOWER = 1,
  __RAL_WT_TOUPPER
};

typedef struct {

  int (*__isctype)(int, int);
  int (*__toupper)(int);
  int (*__tolower)(int);


  int (*__iswctype)(long, int);
  long (*__towupper)(long);
  long (*__towlower)(long);


  int (*__wctomb)(char *s, unsigned int wc, struct __mbstate_s *state);
  int (*__mbtowc)(unsigned int *pwc, const char *s, unsigned len, struct __mbstate_s *state);
} __RAL_locale_codeset_t;

typedef struct {
  const char *name;
  const __RAL_locale_data_t *data;
  const __RAL_locale_codeset_t *codeset;
} __RAL_locale_t;



typedef struct __locale_s {
  const __RAL_locale_t *__category[5];
} *__locale_t;


const __RAL_locale_t *__user_find_locale(const char *locale);
# 237 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/__crossworks.h" 3 4
const __RAL_locale_t *__RAL_find_locale(const char *locale);







const __RAL_locale_t *__RAL_global_locale_category(int __category);







const __RAL_locale_t *__RAL_locale_category(__locale_t __locale, int __category);






extern struct __locale_s __RAL_global_locale;






extern const __RAL_locale_t __RAL_c_locale;


extern const __RAL_locale_codeset_t __RAL_codeset_ascii;
extern const __RAL_locale_codeset_t __RAL_codeset_utf8;

extern const unsigned char __RAL_ascii_ctype_map[128];

extern const char __RAL_c_locale_day_names[];
extern const char __RAL_c_locale_abbrev_day_names[];
extern const char __RAL_c_locale_month_names[];
extern const char __RAL_c_locale_abbrev_month_names[];

extern const char __RAL_data_utf8_period[];
extern const char __RAL_data_utf8_comma[];
extern const char __RAL_data_utf8_space[];
extern const char __RAL_data_utf8_plus[];
extern const char __RAL_data_utf8_minus[];
extern const char __RAL_data_empty_string[];

const char *__RAL_string_list_decode(const char *str, int index);
int __RAL_string_list_encode(const char *list, const char *str);


void __RAL_init_mbstate(struct __mbstate_s *state);

int __RAL_ascii_wctomb(char *s, unsigned int wc, struct __mbstate_s *state);
int __RAL_ascii_mbtowc(unsigned int *pwc, const char *s, unsigned len, struct __mbstate_s *state);

int __RAL_utf8_wctomb(char *s, unsigned int wc, struct __mbstate_s *state);
int __RAL_utf8_mbtowc(unsigned int *pwc, const char *s, unsigned len, struct __mbstate_s *state);

int __RAL_mb_max(const struct __locale_s *loc);

struct timeval;


int __RAL_compare_locale_name(const char *str0, const char *str1);


extern int (*__user_set_time_of_day)(const struct timeval *tp);
extern int (*__user_get_time_of_day)(struct timeval *tp);


typedef struct { unsigned short min, max, map; } __RAL_unicode_map_bmp_range_t;
typedef struct { unsigned short cp, map; } __RAL_unicode_map_bmp_singleton_t;


typedef struct { unsigned short min, max; } __RAL_unicode_set_bmp_range_t;
typedef struct { long min, max; } __RAL_unicode_set_nonbmp_range_t;


int __RAL_unicode_iswctype(long ch, int ty);
long __RAL_unicode_towupper(long ch);
long __RAL_unicode_towlower(long ch);


int __RAL_unicode_map_range_search(const void *k0, const void *k1);
int __RAL_unicode_map_singleton_search(const void *k0, const void *k1);


int __RAL_unicode_set_bmp_range_search(const void *k0, const void *k1);
int __RAL_unicode_set_nonbmp_range_search(const void *k0, const void *k1);

typedef const char * (*__RAL_error_decoder_fn_t)(int error);

typedef struct __RAL_error_decoder_s
{
  __RAL_error_decoder_fn_t decode;
  struct __RAL_error_decoder_s *next;
} __RAL_error_decoder_t;

void __RAL_register_error_decoder(__RAL_error_decoder_t *decoder);

extern __RAL_error_decoder_t *__RAL_error_decoder_head;

const char *__RAL_decode_error(int num);
# 45 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 2 3 4
# 60 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
typedef unsigned size_t;
# 72 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int putchar(int __c);
# 81 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int getchar(void);
# 93 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int puts(const char *__s);
# 110 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
char *gets(char *__s);
# 129 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int sprintf(char *__s, const char *__format, ...);
# 157 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int snprintf(char *__s, size_t __n, const char *__format, ...);
# 193 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int vsnprintf(char *__s, size_t __n, const char *__format, __va_list __arg);
# 439 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int printf(const char *__format, ...);
# 459 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int vprintf(const char *__format, __va_list __arg);
# 488 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int vsprintf(char *__s, const char *__format, __va_list __arg);
# 689 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int scanf(const char *__format, ...);
# 709 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int sscanf(const char *__s, const char *__format, ...);
# 735 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int vscanf(const char *__format, __va_list __arg);
# 759 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
int vsscanf(const char *__s, const char *__format, __va_list __arg);





typedef struct __printf_tag *__printf_tag_ptr;

int __putchar(int, __printf_tag_ptr);
# 785 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdio.h" 3 4
typedef struct __RAL_FILE FILE;


typedef long fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE *, fpos_t *);
char *fgets(char *, int, FILE *);
int fileno(FILE *);
FILE *fopen(const char *, const char *);
int fprintf(FILE *, const char *, ...);
int fputc(int, FILE *);
int fputs(const char *, FILE *);
size_t fread(void *, size_t, size_t, FILE *);
FILE *freopen(const char *, const char *, FILE *);
int fscanf(FILE *, const char *, ...);
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
int getc(FILE *);
void perror(const char *);
int putc(int, FILE *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE *, const char *, __va_list);
int vfscanf(FILE *, const char *, __va_list);
# 2 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 2
# 1 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdbool.h" 1 3 4
# 3 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 2
# 1 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 1 3 4
# 84 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *memcpy(void *__s1, const void *__s2, size_t __n);
# 99 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *memcpy_fast(void *__s1, const void *__s2, size_t __n);
# 118 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *memccpy(void *__s1, const void *__s2, int __c, size_t __n);
# 132 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *mempcpy(void *__s1, const void *__s2, size_t __n);
# 147 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *memmove(void *__s1, const void *__s2, size_t __n);
# 158 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
int memcmp(const void *__s1, const void *__s2, size_t __n);
# 172 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *memchr(const void *__s, int __c, size_t __n);
# 182 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
void *memset(void *__s, int __c, size_t __n);
# 193 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strcpy(char *__s1, const char *__s2);
# 213 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strncpy(char *__s1, const char *__s2, size_t __n);
# 230 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
size_t strlcpy(char *__s1, const char *__s2, size_t __n);
# 243 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strcat(char *__s1, const char *__s2);
# 257 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strncat(char *__s1, const char *__s2, size_t __n);
# 278 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
size_t strlcat(char *__s1, const char *__s2, size_t __n);
# 288 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
int strcmp(const char *__s1, const char *__s2);
# 301 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
int strncmp(const char *__s1, const char *__s2, size_t __n);
# 313 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
int strcasecmp(const char *__s1, const char *__s2);
# 328 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
int strncasecmp(const char *__s1, const char *__s2, size_t __n);
# 340 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strchr(const char *__s, int __c);
# 352 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strnchr(const char *__str, size_t __n, int __ch);
# 363 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
size_t strcspn(const char *__s1, const char *__s2);
# 374 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strpbrk(const char *__s1, const char *__s2);
# 386 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strrchr(const char *__s, int __c);
# 397 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
size_t strspn(const char *__s1, const char *__s2);
# 410 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strstr(const char *__s1, const char *__s2);
# 425 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strnstr(const char *__s1, const char *__s2, size_t __n);
# 440 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strcasestr(const char *__s1, const char *__s2);
# 456 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strncasestr(const char *__s1, const char *__s2, size_t __n);







size_t strlen(const char *__s);
# 475 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
size_t strnlen(const char *__s, size_t __n);
# 509 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strtok(char *__s1, const char *__s2);
# 528 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strsep(char **__stringp, const char *__delim);
# 541 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strtok_r(char *__s1, const char *__s2, char **__s3);
# 555 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strdup(const char *__s1);
# 573 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strndup(const char *__s1, size_t __n);
# 586 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/string.h" 3 4
char *strerror(int __num);



int strcoll(const char *__str1, const char *__str2);
size_t strxfrm( char *__str1, const char *__str2, size_t __num);
# 4 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 2
# 1 "C:/Users/sean/Git/nRF52-PlayOpus/PlayOpus/include/ogg_stripper.h" 1



# 1 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdint.h" 1 3 4
# 41 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdint.h" 3 4
typedef signed char int8_t;
typedef unsigned char uint8_t;




typedef signed short int16_t;
typedef unsigned short uint16_t;





typedef signed int int32_t;
typedef unsigned int uint32_t;
# 68 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdint.h" 3 4
typedef signed long long int64_t;
typedef unsigned long long uint64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;



typedef int32_t int_fast8_t;
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;

typedef uint32_t uint_fast8_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef int32_t intptr_t;
typedef uint32_t uintptr_t;
# 118 "C:/Users/sean/ncs/v1.4.1/toolchain/segger_embedded_studio/include/stdint.h" 3 4
typedef int64_t intmax_t;
typedef uint64_t uintmax_t;
# 5 "C:/Users/sean/Git/nRF52-PlayOpus/PlayOpus/include/ogg_stripper.h" 2








# 12 "C:/Users/sean/Git/nRF52-PlayOpus/PlayOpus/include/ogg_stripper.h"
typedef struct __attribute((packed)) {
    uint32_t Signature;
    uint8_t Version;
    uint8_t Flags;
    uint64_t GranulePosition;
    uint32_t SerialNumber;
    uint32_t SequenceNumber;
    uint32_t Checksum;
    uint8_t Segments;
    uint8_t SegmentTable[255];
    uint32_t DataLength;
} oggPageHeader_t;

typedef struct __attribute((packed)) {
    uint64_t Signature;
    uint8_t Version;
    uint8_t ChannelCount;
    uint16_t PreSkip;
    uint32_t InputSampleRate;
    uint16_t OutputGain;
    uint8_t MappingFamily;
} oggIDHeader_t;

typedef struct __attribute((packed)) {
    uint64_t Signature;
    uint32_t VendorStringLength;
} oggCommentHeader_t;

enum {
    OGG_STRIP_OK = 0,
    OGG_STRIP_ERR_UNKNOWN = -1,
    OGG_STRIP_EOF = -2,
    OGG_STRIP_BAD_MAGIC = -3,
    OGG_STRIP_NO_SEGS = -4,
    OGG_STRIP_LEN_SHORT = -5
};

int OggReadPageHeader (FILE * oggFile, oggPageHeader_t * header);
int OggGetNextDataPage (FILE * oggFile, uint8_t * destination, size_t maxLength);
int OggGetNextPacket (FILE * oggFile, uint8_t * destination, size_t maxLength);
oggPageHeader_t* OggGetLastPageHeader(void);
int OggGetIDHeader (FILE * oggFile, oggIDHeader_t * destination, int dataLen);
int OggGetCommentHeader (FILE * oggFile, oggCommentHeader_t * destination, int dataLen);

# 55 "C:/Users/sean/Git/nRF52-PlayOpus/PlayOpus/include/ogg_stripper.h" 3 4
_Bool 
# 55 "C:/Users/sean/Git/nRF52-PlayOpus/PlayOpus/include/ogg_stripper.h"
    OggPrepareFile (FILE * oggFile);
# 5 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 2

static oggPageHeader_t currentPageHeader;
static oggIDHeader_t currentIDHeader;
static oggCommentHeader_t currentCommentHeader;





int OggReadPageHeader (FILE * oggFile, oggPageHeader_t * header) {
    size_t i;
    if ( fread(header, 1, 27, oggFile) == 27) {
        if (header->Signature == 0x5367674F) {
            if (header->Segments) {

                if ( fread(header->SegmentTable, 1, header->Segments, oggFile) == header->Segments ) {
                    header->DataLength = 0;
                    for (i = 0; i < header->Segments; i++)
                        header->DataLength += header->SegmentTable[i];
                    return header->DataLength;
                } else {
                    return OGG_STRIP_EOF;
                }
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






int OggGetNextDataPage (FILE * oggFile, uint8_t * destination, size_t maxLength) {
    int dataLen = OggReadPageHeader(oggFile, &currentPageHeader);
    if (dataLen > 0) {


        if ((unsigned)dataLen > maxLength)
            dataLen = maxLength;

        if ( fread(destination, 1, dataLen, oggFile) == (unsigned)dataLen ) {
            return dataLen;
        } else {
            return OGG_STRIP_EOF;
        }
    } else {
        return dataLen;
    }
}






int OggGetNextPacket (FILE * oggFile, uint8_t * destination, size_t maxLength) {
    static size_t currentPacket = 0;
    int dataLen;
    int packetLen;


    if (currentPacket >= currentPageHeader.Segments)
        currentPacket = 0;

    if (!currentPacket++)
        dataLen = OggReadPageHeader(oggFile, &currentPageHeader);

    if (dataLen > 0) {


        packetLen = fread(destination, 1, currentPageHeader.SegmentTable[currentPacket], oggFile);

        if ( packetLen == currentPageHeader.SegmentTable[currentPacket] )
            return packetLen;
        else
            return OGG_STRIP_EOF;
    } else {
        return dataLen;
    }
}

oggPageHeader_t* OggGetLastPageHeader(void) {
    return &currentPageHeader;
}



int OggGetIDHeader (FILE * oggFile, oggIDHeader_t * destination, int dataLen) {
    int extraBytes = dataLen - 19;


    if (dataLen >= 19) {

        if ( fread(destination, 1, 19, oggFile) == 19 ) {

            if (extraBytes > 0)
                fseek(oggFile, extraBytes, 
# 108 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 3 4
                                          1
# 108 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
                                                  );

            if (destination->Signature == 0x646165487375704F)
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



int OggGetCommentHeader (FILE * oggFile, oggCommentHeader_t * destination, int dataLen) {
    int extraBytes = dataLen - 12;


    if (dataLen >= 12) {
        if ( fread(destination, 1, 12, oggFile) == 12 ) {

            if (extraBytes > 0)
                fseek(oggFile, extraBytes, 
# 136 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 3 4
                                          1
# 136 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
                                                  );

            if (destination->Signature == 0x736761547375704F)
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






# 158 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 3 4
_Bool 
# 158 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
    OggPrepareFile (FILE * oggFile) {
    int dataLen;
    fseek(oggFile, 0, 
# 160 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 3 4
                     0
# 160 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
                             );


    dataLen = OggReadPageHeader(oggFile, &currentPageHeader);
    if ( OggGetIDHeader(oggFile, &currentIDHeader, dataLen) == OGG_STRIP_OK ) {
        printf("Got ID Header!\r\n");
    }


    dataLen = OggReadPageHeader(oggFile, &currentPageHeader);
    if ( OggGetCommentHeader(oggFile, &currentCommentHeader, dataLen) == OGG_STRIP_OK ) {
        printf("Got Comment Header!\r\n");
    }

    if (dataLen > 0)
        return 
# 175 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 3 4
              1
# 175 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
                  ;
    else
        return 
# 177 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c" 3 4
              0
# 177 "C:\\Users\\sean\\Git\\nRF52-PlayOpus\\PlayOpus\\src\\ogg_stripper.c"
                   ;
}
