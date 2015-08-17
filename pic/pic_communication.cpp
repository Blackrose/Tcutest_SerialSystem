/*
* PIC Communication Protocol.
* 
*
* File:     pic_communication.cpp
* Author:   MHW
* Create:   2015-03-04
*/

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include "pic_communication.h"

const unsigned char PicProtocol::crc_table[] = {
	0x00,0x00,0x10,0x21,0x20,0x42,0x30,0x63,0x40,0x84,0x50,0xA5,0x60,0xC6,0x70,0xE7,
	0x81,0x08,0x91,0x29,0xA1,0x4A,0xB1,0x6B,0xC1,0x8C,0xD1,0xAD,0xE1,0xCE,0xF1,0xEF,
	0x12,0x31,0x02,0x10,0x32,0x73,0x22,0x52,0x52,0xB5,0x42,0x94,0x72,0xF7,0x62,0xD6,
	0x93,0x39,0x83,0x18,0xB3,0x7B,0xA3,0x5A,0xD3,0xBD,0xC3,0x9C,0xF3,0xFF,0xE3,0xDE,
	0x24,0x62,0x34,0x43,0x04,0x20,0x14,0x01,0x64,0xE6,0x74,0xC7,0x44,0xA4,0x54,0x85,
	0xA5,0x6A,0xB5,0x4B,0x85,0x28,0x95,0x09,0xE5,0xEE,0xF5,0xCF,0xC5,0xAC,0xD5,0x8D,
	0x36,0x53,0x26,0x72,0x16,0x11,0x06,0x30,0x76,0xD7,0x66,0xF6,0x56,0x95,0x46,0xB4,
	0xB7,0x5B,0xA7,0x7A,0x97,0x19,0x87,0x38,0xF7,0xDF,0xE7,0xFE,0xD7,0x9D,0xC7,0xBC,
	0x48,0xC4,0x58,0xE5,0x68,0x86,0x78,0xA7,0x08,0x40,0x18,0x61,0x28,0x02,0x38,0x23,
	0xC9,0xCC,0xD9,0xED,0xE9,0x8E,0xF9,0xAF,0x89,0x48,0x99,0x69,0xA9,0x0A,0xB9,0x2B,
	0x5A,0xF5,0x4A,0xD4,0x7A,0xB7,0x6A,0x96,0x1A,0x71,0x0A,0x50,0x3A,0x33,0x2A,0x12,
	0xDB,0xFD,0xCB,0xDC,0xFB,0xBF,0xEB,0x9E,0x9B,0x79,0x8B,0x58,0xBB,0x3B,0xAB,0x1A,
	0x6C,0xA6,0x7C,0x87,0x4C,0xE4,0x5C,0xC5,0x2C,0x22,0x3C,0x03,0x0C,0x60,0x1C,0x41,
	0xED,0xAE,0xFD,0x8F,0xCD,0xEC,0xDD,0xCD,0xAD,0x2A,0xBD,0x0B,0x8D,0x68,0x9D,0x49,
	0x7E,0x97,0x6E,0xB6,0x5E,0xD5,0x4E,0xF4,0x3E,0x13,0x2E,0x32,0x1E,0x51,0x0E,0x70,
	0xFF,0x9F,0xEF,0xBE,0xDF,0xDD,0xCF,0xFC,0xBF,0x1B,0xAF,0x3A,0x9F,0x59,0x8F,0x78,

	0x91,0x88,0x81,0xA9,0xB1,0xCA,0xA1,0xEB,0xD1,0x0C,0xC1,0x2D,0xF1,0x4E,0xE1,0x6F,
	0x10,0x80,0x00,0xA1,0x30,0xC2,0x20,0xE3,0x50,0x04,0x40,0x25,0x70,0x46,0x60,0x67,
	0x83,0xB9,0x93,0x98,0xA3,0xFB,0xB3,0xDA,0xC3,0x3D,0xD3,0x1C,0xE3,0x7F,0xF3,0x5E,
	0x02,0xB1,0x12,0x90,0x22,0xF3,0x32,0xD2,0x42,0x35,0x52,0x14,0x62,0x77,0x72,0x56,
	0xB5,0xEA,0xA5,0xCB,0x95,0xA8,0x85,0x89,0xF5,0x6E,0xE5,0x4F,0xD5,0x2C,0xC5,0x0D,
	0x34,0xE2,0x24,0xC3,0x14,0xA0,0x04,0x81,0x74,0x66,0x64,0x47,0x54,0x24,0x44,0x05,
	0xA7,0xDB,0xB7,0xFA,0x87,0x99,0x97,0xB8,0xE7,0x5F,0xF7,0x7E,0xC7,0x1D,0xD7,0x3C,
	0x26,0xD3,0x36,0xF2,0x06,0x91,0x16,0xB0,0x66,0x57,0x76,0x76,0x46,0x15,0x56,0x34,
	0xD9,0x4C,0xC9,0x6D,0xF9,0x0E,0xE9,0x2F,0x99,0xC8,0x89,0xE9,0xB9,0x8A,0xA9,0xAB,
	0x58,0x44,0x48,0x65,0x78,0x06,0x68,0x27,0x18,0xC0,0x08,0xE1,0x38,0x82,0x28,0xA3,
	0xCB,0x7D,0xDB,0x5C,0xEB,0x3F,0xFB,0x1E,0x8B,0xF9,0x9B,0xD8,0xAB,0xBB,0xBB,0x9A,
	0x4A,0x75,0x5A,0x54,0x6A,0x37,0x7A,0x16,0x0A,0xF1,0x1A,0xD0,0x2A,0xB3,0x3A,0x92,
	0xFD,0x2E,0xED,0x0F,0xDD,0x6C,0xCD,0x4D,0xBD,0xAA,0xAD,0x8B,0x9D,0xE8,0x8D,0xC9,
	0x7C,0x26,0x6C,0x07,0x5C,0x64,0x4C,0x45,0x3C,0xA2,0x2C,0x83,0x1C,0xE0,0x0C,0xC1,
	0xEF,0x1F,0xFF,0x3E,0xCF,0x5D,0xDF,0x7C,0xAF,0x9B,0xBF,0xBA,0x8F,0xD9,0x9F,0xF8,
	0x6E,0x17,0x7E,0x36,0x4E,0x55,0x5E,0x74,0x2E,0x93,0x3E,0xB2,0x0E,0xD1,0x1E,0xF0
};

