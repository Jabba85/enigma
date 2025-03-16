#ifndef BASE_64H
 #define BASE_64H
//#include <stdint.h>
//#include <stdlib.h>
#ifndef __SIZE_T
 #define __SIZE_T
 typedef unsigned int 	size_t;
#endif
size_t b64_encoded_size(size_t inlen);
size_t b64_decoded_size(const char *in);
char *base64_encode(const unsigned char *data,size_t input_length);
int base64_decode(const char *in, unsigned char *out,size_t inlen, size_t outlen);
#endif
