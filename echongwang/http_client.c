#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>
#include "hmac.h"
#include "sha1.h"
#include "base64.h"
#include "aes.h"
#include "jsmn.h"
#include "error.h"

typedef struct register_ret
{
    int result; // 0 success -1 failed
    int ret;
    int data_len;
    char* data;
    char* err;
}RegisterRet;

void error(const char *msg) { perror(msg);}

static char *phex(unsigned char *md, unsigned int len)
{
    unsigned int i;
    static char buf[80];

    for (i = 0; i < len; i++)
        sprintf(&(buf[i * 2]), "%02X", md[i]);
    printf("buf==%s\n",buf);
    return (buf);
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

void gen_sig(char* input,int inputSize,const char* key,char * output)
{
  assert(NULL != input && NULL != output);
  assert(inputSize > 0);
  assert(16 == strlen(key));

  char dataSig[24] = {0};
  hmac_sha1((uint8_t*)key,16,(uint8_t*)input,inputSize,dataSig,sizeof(dataSig));
  base64_encode(dataSig,20,output);
}

/*input为输入数组,inputSize为输入数组长度,key为加密密匙,output为输出加密数组*/
void aes_encrypt(char* input,int inputSize,const char* key,char* output)
{
  assert(NULL != input && NULL != output); 
  assert(inputSize <=1024 && inputSize > 0);
  
  int pendLen = 16 - inputSize % 16; // 不足16补全长度
  unsigned char iv[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 加密矢量,在此固定

  char temp[1024] = {0};

  strcpy(temp,input);
  memset(temp+inputSize,pendLen,pendLen);
  
  printf("inputSize==%d pendLen==%d\n",inputSize,pendLen);
  printf("temp==%s\n",temp);
  char aes_result_str[1024];   // 存储加密字段
  AES128_CBC_encrypt_buffer(aes_result_str,temp,inputSize+pendLen,key,iv);
	printf("aes_result_str_len==%d\n",strlen(aes_result_str));
    phex(aes_result_str,16);
  Base64Encode(aes_result_str, output);
  printf("output==%s\n",output);
}

void aes_decrypt(char* input,const char* key,char* output,int outputSize)//解密
{
  assert(NULL != input && NULL != output);
  char* base64DecodeOutput;
  Base64Decode(input, &base64DecodeOutput);
      //phex(base64DecodeOutput,16);
     // char base64DecodeOutput[16] = {0x47,0x9F,0xAF,0x6F,0xEC,0x97,0x08,0x67,0xB9,0xE2,0x70,0xB9,0x32,0x4C,0xB2,0x33};
  //char base64DecodeOutput[16] = {0x93,0x7F,0x61,0x2D,0x9D,0x68,0x75,0x47,0xDC,0xAB,0x53,0x71,0xB6,0x18,0x12,0xE0};
      //char base64DecodeOutput[16] = {0xAF,0xDD,0x39,0xFA,0xE8,0xB3,0x6B,0xE7,0xD7,0xA8,0xF5,0x51,0x8D,0xCC,0x89,0x2B};

  unsigned char iv[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 加密矢量,在此固定
  int pendLen = 16 - outputSize % 16;    // 不足16补全长度

  AES128_CBC_decrypt_buffer(output,base64DecodeOutput,outputSize+pendLen,key,iv);
  printf("outputSize==%d  pendLen==%d\n",outputSize,pendLen);
  memset(output+outputSize,0,pendLen);   // 去除末尾填充字符,填0
}

//int main()
//{
//    e_register();
//    return 0;
//}

char* http_post(char* host, char* port, char* func, char* form_str)
{

    int i;
    int arg_num = 7;
    int portno = atoi(port)>0?atoi(port):80;
    char * method = "POST";
    char * content_type = "Content-Type: application/x-www-form-urlencoded";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message, response[4096];

    /* How big is the message? */
    message_size=0;
    if(!strcmp(method,"GET"))
    {
        message_size+=strlen("%s %s%s%s HTTP/1.0\r\n");        /* method         */
        message_size+=strlen(method);                         /* path           */
        message_size+=strlen(func);                         /* headers        */
        if(arg_num>5)
            message_size+=strlen(form_str);                     /* query string   */
        //for(i=6;i<arg_num;i++)                                    /* headers        */
        message_size+=strlen(host)+strlen("\r\n");
        message_size+=strlen(port)+strlen("\r\n");
        message_size+=strlen(method)+strlen("\r\n");
        message_size+=strlen(func)+strlen("\r\n");
        message_size+=strlen(form_str)+strlen("\r\n");
        message_size+=strlen(content_type)+strlen("\r\n");
        message_size+=strlen("\r\n");                          /* blank line     */
    }
    else
    {
        message_size+=strlen("%s %s HTTP/1.0\r\n");
        message_size+=strlen(method);                         /* method         */
        message_size+=strlen(func);                         /* path           */
        message_size+=strlen(host)+strlen("\r\n");
        message_size+=strlen(port)+strlen("\r\n");
        message_size+=strlen(method)+strlen("\r\n");
        message_size+=strlen(func)+strlen("\r\n");
        message_size+=strlen(form_str)+strlen("\r\n");
        message_size+=strlen(content_type)+strlen("\r\n");
        message_size+=strlen("\r\n");                          /* blank line     */
        if(arg_num>5)
            message_size+=strlen("Content-Length: %d\r\n")+10; /* content length */
        message_size+=strlen("\r\n");                          /* blank line     */
        if(arg_num>5)
            message_size+=strlen(form_str);                     /* body           */
    }

    /* allocate space for the message */
    message=malloc(message_size);

    /* fill in the parameters */
    if(!strcmp(method,"GET"))
    {
        if(arg_num>5)
            sprintf(message,"%s %s%s%s HTTP/1.0\r\n",
                strlen(method)>0?method:"GET",               /* method         */
                strlen(func)>0?func:"/",                 /* path           */
                strlen(form_str)>0?"?":"",                      /* ?              */
                strlen(form_str)>0?form_str:"");                 /* query string   */
        else
            sprintf(message,"%s %s HTTP/1.0\r\n",
                strlen(method)>0?method:"GET",               /* method         */
                strlen(func)>0?func:"/");                /* path           */
        {strcat(message,host);strcat(message,"\r\n");}
        {strcat(message,port);strcat(message,"\r\n");}
        {strcat(message,method);strcat(message,"\r\n");}
        {strcat(message,func);strcat(message,"\r\n");}
        {strcat(message,form_str);strcat(message,"\r\n");}
        {strcat(message,content_type);strcat(message,"\r\n");}
        strcat(message,"\r\n");                                /* blank line     */
    }
    else
    {
        sprintf(message,"%s %s HTTP/1.0\r\n",
            strlen(method)>0?method:"POST",                  /* method         */
            strlen(func)>0?func:"/");                    /* path           */
        {strcat(message,content_type);strcat(message,"\r\n");}
        if(arg_num>5)
            sprintf(message+strlen(message),"Content-Length: %d\r\n",strlen(form_str));
        strcat(message,"\r\n");                                /* blank line     */
        if(arg_num>5)
            strcat(message,form_str);                           /* body           */
    }

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
        return NULL;
    }

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL)
    {
        error("ERROR, no such host");
        return NULL;
    }

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
        return NULL;
    }

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
        {
            error("ERROR writing message to socket");
            return NULL;
        }
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
        {
            error("ERROR reading response from socket");
            return NULL;
        }
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
    {
        error("ERROR storing complete response from socket");
        return NULL;
    }

    /* close the socket */
    close(sockfd);

    /* process response */
    char *pch = strstr(response, "200 OK");
    if (pch == NULL)
    {
        error("ERROR http request failed!");
        return NULL;
    }

    char *token = NULL;
    char *data = NULL;
    token = strtok(response, "\n");
    while (token) {
        data = token;
        token = strtok(NULL, "\n");
    }

    free(message);
    return data;
}

