/* ************************************************************************
 *       Filename:  echong_api.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2016年11月14日 15时01分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (andy.zhao), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "echong_api.h"
#include "error.h"
#include "openssl/include/openssl/hmac.h"
#include "openssl/include/openssl/sha.h"
#include "openssl/include/openssl/aes.h"
#include "mongoose/mongoose.h"

#include "tcu.h"


#define IPDST "192.168.122.204"
#define IPSTR "192.168.122.204"
#define PORT 8080
#define BUFSIZE 1024


#define APP_ID "1111111111"
#define INFO "aaaa"

#define MAC "04a316e03aee"//"20112233ef00"//"04A316E03AEE"
#define TYPE "normal"
#define TIMESTAMP 1410349438


#define TOKEN_LEN  33
#define SIG_LEN  20
#define EncodingAESKey_LEN 44  //43
#define kAesKeySize 32
#define kAesIVSize 16

int sig_len = 20;
int aes_key_len = 32;

char token[TOKEN_LEN] = "228bf094169a40a3bd188ba37ebe8723&";
char sig[SIG_LEN] = " ";
char base64_sig[100] =" ";
char encoding_aes_key[EncodingAESKey_LEN] = "0123456789abcdef";//"abcdefghijklmnopqrstuvwxyz0123456789ABCDEFG=";
char aes_key[16] = "0123456789abcdef";
char key[] = "0123456789abcdef";
char sNeedEncrypt_info[100] = "mac=04A316E03AEE&timestamp=1410349438&type=normal";
char sAesData[200] = " ";
char sBase64Data[200] = " ";
char sEncryptMsg[EncodingAESKey_LEN]="QGUlgqDyIh6AlRvofZDcqzWgCURll+qcgPW4czwghqo=";
//char sEncryptMsg[2048]="oGHlPDbhmdZuuQCckqBnJkJljSKiWiEMO3IaKNUX2BS+3Nzolp3xjNRXhYlc73/XH0LmshpwM744RoQrXLS/v2y1FGpiOSCXjgGNSEuCa7VQwgmgJsGxp6QWRwR0IA3iZpvWRw2iPo+vaAIjSMPZmeqqHItV8Jpsc4Vw+3M+AmA=";

//char sEncryptMsg[EncodingAESKey_LEN]="aAExMDAwMDAwMDAwMDAwMDExBACyAAcAEDFhP6EgbwtdFit79Drute8AzRY=";


char mac[13] = "04A316E03AEE";
char type[8] = "normal";
int  timestamp = 1410349438;
char sig_key[EncodingAESKey_LEN] = "0123456789abcdef";




static char *pt(unsigned char *md, unsigned int len)
{
    unsigned int i;
    static char buf[80];

    for (i = 0; i < len; i++)
        sprintf(&(buf[i * 2]), "%02X", md[i]);
    printf("buf==%s\n",buf);
    return (buf);
}

//=====c++(openssl):
//    HMAC(  EVP_sha1(),
//                     /*key data*/ strKey.data(),
//                     /*key len*/  strKey.size(),
//                     /*data  */(unsigned char*) strRandom.data(),
//                     /*data len*/ strRandom.size(), digest, &digest_len))


//1.开放平台为每一个接入者分配唯一的 EncodingAESKey。长度固定为 43个字符，从 a-z,A-Z,0-9 共 62 个字符中选取。

//2. AES 密钥：AESKey=Base64_Decode(EncodingAESKey + “=”)，EncodingAESKey尾部填充一 个字符的“=”, 用 Base64_Decode 生成 32 个字节的 AESKey；

//3. AES 采用 CBC 模式，秘钥长度为 32 个字节，数据采用 PKCS#7 填充；PKCS#7：K 为秘钥字节 数（采用 32），buf 为待加密的内容，N 为其字节数。Buf 需要被填充为 K 的整数倍。在 buf 的尾部 填充(K-N%K)个字节，每个字节的内容是(K- N%K)；具体参考：http://tools.ietf.org/html/rfc2315

//4.所有接口中的 info 字段均需要进行加密

//#define EncodingAESKey  //消息加密

int length_data(int tmp_Len,char *Length)
{
    printf("tmp_Len==%d\n",tmp_Len);
    if(tmp_Len<256){
        Length[0] = 0;
        Length[1] = tmp_Len;
    }else{
        Length[0] = tmp_Len/256;
        Length[1] = tmp_Len%256;
    }//长度为两个字节
}

int lengthL1_data(int tmp_Len,char *Length)
{
    printf("lengthL1_data  tmp_Len==%d\n",tmp_Len);
    char tmp_len[2] = " ";
    if(tmp_Len<256){
        tmp_len[0] = 0;
        tmp_len[1] = tmp_Len;
    }else{
        tmp_len[0] = tmp_Len/256;
        tmp_len[1] = tmp_Len%256;
    }//长度为两个字节

    Length[0] = (tmp_len[0] << 2) | ((tmp_len[1] >> 6) & 0x03);
    printf("Length0===%02X\n",Length[0]);

    Length[1] = (tmp_len[1] << 2 ) | 0x02;
    printf("Length1===%02X\n",Length[1]);
}


