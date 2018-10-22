/*========================================================================
 *
 * File:      $RCSfile: gs_crypt.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:43 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/*****************************************************************************/
/* Security:  Note that this code contains the key schedule and algorithm    */
/*            for decrypting the archetype files.  Release of this code in   */
/*            source or object form can defeat the purpose of encrypting the */
/*            archetypes.                                                    */
/*****************************************************************************/
/** Export Control: (from Federal Information Processing Standards Pub 46)  **/
/** "Cryptographic devices and technical data regarding them are            **/
/**  subject to Feferal Government export controls as specified in Title    **/
/**  22, Code of Federal Regulations, Parts 121 through 128.                **/
/**  Cryptographic devices implementing this standard and technical data    **/
/**  regarding them must comply with these Federal regulations."            **/
/*****************************************************************************/


/* The following macro turns on full DES encryption.  If this is not         */
/* defined, just the "initial permutation is used.  This will considerably   */
/* speed up the routine with a relatively small decrease in security.        */
#undef FULL_DES_ENCRYPTION  

/* The basic idea is that each line is prefixed with a
 * random set of 32 bits and 32 bits of string length
 * and padded to a multiple of 64 
 * bits.  Then each 64 bits is XORed with the previously 
 * enciphered set, encrypted using the DES 
 * algorithm (encipher) and then base 64 encoded (using MIME format)
 *
 * This implies that the encoded string length will be 
 *   11 * (15+clear_length div 8) (not including the terminating
 *                                 zero in either length)
 *
 *
 * These routines have been designed to be endian independant.
 */


/* Include the interface to the routines */
#include "gs_crypt.hh"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/*----------------------------------------------------*/
/* Basic block used in the DES algorithm is 64 bits   */
/* Most calculations are performed on 32 bit numbers  */
/*----------------------------------------------------*/

typedef unsigned char Bit64[8];
typedef unsigned long int Bit32;

/* Convert a string to 64 bits, padding with random bytes */
static inline void string_to_bit64(const char *string, Bit64 result, int len)
{
  int i;
  for (i=7; i>=0 && len>0; i--, len--)
    result[i] = *string++;

  for (;i>=0; i--)
    result[i] = rand();
}

/* Overwrite 64 bit number into a string */
static inline void bit64_to_string(const Bit64 bit64, char *result, int len)
{
  int i;
  for (i=7; i>=0 && len>0; i--, len--)
    *result++ = bit64[i];
}

/* Convert a 64 bit number into a 32 bit number (least significant bytes) */
static inline Bit32 bit64_to_bit32(const Bit64 bit64)
{
  Bit32 first =  bit64[4];
  Bit32 second = bit64[5];
  Bit32 third =  bit64[6];
  Bit32 fourth = bit64[7];

  return (((((first<<8)+second)<<8)+third)<<8)+fourth;
}

/* Convert a 32 bit number into a 64 bit number (least significant bytes),
   leaving the most significant bytes alone */
static inline void bit32_to_bit64(const Bit32 l, Bit64 bit64)
{
  bit64[4] = ( unsigned char ) ( 0xFF & (l>>24) );
  bit64[5] = ( unsigned char ) ( 0xFF & (l>>16) );
  bit64[6] = ( unsigned char ) ( 0xFF & (l>>8) );
  bit64[7] = ( unsigned char ) ( 0xFF & l );
}

/* Convert two 32 bit numbers into a 64 bit number */
static inline void bit32s_to_bit64(const Bit32 h, const Bit32 l, Bit64 bit64)
{
  bit64[0] = ( unsigned char ) ( 0xFF & (h>>24) );
  bit64[1] = ( unsigned char ) ( 0xFF & (h>>16) );
  bit64[2] = ( unsigned char ) ( 0xFF & (h>>8) );
  bit64[3] = ( unsigned char ) ( 0xFF & h );
  bit64[4] = ( unsigned char ) ( 0xFF & (l>>24) );
  bit64[5] = ( unsigned char ) ( 0xFF & (l>>16) );
  bit64[6] = ( unsigned char ) ( 0xFF & (l>>8) );
  bit64[7] = ( unsigned char ) ( 0xFF & l );
}

/* Convert a 64 bit number into two 32 bit numbers */
static inline void bit64_to_bit32s(const Bit64 bit64, Bit32 *h, Bit32 *l)
{
  Bit32 first = bit64[0];
  Bit32 second = bit64[1];
  Bit32 third = bit64[2];
  Bit32 fourth = bit64[3];
  Bit32 fifth = bit64[4];
  Bit32 sixth = bit64[5];
  Bit32 seventh = bit64[6];
  Bit32 eighth = bit64[7];

  *h = (((((first<<8)+second)<<8)+third)<<8)+fourth;
  *l = (((((fifth<<8)+sixth)<<8)+seventh)<<8)+eighth;
}

/* Exclusive-or two 64 bit numbers */
static inline void xor_bit64s(const Bit64 source, Bit64 dest)
{
  int i;
  for (i=0; i<7; i++)
    dest[i] ^= source[i];
}

