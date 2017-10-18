//Encodes Base64
//#include <openssl/bio.h>
//#include <openssl/evp.h>
//#include <openssl/buffer.h>
#include "openssl/include/openssl/evp.h"
#include "openssl/include/openssl/bio.h"
#include "openssl/include/openssl/buffer.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

int Base64Encode(const char* message, char** buffer) { //Encodes a string to base64
  
#if 0
  BIO *bio, *b64;
  FILE* stream;
  BUF_MEM *bptr = NULL;
  int len = 0;

  int encodedSize = 4*ceil((double)strlen(message)/3);
  *buffer = (char *)malloc(encodedSize+1);

  printf("encodeSize==%d\n",encodedSize);
  stream = fmemopen(*buffer, encodedSize+1, "w");
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new_fp(stream, BIO_NOCLOSE);
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
  BIO_write(bio, message, strlen(message));
    
  //len = BIO_read(bio, *buffer, strlen(message)); 
  //(*buffer)[len] = '\0';

  BIO_get_mem_ptr(bio, &bptr); 
  memcpy(buffer, bptr->data, bptr->length);
  printf("bptr->data=%s\n",bptr->data);  
  buffer[bptr->length] = 0;

  BIO_flush(bio);


  BIO_free_all(bio);
  fclose(stream);
#endif
    BIO * bmem = NULL;  
    BIO * b64 = NULL;  
    BUF_MEM * bptr = NULL;  
  
    b64 = BIO_new(BIO_f_base64());  
    {  
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  
    }  
    bmem = BIO_new(BIO_s_mem());  
    b64 = BIO_push(b64, bmem);  
    BIO_write(b64, message, 16);
    BIO_flush(b64);  
    BIO_get_mem_ptr(b64, &bptr);  
  
    *buffer = (char *)malloc(bptr->length + 1);
printf("bptr->length==%d  message=%d\n",bptr->length,strlen(message));  
    memcpy(buffer, bptr->data, bptr->length);  
    buffer[bptr->length] = 0;  
  
    BIO_free_all(b64);  

  return (0); //success
}