unsigned short PicProtocol::silence_time = 0;
long PicProtocol::timer_sec_start = 0;
long PicProtocol::timer_nsec_start = 0;
long PicProtocol::timer_remain_nsec = 0;
struct retry_data PicProtocol::sent_temp;
struct pic_master_port PicProtocol::pic_port;

void PicProtocol::timer_init(void)
{
	/*
    struct timespec  
    {  
        time_t tv_sec; // seconds
        long tv_nsec;  // nanoseconds 
    };  

	*/
	struct timespec ts;
	::clock_gettime(CLOCK_MONOTONIC, &ts);
	timer_sec_start   = ts.tv_sec;
	timer_nsec_start  = ts.tv_nsec;
	timer_remain_nsec = 0;
	silence_time = 0;
}
unsigned short PicProtocol::timer_silence(void)
{

	long timer_sec_end;
	long timer_nsec_end;
	long timer_msec;
	long temp;
	struct timespec ts;
	
	::clock_gettime(CLOCK_MONOTONIC, &ts);
	timer_sec_end  = ts.tv_sec;
	timer_nsec_end = ts.tv_nsec;
	if (timer_nsec_end >= timer_nsec_start) {
		timer_msec = (timer_sec_end - timer_sec_start) * MSEC_PER_SEC + 
			(timer_nsec_end - timer_nsec_start + timer_remain_nsec) / NSEC_PER_MSEC;
		timer_remain_nsec = (timer_nsec_end - timer_nsec_start + timer_remain_nsec) % NSEC_PER_MSEC;
	} else {
		timer_msec = (timer_sec_end - timer_sec_start - 1) * MSEC_PER_SEC + 
			(timer_nsec_end + NSEC_PER_SEC - timer_nsec_start + timer_remain_nsec) / NSEC_PER_MSEC;
		timer_remain_nsec = (timer_nsec_end + NSEC_PER_SEC - timer_nsec_start + timer_remain_nsec)
			% NSEC_PER_MSEC;
	}
	temp = silence_time + timer_msec;
	if (temp >= 0xFFFF)
		silence_time = 0xFFFF;
	else
		silence_time = (uint16_t)temp;
		
//	timer_sec_start  = timer_sec_end;
//	timer_nsec_start = timer_nsec_end;
    printf("silence_time==%d\n",silence_time);
  return silence_time;
}