/* Copy between 64 bit numbers */
static inline void copy_bit64(const Bit64 source,Bit64 dest)
{
  int i;
  for (i=0; i<7; i++)
    dest[i] = source[i];
}


/*----------------------------------------------------*/
/* Base 64 encoding/decoding                          */
/*----------------------------------------------------*/

/* These are the characters used to represent the digits */
static const char BASE64_DIGITS[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/* Each base 64 character encodes 6 bits.  Thus we have three cases:
 *   1 Encode the highest 6 bits in a byte,
 *   2 Encode the lowest 6 bits in a byte,
 *   3 Encode the lowest 4 bits in a byte combined with the highest 2 bits
 *     in the next byte,
 *   4 Encode the lowest 2 bits in a byte combined with the highest 4 bits in 
 *     the next byte 
 */

static const unsigned char MASK1 = 0xFC;
static const unsigned char MASK2 = 0x3F;
static const unsigned char MASK3_HIGH = 0x0F;
static const unsigned char MASK3_LOW  = 0xC0;
static const unsigned char MASK4_HIGH = 0x03;
static const unsigned char MASK4_LOW  = 0xF0;

/* Right shifts */
static int SHIFT1 = 2;
static int SHIFT2 = 0;
static int SHIFT3_LOW = 6;
static int SHIFT4_LOW = 4;
/* Left shifts */
static int SHIFT3_HIGH = 2;
static int SHIFT4_HIGH = 4;

/* Encode 64 bits using big-endian base-64 encoding */
static char *encode(const Bit64 bits, char *string)
{
  /* Case 1 with byte 7 */
  *string++ = BASE64_DIGITS[(bits[7] & MASK1) >> SHIFT1];

  /* Case 4 with bytes 7 and 6 */
  *string++ = BASE64_DIGITS[((bits[7] & MASK4_HIGH) << SHIFT4_HIGH) |
                             ((bits[6] & MASK4_LOW) >> SHIFT4_LOW)];

  /* Case 3 with bytes 6 and 5 */
  *string++ = BASE64_DIGITS[((bits[6] & MASK3_HIGH) << SHIFT3_HIGH) |
                             ((bits[5] & MASK3_LOW) >> SHIFT3_LOW)];

  /* Case 2 with byte 5 */
  *string++ = BASE64_DIGITS[(bits[5] & MASK2) >> SHIFT2];

  /* Case 1 with byte 4 */
  *string++ = BASE64_DIGITS[(bits[4] & MASK1) >> SHIFT1];

  /* Case 4 with bytes 4 and 3 */
  *string++ = BASE64_DIGITS[((bits[4] & MASK4_HIGH) << SHIFT4_HIGH) |
                             ((bits[3] & MASK4_LOW) >> SHIFT4_LOW)];

  /* Case 3 with bytes 3 and 2 */
  *string++ = BASE64_DIGITS[((bits[3] & MASK3_HIGH) << SHIFT3_HIGH) |
                             ((bits[2] & MASK3_LOW) >> SHIFT3_LOW)];

  /* Case 2 with byte 2 */
  *string++ = BASE64_DIGITS[(bits[2] & MASK2) >> SHIFT2];

  /* Case 1 with byte 1 */
  *string++ = BASE64_DIGITS[(bits[1] & MASK1) >> SHIFT1];

  /* Case 4 with bytes 1 and 0 */
  *string++ = BASE64_DIGITS[((bits[1] & MASK4_HIGH) << SHIFT4_HIGH) |
                             ((bits[0] & MASK4_LOW) >> SHIFT4_LOW)];

  /* Case 3 with byte 0 */
  *string++ = BASE64_DIGITS[(bits[0] & MASK3_HIGH) << SHIFT3_HIGH];

  return string;
}

/* Decode 64 bits using big-endian base-64 encoding */
static const char *decode(const char *string, Bit64 bits)
{
  static unsigned char reverse_map[256];
  static map_initialized=0;

  unsigned char six_bits[11];

  if (!map_initialized)
    {
      int i;
      for (i=0; i<64; i++)
        reverse_map[BASE64_DIGITS[i]] = i;
      map_initialized = 1;
    }

  /* Translate the string into numeric form */
  {
    int i;
    for (i=0; i<11; i++)
      six_bits[i] = reverse_map[*string++];
  }

  /* Case 1 with byte 7 */
  bits[7] = MASK1 & (six_bits[0] << SHIFT1);

  
  /* Case 4 with bytes 7 and 6 */
  bits[7] |= MASK4_HIGH & (six_bits[1] >> SHIFT4_HIGH);
  bits[6] =  MASK4_LOW  & (six_bits[1] << SHIFT4_LOW);

  /* Case 3 with bytes 6 and 5 */
  bits[6] |= MASK3_HIGH & (six_bits[2] >> SHIFT3_HIGH);
  bits[5] =  MASK3_LOW  & (six_bits[2] << SHIFT3_LOW);

  /* Case 2 with byte 5 */
  bits[5] |= MASK2 & (six_bits[3] << SHIFT2);

  /* Case 1 with byte 4 */
  bits[4] = MASK1 & (six_bits[4] << SHIFT1);
  
  /* Case 4 with bytes 4 and 3 */
  bits[4] |= MASK4_HIGH & (six_bits[5] >> SHIFT4_HIGH);
  bits[3] =  MASK4_LOW  & (six_bits[5] << SHIFT4_LOW);

  /* Case 3 with bytes 3 and 2 */
  bits[3] |= MASK3_HIGH & (six_bits[6] >> SHIFT3_HIGH);
  bits[2] =  MASK3_LOW  & (six_bits[6] << SHIFT3_LOW);

  /* Case 2 with byte 2 */
  bits[2] |= MASK2 & (six_bits[7] << SHIFT2);

  /* Case 1 with byte 1 */
  bits[1] = MASK1 & (six_bits[8] << SHIFT1);

  /* Case 4 with bytes 1 and 0 */
  bits[1] |= MASK4_HIGH & (six_bits[9] >> SHIFT4_HIGH);
  bits[0] =  MASK4_LOW  & (six_bits[9] << SHIFT4_LOW);

  /* Case 3 with byte 0 */
  bits[0] |= MASK3_HIGH & (six_bits[10] >> SHIFT3_HIGH);

  return string;
}


/*------------------------------------------------------*/
/* Encryption and decryption routines                   */
/*------------------------------------------------------*/

void encipher(Bit64 bits);
void decipher(Bit64 bits);

#define METACHARACTER '.'
#define ENCRYPTION_FLAG '+'

/* Encrypt a line of input */
int Encrypt_Line(const char *input_buffer, char *output_buffer, 
                 int output_buffer_length)
{
  int input_length;
  int octets;

  input_length = strlen(input_buffer);
  octets = (15+input_length)/8; /* Number of Bit64s */

  if (output_buffer_length<=(3+8*octets))
    return 3+8*octets;

  {
    Bit64 previous;
    Bit64 current;

    char *output = output_buffer+2;

    int octet;

    /* Put the sequence .+ at the start of the encrypted lines */
    output_buffer[0] = METACHARACTER;
    output_buffer[1] = ENCRYPTION_FLAG;

    for (octet=0; octet<octets; octet++)
      {
        if (octet)
          {
            string_to_bit64(input_buffer+8*(octet-1), current, input_length);

            input_length -= 8;
            xor_bit64s(previous, current);
          }
        else
          {
            string_to_bit64(NULL, current, 0);
            bit32_to_bit64(input_length, current);
          }

        encipher(current);

        output = encode(current, output);
        copy_bit64(current, previous);
      }

    *output = 0;
  
  }

  return 0;
}

/* Decrypt a line of input */
void Decrypt_Line(const char *input_buffer, char *output_buffer)
{
  Bit64 previous_enciphered, current_enciphered;
  Bit64 current;
  
  const char *input = input_buffer+2;

  int octet;
  Bit32 output_length;

  if (input_buffer[0] != METACHARACTER || 
      input_buffer[1] != ENCRYPTION_FLAG)
    {
      /* Input is not encrypted, simply copy to output */
      
      char *output = output_buffer;

      for (input = input_buffer; *input; )
	*output++ = *input++;
      
      *output = *input;		/* Copy trailing '/0' */

    }
  else
    {
      

      for (octet=0; *input; octet++)
	{
	  input = decode(input, current);
	  
	  copy_bit64(current, current_enciphered);
	  
	  decipher(current);
	  
	  if (octet==0)
	    {
	      output_length = bit64_to_bit32(current);
	      
	      output_buffer[output_length] = 0;
	    }
	  else
	    {
	      xor_bit64s(previous_enciphered, current);
	      
	      bit64_to_string(current, output_buffer+(octet-1)*8, 
			      (int) output_length);
	      output_length -= 8;
	    }
	  
	  copy_bit64(current_enciphered, previous_enciphered);
	}
    }

}

 
/*-------------------------------------------------------------------*/
/* The DES Algorithm                                                 */
/*-------------------------------------------------------------------*/

/*********/
/* Types */
/*********/
typedef struct 
{
  int length;
  Bit32 source[32];
} Permutation;

typedef struct
{
  Permutation high_to_high;
  Permutation high_to_low;
  Permutation low_to_high;
  Permutation low_to_low;
} Double_Permutation;

typedef struct
{
  Permutation high;
  Permutation low;
} Expansion;

Bit32 permute(Bit32 input, const Permutation p)

{
  int i;
  Bit32 data = 0;
  Bit32 mask = 0x80000000l;

  mask >>= 32 - p.length;               /* Adjust so result is right aligned */

  for (i=0; i<p.length; i++)
    {
      if (input & p.source[i])
        data |= mask;

      mask >>= 1;
    }

  return data;
  
}

inline void double_permute(Bit32 high_input, Bit32 low_input,
                           const Double_Permutation p, 
                           Bit32 *high_output, Bit32 *low_output)
{
  *high_output = 
    permute(high_input, p.high_to_high) | 
      permute(low_input, p.low_to_high);
  *low_output = 
    permute(high_input, p.high_to_low) |
      permute(low_input, p.low_to_low);
}


inline void expand(Bit32 input, 
                   const Expansion e, 
                   Bit32 *high_output, Bit32 *low_output)
{
  *high_output = 
    permute(input, e.high);
  *low_output = 
    permute(input, e.low);
}

/*---------------------------------*/
/* Include the magic DES constants */
/*---------------------------------*/

/* Following tables are contents of #include "des_tbls.inc" */

/* Subsystem: Encryption                                                     */
/* File:      DES Constants Include File                                     */
/* Author:    John Yeager                                                    */
/* Purpose:   Defines the permutation and selection tables used by the       */
/*            data encryption standard (DES) algorithm.                      */
/* Notes:                                                                    */
/*   1. The key scheduling tables are not included, since the key schedule   */
/*      is precomputed.                                                      */
/*   2. The S tables have been rearranged from FIPS PUB 46 to allow the six  */
/*      bit numbers to be used as indices into the tables.                   */
/*   3. These tables are defined in terms of typedefs declared in crypt.c    */


/* The Initial and Inverse initial permutations are 64-bits */
static const Double_Permutation IP = 
{
  { /* High to high */
    32, 
    {
      0x00000000l,              /* 58 -> 0*/
      0x00000000l,              /* 50 -> 0*/
      0x00000000l,              /* 42 -> 0*/
      0x00000000l,              /* 34 -> 0*/
      0x00000040l,              /* 26     */
      0x00004000l,              /* 18     */
      0x00400000l,              /* 10     */
      0x40000000l,              /*  2     */
      0x00000000l,              /* 60 -> 0*/
      0x00000000l,              /* 52 -> 0*/
      0x00000000l,              /* 44 -> 0*/
      0x00000000l,              /* 36 -> 0*/
      0x00000010l,              /* 28     */
      0x00001000l,              /* 20     */
      0x00100000l,              /* 12     */
      0x10000000l,              /*  4     */
      0x00000000l,              /* 62 -> 0*/
      0x00000000l,              /* 54 -> 0*/
      0x00000000l,              /* 46 -> 0*/
      0x00000000l,              /* 38 -> 0*/
      0x00000004l,              /* 30     */
      0x00000400l,              /* 22     */
      0x00040000l,              /* 14     */
      0x04000000l,              /*  6     */
      0x00000000l,              /* 64 -> 0*/
      0x00000000l,              /* 56 -> 0*/
      0x00000000l,              /* 48 -> 0*/
      0x00000000l,              /* 40 -> 0*/
      0x00000001l,              /* 32     */
      0x00000100l,              /* 24     */
      0x00010000l,              /* 16     */
      0x01000000l               /*  8     */
    }
  },
  { /* High-order to Low-order */
    32,
    {
      0x00000000l,              /* 57 -> 0*/
      0x00000000l,              /* 49 -> 0*/
      0x00000000l,              /* 41 -> 0*/
      0x00000000l,              /* 33 -> 0*/
      0x00000080l,              /* 25     */
      0x00008000l,              /* 17     */
      0x00800000l,              /*  9     */
      0x80000000l,              /*  2     */
      0x00000000l,              /* 59 -> 0*/
      0x00000000l,              /* 51 -> 0*/
      0x00000000l,              /* 43 -> 0*/
      0x00000000l,              /* 35 -> 0*/
      0x00000020l,              /* 27     */
      0x00002000l,              /* 19     */
      0x00200000l,              /* 11     */
      0x20000000l,              /*  3     */
      0x00000000l,              /* 61 -> 0*/
      0x00000000l,              /* 53 -> 0*/
      0x00000000l,              /* 45 -> 0*/
      0x00000000l,              /* 37 -> 0*/
      0x00000008l,              /* 29     */
      0x00000800l,              /* 21     */
      0x00080000l,              /* 13     */
      0x08000000l,              /*  5     */
      0x00000000l,              /* 63 -> 0*/
      0x00000000l,              /* 55 -> 0*/
      0x00000000l,              /* 47 -> 0*/
      0x00000000l,              /* 39 -> 0*/
      0x00000002l,              /* 31     */
      0x00000200l,              /* 23     */
      0x00020000l,              /* 15     */
      0x02000000l               /*  7     */
    }
  },
  { /* Low-order to High-order */
    32, 
    {
      0x00000040l,              /* 58 -> 26*/
      0x00004000l,              /* 50 -> 18*/
      0x00400000l,              /* 42 -> 10*/
      0x40000000l,              /* 34 ->  2*/
      0x00000000l,              /* 26      */
      0x00000000l,              /* 18      */
      0x00000000l,              /* 10      */
      0x00000000l,              /*  2      */
      0x00000010l,              /* 60 -> 28*/
      0x00001000l,              /* 52 -> 20*/
      0x00100000l,              /* 44 -> 12*/
      0x10000000l,              /* 36 ->  4*/
      0x00000000l,              /* 28      */
      0x00000000l,              /* 20      */
      0x00000000l,              /* 12      */
      0x00000000l,              /*  4      */
      0x00000004l,              /* 62 -> 30*/
      0x00000400l,              /* 54 -> 22*/
      0x00040000l,              /* 46 -> 14*/
      0x04000000l,              /* 38 ->  6*/
      0x00000000l,              /* 30      */
      0x00000000l,              /* 22      */
      0x00000000l,              /* 14      */
      0x00000000l,              /*  6      */
      0x00000001l,              /* 64 -> 32*/
      0x00000100l,              /* 56 -> 24*/
      0x00010000l,              /* 48 -> 16*/
      0x01000000l,              /* 40 ->  8*/
      0x00000000l,              /* 32      */
      0x00000000l,              /* 24      */
      0x00000000l,              /* 16      */
      0x00000000l               /*  8      */
    }
  },
  { /* Low-order to Low-order */
    32, 
    {
      0x00000080l,              /* 57 -> 25*/
      0x00008000l,              /* 49 -> 17*/
      0x00800000l,              /* 41 ->  9*/
      0x80000000l,              /* 33 ->  1*/
      0x00000000l,              /* 25      */
      0x00000000l,              /* 17      */
      0x00000000l,              /*  9      */
      0x00000000l,              /*  1      */
      0x00000020l,              /* 59 -> 27*/
      0x00002000l,              /* 51 -> 19*/
      0x00200000l,              /* 43 -> 11*/
      0x20000000l,              /* 35 ->  3*/
      0x00000000l,              /* 27      */
      0x00000000l,              /* 19      */
      0x00000000l,              /* 11      */
      0x00000000l,              /*  3      */
      0x00000008l,              /* 61 -> 29*/
      0x00000800l,              /* 53 -> 21*/
      0x00080000l,              /* 45 -> 13*/
      0x08000000l,              /* 37 ->  5*/
      0x00000000l,              /* 29      */
      0x00000000l,              /* 21      */
      0x00000000l,              /* 13      */
      0x00000000l,              /*  5      */
      0x00000002l,              /* 64 -> 31*/
      0x00000200l,              /* 55 -> 23*/
      0x00020000l,              /* 47 -> 15*/
      0x02000000l,              /* 39 ->  7*/
      0x00000000l,              /* 31      */
      0x00000000l,              /* 23      */
      0x00000000l,              /* 15      */
      0x00000000l               /*  7      */
    }
  }
};


static const Double_Permutation Inverse_IP = 
{
  { /* High to high */
    32, 
    {
      0x00000000l,              /* 40 ->  0*/
      0x01000000l,              /*  8      */
      0x00000000l,              /* 48 ->  0*/
      0x00010000l,              /* 16      */
      0x00000000l,              /* 56 ->  0*/
      0x00000100l,              /* 24      */
      0x00000000l,              /* 64 ->  0*/
      0x00000001l,              /* 32      */
      0x00000000l,              /* 39 ->  0*/
      0x02000000l,              /*  7      */
      0x00000000l,              /* 47 ->  0*/
      0x00020000l,              /* 15      */
      0x00000000l,              /* 55 ->  0*/
      0x00000200l,              /* 23      */
      0x00000000l,              /* 63 ->  0*/
      0x00000002l,              /* 31      */
      0x00000000l,              /* 38 ->  0*/
      0x04000000l,              /*  6      */
      0x00000000l,              /* 46 ->  0*/
      0x00040000l,              /* 14      */
      0x00000000l,              /* 54 ->  0*/
      0x00000400l,              /* 22      */
      0x00000000l,              /* 62 ->  0*/
      0x00000004l,              /* 30      */
      0x00000000l,              /* 37 ->  0*/
      0x08000000l,              /*  5      */
      0x00000000l,              /* 45 ->  0*/
      0x00080000l,              /* 13      */
      0x00000000l,              /* 53 ->  0*/
      0x00000800l,              /* 21      */
      0x00000000l,              /* 61 ->  0*/
      0x00000008l,              /* 29      */
    }
  },
  { /* High-order to Low-order */
    32,
    {
      0x00000000l,              /* 36 ->  0*/
      0x10000000l,              /*  4      */
      0x00000000l,              /* 44 ->  0*/
      0x00100000l,              /* 12      */
      0x00000000l,              /* 52 ->  0*/
      0x00001000l,              /* 20      */
      0x00000000l,              /* 60 ->  0*/
      0x00000010l,              /* 28      */
      0x00000000l,              /* 35 ->  0*/
      0x20000000l,              /*  3      */
      0x00000000l,              /* 43 ->  0*/
      0x00200000l,              /* 11      */
      0x00000000l,              /* 51 ->  0*/
      0x00002000l,              /* 19      */
      0x00000000l,              /* 59 ->  0*/
      0x00000020l,              /* 27      */
      0x00000000l,              /* 34 ->  0*/
      0x40000000l,              /*  2      */
      0x00000000l,              /* 42 ->  0*/
      0x00400000l,              /* 10      */
      0x00000000l,              /* 50 ->  0*/
      0x00004000l,              /* 18      */
      0x00000000l,              /* 58 ->  0*/
      0x00000040l,              /* 26      */
      0x00000000l,              /* 33 ->  0*/
      0x80000000l,              /*  1      */
      0x00000000l,              /* 41 ->  0*/
      0x00800000l,              /*  9      */
      0x00000000l,              /* 49 ->  0*/
      0x00008000l,              /* 17      */
      0x00000000l,              /* 57 ->  0*/
      0x00000080l,              /* 25      */
    }
  },
  { /* Low-order to High-order */
    32, 
    {
      0x01000000l,              /* 40 ->  8*/
      0x00000000l,              /*  8      */
      0x00010000l,              /* 48 -> 16*/
      0x00000000l,              /* 16      */
      0x00000100l,              /* 56 -> 24*/
      0x00000000l,              /* 24      */
      0x00000001l,              /* 64 -> 32*/
      0x00000000l,              /* 32      */
      0x02000000l,              /* 39 ->  7*/
      0x00000000l,              /*  7      */
      0x00020000l,              /* 47 -> 15*/
      0x00000000l,              /* 15      */
      0x00000200l,              /* 55 -> 23*/
      0x00000000l,              /* 23      */
      0x00000002l,              /* 63 -> 31*/
      0x00000000l,              /* 31      */
      0x04000000l,              /* 38 ->  6*/
      0x00000000l,              /*  6      */
      0x00040000l,              /* 46 -> 14*/
      0x00000000l,              /* 14      */
      0x00000400l,              /* 54 -> 22*/
      0x00000000l,              /* 22      */
      0x00000004l,              /* 62 -> 30*/
      0x00000000l,              /* 30      */
      0x08000000l,              /* 37 ->  5*/
      0x00000000l,              /*  5      */
      0x00080000l,              /* 45 -> 13*/
      0x00000000l,              /* 13      */
      0x00000800l,              /* 53 -> 21*/
      0x00000000l,              /* 21      */
      0x00000008l,              /* 61 -> 29*/
      0x00000000l,              /* 29      */
    }
  },
  { /* Low-order to Low-order */
    32, 
    {
      0x10000000l,              /* 36 ->  4*/
      0x00000000l,              /*  4      */
      0x00100000l,              /* 44 -> 12*/
      0x00000000l,              /* 12      */
      0x00001000l,              /* 52 -> 20*/
      0x00000000l,              /* 20      */
      0x00000010l,              /* 60 -> 28*/
      0x00000000l,              /* 28      */
      0x20000000l,              /* 35 ->  3*/
      0x00000000l,              /*  3      */
      0x00200000l,              /* 43 -> 11*/
      0x00000000l,              /* 11      */
      0x00002000l,              /* 51 -> 19*/
      0x00000000l,              /* 19      */
      0x00000020l,              /* 59 -> 27*/
      0x00000000l,              /* 27      */
      0x40000000l,              /* 34 ->  2*/
      0x00000000l,              /*  2      */
      0x00400000l,              /* 42 -> 10*/
      0x00000000l,              /* 10      */
      0x00004000l,              /* 50 -> 18*/
      0x00000000l,              /* 18      */
      0x00000040l,              /* 58 -> 26*/
      0x00000000l,              /* 26      */
      0x80000000l,              /* 33 ->  1*/
      0x00000000l,              /*  1      */
      0x00800000l,              /* 41 ->  9*/
      0x00000000l,              /*  9      */
      0x00008000l,              /* 49 -> 17*/
      0x00000000l,              /* 17      */
      0x00000080l,              /* 57 -> 25*/
      0x00000000l,              /* 25      */
    }
  }
};

/* This permutation is referred to as the "primative function" */
static const Permutation P =
{
  32,
  { 
    0x00010000l,                /* 16 */
    0x02000000l,                /*  7 */
    0x00001000l,                /* 20 */
    0x00000800l,                /* 21 */
    0x00000008l,                /* 29 */
    0x00100000l,                /* 12 */
    0x00000010l,                /* 28 */
    0x00008000l,                /* 17 */
    0x80000000l,                /*  1 */
    0x00020000l,                /* 15 */
    0x00000200l,                /* 23 */
    0x00000040l,                /* 26 */
    0x08000000l,                /*  5 */
    0x00004000l,                /* 18 */
    0x00000002l,                /* 31 */
    0x00400000l,                /* 10 */
    0x40000000l,                /*  2 */
    0x01000000l,                /*  8 */
    0x00000100l,                /* 24 */
    0x00040000l,                /* 14 */
    0x00000001l,                /* 32 */
    0x00000020l,                /* 27 */
    0x20000000l,                /*  3 */
    0x00800000l,                /*  9 */
    0x00002000l,                /* 19 */
    0x00080000l,                /* 13 */
    0x00000004l,                /* 30 */
    0x04000000l,                /*  6 */
    0x00000400l,                /* 22 */
    0x00200000l,                /* 11 */
    0x10000000l,                /*  4 */
    0x00000080l                 /* 25 */
  }
};

/* Expansion table */
static const Expansion E = 
{
  { /* High */
    16,
	{
    0x00000001l,                /* 32 */
    0x80000000l,                /*  1 */
    0x40000000l,                /*  2 */
    0x20000000l,                /*  3 */
    0x10000000l,                /*  4 */
    0x08000000l,                /*  5 */
    0x10000000l,                /*  4 */
    0x08000000l,                /*  5 */
    0x04000000l,                /*  6 */
    0x02000000l,                /*  7 */
    0x01000000l,                /*  8 */
    0x00800000l,                /*  9 */
    0x01000000l,                /*  8 */
    0x00800000l,                /*  9 */
    0x00400000l,                /* 10 */
    0x00200000l                 /* 11 */
	}
  },
  { /* Low */
    32,
	{
    0x00100000l,                /* 12 */
    0x00080000l,                /* 13 */
    0x00100000l,                /* 12 */
    0x00080000l,                /* 13 */
    0x00040000l,                /* 14 */
    0x00020000l,                /* 15 */
    0x00010000l,                /* 16 */
    0x00008000l,                /* 17 */
    0x00010000l,                /* 16 */
    0x00008000l,                /* 17 */
    0x00004000l,                /* 18 */
    0x00002000l,                /* 19 */
    0x00001000l,                /* 20 */
    0x00000800l,                /* 21 */
    0x00001000l,                /* 20 */
    0x00000800l,                /* 21 */
    0x00000400l,                /* 22 */
    0x00000200l,                /* 23 */
    0x00000100l,                /* 24 */
    0x00000080l,                /* 25 */
    0x00000100l,                /* 24 */
    0x00000080l,                /* 25 */
    0x00000040l,                /* 26 */
    0x00000020l,                /* 27 */
    0x00000010l,                /* 28 */
    0x00000008l,                /* 29 */
    0x00000010l,                /* 28 */
    0x00000008l,                /* 29 */
    0x00000004l,                /* 30 */
    0x00000002l,                /* 31 */
    0x00000001l,                /* 32 */
    0x80000000l                 /*  1 */
	}
  }
};  

/* These are the "S boxes" rearranged to allow the six bits to be used
 * as an index (in FIPS PUB 46 the middle four bits were used as one index
 * and the outer two bits as the other into a two-dimensional array for each 
 * S box 
 */
Bit32 S[8][64] = 
{ 
  { /* S1 */ 
    14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8, 1,
     3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7, 8, 
     4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11, 7, 
    15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13 
  },
  { /* S2 */
    15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  1,  3,  8,  4, 14, 
     9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5,
     0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2, 
     5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 14,  9
  },
  { /* S3 */
    10, 13,  0,  7,  9,  0, 14,  9,  6,  3,  3,  4, 15,  6,  5, 10, 
     1,  2, 13,  8, 12,  5,  7, 14, 11, 12,  4, 11,  2, 15,  8,  1,
    13,  1,  6, 10,  4, 13,  9,  0,  8,  6, 15,  9,  3,  8,  0,  7,
    11,  4,  1, 15,  2, 14, 12,  3,  5, 11, 10,  5, 14,  2,  7, 12
  },
  { /* S4 */
     7, 13, 13,  8, 14, 11,  3,  5,  0,  6,  6, 15,  9,  0, 10,  3,
     1,  4,  2,  7,  8,  2,  5, 12, 11,  1, 12, 10,  4, 14, 15,  9,
    10,  3,  6, 15,  9,  0,  0,  6, 12, 10, 11,  1,  7, 13, 13,  8, 
    15,  9,  1,  4,  3,  5, 14, 11,  5, 12,  2,  7,  8,  2,  4, 14
  },
  { /* S5 */
     2, 14, 12, 11,  4,  2,  1, 12,  7,  4, 10,  7, 11, 13,  6,  1,
     8,  5,  5,  0,  3, 15, 15, 10, 13,  3,  0,  9, 14,  8,  9,  6,
     4, 11,  2,  8,  1, 12, 11,  7, 10,  1, 13, 14,  7,  2,  8, 13, 
    15,  6,  9, 15, 12,  0,  5,  9,  6, 10,  3,  4,  0,  5, 14,  3
  },
  { /* S6 */
    12, 10,  1, 15, 10,  4, 15,  2,  9,  7,  2, 12,  6,  9,  8,  5,
     0,  6, 13,  1,  3, 13,  4, 14, 14,  0,  7, 11,  5,  3, 11,  8,
     9,  4, 14,  3, 15,  2,  5, 12,  2,  9,  8,  5, 12, 15,  3, 10,
     7, 11,  0, 14,  4,  1, 10,  7,  1,  6, 13,  0, 11,  8,  6, 13
  },
  { /* S7 */
     4, 13, 11,  0,  2, 11, 14,  7, 15,  4,  0,  9,  8,  1, 13, 10, 
     3, 14, 12,  3,  9,  5,  7, 12,  5,  2, 10, 15,  6,  8,  1,  6,
     1,  6,  4, 11, 11, 13, 13,  8, 12,  1,  3,  4,  7, 10, 14,  7,
    10,  9, 15,  5,  6,  0,  8, 15,  0, 14,  5,  2,  9,  3,  2, 12
  },
  { /* S8 */
    13,  1,  2, 15,  8, 13,  4,  8,  6, 10, 15,  3, 11,  7,  1,  4,
    10, 12,  9,  5,  3,  6, 14, 11,  5,  0,  0, 14, 12,  9,  7,  2,
     7,  2, 11,  1,  4, 14,  1,  7,  9,  4, 12, 10, 14,  8,  2, 13,
     0, 15,  6, 12, 10,  9, 13,  0, 15,  3,  3,  5,  5,  6,  8, 11
  }
};
/* End contents of #include "des_tbls.inc" */


/*------------------------------------------------------*/
/* The following is the key schedule which causes the   */
/* information to be scrambled.  This is the standard   */
/* DES key schedule for the key 0x6A28 A20A 08A2 0828   */
/* (This key has a 1 for each bit which is prime).      */
/*------------------------------------------------------*/

/* This table was generated by the following command:
 * awk -f pc1.awk | awk -f cd.awk | awk -f pc2.awk
 * with input 
 * 0110101000101000101000100000101000001000101000100000100000101000 
 */

static const Bit32 KS[16][2] =
{
  {0x04A8l, 0x20AF809l},
  {0xC8A1l, 0x0280CABl},
  {0x0086l, 0x08E5813l},
  {0x6110l, 0x2074370l},
  {0xA088l, 0xE918940l},
  {0x9062l, 0x1C08614l},
  {0x2417l, 0x159268Cl},
  {0x4610l, 0x4385089l},
  {0x0805l, 0x73A2CA4l},
  {0xC540l, 0x1284993l},
  {0x0783l, 0x8076013l},
  {0x1A18l, 0x8E70140l},
  {0x3920l, 0x480834El},
  {0x0044l, 0x8549684l},
  {0x5009l, 0x15804E9l},
  {0x524Cl, 0x260F4A4l}
};


#if 0
#  define DISPLAY(TEXT,H,L) \
  fprintf(stderr,"%s %lx%lx\n",TEXT,H,L)
#else
#  define DISPLAY(TEXT, H, L)
#endif


static Bit32 f(Bit32 r, Bit32 key_high, Bit32 key_low);

/* DES Block Encryption */
void encipher(Bit64 bits)
{
  Bit32 low_input_word;
  Bit32 high_input_word;

  Bit32 l;
  Bit32 r;

  Bit32 low_output_word;
  Bit32 high_output_word;

  int round;

  bit64_to_bit32s(bits, &high_input_word, &low_input_word);

  DISPLAY("Encoding: ",high_input_word, low_input_word);

  /* Perform initial permutation */

  double_permute(high_input_word, low_input_word, IP, &l, &r);

  DISPLAY(" IP",l,r);

#ifdef FULL_DES_ENCRYPTION

  /* Peform 16 rounds with interchange */
  for (round=0; round<16; round++)
    {
      Bit32 l_prime = r;
      r = l ^ f(r, KS[round][0], KS[round][1]);
      l = l_prime;
      DISPLAY(" RR",l,r);
    }

  /* Perform inverse permutation (L/R reversed to undo last interchange) */
  double_permute(r, l, Inverse_IP, &high_output_word, &low_output_word);

  DISPLAY("IIP",high_output_word,low_output_word);

  bit32s_to_bit64(high_output_word, low_output_word, bits);
#else
  bit32s_to_bit64(r, l, bits);
#endif  
}

/* DES Block Decryption */
void decipher(Bit64 bits)
{
  Bit32 low_input_word;
  Bit32 high_input_word;

  Bit32 l;
  Bit32 r;

  Bit32 low_output_word;
  Bit32 high_output_word;

  int round;

  bit64_to_bit32s(bits, &high_input_word, &low_input_word);

  DISPLAY("Decoding: ",high_input_word, low_input_word);

#ifdef FULL_DES_ENCRYPTION

  /* Perform initial permutation */

  double_permute(high_input_word, low_input_word, IP, &l, &r);

  DISPLAY(" IP",l,r);

  /* Peform 16 rounds with interchange */
  for (round=15; round>=0; round--)
    {
      Bit32 l_prime = r;
      r = l ^ f(r, KS[round][0], KS[round][1]);
      l = l_prime;
      DISPLAY(" RR",l,r);
    }
#else
  l = high_input_word;
  r = low_input_word;
#endif  

  /* Perform inverse permutation (L/R reversed to undo last interchange) */
  double_permute(r, l, Inverse_IP, &high_output_word, &low_output_word);
  

  DISPLAY("IIP",high_output_word,low_output_word);

  bit32s_to_bit64(high_output_word, low_output_word, bits);
  
}



const Bit32 SIX_BIT_MASK = 0x3F;

/* The function f serves as the core of the encryption iterations */
Bit32 f(Bit32 r, Bit32 key_high, Bit32 key_low)
{
  Bit32 h, l;
  Bit32 result = 0;
  int i;

  /* Expand the input to 48 bits */
  expand(r, E, &h, &l);

  /* Perform the key xor */
  h ^= key_high;
  l ^= key_low;


  for (i=7; i>=0; i--)
    {
      result |= S[i][l & SIX_BIT_MASK]<<(i*4);

      /* Shift the doubleword right 6 bits */
      l <<= 6;
      l |= (r & SIX_BIT_MASK);
      r <<= 6;
    }
      
  return permute(result, P);
}

