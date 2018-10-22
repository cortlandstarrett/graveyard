/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CHRCONV_HH
#define CHRCONV_HH

#include <ostore/portypes.hh>
#include <ostore/strconv/strconv.hh>

class _OS_DLLIMPORT(_OS_STRCONV) os_chr_conv { 
    friend class os_str_conv;
public:
    enum esc_seq { /* ---- JIS code escape sequence type ------------------- */
        ESC_UNKNOWN, ESC_ASCII, ESC_KANA, ESC_ZEN
    };
    /* --------------------------------------------------------------------- */
    os_chr_conv(os_str_conv::encode_type src);
    void set_type(os_str_conv::encode_type src);
    void set_esc(esc_seq esc);
    /* ------------------------------------------------------------- */
    esc_seq esc() const { return _esc; }
    esc_seq esc_old() const { return _esc_old; }
    os_str_conv::encode_type type() const { return _src; }
    operator os_unsigned_int16() const { return to_int16(); }
    int operator !() const { return (!_c1 && !_c2 && !_c3 && !_c4); }
    int size() const;   /* get this code's byte size                 */
    /* ------------------------------------------------------------- */
    int ctrl_code() const;
    int ascii() const;
    int not_use() const;
    int euc_byte() const;
    int euc_kana() const;
    int sjis_1st_grp1() const;
    int sjis_1st_grp2() const;
    int sjis_1st_byte() const;
    int sjis_2nd_byte() const;
    int sjis_kana() const;
    int unicode_kana() const;
    int unicode_ascii() const;
    int utf8_chk() const;
    int utf8_byte_size() const;
    /* ------------------------------------------------------------- */
    os_chr_conv& in(const unsigned char** src);
    os_chr_conv& out(unsigned char** dst);
    os_chr_conv& in(const os_unsigned_int16** src);
    os_chr_conv& out(os_unsigned_int16** dst);
    os_chr_conv& convert(os_str_conv::encode_type dst);
    unsigned char* write_esc(unsigned char* dst) const;
    const unsigned char* read_esc(const unsigned char* src);
protected:
    int forward(os_str_conv::encode_type dst);
    int reverse(os_str_conv::encode_type dst);
    os_unsigned_int16 to_int16() const;
    void to_byte(os_unsigned_int16 code);
    /* ------------------------------------------------------------- */
    void euc_to_jis();
    void jis_to_euc();
    void jis_to_sjis();
    void sjis_to_jis();
    int sjis_to_uni();
    int uni_to_sjis();
    int uni_to_utf8();
    int utf8_to_uni();
    /* ------------------------------------------------------------- */
    os_str_conv::encode_type _src;
    esc_seq       _esc;
    esc_seq       _esc_old;
    unsigned char _c1,_c2,_c3,_c4;
    int           _size;
};

#endif /* CHRCONV_HH */