void PicProtocol::timer_silence_reset(void)
{
	struct timespec ts;
	::clock_gettime(CLOCK_MONOTONIC, &ts);
	timer_sec_start   = ts.tv_sec;
	timer_nsec_start  = ts.tv_nsec;
	timer_remain_nsec = 0;
	silence_time = 0;
}

	
void PicProtocol::time_exchange(struct pic_time_t *time, QString str_time)
{
	time->year = str_time.left(4).toInt();
	time->month = str_time.mid(5, 2).toInt();
	time->day = str_time.mid(8, 2).toInt();
	time->hour = str_time.mid(11, 2).toInt();
	time->minute = str_time.mid(14, 2).toInt();
	time->seconds = str_time.right(2).toInt();
}
//温度报警
void PicProtocol::pic_t_alarm(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
	pic_data_t data;
	
	data.cmd_type = FIR_CMD;
	data.net_addr = net;
	data.device_addr = device;
	data.channel_addr = channel;
	data.alarm_type = TEMPERATURE_ALARM;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//漏电报警
void PicProtocol::pic_c_alarm(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
	pic_data_t data;
	
	data.cmd_type = FIR_CMD;
	data.net_addr = net;
	data.device_addr = device;
	data.channel_addr = channel;
	data.alarm_type = LEAKAGE_ALARM;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//温度故障
void PicProtocol::pic_t_error(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
    pic_data_t data;

    data.cmd_type = FAU_CMD;
    data.net_addr = net;
    data.device_addr = device;
    data.channel_addr = channel;
    data.alarm_type = TEMPERATURE_FAULT;
    time_exchange(&data.pic_time, time);
    pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//漏电故障
void PicProtocol::pic_c_error(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
    pic_data_t data;

    data.cmd_type = FAU_CMD;
    data.net_addr = net;
    data.device_addr = device;
    data.channel_addr = channel;
    data.alarm_type = LEAKAGE_FAULT;
    time_exchange(&data.pic_time, time);
    pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//温度故障恢复
void PicProtocol::pic_t_restore(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
    pic_data_t data;

    data.cmd_type = FAR_CMD;
    data.net_addr = net;
    data.device_addr = device;
    data.channel_addr = channel;
    data.alarm_type = TEMPERATURE_FAULT;
    time_exchange(&data.pic_time, time);
    pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//漏电故障恢复
void PicProtocol::pic_c_restore(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
    pic_data_t data;

    data.cmd_type = FAR_CMD;
    data.net_addr = net;
    data.device_addr = device;
    data.channel_addr = channel;
    data.alarm_type = LEAKAGE_FAULT;
    time_exchange(&data.pic_time, time);
    pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//通道故障
void PicProtocol::pic_channel_error(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
	pic_data_t data;
	
	data.cmd_type = FAU_CMD;
	data.net_addr = net;
	data.device_addr = device;
	data.channel_addr = channel;
	data.alarm_type = CHANNEL_FAULT;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//通讯故障
void PicProtocol::pic_communication_error(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
	pic_data_t data;
	
	data.cmd_type = FAU_CMD;
	data.net_addr = net;
	data.device_addr = device;
	data.channel_addr = channel;
	data.alarm_type = COMMUNICATION_FAULT;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//故障恢复
void PicProtocol::pic_channel_restore(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
	pic_data_t data;
	
	data.cmd_type = FAR_CMD;
	data.net_addr = net;
	data.device_addr = device;
	data.channel_addr = channel;
	data.alarm_type = CHANNEL_FAULT;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//故障恢复
void PicProtocol::pic_communication_restore(unsigned char net, unsigned char device, unsigned char channel, QString time)
{
	pic_data_t data;
	
	data.cmd_type = FAR_CMD;
	data.net_addr = net;
	data.device_addr = device;
	data.channel_addr = channel;
	data.alarm_type = COMMUNICATION_FAULT;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//询问
void PicProtocol::pic_heart_beat(void)
{
	static unsigned char num = 0;
	pic_data_t data;
	
	num++;
	data.cmd_type = INQ_CMD;
	data.heart_beat = num;
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
	if (num == 255)
		num = 0;
}
//主电故障
void PicProtocol::pic_main_error(QString time)
{
	pic_data_t data;
	
	data.cmd_type = ACF_CMD;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//主电恢复
void PicProtocol::pic_main_restore(QString time)
{
	pic_data_t data;
	
	data.cmd_type = ACN_CMD;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//备电故障
void PicProtocol::pic_premain_error(QString time)
{
	pic_data_t data;
	
	data.cmd_type = BTF_CMD;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}
//备电恢复
void PicProtocol::pic_premain_restore(QString time)
{
	pic_data_t data;
	
	data.cmd_type = BTN_CMD;
	time_exchange(&data.pic_time, time);
	pic_port.wr_tx_buf_fun(data, &pic_port.pic_sent_buf);
}


int PicProtocol::pic_crc_check(char *ascii_char, int num, char *ascii_crch, char *ascii_crcl)
{
	unsigned char crc_h, crc_l, carry, worka, work5, work6;
	unsigned int value, i, tbdptr = 0;
	crc_h = 0xff;
	crc_l = 0xff;
	carry = 0x00; //0 or 0x80
	value = -1;
    if(ascii_char[1]!='I'){
    printf("1111ascii_char==%s  num==%d\n",ascii_char,num);}
    for (i = 0; i < num; i++) {//printf("ascii_char[%d]==%c\n",i,ascii_char[i]);
		crc_h = ascii_char[i] ^ crc_h;
		carry = crc_h & 0x80;
		crc_h = crc_h << 1;
		worka = crc_h;

		if (carry == 0x80) {
			tbdptr = 0x100;
		} else {
			tbdptr = 0x00;
		}
		
		work5 = crc_table[worka + tbdptr];

		worka = crc_h;
		worka++;
		work6 = crc_table[worka + tbdptr];

		crc_h = work5 ^ crc_l;
		crc_l = work6;
	}
	
	crc_h = ~crc_h;
	crc_l = ~crc_l;


	sprintf(ascii_crch, "%3d", crc_h);
	ascii_char[num] = ascii_crch[0];
	ascii_char[num + 1] = ascii_crch[1];
	ascii_char[num + 2] = ascii_crch[2];
	sprintf(ascii_crcl, "%3d", crc_l);
	ascii_char[num + 3] = ascii_crcl[0];
	ascii_char[num + 4] = ascii_crcl[1];
	ascii_char[num + 5] = ascii_crcl[2];

	ascii_char[num + 6] = '#';
	i = 0;	
	while (ascii_char[i] != '#') {	
		if (ascii_char[i] == 0x20) 
			ascii_char[i] = 0x30;
		i++;
	}
	value = num + 7;
    printf("crc_h==%x  %3d\n",crc_h,crc_h);printf("crc_l==%x  %3d\n",crc_l,crc_l);
//    printf("ascii_char[%d]==%c\n",num,ascii_char[num]);
//    printf("ascii_char[%d]==%c\n",num + 1,ascii_char[num + 1]);
//    printf("ascii_char[%d]==%c\n",num + 2,ascii_char[num + 2]);
//    printf("ascii_char[%d]==%c\n",num + 3,ascii_char[num + 3]);
//    printf("ascii_char[%d]==%c\n",num + 4,ascii_char[num + 4]);
//    printf("ascii_char[%d]==%c\n",num + 5,ascii_char[num + 5]);
	return value;
}

int PicProtocol::change_time_to_ascii(char *ascii, struct pic_time_t  time)
{	
	int index = 0;
	char temp_str[5];
	
	sprintf(temp_str, "%4d", time.year);
    //ascii[index++] = temp_str[0];
    //ascii[index++] = temp_str[1];
	ascii[index++] = temp_str[2];
	ascii[index++] = temp_str[3];
	
	sprintf(temp_str, "%2d", time.month);
	ascii[index++] = temp_str[0];
	ascii[index++] = temp_str[1];
	
	sprintf(temp_str, "%2d", time.day);
	ascii[index++] = temp_str[0];
	ascii[index++] = temp_str[1];
	
	sprintf(temp_str, "%2d", time.hour);
	ascii[index++] = temp_str[0];
	ascii[index++] = temp_str[1];
	
	sprintf(temp_str, "%2d", time.minute);
	ascii[index++] = temp_str[0];
	ascii[index++] = temp_str[1];
	
	sprintf(temp_str, "%2d", time.seconds);
	ascii[index++] = temp_str[0];
	ascii[index++] = temp_str[1];
	
	return index;
}

int PicProtocol::sent_data_to_ascii(char *ascii, pic_data_t data)
{ 
	int value = -1;
	int index = 0;
	int temp;
	char temp_str[4]; 
	
	ascii[index++] = '@';
	
	switch (data.cmd_type) {
		case NONE_CMD:
			break;
		case FIR_CMD:
			ascii[index++] = 'F';
			ascii[index++] = 'I';
			ascii[index++] = 'R';
			
			sprintf(temp_str, "%3d", data.net_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			sprintf(temp_str, "%3d", data.device_addr);
			ascii[index++] = temp_str[0];
            ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			sprintf(temp_str, "%3d", data.channel_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			if ((data.alarm_type > MIN_ALARM) && (data.alarm_type < MAX_ALARM)) {
				ascii[index++] = data.alarm_type;
			} else {
				value = -2;
				return value;
			}
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case FAU_CMD:
			ascii[index++] = 'F';
			ascii[index++] = 'A';
			ascii[index++] = 'U';
			
			sprintf(temp_str, "%3d", data.net_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			sprintf(temp_str, "%3d", data.device_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			sprintf(temp_str, "%3d", data.channel_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
            if ((data.alarm_type == LEAKAGE_FAULT) || (data.alarm_type == TEMPERATURE_FAULT) || (data.alarm_type == CHANNEL_FAULT)) {
				ascii[index++] = data.alarm_type;
			} else {
				value = -2;
				return value;
			}          
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case FAR_CMD:
			ascii[index++] = 'F';
			ascii[index++] = 'A';
			ascii[index++] = 'R';
			
			sprintf(temp_str, "%3d", data.net_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			sprintf(temp_str, "%3d", data.device_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
			sprintf(temp_str, "%3d", data.channel_addr);
			ascii[index++] = temp_str[0];
			ascii[index++] = temp_str[1];
			ascii[index++] = temp_str[2];
			
            if ((data.alarm_type == LEAKAGE_FAULT) || (data.alarm_type == TEMPERATURE_FAULT) || (data.alarm_type == CHANNEL_FAULT)) {
				ascii[index++] = data.alarm_type;
			} else {
				value = -2;
				return value;
			}
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case RST_CMD:
			ascii[index++] = 'R';
			ascii[index++] = 'S';
			ascii[index++] = 'T';
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case INQ_CMD:
			ascii[index++] = 'I';
			ascii[index++] = 'N';
			ascii[index++] = 'Q';
			
//			sprintf(temp_str, "%3d", data.heart_beat);
//			ascii[index++] = temp_str[0];
//			ascii[index++] = temp_str[1];
//			ascii[index++] = temp_str[2];
            ascii[index++] = '0';
            ascii[index++] = '0';
            ascii[index++] = '1';
			value = index;
			break;
		case ACF_CMD:
			ascii[index++] = 'A';
			ascii[index++] = 'C';
			ascii[index++] = 'F';
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case ACN_CMD:
			ascii[index++] = 'A';
			ascii[index++] = 'C';
			ascii[index++] = 'N';
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case BTF_CMD:
			ascii[index++] = 'B';
			ascii[index++] = 'T';
			ascii[index++] = 'F';
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		case BTN_CMD:
			ascii[index++] = 'B';
			ascii[index++] = 'T';
			ascii[index++] = 'N';
			
			temp = change_time_to_ascii(&ascii[index], data.pic_time);
			
			if (temp)
				index += temp;
			else {
				value = -3;
				return value;
			}
			value = index;
			break;
		default:
			break;
	}
	
	return value;
}

void PicProtocol::pic_write_sent_buf(struct pic_data_t data, struct pic_buf_t *buf)
{
    if (buf->lock == 0) {
        buf->lock = 1;
        if (CIRC_SPACE(buf->head, buf->tail, PIC_BUF_LEN)) {
            buf->data[buf->head] = data;
            buf->head = (buf->head + 1) & (PIC_BUF_LEN - 1);
        }
        buf->lock = 0;
    }
}

int PicProtocol::pic_read_sent_buf(int fd, struct pic_buf_t *buf, SENT_TPYE *type)
{
	struct pic_data_t data;
	int data_len, value = -1;
	char calculation_crch[PIC_CRCH_LEN + 1], calculation_crcl[PIC_CRCL_LEN + 1];
	
	*type = NONE_TPYE;
	
	if (fd < 0)
		return value;
	
	if (buf->lock == 0) {
		buf->lock = 1;
		data_len = CIRC_CNT(buf->head, buf->tail, PIC_BUF_LEN);
		if (data_len) {
			data = buf->data[buf->tail];
			buf->tail = (buf->tail + 1) & (PIC_BUF_LEN - 1);
		}
		buf->lock = 0;
	}
	if (data_len) {
		value = sent_data_to_ascii(sent_temp.sent_ascii_char, data);
		if (value) {
			value = pic_crc_check(sent_temp.sent_ascii_char, value, calculation_crch, calculation_crcl);
			if (value) {
				sent_temp.sent_len = value;
				sent_temp.sent_count = 1;
				value = ::write(fd, sent_temp.sent_ascii_char, value);
				if (sent_temp.sent_ascii_char[1] == 'I')
					*type = POLL_TPYE;
				else
					*type = NORMAL_TPYE;
			}
		}
	}
	return value;
}

int PicProtocol::pic_write_receive_buf(int fd, struct circ_buf *data)
{
	int rx_len, space_len, value = -1;
	char temp[CIRC_LEN];
    printf("data->lock==%d\n",data->lock);
	if ((fd >= 0) && (data->lock == 0)) {
		data->lock = 1;
        space_len = CIRC_SPACE(data->head, data->tail, CIRC_LEN);printf("data->head==%d data->tail===%d  space_len==%d\n",data->head,data->tail,space_len);
		if (space_len) {
			rx_len = ::read(fd, temp, space_len);
            printf("rx_len==%d\n",rx_len);
			value = rx_len;
			if (rx_len) {
				for (int i = 0; i < rx_len; i++) {
					data->buf[data->head] = temp[i];
					data->head = (data->head + 1) & (CIRC_LEN - 1);
				}
			}
		}
		data->lock = 0;
	}
	return value;
}



PIC_ANSWER PicProtocol::receive_handle(char *data, int len)
{printf("receive_handle  data===%s \n",data);
	PIC_ANSWER value = AN_NONE;
	char loop = 1;
	int i, start_index = -1, end_index = -1;
	//char temp[CIRC_LEN];
	int temp_len = -1;
    char crch[PIC_CRCH_LEN]={}, crcl[PIC_CRCL_LEN]={};
    char calculation_crch[PIC_CRCH_LEN + 1]={}, calculation_crcl[PIC_CRCL_LEN + 1]={};
	char str_cmd[3];
	HANDLE_STATE handle_state = FIND_START;
	
	if (len > PIC_FREAM_MIN_LEN) {
		while (loop) {
			switch (handle_state) {
				case FIND_START:
					for (i = 0; i < len; i++) {
						if (data[i] == '@') {
							handle_state = FIND_END;
							start_index = i;
							break;
						}
					}
					if (start_index < 0)
						handle_state = HANDLE_ERROR;                    
					break;
				case FIND_END:
					for (i = start_index; i < len; i++) {
						if (data[i] == '@') {
							start_index = i;
						} else if (data[i] == '#') {
							handle_state = CHECK_CRC;
							end_index = i;
							break;
						}
					}
					if (end_index < 0)
						handle_state = HANDLE_ERROR;
					else {
						temp_len = end_index - start_index - PIC_CRCH_LEN - PIC_CRCL_LEN;
                        printf("end_index==%d start_index==%d temp_len==%d\n",end_index,start_index,temp_len);
                        if (temp_len >= 4) {printf("111data ===%s\n",data);
                            memmove(data, &data[start_index], temp_len);printf("data ===%s\n",data);
                            memcpy(crch, &data[end_index - PIC_CRCH_LEN - PIC_CRCL_LEN], PIC_CRCH_LEN);//printf("crch ===%s\n",crch);
                            printf("crch[0]==%x crch[1]==%x crch[2]==%x \n",crch[0],crch[1],crch[2]);
                            memcpy(crcl, &data[end_index - PIC_CRCL_LEN], PIC_CRCL_LEN);//printf("crcl ===%s\n",crcl);
                            printf("crcl[0]==%x crcl[1]==%x crcl[2]==%x \n",crcl[0],crcl[1],crcl[2]);
							handle_state = CHECK_CRC;
						} else
							handle_state = HANDLE_ERROR;

                    } printf("FIND_END  handle_state==%d\n",handle_state);
					break;
				case CHECK_CRC:
					if (pic_crc_check(data, temp_len, calculation_crch, calculation_crcl)) {//计算CRC
                        printf("pic_crc_check\n");
                        if(1) /*((calculation_crch[0] == crch[0]) && (calculation_crch[1] == crch[1]) && (calculation_crch[2] == crch[2])
                            && (calculation_crcl[0] == crcl[0]) && (calculation_crcl[1] == crcl[1]) && (calculation_crcl[2] == crcl[2]))*/ {
							handle_state = HANDLE_CRECET;
						} else
							handle_state = HANDLE_ERROR;
					} else
						handle_state = HANDLE_ERROR;
                    printf("CHECK_CRC handle_state==%d\n",handle_state);
					break;
				case HANDLE_CRECET:
					memcpy(str_cmd, &data[1], PIC_CMD_LEN);
					if (memcmp(str_cmd, "AN1", PIC_CMD_LEN) == 0)
						value = AN1;
					else if (memcmp(str_cmd, "AN2", PIC_CMD_LEN) == 0)
						value = AN2;
					else if (memcmp(str_cmd, "AN3", PIC_CMD_LEN) == 0)
						value = AN3;
					else if (memcmp(str_cmd, "AN4", PIC_CMD_LEN) == 0)
						value = AN4;
					else if (memcmp(str_cmd, "RST", PIC_CMD_LEN) == 0) {
						value = RST;
                    }printf("HANDLE_CRECET   value ===%d\n",value);
					loop = 0;
					handle_state = FIND_START;
					break;
				case HANDLE_ERROR:
					loop = 0;
					handle_state = FIND_START;
					break;
				default:
					loop = 0;
					handle_state = FIND_START;
					break;
			}	
		}
	}
    printf("value ===%d\n",value);
	return value;
}

PIC_ANSWER PicProtocol::pic_read_receive_buf(struct circ_buf *data)
{
	int data_len;
	PIC_ANSWER value = AN_NONE;
	char temp[CIRC_LEN];
	
	if (data->lock == 0) {
		data->lock = 1;
		data_len = CIRC_CNT(data->head, data->tail, CIRC_LEN);
		if (data_len) {
			for (int i = 0; i < data_len; i++) {
				temp[i] = data->buf[data->tail];
				data->tail = (data->tail + 1) & (CIRC_LEN - 1);
			}
		}
		data->lock = 0;
	}
	value = receive_handle(temp, data_len);
	return value;
}

int PicProtocol::retry_sent_buf(int fd, char *data, int len)
{
	int value = -1;
	
	if ((fd < 0) || (len <= 0))
		return value;
		
	value = ::write(fd, data, len);
	return value;
}

int PicProtocol::pic_port_init(struct pic_master_port *port, int fd)
{
	if (fd < 0) {
		printf("open pic protocol failed.\n");
		return -1;
	}
		
	port->sent_state = MASTER_IDLE;
	port->timer.timer_fun = timer_silence;
	port->timer.timer_rest_fun = timer_silence_reset;
	port->timer.retry_time = RETRY_TIME_MS;
	port->timer.retry_count = RETRY_COUNT;
	
	port->rd_rx_buf_fun = pic_read_receive_buf;
	port->wr_rx_buf_fun = pic_write_receive_buf;
	port->rd_tx_buf_fun = pic_read_sent_buf;
	port->wr_tx_buf_fun = pic_write_sent_buf;
	port->retry_sent_fun = retry_sent_buf;
	
	
	port->pic_fd = fd;
	port->pic_receive_buf.head = 0;
	port->pic_receive_buf.tail = 0;
	port->pic_receive_buf.lock = 0;
	port->pic_sent_buf.head = 0;
	port->pic_sent_buf.tail = 0;
	port->pic_sent_buf.lock = 0;
	port->rebulid = 0;
	
	printf("open pic protocol!\n");
	return 1;
}

void PicProtocol::pic_port_state_fsm(struct pic_master_port *port)
{
	SENT_TPYE sent_tpye = NONE_TPYE;
	PIC_ANSWER replay_type = AN_NONE;
	
	switch (port->sent_state) {
		case MASTER_IDLE:
			port->timer.timer_rest_fun();
			if (port->rd_tx_buf_fun(port->pic_fd, &port->pic_sent_buf, &sent_tpye)) {
				if (sent_tpye == POLL_TPYE)
					port->sent_state = MASTER_POLL_REPLY;
				else if (sent_tpye == NORMAL_TPYE)
					port->sent_state = MASTER_NORMAL_REPLY;
			}
			break;
		case MASTER_SENT_NORMAL:
			break;
		case MASTER_SENT_POLL:
			break;
		case MASTER_NORMAL_REPLY:
            printf("MASTER_NORMAL_REPLY\n");
            if (port->timer.timer_fun() < port->timer.retry_time) {printf("port->timer.retry_time\n");
				if (port->wr_rx_buf_fun(port->pic_fd, &port->pic_receive_buf)) {
					replay_type = port->rd_rx_buf_fun(&port->pic_receive_buf);
                    if (replay_type == AN3){printf("AN3--AN3\n");
                        port->sent_state = MASTER_IDLE;}
                    else if (replay_type == AN4) {printf("AN4--AN4\n");
						if (sent_temp.sent_count < port->timer.retry_count) {
							port->retry_sent_fun(port->pic_fd, sent_temp.sent_ascii_char, sent_temp.sent_len);
							sent_temp.sent_count++;
							port->timer.timer_rest_fun();
						} else
							port->sent_state = MASTER_IDLE;
					} else
						port->sent_state = MASTER_PROCESSING_ERROR;
				}
			} else if (sent_temp.sent_count < port->timer.retry_count) {
				port->retry_sent_fun(port->pic_fd, sent_temp.sent_ascii_char, sent_temp.sent_len);
				sent_temp.sent_count++;
				port->timer.timer_rest_fun();
			} else
				port->sent_state = MASTER_IDLE;
			break;
		case MASTER_POLL_REPLY:
        printf("MASTER_POLL_REPLY  \n");
            if (port->timer.timer_fun() < port->timer.retry_time) {printf("MASTER_POLL_REPLY < port->timer.retry_time\n");
				if (port->wr_rx_buf_fun(port->pic_fd, &port->pic_receive_buf)) {
					replay_type = port->rd_rx_buf_fun(&port->pic_receive_buf);
                    if (replay_type == AN1){printf("AN1--AN1\n");
                        port->sent_state = MASTER_IDLE;}
                    else if (replay_type == AN2) {printf("AN2--AN2\n");
						port->rebulid = 1;
						port->sent_state = MASTER_IDLE;
                    } else{printf("MASTER_PROCESSING_ERROR\n");
                        port->sent_state = MASTER_PROCESSING_ERROR;}
				}
			} else
				port->sent_state = MASTER_IDLE;
			break;
		case MASTER_PROCESSING_ERROR:
			port->sent_state = MASTER_IDLE;
			break;
		default:
			port->sent_state = MASTER_IDLE;
			break;
	}
}

PicProtocol::PicProtocol()
{
	printf("we need to call pic_port_init function in order to enable pic protocol.\n");
}

PicProtocol::~PicProtocol()
{
	printf("exit PicProtocol!\n");
}

