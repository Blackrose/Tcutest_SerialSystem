/*
* PIC Communication Protocol.
* 
*
* File:     pic_communication.h
* Author:   MHW
* Create:   2015-03-04
*/

#ifndef __PIC_COMMU_H__
#define __PIC_COMMU_H__

#include <QString>

#define CIRC_CNT(head, tail, size)    (((head) - (tail)) & ((size)-1))
#define CIRC_SPACE(head, tail, size)  CIRC_CNT((tail),((head)+1),(size))

#define CIRC_LEN        1024
#define RETRY_TIME_MS   30 
#define RETRY_COUNT     3
#define PIC_BUF_LEN     16

#define PIC_FREAM_MIN_LEN  10
#define PIC_CRCH_LEN       3
#define PIC_CRCL_LEN       3
#define PIC_CMD_LEN        3

#define NSEC_PER_SEC  1000000000
#define NSEC_PER_MSEC 1000000
#define MSEC_PER_SEC  1000

typedef enum {
    FIND_START = 0,
	FIND_END = 1,
	CHECK_CRC = 2,
    HANDLE_CRECET = 3,
	HANDLE_ERROR = 4,
} HANDLE_STATE;

typedef enum {
    AN_NONE = 0,
	AN1 = 1,
	AN2 = 2,
    AN3 = 3,
	AN4 = 4,
	RST = 5
} PIC_ANSWER;

typedef enum {
    MASTER_IDLE = 0,
	MASTER_SENT_NORMAL = 1,
	MASTER_SENT_POLL = 2,
    MASTER_NORMAL_REPLY = 3,
	MASTER_POLL_REPLY = 4,
    MASTER_PROCESSING_ERROR = 5
} PIC_MASTER_STATE;

typedef enum {
	NONE_TPYE = 0,
    POLL_TPYE  = 1,
    NORMAL_TPYE  = 2
} SENT_TPYE;

typedef enum {
	NONE_CMD = 0,
    FIR_CMD  = 1,//报警信息
    FAU_CMD  = 2,//故障信息
    FAR_CMD  = 3,//故障恢复
    RST_CMD  = 4,//复位
    INQ_CMD  = 5,//询问
    ACF_CMD  = 6,//主电故障
    ACN_CMD  = 7,//主电恢复
    BTF_CMD  = 8,//备电故障
    BTN_CMD  = 9 //备电恢复
} PIC_CMD_TPYE;

typedef enum {
	MIN_ALARM            = 0X30,
    LEAKAGE_ALARM        = 0x31,//漏电报警
    TEMPERATURE_ALARM    = 0x32,//温度报警
    ARC_ALARM            = 0x33,//电弧报警
    CURRENT_ALARM        = 0x34,//过流报警
	MAX_ALARM            = 0X35,
    LEAKAGE_FAULT        = 0x41,//漏电故障
    TEMPERATURE_FAULT    = 0x42,//温度故障
    COMMUNICATION_FAULT  = 0x50,//通讯故障
    CHANNEL_FAULT        = 0x45 //通道故障
} PIC_ALARM_TPYE;

struct pic_time_t {
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char seconds;
};

struct pic_data_t {
	PIC_CMD_TPYE     cmd_type;
	PIC_ALARM_TPYE   alarm_type;
	struct pic_time_t  pic_time;
	unsigned char    net_addr;
	unsigned char    device_addr;
	unsigned char    channel_addr;
	unsigned char    heart_beat;
};

struct pic_buf_t {
	struct pic_data_t data[PIC_BUF_LEN];
	int head;
	int tail;
	volatile unsigned char lock;
};

struct circ_buf {
	char buf[CIRC_LEN];
	int head;
	int tail;
	volatile unsigned char lock;
};

typedef unsigned short (*silence_timer)(void);
typedef void (*silence_timer_reset)(void);
typedef PIC_ANSWER (*rd_rx_buf)(struct circ_buf *data);
typedef int (*wr_rx_buf)(int fd, struct circ_buf *data);
typedef int (*rd_tx_buf)(int fd, struct pic_buf_t *buf, SENT_TPYE *type);
typedef void (*wr_tx_buf)(struct pic_data_t data, struct pic_buf_t *buf);
typedef int (*retry_sent)(int fd, char *data, int len);

struct pic_timer {
	silence_timer timer_fun;
	silence_timer_reset timer_rest_fun;
	unsigned short retry_time;
	int retry_count;
};

struct pic_master_port {
	PIC_MASTER_STATE sent_state;
	struct pic_timer timer;
	rd_rx_buf rd_rx_buf_fun;
	wr_rx_buf wr_rx_buf_fun;
	rd_tx_buf rd_tx_buf_fun;
	wr_tx_buf wr_tx_buf_fun;
	retry_sent retry_sent_fun;
	int pic_fd;
	struct circ_buf pic_receive_buf;
	struct pic_buf_t pic_sent_buf;
	unsigned char rebulid;
};

struct retry_data {
	char sent_ascii_char[50];
	int sent_len;
	int sent_count;
};

class PicProtocol
{
public:
	static const unsigned char crc_table[512];
	static unsigned short silence_time;
	static long timer_sec_start;
	static long timer_nsec_start;
	static long timer_remain_nsec;
	static struct retry_data sent_temp;
	static struct pic_master_port pic_port;
	
	PicProtocol();
	virtual ~PicProtocol();
	static void timer_init(void);
	static unsigned short timer_silence(void);
	static void timer_silence_reset(void);
	static void pic_write_sent_buf(struct pic_data_t data, struct pic_buf_t *buf);
	static void time_exchange(struct pic_time_t *time, QString str_time);
	
	static void pic_t_alarm(unsigned char net, unsigned char device, unsigned char channel, QString time);
	static void pic_c_alarm(unsigned char net, unsigned char device, unsigned char channel, QString time);
    static void pic_t_error(unsigned char net, unsigned char device, unsigned char channel, QString time);
    static void pic_c_error(unsigned char net, unsigned char device, unsigned char channel, QString time);
    static void pic_t_restore(unsigned char net, unsigned char device, unsigned char channel, QString time);
    static void pic_c_restore(unsigned char net, unsigned char device, unsigned char channel, QString time);
    static void pic_channel_error(unsigned char net, unsigned char device, unsigned char channel, QString time);
	static void pic_communication_error(unsigned char net, unsigned char device, unsigned char channel, QString time);
	static void pic_channel_restore(unsigned char net, unsigned char device, unsigned char channel, QString time);
	static void pic_communication_restore(unsigned char net, unsigned char device, unsigned char channel, QString time);
	static void pic_heart_beat(void);
	static void pic_main_error(QString time);
	static void pic_main_restore(QString time);
	static void pic_premain_error(QString time);
	static void pic_premain_restore(QString time);
	
	static int pic_crc_check(char *ascii_char, int num, char *ascii_crch, char *ascii_crcl);
	static int change_time_to_ascii(char *ascii, struct pic_time_t  time);
	static int sent_data_to_ascii(char *ascii, pic_data_t data);
	static int pic_read_sent_buf(int fd, struct pic_buf_t *buf, SENT_TPYE *type);
	static int pic_write_receive_buf(int fd, struct circ_buf *data);
	static PIC_ANSWER receive_handle(char *data, int len);
	static PIC_ANSWER pic_read_receive_buf(struct circ_buf *data);
	static int retry_sent_buf(int fd, char *data, int len);
	
	static int pic_port_init(struct pic_master_port *port, int fd);
	static void pic_port_state_fsm(struct pic_master_port *port);
};

#endif