RegisterRet register_json_decode(char * data)
{
    RegisterRet reg_ret;
	int ii;
	int r;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */

	jsmn_init(&p);
	r = jsmn_parse(&p, data, strlen(data), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
        error("ERROR failed to parse JSON");
        reg_ret.result = -1;
        return reg_ret;
	}

	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
        error("ERROR failed to parse JSON, Object expected");
        reg_ret.result = -1;
        return reg_ret;
	}
	/* Loop over all keys of the root object */
    
    char* data_str = NULL;
    char* err = NULL;
	int data_len;
	int ret;
    int i;
	for (i = 1; i < r; i++) {
		if (jsoneq(data, &t[i], "data") == 0) {
			data_str = strndup(data + t[i+1].start, t[i+1].end-t[i+1].start);
            reg_ret.data = data_str;
			i++;
		} else if (jsoneq(data, &t[i], "data_len") == 0) {
            data_len = strtol(data + t[i+1].start, NULL, 10);
            reg_ret.data_len = data_len;
			i++;
		} else if (jsoneq(data, &t[i], "err") == 0) {
			err = strndup(data + t[i+1].start, t[i+1].end-t[i+1].start);
            reg_ret.err = err;
			i++;
		} else if (jsoneq(data, &t[i], "ret") == 0) {
            ret = strtol(data + t[i+1].start, NULL, 10);
            reg_ret.ret = ret;
			i++;
		}
	}

    return reg_ret;
}