//获取当前时间
int getcurrenttime(char *thiz,char *LengthL2)
{
    time_t timep;
    struct tm *p;
    char tmptime[14] = {0};

    time(&timep);
    p =localtime(&timep);
    if ( p == NULL ) {
        //param->evt_param = EVT_RET_ERR;
        return 0;
    }
    printf("Local time is: %s\n",asctime(p));
    printf("%4d年%02d月%02d日 %02d:%02d:%02d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);

//    tmptime.Current_time_bcd_sec = (((p->tm_sec / 10 ) & 0x0F ) << 4) |
//            ((p->tm_sec % 10) & 0x0F);
//    tmptime.Current_time_bcd_min = (((p->tm_min / 10 ) & 0x0F ) << 4) |
//            ((p->tm_min % 10) & 0x0F);
//    tmptime.Current_time_bcd_hour = (((p->tm_hour / 10 ) & 0x0F ) << 4) |
//            ((p->tm_hour % 10) & 0x0F);
//    tmptime.Current_time_bcd_day = (((p->tm_mday / 10 ) & 0x0F ) << 4) |
//            ((p->tm_mday % 10) & 0x0F);
//    tmptime.Current_time_bcd_mon = (((p->tm_mon / 10 ) & 0x0F ) << 4) |
//            ((p->tm_mon % 10) & 0x0F);
//    tmptime.Current_time_bcd_year_h = (((p->tm_year / 100 ) & 0x0F ) << 4) |
//            ((p->tm_year % 100) & 0x0F);
//    tmptime.Current_time_bcd_year_l = (((p->tm_year / 10 ) & 0x0F ) << 4) |
//            ((p->tm_year % 10) & 0x0F);
    sprintf(tmptime,"%4d",p->tm_year+1900);
    sprintf(tmptime,"%s%02d",tmptime,p->tm_mon+1);
    sprintf(tmptime,"%s%02d",tmptime,p->tm_mday);
    sprintf(tmptime,"%s%02d",tmptime,p->tm_hour);
    sprintf(tmptime,"%s%02d",tmptime,p->tm_min);
    sprintf(tmptime,"%s%02d",tmptime,p->tm_sec);

    str2bcd(tmptime,thiz,7);

#if 0
    if(strlen(thiz)<256){
        LengthL2[0] = 0;
        LengthL2[1] = strlen(thiz);
    }else{
        LengthL2[0] = strlen(thiz)/256;
        LengthL2[1] = strlen(thiz)%256;
    }//长度为两个字节
#endif
    length_data(strlen(thiz),LengthL2);//长度为两个字节
    printf("time===%s LengthL2==%s\ngetcurrenttime end\n",tmptime,LengthL2);

    return strlen(thiz);
}

int getver(char *thiz,char *LengthL2)
{
    //操作序列号//软件版本号
    //memcpy(thiz,command_c_ver,sizeof(struct command_ver));
    length_data(strlen(thiz),LengthL2);//长度为两个字节
    printf("LengthL2==%s\ngetver end\n",LengthL2);
    return strlen(thiz);
}


int aes_128_cbc()
{

}

int DecodeBase64(const char *sSrc, char *sTarget)
{

    //计算末尾=号个数
    int iEqualNum = 0;
    int n =0;
    printf("len===%d\n", strlen(sSrc));
    for(n= strlen(sSrc) - 2; n>=0; --n)
    {
        if(sSrc[n] == '=')
        {
            iEqualNum++;
        }
        else
        {
            break;
        }
    }

    int iOutBufSize = strlen(sSrc)-1;
    char * pcOutBuf = (char*)malloc( iOutBufSize);
    if(NULL == pcOutBuf)
    {
        return -1;
    }

    int iRet = 0;
    int iTargetSize = 0;
    iTargetSize =  EVP_DecodeBlock((unsigned char*)pcOutBuf, (const unsigned char*)sSrc, iOutBufSize);
    printf("pcOutBuf===%s\n",pcOutBuf);
    printf("111iTargetSize==%d  iEqualNum==%d\n",iTargetSize,iEqualNum);
    if(iTargetSize > iEqualNum && iTargetSize < iOutBufSize)
    {
        printf("iTargetSize==%d  iEqualNum==%d\n",iTargetSize,iEqualNum);
        memcpy(sTarget,pcOutBuf, iTargetSize - iEqualNum);
        printf("target==%s  len===%d\n",sTarget,strlen(sTarget));
        iRet = iTargetSize - iEqualNum;
    }
    else
    {
        iRet = -1;
    }

    free(pcOutBuf);
    return iRet;
}

int EncodeBase64(const char * sSrc, char * sTarget)
{
    printf("len===%d\n",strlen(sSrc));
    uint32_t iBlockNum = strlen(sSrc) / 3;
    if (iBlockNum * 3 != strlen(sSrc))
    {
        iBlockNum++;
    }
    uint32_t iOutBufSize = iBlockNum * 4 + 1;

    char * pcOutBuf = (char*)malloc( iOutBufSize);
    if(NULL == pcOutBuf)
    {
        return -1;
    }
    int iReturn = 0;
    int ret = EVP_EncodeBlock((unsigned char*)pcOutBuf, (const unsigned char*)sSrc, strlen(sSrc));
    if (ret > 0 && ret < (int)iOutBufSize)
    {
        printf("ret==%d\n",ret);
        memcpy(sTarget,pcOutBuf,ret);
    }
    else
    {
        iReturn = -1;
    }

    free(pcOutBuf);
    return iReturn;
}

int AES_CBCEncrypt( const char * sSource, const uint32_t iSize,
        const char * sKey,  uint32_t iKeySize, char * poResult )
{
    if ( !sSource || !sKey || !poResult || iSize <= 0)
    {
        return -1;
    }

    //poResult->clear();

    int padding = kAesKeySize - iSize % kAesKeySize;

    char * tmp = (char*)malloc( iSize + padding );
    if(NULL == tmp)
    {
        return -1;
    }
    memcpy( tmp, sSource, iSize );
    memset( tmp + iSize, padding, padding );

    unsigned char * out = (unsigned char*)malloc( iSize + padding );
    if(NULL == out)
    {
        free(tmp);
        return -1;
    }

    unsigned char key[ kAesKeySize ] = { 0 };
    unsigned char iv[ kAesIVSize ] = { 0 };
    memcpy( key, sKey, iKeySize > kAesKeySize ? kAesKeySize : iKeySize );
    memcpy(iv, key, sizeof(iv) < sizeof(key) ? sizeof(iv) : sizeof(key));

    AES_KEY aesKey;
    AES_set_encrypt_key( key, 8 * kAesKeySize, &aesKey );
    AES_cbc_encrypt((unsigned char *)tmp, out,iSize + padding,  &aesKey, iv, AES_ENCRYPT);

    memcpy(poResult,out,iSize + padding);

    free(tmp);
    free(out);
    return 0;
}

int AES_CBCDecrypt( const char * sSource, const uint32_t iSize,
        const char * sKey, uint32_t iKeySize, char * poResult )
{
    if ( !sSource || !sKey || iSize < kAesKeySize || iSize % kAesKeySize != 0 || !poResult)
    {
        return -1;
    }

    //poResult->clear();

    unsigned char * out = (unsigned char*)malloc( iSize );
    if(NULL == out)
    {
        return -1;
    }

    unsigned char key[ kAesKeySize ] = { 0 };
    unsigned char iv[ kAesIVSize ] = {0} ;
    memcpy( key, sKey, iKeySize > kAesKeySize ? kAesKeySize : iKeySize );
    memcpy(iv, key, sizeof(iv) < sizeof(key) ? sizeof(iv) : sizeof(key));

    int iReturnValue = 0;
    AES_KEY aesKey;
    AES_set_decrypt_key( key, 8 * kAesKeySize, &aesKey );
    AES_cbc_encrypt( (unsigned char *)sSource, out, iSize, &aesKey, iv ,AES_DECRYPT);
    if( out[iSize-1] > 0 && out[iSize-1] <= kAesKeySize && (iSize - out[iSize-1]) > 0 )
    {
        //poResult->append( (char *)out , iSize - out[iSize-1] );
        memcpy(poResult,out,iSize - out[iSize-1] );
    } else {
        iReturnValue = -1;
    }

    free(out);
    return iReturnValue;
}


#if 1
void encryptmsg_test()
{
    aes_key_len = DecodeBase64(encoding_aes_key, &aes_key);
    //printf("aes_key==%s  len==%d\n",aes_key,strlen(aes_key));
    pt(&aes_key,32);
    AES_CBCEncrypt(sNeedEncrypt_info, strlen(sNeedEncrypt_info),aes_key,aes_key_len/*strlen(aes_key)*/, &sAesData);//aes_key_len != strlen(aes_key)
    //printf("sAesData==%s len==%d\n",sAesData,strlen(sAesData));
    pt(&sAesData,32);
    EncodeBase64(sAesData,sBase64Data);
    printf("sBase64Data==%s\n",sBase64Data);

    return strlen(sBase64Data);
}

void decryptmsg_test()
{
    DecodeBase64(sEncryptMsg,&sAesData);
    pt(&sAesData,32);

//    aes_key_len = DecodeBase64(key, &aes_key);
//    pt(&aes_key,32);

    aes_key_len = DecodeBase64(encoding_aes_key, &aes_key);
    pt(&aes_key,32);
    //aes_key_len = strlen(aes_key);
    AES_CBCDecrypt(sAesData, strlen(sAesData),aes_key,aes_key_len, &sNeedEncrypt_info);//aes_key_len != strlen(aes_key)
    printf("sNeedEncrypt_info==%s\n",sNeedEncrypt_info);

}
//#else
int encryptmsg(char *sNeedEncrypt_info,char *sBase64Data)
{
    char tmpbase64[200] =" ";
#if 1
    aes_key_len = DecodeBase64(encoding_aes_key, &aes_key);
    //printf("aes_key==%s  len==%d\n",aes_key,strlen(aes_key));
    pt(&aes_key,32);
    AES_CBCEncrypt(sNeedEncrypt_info, strlen(sNeedEncrypt_info),aes_key,aes_key_len/*strlen(aes_key)*/, &sAesData);//aes_key_len != strlen(aes_key)
    //printf("sAesData==%s len==%d\n",sAesData,strlen(sAesData));
#endif
    //AES_CBCEncrypt(sNeedEncrypt_info, strlen(sNeedEncrypt_info),sig_key,strlen(sig_key), &sAesData);//aes_key_len != strlen(aes_key)

    pt(&sAesData,32);
    EncodeBase64(sAesData,tmpbase64);
    memcpy(sBase64Data,tmpbase64,strlen(tmpbase64));
    printf("sBase64Data==%s\n",sBase64Data);

    return strlen(sBase64Data);
}

int decryptmsg(char *sEncryptMsg,char *sNeedEncrypt_info )
{
    printf("decryptmsg\n");
    char tmpEncrypt_info[200] =" ";
    DecodeBase64(sEncryptMsg,&sAesData);
    pt(&sAesData,32);
printf("decryptmsg11111111\n");
    aes_key_len = DecodeBase64(encoding_aes_key, &aes_key);
    pt(&aes_key,32);

    AES_CBCDecrypt(sAesData, strlen(sAesData),aes_key,aes_key_len, &tmpEncrypt_info);//aes_key_len != strlen(aes_key)
    memcpy(sNeedEncrypt_info,tmpEncrypt_info,strlen(tmpEncrypt_info));
    printf("tmpEncrypt_info==%s\n",tmpEncrypt_info);
    printf("sNeedEncrypt_info==%s\n",sNeedEncrypt_info);

    return strlen(sNeedEncrypt_info);
}

#endif



//=====设置参数 确认/否认========================================================================

int packet_echong_command_ack(struct command_osn * thiz)//确认帧
{
//打包操作序列号
    aes_128_cbc();//加密数据
}

int packet_echong_command_deny(struct command_osn * thiz)//否认帧
{
//打包操作序列号
    aes_128_cbc();//加密数据
}



//int packet_echong_command_c_thb(char *thiz,char *LengthL1,char  *LengthL2,char *LengthL3)//充电桩心跳指令数据
int packet_echong_command_c_thb(struct echong_pack *outRulerInfo)//充电桩心跳指令数据
{
//获取当前时间
    int tmpLenL1 = 0;
    int tmpLenL2 = 0;
    int tmpLenL3 = 0;

    tmpLenL2 = getcurrenttime(outRulerInfo->data_pack,outRulerInfo->LengthL2);//未加密数据长度
    //tmpLenL3 = aes_128_cbc();//加密数据长度
    //tmpLenL3 = encryptmsg(sNeedEncrypt_info,sBase64Data);
    tmpLenL3 = encryptmsg(outRulerInfo->data_pack,outRulerInfo->data_aes_pack);
    length_data(tmpLenL3,outRulerInfo->LengthL3);//长度为两个字节

    tmpLenL1 = tmpLenL3 + FRAME_LEN;//未补齐
    lengthL1_data(tmpLenL1,outRulerInfo->LengthL1);//长度为两个字节


    decryptmsg(sEncryptMsg,outRulerInfo->data_pack);
   // decryptmsg(outRulerInfo->data_aes_pack,outRulerInfo->data_pack);

    return tmpLenL3;
}//返回加密数据长度

int packet_echong_command_c_ver(struct echong_pack *outRulerInfo)//充电桩返回软件版本号
{
//打包版本号
    int tmpLenL1 = 0;
    int tmpLenL2 = 0;
    int tmpLenL3 = 0;

    tmpLenL2 = getver(outRulerInfo->data_pack,outRulerInfo->LengthL2);//未加密数据长度

    tmpLenL3 = encryptmsg(outRulerInfo->data_pack,outRulerInfo->data_aes_pack);//加密数据长度
    length_data(tmpLenL3,outRulerInfo->LengthL3);//长度为两个字节

    tmpLenL1 = tmpLenL3 + FRAME_LEN;//未补齐
    lengthL1_data(tmpLenL1,outRulerInfo->LengthL1);//长度为两个字节

    decryptmsg(sEncryptMsg,outRulerInfo->data_pack);
   // decryptmsg(outRulerInfo->data_aes_pack,outRulerInfo->data_pack);

    return tmpLenL3;

}//返回加密数据长度

int packet_echong_command_c_login(struct echong_pack *outRulerInfo)//充电桩发送登录指令
{
//获取当前时间
    int tmpLenL1 = 0;
    int tmpLenL2 = 0;
    int tmpLenL3 = 0;

    tmpLenL2 = getcurrenttime(outRulerInfo->data_pack,outRulerInfo->LengthL2);//未加密数据长度
    tmpLenL3 = encryptmsg(outRulerInfo->data_pack,outRulerInfo->data_aes_pack);//加密数据长度
    length_data(tmpLenL3,outRulerInfo->LengthL3);//长度为两个字节

    tmpLenL1 = tmpLenL3 + FRAME_LEN;//未补齐
    lengthL1_data(tmpLenL1,outRulerInfo->LengthL1);//长度为两个字节

    decryptmsg(sEncryptMsg,outRulerInfo->data_pack);
   // decryptmsg(outRulerInfo->data_aes_pack,outRulerInfo->data_pack);

    return tmpLenL3;
}

//=======================================================================================
//=============查询参数 ===================================================================

int packet_echong_command_c_clock_inf(struct echong_pack *outRulerInfo)//返回充电桩时钟及当前执行电价
{
//打包
    struct timeval timenow;

    gettimeofday(&timenow,NULL);
    sprintf(outRulerInfo->data_pack,"%s",command_c_clock_inf.Operation_sequence_num);//操作序列号
    //strcat(outRulerInfo->data_pack,timenow.tv_sec);
    printf("timenow==%s\n",timenow.tv_sec);//充电桩当前时间
    //getcurrenttime(command_c_clock_inf.command_c_changetime);//电价开始变更时间
    //strcat(outRulerInfo->data_pack,command_c_clock_inf.command_c_changetime);

    //尖费率   xx.xxxx元
    //峰费率
    //平费率
    //谷费率
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_clock_service(struct command_c_clock * thiz)//返回充电桩时钟及当前执行服务费
{
//打包
    //操作序列号
    //getcurrenttime(thiz->command_c_currenttime);//充电桩时间
    //getcurrenttime(thiz->command_c_changetime);//服务费率开始变更时间
    //尖费率   xxx.xx元
    //峰费率
    //平费率
    //谷费率
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_clock_price(struct command_c_clock * thiz)//查询充电桩时钟及最终执行电价
{
//打包
    //操作序列号
    //充电桩时间
    //getcurrenttime(thiz->command_c_changetime);//电价变更开始时间
    //尖费率   xxx.xxxx元
    //峰费率
    //平费率
    //谷费率
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_end_service(struct command_c_clock * thiz)//充电桩返回时钟及最终执行服务费价格
{
//打包
    //操作序列号
    //getcurrenttime(thiz->command_c_currenttime);//充电桩时间
    //getcurrenttime(thiz->command_c_changetime);//服务费率开始变更时间
    //尖费率   xxx.xx元
    //峰费率
    //平费率
    //谷费率
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_interval(struct command_set_interval * thiz)//充电桩返回上报时间间隔
{
//打包
    //操作序列号
    //状态上报间隔 Xx精确到秒
    //实时数据上报间隔
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_meterrate(struct command_set_meterpara * thiz)//充电桩返回电表倍率
{
//打包
    //操作序列号
    //电表倍率  xxxxxxxx
    aes_128_cbc();//加密数据
}

//==============数据状态 ==============================================================
//====================================================================================

int packet_echong_command_c_status_inf(struct command_c_status * thiz)//充电桩上报实时状态
{
//打包
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_s_t_inf(struct command_c_s_t * thiz)//充电桩启停操作(无卡)
{
//打包
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_upchargingdata_inf(struct command_c_upchargingdata * thiz)//充电桩上报实时充电数据(无卡)
{
//打包
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_uptransactiondata_inf(struct command_c_uptransactiondata * thiz)//充电桩上报交易记录(无卡／有卡)
{
//打包
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_update_inf(struct command_c_update * thiz)//平台发下发升级命令
{
//打包
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_updateprogress_inf(struct command_c_updateprogress * thiz)//充电桩升级进度应答
{
//打包
    aes_128_cbc();//加密数据
}

int packet_echong_command_c_infsync_inf(struct command_c_infsync * thiz)//设备信息同步指令
{
//打包
    aes_128_cbc();//加密数据
}

//====================================================================================================



int analysis_echong_command_p_thb(struct command_c_time * thiz)//平台发送心跳包到充电桩
{
    //解密数据
//解析当前时间
}

int analysis_echong_command_p_reboot()
{

}

int analysis_echong_command_c_ver(struct command_ver * thiz)//平台读取充电桩软件版本号
{
//解析操作序列号
}

int analysis_echong_frame()
{
    //验证正确性 1.起始字符  结束字符  2.桩编码    3.校验和
    //ID frame[18]
    //应用层数据加密后长度 L3  frame[23] frame[24]
    //应用数据加密前长度 L2  frame[21] frame[22]
    //加密数据  frame[25]------frame[25+ L3 -1]
    //解密数据
    //数据归类   get_echong_ruler_info();
}

void show_frame(int buflen, char* buf)
{

    int j = buflen;
    int i;
    printf("packet length :%d\n packet content : ",j);
    for(i = 0; i < j;i++)
    {
        printf("%02X ", (unsigned char)buf[i]);
    }
}



int split_receive_data()//拆分接收数据 https   POST
{
//拆分出报文
}

int conn_send_data()//连接发送数据 https   POST
{
//增加发送https + 报文
}

int get_echong_command_ID(char *receive_buffer)
{
    if(NULL == receive_buffer){
           return 0;
    }
    if(receive_buffer[0] == START && receive_buffer[0 + START_LEN] == HEAD_VER){
        return  receive_buffer[0 + START_LEN + HEAD_VER_LEN + PILE_CODE_LEN];
    }else{
        return 0;
    }

}

int get_echong_ruler_info(int CommandID, struct echong_pack *outRulerInfo)//根据CommandID获取当前数据
{

    switch (CommandID) {
    case COMMAND_ACK:

        break;
    case COMMAND_DENY:

        break;
    case COMMAND_C_THB://充电桩心跳请求
        //packet_echong_command_c_thb(outRulerInfo->data_pack,outRulerInfo->LengthL1,outRulerInfo->LengthL2,outRulerInfo->LengthL3);
        packet_echong_command_c_thb(outRulerInfo);

        break;
    case COMMAND_P_THB://平台发送心跳包到充电桩

        break;
    case COMMAND_P_VER://读取充电桩软件版本号 ver

        break;
    case COMMAND_C_VER://充电桩返回软件版本号
        //packet_echong_command_c_thb(command_c_ver);
        //memcpy(outRulerInfo->data_pack,command_c_ver,sizeof(struct command_ver));
        packet_echong_command_c_ver(outRulerInfo);

        break;
    case COMMAND_P_REBOOT: // 0x07,//平台下发重启充电桩
        break;
    case COMMAND_C_REBOOT: // 0x08,//充电桩返回重启电桩命令
        break;
    case COMMAND_C_LOGIN: // 0x09,//充电桩发送登录指令
        break;
    case COMMAND_P_LOGIN: // 0x10,//平台回复充电桩登录
        break;
    case COMMAND_P_ELEPRICE: // 0x11,//设置电费价格信息
        break;
    case COMMAND_P_SERVICE: // 0x12,//设置服务费价格信息
        break;
    case COMMAND_C_SETINTERVAL: // 0x13,//设置充电桩上报状态时间间隔
        break;
    case COMMAND_C_SETMETERRATE: // 0x14,//设置充电桩电表倍率
        break;
    case COMMAND_C_KEY: // 0x15,//设置充电桩加密密钥
        break;
    case  COMMAND_P_CLOCK: // 0x21,//查询充电桩时钟及当前执行电价
        break;
    case COMMAND_C_CLOCK: // 0x22,//返回充电桩时钟及当前执行电价
        break;
    case COMMAND_P_CLOCK_SERVICE: // 0x23,//查询充电桩时钟及当前执行服务费
        break;
    case COMMAND_C_CLOCK_SERVICE: // 0x24,//返回充电桩时钟及当前执行服务费
        break;
    case COMMAND_P_CLOCK_PRICE: // 0x25,//查询充电桩时钟及最终执行电价
        break;
    case COMMAND_C_CLOCK_PRICE: // 0x26,//返回充电桩时钟及最终执行电价
        break;
    case COMMAND_P_END_SERVICE: // 0x27,//查询充电桩时钟及最终执行服务费价格
        break;
    case COMMAND_C_END_SERVICE: // 0x28,//充电桩返回时钟及最终执行服务费价格
        break;
    case COMMAND_P_INTERVAL: // 0x29,//查询充电桩自动上报时间间隔
        break;
    case COMMAND_C_INTERVAL: // 0x30,//充电桩返回上报时间间隔
        break;
    case COMMAND_P_METERRATE: // 0x31,//查询充电桩电表倍率
        break;
    case COMMAND_C_METERRATE: // 0x32,//充电桩返回电表倍率
        break;
    case COMMAND_C_STATUS: // 0x41,//充电桩上报实时状态
        break;
    case COMMAND_P_STATUS: // 0x42,//查询充电桩实时状态
        break;
    case COMMAND_C_S_T: // 0x43,//充电桩启停操作(无卡)
        break;
    case COMMAND_P_S_T: // 0x44,//充电桩启停操作回调(无卡)  桩返回启停操作结果
        break;
    case COMMAND_C_UPCHARGINGDATA: // 0x45,//充电桩上报实时充电数据(无卡)
        break;
    case COMMAND_C_UPTRANSACTIONDATA: // 0x46,//充电桩上报交易记录(无卡／有卡)
        break;
    case COMMAND_P_DOWNTRANSACTIONDATA: // 0x47,//平台返回充电桩交易记录应答
        break;
    case COMMAND_P_NOCARD_TRANSACTIONDATA: // 0x48,//查询充电桩无卡交易记录
        break;
    case COMMAND_P_CARD_TRANSACTIONDATA: // 0x49,//查询用户卡消费记录(预留)
        break;
    case COMMAND_P_UPDATE: // 0x50,//平台发下发升级命令
        break;
    case COMMAND_P_UPDATEPROGRESS: // 0x51,//平台查询充电桩升级进度
        break;
    case COMMAND_C_UPDATEPROGRESS: // 0x52,//充电桩升级进度应答
        break;
    case COMMAND_C_INFSYNC: // 0x53,//设备信息同步指令
        break;
    case COMMAND_P_INFSYNC: // 0x54,//平台召唤信息同步
        break;
    default:
        break;
    }
}


int pack_echong_frame_by_data(struct echong_AES_pack *in_aes_data,struct echong_pack *in_data, char *outBuffer, int *outLength)
{
    printf("pack_echong_frame_by_data\n");
    int i;
    int len = 0; /* 计算包的总字节长 */
    unsigned char ucCheckSum = 0;
    char    pile_code[16]="1000000000000011";

    if(NULL == outBuffer || NULL == in_data ||  NULL == outLength)
    {
        printf("pack_echong_frame_by_data----exit\n");
        return 0;//E_D07_ERRO_NULL;
    }
    // 准备数据

    /* 开始封帧 */
    // 1 帧起始符
    outBuffer[len++] = START;

    // 2 帧头部版本号
    outBuffer[len++] = HEAD_VER;

    // 3 帧桩编码
    for(i = 0; i < 16; i++)
    {
        outBuffer[len++] = pile_code[i];
    }

    // 4 帧指令 ID
    outBuffer[len++] = in_data->Command_ID;

    // 5 帧总长度 L1
    for(i = 0; i < 2; i++)
    {
        outBuffer[len++] = in_data->LengthL1[i];
    }
    printf("in_data->LengthL1==%02x %02x\n",in_data->LengthL1[0],in_data->LengthL1[1]);

    // 6 帧应用数据加密前长度 L2
    for(i = 0; i < 2; i++)
    {
        outBuffer[len++] = in_data->LengthL2[i];
    }
    printf("in_data->LengthL2==%02x %02x\n",in_data->LengthL2[0],in_data->LengthL2[1]);


    // 7 帧应用层数据加 密后长度 L3    
    for(i = 0; i < 2; i++)
    {
        outBuffer[len++] = in_data->LengthL3[i];
    }
    printf("in_data->LengthL3==%02x %02x\n",in_data->LengthL3[0],in_data->LengthL3[1]);

    // 8 帧应用层数据 (AES128加密)
//    memcpy(outBuffer+len,in_data->data_pack,strlen(in_data->data_pack));
//    len+=strlen(in_data->data_pack);

#if 0
    for(i = 0; i < strlen(in_data->data_pack); i++)
    {
       outBuffer[len++] = in_data->data_pack[i];
    }
#else
    for(i = 0; i < strlen(in_data->data_aes_pack); i++)
    {
       outBuffer[len++] = in_data->data_aes_pack[i];
    }
#endif

    // 9 帧计数检验和
    for(i = 0; i < COMMAND_LEN + LEN123_LEN/*7*/; i++)
    {
        ucCheckSum += outBuffer[i + START_LEN + HEAD_VER_LEN + PILE_CODE_LEN/*18*/];
    }

    printf("ucCheckSum==%02X\n",ucCheckSum);
    // 9 帧检验和
    outBuffer[len++] = 0x00;
    outBuffer[len++] = ucCheckSum;

    // 10 结束符
    outBuffer[len++] = END;

    /* 输出参数 */
    *outLength = len;

    printf("pack_echong_frame_by_data----end  len==%d\n",len);
    return 1;//E_OK;
}

int unpack_echong_frame_by_data(char *inBuffer, int inLength,struct echong_pack *outPara)
{
    //get_echong_ruler_info();
}



static int s_exit_flag = 0;
static int s_show_headers = 1;
static const char *s_show_headers_opt = "--show-headers";

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  struct echong_pack  frame_data = {0};
  struct echong_AES_pack  frame_aes_data = {0};
  char outbuffer[256] = {0};
  int length = 0;

  printf("111ev==%d\n",ev);
  switch (ev) {
    case MG_EV_CONNECT:
      if (*(int *) ev_data != 0) {
        fprintf(stderr, "connect() failed: %s\n", strerror(*(int *) ev_data));
        s_exit_flag = 1;
      }
      break;
    case MG_EV_RECV:
      fwrite(nc->recv_mbuf.buf,1,nc->recv_mbuf.len,stdout);
      mbuf_remove(&nc->recv_mbuf,nc->recv_mbuf.len);
      putchar('\n');

      mbuf_append(&nc->send_mbuf, "buftest", 7);
      fwrite(nc->send_mbuf.buf,1,nc->send_mbuf.len,stdout);
      putchar('\n');

      //frame_data.Command_ID = get_echong_command_ID(nc->send_mbuf.buf);
      frame_data.Command_ID = 0x03;

      get_echong_ruler_info(frame_data.Command_ID,&frame_data);
      pack_echong_frame_by_data(&frame_aes_data,&frame_data,outbuffer,&length);
      show_frame(length,outbuffer);


      break;
    case MG_EV_SEND:
        printf("111111111111111111111111nc->send_mbuf.buf==%s\n",nc->send_mbuf.buf);
        break;
    case MG_EV_HTTP_REPLY:
      nc->flags |= MG_F_CLOSE_IMMEDIATELY;
      if (s_show_headers) {
        fwrite(hm->message.p, 1, hm->message.len, stdout);
      } else {
        fwrite(hm->body.p, 1, hm->body.len, stdout);
      }
      putchar('\n');
      s_exit_flag = 1;
      break;
    default:
      break;
  }
}

void mongoose_data()
{
    struct mg_mgr mgr;
      int i;

      mg_mgr_init(&mgr, NULL);

      /* Process command line arguments */
   do{
        //mg_connect_http(&mgr, ev_handler, "http://192.168.122.204:8080", "Content-Type: application/x-www-form-urlencoded\r\n", "appid=111111111&info=aaaa&sig=P8B2OK/f/HK6WIcb3cSpsP7kfO8=");
        mg_connect_http(&mgr, ev_handler, "http://123.56.113.123:8002/register", "Content-Type: application/x-www-form-urlencoded\r\n", "mac=04a316e03aee&type=normal&timestamp=1410349438&sig=c6+9h2687GbXIaEWgEtrCus7W2c=");

          //mg_connect_http(&mgr, ev_handler, "http://123.56.113.123:8002/register", "Content-Type: application/x-www-form-urlencoded\r\n", "mac=20112233ef00&type=normal&timestamp=1410349438&sig=QAUheeaw0UCYYpsFYzCAfjSyZEY=");

    }while(0);

      while (s_exit_flag == 0) {
        mg_mgr_poll(&mgr, 1000);
      }
      mg_mgr_free(&mgr);

}


void http_post_data()
{
    char *p;
    char  data[100] = " ";
#if 1
    printf("http_post_data\n");

    sprintf(data,"mac=%s",MAC);//mac
    sprintf(data,"%s&timestamp=%d",data,TIMESTAMP);//timestamp
    sprintf(data,"%s&type=%s",data,TYPE);//type

    //EncodingAESKey

    p = pt(HMAC(  EVP_sha1(),
           /*key data*/ sig_key,
           /*key len*/  EncodingAESKey_LEN - 1,
           /*data  */data,
           /*data len*/strlen(data),
           /*digest*/sig,
           &sig_len),SHA_DIGEST_LENGTH);//sig  HMAC openssl

  printf("HMAC\n");
  EVP_EncodeBlock(base64_sig,sig,sig_len);
  printf("base64_sig==%s\n",base64_sig);
#else
    printf("http_post_data\n");
    //appid
    sprintf(data,"app_id=%s",APP_ID);
    sprintf(data,"%s&info=%s",data,INFO);
    //info  EncodingAESKey
    //sig  HMAC openssl
    //appid&info

    p = pt(HMAC(  EVP_sha1(),
           /*key data*/ token,
           /*key len*/  TOKEN_LEN,
           /*data  */data,
           /*data len*/strlen(data),
           /*digest*/sig,
           &sig_len),SHA_DIGEST_LENGTH);
  printf("HMAC\n");
  EVP_EncodeBlock(base64_sig,sig,sig_len);
  printf("base64_sig==%s\n",base64_sig);
#endif

  //encryptmsg();
  encryptmsg_test();
  decryptmsg_test();
}

char * http_get(const char *url);
char * http_post1(const char *url,const char * post_str);

void *thread_echong_send_service(void *arg) ___THREAD_ENTRY___
{
//    int *done = (int *)arg;
//    int mydone = 0;
//    int s;
//    while ( ! *done ) {

//    }
//    return NULL;

    int sockfd, ret, i, h;
    struct sockaddr_in servaddr;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;

    const char url[200];
    const char post_str[200];
    strcpy(url, "http://192.168.122.204");
    strcpy(post_str,"22222222222222");


    //encryptmsg_test();
     //decryptmsg_test();
   // http_post_data();
    //mongoose_data();
    //http_post(url,post_str);

#if 0
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
            printf("创建网络连接失败,本线程即将终止---socket error!\n");
            exit(0);
    };

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 ){
            printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
            exit(0);
    };

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
            printf("连接到服务器失败,connect error!\n");
            exit(0);
    }
    printf("与远端建立了连接\n");

    //发送数据
    memset(str2, 0, 4096);
    strcat(str2, "app_id=1111111111&");
    strcat(str2, "info=1111111111&");
    strcat(str2, "sig=1111111111");
    str=(char *)malloc(128);
    len = strlen(str2);
    sprintf(str, "%d", len);

    memset(str1, 0, 4096);
    strcat(str1, "POST /mytest.html HTTP/1.1\n");
    strcat(str1, "Host: 192.168.122.*\n");
    strcat(str1, "Content-Type: application/x-www-form-urlencoded\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");

    //strcat(str1, str2);
    strcat(str1, "\r\n\r\n");
    printf("%s\n",str1);

    ret = write(sockfd,str1,strlen(str1));
    if (ret < 0) {
            printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
            exit(0);
    }else{
            printf("消息发送成功，共发送了%d个字节！\n\n", ret);
    }

    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);

    while(1){
            //sleep(2);
            tv.tv_sec= 0;
            tv.tv_usec= 0;
            h= 0;
            //printf("--------------->1");
            h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
            //printf("--------------->2");

            //if (h == 0) continue;
            if (h < 0) {
                    close(sockfd);
                    printf("在读取数据报文时SELECT检测到异常，该异常导致线程终止！\n");
                    return -1;
            };

            /*if (h > 0)*/{
                printf("h > 0 ");
                //if(FD_ISSET(sockfd, &t_set1))
                    memset(buf, 0, 1024);
                    i= read(sockfd, buf, 1023);
                    if (i==0){
                            close(sockfd);
                            printf("读取数据报文时发现远端关闭，该线程终止！\n");
                            return -1;
                    }

                    printf("%s\n", buf);
            }
    }
    close(sockfd);
#endif

    return 0;
}

#define MY_HTTP_DEFAULT_PORT 8080

//char * http_get(const char *url);
//char * http_post(const char *url,const char * post_str);

#define BUFFER_SIZE 1024
#define HTTP_POST "POST /%s HTTP/1.1\r\nHOST: %s:%d\r\nAccept: */*\r\n"\
    "Content-Type:application/x-www-form-urlencoded\r\nContent-Length: %d\r\n\r\n%s"
#define HTTP_GET "GET /%s HTTP/1.1\r\nHOST: %s:%d\r\nAccept: */*\r\n\r\n"

static int http_tcpclient_create(const char *host, int port){
    //struct hostent *he;
    struct sockaddr_in server_addr;
    int socket_fd;

//    if((he = gethostbyname(host))==NULL){
//        return -1;
//    }

//   server_addr.sin_family = AF_INET;
//   server_addr.sin_port = htons(port);
//   server_addr.sin_addr = *((struct in_addr *)he->h_addr);

//    if((socket_fd = socket(AF_INET,SOCK_STREAM,0))==-1){
//        return -1;
//    }

//    if(connect(socket_fd, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
//        return -1;
//    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
            printf("创建网络连接失败,本线程即将终止---socket error!\n");
            exit(0);
    };

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPSTR, &server_addr.sin_addr) <= 0 ){
            printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
            exit(0);
    };

    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
            printf("连接到服务器失败,connect error!\n");
            exit(0);
    }
    printf("与远端建立了连接\n");


    return socket_fd;
}

static void http_tcpclient_close(int socket){
    close(socket);
}

static int http_parse_url(const char *url,char *host,char *file,int *port)
{
    char *ptr1,*ptr2;
    int len = 0;
    if(!url || !host || !file || !port){
        return -1;
    }

    ptr1 = (char *)url;

    if(!strncmp(ptr1,"http://",strlen("http://"))){
        ptr1 += strlen("http://");
    }else{
        return -1;
    }

    ptr2 = strchr(ptr1,'/');
    if(ptr2){
        len = strlen(ptr1) - strlen(ptr2);
        memcpy(host,ptr1,len);
        host[len] = '\0';
        if(*(ptr2 + 1)){
            memcpy(file,ptr2 + 1,strlen(ptr2) - 1 );
            file[strlen(ptr2) - 1] = '\0';
        }
    }else{
        memcpy(host,ptr1,strlen(ptr1));
        host[strlen(ptr1)] = '\0';
    }
    //get host and ip
    ptr1 = strchr(host,':');
    if(ptr1){
        *ptr1++ = '\0';
        *port = atoi(ptr1);
    }else{
        *port = MY_HTTP_DEFAULT_PORT;
    }

    return 0;
}


static int http_tcpclient_recv(int socket,char *lpbuff){
    int recvnum = 0;

    recvnum = recv(socket, lpbuff,BUFFER_SIZE*4,0);
    printf("lpbuff==%s\n",lpbuff);
    return recvnum;
}

static int http_tcpclient_send(int socket,char *buff,int size){
    int sent=0,tmpres=0;

    while(sent < size){
        tmpres = send(socket,buff+sent,size-sent,0);
        if(tmpres == -1){
            return -1;
        }
        sent += tmpres;
    }
    return sent;
}

static char *http_parse_result(const char*lpbuf)
{
    char *ptmp = NULL;
    char *response = NULL;
    ptmp = (char*)strstr(lpbuf,"HTTP/1.1");
    if(!ptmp){
        printf("http/1.1 not find\n");
        return NULL;
    }
    if(atoi(ptmp + 9)!=200){
        printf("result:\n%s\n",lpbuf);
        return NULL;
    }

    ptmp = (char*)strstr(lpbuf,"\r\n\r\n");
    if(!ptmp){
        printf("ptmp is NULL\n");
        return NULL;
    }
    response = (char *)malloc(strlen(ptmp)+1);
    if(!response){
        printf("malloc failed \n");
        return NULL;
    }
    strcpy(response,ptmp+4);
    return response;
}

char * http_post1(const char *url,const char *post_str){

    char post[BUFFER_SIZE] = {'\0'};

    int socket_fd = -1;
    char lpbuf[BUFFER_SIZE*4] = {'\0'};
    char *ptmp;
    char host_addr[BUFFER_SIZE] = "192.168.122.38";
    char file[BUFFER_SIZE] = {'\0'};
    int port = 8080;
    int len=0;
    char *response = NULL;



    if(!url || !post_str){
        printf("      failed!\n");
        return NULL;
    }


    if(http_parse_url(url,host_addr,file,&port)){
        printf("http_parse_url failed!\n");
        return NULL;
    }
    printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);

    socket_fd = http_tcpclient_create(host_addr,port);
    if(socket_fd < 0){
        printf("http_tcpclient_create failed\n");
        return NULL;
    }

    sprintf(lpbuf,HTTP_POST,file,host_addr,port,strlen(post_str),post_str);

    if(http_tcpclient_send(socket_fd,lpbuf,strlen(lpbuf)) < 0){
        printf("http_tcpclient_send failed..\n");
        return NULL;
    }
    printf("发送请求:\n%s\n",lpbuf);

    /*it's time to recv from server*/
    if(http_tcpclient_recv(socket_fd,lpbuf) <= 0){
        printf("http_tcpclient_recv failed\n");
        return NULL;
    }

    http_tcpclient_close(socket_fd);

    return http_parse_result(lpbuf);
}

char * http_get(const char *url)
{

    char post[BUFFER_SIZE] = {'\0'};
    int socket_fd = -1;
    char lpbuf[BUFFER_SIZE*4] = {'\0'};
    char *ptmp;
    char host_addr[BUFFER_SIZE] = {'\0'};
    char file[BUFFER_SIZE] = {'\0'};
    int port = 0;
    int len=0;

    if(!url){
        printf("      failed!\n");
        return NULL;
    }

    if(http_parse_url(url,host_addr,file,&port)){
        printf("http_parse_url failed!\n");
        return NULL;
    }
    //printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);

    socket_fd =  http_tcpclient_create(host_addr,port);
    if(socket_fd < 0){
        printf("http_tcpclient_create failed\n");
        return NULL;
    }

    sprintf(lpbuf,HTTP_GET,file,host_addr,port);

    if(http_tcpclient_send(socket_fd,lpbuf,strlen(lpbuf)) < 0){
        printf("http_tcpclient_send failed..\n");
        return NULL;
    }
//  printf("发送请求:\n%s\n",lpbuf);

    if(http_tcpclient_recv(socket_fd,lpbuf) <= 0){
        printf("http_tcpclient_recv failed\n");
        return NULL;
    }
    http_tcpclient_close(socket_fd);

    return http_parse_result(lpbuf);
}



