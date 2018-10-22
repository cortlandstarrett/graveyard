/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef STRCONV_HH
#define STRCONV_HH

#include <ostore/portypes.hh>

class os_chr_conv;

class _OS_DLLIMPORT(_OS_STRCONV) os_str_conv {
public:
    enum encode_type {  /* string encode type ------------------------------ */
        /*  DON'T change this order !                                        */
        UNKNOWN=0,            /* convert or auto-detect fail                 */
        AUTOMATIC,            /* detect automatically                        */
        AUTOMATIC_ALLOW_KANA, /* detect automatically, allow half-width-kana */
        ASCII,                /* ASCII                                       */
        EUC,                  /* EUC                                         */
        JIS,                  /* JIS                                         */
        SJIS,                 /* Shift-JIS                                   */
        UNICODE_PLATFORM,     /* Unicode Platform-dependent endian           */
        UTF8,                 /* UTF-8                                       */
        /* ---------------------- Add in 5.1 SP1 --------------------------- */
        UNICODE_BIG    = UNICODE_PLATFORM|0x80,   /* Unicode Big endian      */
        UNICODE_LITTLE = UNICODE_PLATFORM|0xC0    /* Unicode Little endian   */
    };
    /* --------------------------------------------------------------------- */
    os_str_conv(encode_type dst,encode_type src=AUTOMATIC);
    virtual ~os_str_conv();
    int set_code_type(encode_type dst,encode_type src=AUTOMATIC);
    /*  set convert code type, dst >= ascii                                  */
    /* --------------------------------------------------------------------- */
    encode_type get_destination_type() const;
    encode_type get_source_type() const;
    virtual encode_type auto_detect(const char* src) const;
    virtual size_t get_converted_size(const char* src) const;
    virtual size_t get_converted_size(const os_unsigned_int16* src) const;
    /* --------------------------------------------------------------------- */
    encode_type convert(char* dst,const char* src);
    /* convert dst <- src ,     use auto_detect()                            */
    encode_type convert(os_unsigned_int16* dst,const char* src);
    /* convert unicode <- src , use auto_detect()                            */
    encode_type convert(char* dst,const os_unsigned_int16* src);
    /* convert dst <- unicode , NOT use auto_detect()                        */
    /* --------------------------------------------------------------------- */
    struct mapping {
        os_unsigned_int32 dst;      /* destination code */
        os_unsigned_int32 src;      /* source code      */
    };
    int change_mapping(mapping* table,size_t table_sz);
protected:
    /* --------------------------------------------------------------------- */
    virtual int do_convert(encode_type t);     /* convert from t to _dst_type*/
    virtual int do_convert_2_1(encode_type t); /* convert from unicode       */
    virtual int do_convert_1_2(encode_type t); /* convert to   unicode       */
    /* --------------------------------------------------------------------- */
    int mapping_check(os_chr_conv& c);
    /* --------------------------------------------------------------------- */
protected:
    encode_type _dst_type;          /* destination encode type */
    encode_type _src_type;          /* source encode type      */
    unsigned char*       _dst;      /* destination string      */
    const unsigned char* _src;      /* source string           */
    mapping*             _table;    /* mapping change table    */
};

#endif /* STRCONV_HH */