int e_register()
{
    char key[] = "0123456789abcdef";
    int arg_num = 7;
    char * host = "123.56.113.123";
    char* port = "8002";
    char* func = "/register";

    /*对数据生成签名*/
    char dataSig[64] = {0};
    char orinData[128]= "mac=04a316e03aee&timestamp=1479286152&type=normal";
    //char orinData[128]= "mac=20112233ef00&timestamp=1479286152&type=normal";
    gen_sig(orinData,strlen(orinData),key,dataSig);
    strcat(orinData,dataSig);
    char form_str[256];
    char* args = malloc(256);
    sprintf(form_str, "mac=04a316e03aee&timestamp=1479286152&type=normal&sig=%s", dataSig);
    //sprintf(form_str, "mac=20112233ef00&timestamp=1479286152&type=normal&sig=%s", dataSig);

    // 请求的返回结果
    char *data = NULL;
    data = http_post(host, port, func, form_str);
   
    if (data == NULL)
    {
        error("ERROR http post failed.");
        return -1;
    }
    
    char* ret_data;
    char* in_str;
    RegisterRet reg_ret;
    reg_ret = register_json_decode(data);
    if (reg_ret.result == -1)
    {
        error("ERROR json parse failed.");
        return -1;
    }

char input[2018] ="k39hLZ1odUfcq1NxthgS4A==";//"r905+uiza+fXqPVRjcyJKw==";//
//char input[20] = {0x47,0x9F,0xAF,0x6F,0xEC,0x97,0x08,0x67,0xB9,0xE2,0x70,0xB9,0x32,0x4C,0xB2,0x33};
char ret_str[2048] = {0};

	//printf("data==%s\n",data);
	//printf("reg_ret.data==%s\n",reg_ret.data);
    aes_decrypt(reg_ret.data,key,ret_str,reg_ret.data_len);
   // aes_decrypt(input,key,ret_str,14);
    printf("recv data:%s\n:",ret_str);


	
//char inputnew[128]="{\"did\": \"1000000000000011\", \"mq_passwd\": \"123456\", \"mq_port\": 1883, \"mq_user\": \"ral\", \"mq_addr\": \"123.56.113.123\"}";
char inputnew[128]="20161229111606";
	char output[2048]={0};
	aes_encrypt(inputnew,strlen(inputnew),key,output);
	printf("output == %s\n",output);

    return 0;
}



void *thread_http_service(void *arg) ___THREAD_ENTRY___
{
//    int *done = (int *)arg;
//    int mydone = 0;
//    int s;
//    while ( ! *done ) {

//    }
//    return NULL;
    e_register();

    return 0;
}
