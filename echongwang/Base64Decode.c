//Decodes Base64
//#include <openssl/bio.h>
//#include <openssl/evp.h>
#include "openssl/include/openssl/evp.h"
#include "openssl/include/openssl/bio.h"
#include <string.h>
#include <stdio.h>

int calcDecodeLength(const char* b64input) { //Calculates the length of a decoded base64 string
  int len = strlen(b64input);
  int padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;

  return (int)len*0.75 - padding;
}

int Base64Decode(char* b64message, char** buffer) { //Decodes a base64 encoded string

  BIO *bio, *b64;
  int decodeLen = calcDecodeLength(b64message),
      len = 0;
  printf("decodeLen==%d\n",decodeLen);
  *buffer = (char*)malloc(strlen(b64message));
#if 0
  FILE* stream = fmemopen(b64message, strlen(b64message), "r");

  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new_fp(stream, BIO_NOCLOSE);
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
  len = BIO_read(bio, *buffer, strlen(b64message));
    //Can test here if len == decodeLen - if not, then return an error
  (*buffer)[len] = '\0';
  printf("decodeLen==%d\n",decodeLen);
  BIO_free_all(bio);
  fclose(stream);
#else  
    BIO * bmem = NULL; 
  
    b64 = BIO_new(BIO_f_base64());  
    {  
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  
    }  
    bmem = BIO_new_mem_buf(b64message, strlen(b64message));
    bmem = BIO_push(b64, bmem);  
    len = BIO_read(bmem, *buffer, strlen(b64message));
    printf("len==%d\n",len);
    (*buffer)[len] = '\0';
    BIO_free_all(bmem);  
#endif
  return (decodeLen); //success
}
