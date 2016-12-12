/* ************************************************************************
 *       Filename:  echong_api.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2016年11月14日 15时00分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (andy.zhao), 
 *        Company:  
 * ************************************************************************/
#ifndef _ECHONG_API_H_
#define _ECHONG_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define     START   0X68
#define     HEAD_VER    0x01
#define     END     0x16

#define     START_LEN             1
#define     HEAD_VER_LEN    1
#define     PILE_CODE_LEN    16
#define     COMMAND_LEN    1
#define     LEN123_LEN            6
#define     AES_DATA_LEN       0 //()
#define     CHECK_LEN              1
#define     END_LEN                   1

#define     FRAME_LEN      (START_LEN + HEAD_VER_LEN + PILE_CODE_LEN + COMMAND_LEN + LEN123_LEN + AES_DATA_LEN + CHECK_LEN + END_LEN)

#define     LENL1  (FRAME_LEN)


struct echong_AES_pack {
    // 起始字符
    unsigned int    Start_character;
    // 头部版本号
    unsigned int    Head_ver;
    // 桩编码
    unsigned char    Charger_SN[16];
    // 指令 ID
    unsigned int    Command_ID;
    // 总长度 L1
    unsigned char    LengthL1[2];
    // 应用数据加密 前长度 L2
    unsigned char    LengthL2[2];
    // 应用层数据加 密后长度 L3
    unsigned char    LengthL3[2];
    // 应用层数据 (AES128加密)
    unsigned char   data_pack[200];
    // 校验和
    unsigned int    Checksum;
    // 结束字符
    unsigned int    End_character;
};

struct echong_pack {
    // 起始字符
    unsigned int    Start_character;
    // 头部版本号
    unsigned int    Head_ver;
    // 桩编码
    unsigned char    Charger_SN[16];
    // 指令 ID
    unsigned int    Command_ID;
    // 总长度 L1
    unsigned char    LengthL1[2];
    // 应用数据加密 前长度 L2
    unsigned char    LengthL2[2];
    // 应用层数据加 密后长度 L3
    unsigned char    LengthL3[2];
    // 应用层数据
    unsigned char   data_pack[200];
    // 校验和
    unsigned int    Checksum;
    // 结束字符
    unsigned int    End_character;
};

typedef enum {//platform平台  //charger
    COMMAND_ACK = 0x01,//确认帧
    COMMAND_DENY = 0x02,//否认帧
    COMMAND_C_THB = 0x03,//充电桩心跳请求
    COMMAND_P_THB = 0x04,//平台发送心跳包到充电桩
    COMMAND_P_VER = 0x05,//读取充电桩软件版本号 ver
    COMMAND_C_VER = 0x06,//充电桩返回软件版本号
    COMMAND_P_REBOOT = 0x07,//平台下发重启充电桩
    COMMAND_C_REBOOT = 0x08,//充电桩返回重启电桩命令
    COMMAND_C_LOGIN = 0x09,//充电桩发送登录指令
    COMMAND_P_LOGIN = 0x0A,//平台回复充电桩登录
    COMMAND_P_ELEPRICE = 0x0B,//设置电费价格信息
    COMMAND_P_SERVICE = 0x0C,//设置服务费价格信息
    COMMAND_C_SETINTERVAL = 0x0D,//设置充电桩上报状态时间间隔
    COMMAND_C_SETMETERRATE = 0x0E,//设置充电桩电表倍率
    COMMAND_C_KEY = 0x0F,//设置充电桩加密密钥
    COMMAND_P_CLOCK = 0x10,//查询充电桩时钟及当前执行电价
    COMMAND_C_CLOCK = 0x11,//返回充电桩时钟及当前执行电价
    COMMAND_P_CLOCK_SERVICE = 0x12,//查询充电桩时钟及当前执行服务费
    COMMAND_C_CLOCK_SERVICE = 0x13,//返回充电桩时钟及当前执行服务费
    COMMAND_P_CLOCK_PRICE = 0x14,//查询充电桩时钟及最终执行电价
    COMMAND_C_CLOCK_PRICE = 0x15,//返回充电桩时钟及最终执行电价
    COMMAND_P_END_SERVICE = 0x16,//查询充电桩时钟及最终执行服务费价格
    COMMAND_C_END_SERVICE = 0x17,//充电桩返回时钟及最终执行服务费价格
    COMMAND_P_INTERVAL = 0x18,//查询充电桩自动上报时间间隔
    COMMAND_C_INTERVAL = 0x19,//充电桩返回上报时间间隔
    COMMAND_P_METERRATE = 0x1A,//查询充电桩电表倍率
    COMMAND_C_METERRATE = 0x1B,//充电桩返回电表倍率
    COMMAND_C_STATUS = 0x1C,//充电桩上报实时状态
    COMMAND_P_STATUS = 0x1D,//查询充电桩实时状态
    COMMAND_C_S_T = 0x1E,//充电桩启停操作(无卡)
    COMMAND_P_S_T = 0x1F,//充电桩启停操作回调(无卡)  桩返回启停操作结果
    COMMAND_C_UPCHARGINGDATA = 0x20,//充电桩上报实时充电数据(无卡)
    COMMAND_C_UPTRANSACTIONDATA = 0x21,//充电桩上报交易记录(无卡／有卡)
    COMMAND_P_DOWNTRANSACTIONDATA = 0x22,//平台返回充电桩交易记录应答
    COMMAND_P_NOCARD_TRANSACTIONDATA = 0x23,//查询充电桩无卡交易记录
    COMMAND_P_CARD_TRANSACTIONDATA = 0x24,//查询用户卡消费记录(预留)
    COMMAND_P_UPDATE = 0x25,//平台发下发升级命令
    COMMAND_P_UPDATEPROGRESS = 0x26,//平台查询充电桩升级进度
    COMMAND_C_UPDATEPROGRESS = 0x27,//充电桩升级进度应答
    COMMAND_C_INFSYNC = 0x28,//设备信息同步指令
    COMMAND_P_INFSYNC = 0x29,//平台召唤信息同步
}COMMAND_ID;


struct command_osn{
        unsigned char   Operation_sequence_num[4];//操作序列号
};


struct command_c_time{
        //unsigned char    Current_time[7];//BCD码
        unsigned char Current_time_bcd_sec;
        unsigned char Current_time_bcd_min;
        unsigned char Current_time_bcd_hour;
        unsigned char Current_time_bcd_day;
        unsigned char Current_time_bcd_mon;
        unsigned char Current_time_bcd_year_l;
        unsigned char Current_time_bcd_year_h;
};

struct command_ver{//
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   Software_ver[10];
};

struct command_set_parameter{
        unsigned char   Operation_sequence_num[4];//操作序列号
        struct command_c_time  command_c_changetime;
        unsigned char   tip_price[4];
        unsigned char   peak_price[4];
        unsigned char   flat_price[4];
        unsigned char   valley_price[4];
};

struct command_set_update{
        unsigned char   Operation_sequence_num[4];//操作序列号
        struct command_c_time  command_c_changetime;
        unsigned int   status_data;
        unsigned int   real_time_data;
};

struct command_set_meterpara{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   meter_rate[4];
};

struct command_set_key{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   charger_key[16];
};

struct command_c_clock{
        unsigned char   Operation_sequence_num[4];//操作序列号
        struct command_c_time  command_c_currenttime;
        struct command_c_time  command_c_changetime;
        unsigned char   tip_price[4];
        unsigned char   peak_price[4];
        unsigned char   flat_price[4];
        unsigned char   valley_price[4];
};

struct command_set_interval{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned int   status_data_interval;
        unsigned int   real_time_data_interval;
};

struct command_c_status{//充电桩上报实时状态
        unsigned int    charger_interface;
        unsigned int    status;
        unsigned int    parking_status;
        unsigned int    interface_connstatus;
        unsigned int    interface_workstatus;
        unsigned char    output_vol[4];
        unsigned char    output_Avol[4];
        unsigned char    output_Bvol[4];
        unsigned char    output_Cvol[4];
        unsigned char    output_current[4];
        unsigned char    output_Acurrent[4];
        unsigned char    output_Bcurrent[4];
        unsigned char    output_Ccurrent[4];
        unsigned int    output_relay_status;
        unsigned int    system_fan_status;
        unsigned char    real_time_temp[4];
        unsigned char    active_power[4];
        unsigned char    reactive_power[4];
        unsigned char    active_meter[4];
        unsigned char    reactive_meter[4];
        unsigned int    soc;
        unsigned int    fault_code;
        struct command_c_time   command_c_currenttime;
};

struct command_p_status{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned int    charger_interface;
};

struct command_c_s_t{
        unsigned char   action_ID[4];
        unsigned char   Batch[8];
        unsigned int    charger_interface;
        unsigned int    c_s_t;
};

struct  command_p_s_t{
        unsigned char   action_ID[4];
        unsigned char   Batch[8];
        unsigned int    charger_interface;
        unsigned int    p_s_t;
        unsigned int    set_status;
        unsigned int    failure;
        unsigned int    soc;
};

struct command_c_upchargingdata{
        unsigned char   Batch[8];
        unsigned int    charger_interface;
        unsigned char   now_total_power[4];
        unsigned char   now_tip_power[4];
        unsigned char   now_peak_power[4];
        unsigned char   now_flat_power[4];
        unsigned char   now_valley_power[4];
        unsigned char   now_total_price[4];
        unsigned char   now_total_service_price[4];
        unsigned char   now_total_chargingtime[2];
        unsigned int    now_charger_status;
        unsigned int    now_stop_charging_failure;
        unsigned int    now_soc;
        unsigned char   life_charging_time[2];
        unsigned char    now_output_vol[4];
        unsigned char    now_output_current[4];
        unsigned char    now_bat_lowest_temp[4];
        unsigned char    now_bat_highest_temp[4];
        struct command_c_time   command_c_currenttime;
};

struct command_c_uptransactiondata{
        unsigned int    card_flag;
        unsigned char   Batch[8];
        unsigned int    charger_interface;
        unsigned char   Card_num[8];
        unsigned char   before_charging_power[4];
        unsigned char   after_charging_power[4];
        unsigned char   total_price[4];
        unsigned char   total_serviceprice[4];

        unsigned char   tip_price[4];
        unsigned char   tip_serviceprice[4];
        unsigned char   tip_power[4];
        unsigned char   tip_money[4];
        unsigned char   tip_servicemoney[4];
        unsigned char   tip_charging_time[2];

        unsigned char   peak_price[4];
        unsigned char   peak_serviceprice[4];
        unsigned char   peak_power[4];
        unsigned char   peak_money[4];
        unsigned char   peak_servicemoney[4];
        unsigned char   peak_charging_time[2];

        unsigned char   flat_price[4];
        unsigned char   flat_serviceprice[4];
        unsigned char   flat_power[4];
        unsigned char   flat_money[4];
        unsigned char   flat_servicemoney[4];
        unsigned char   flat_charging_time[2];

        unsigned char   valley_price[4];
        unsigned char   valley_serviceprice[4];
        unsigned char   valley_power[4];
        unsigned char   valley_money[4];
        unsigned char   valley_servicemoney[4];
        unsigned char   valley_charging_time[2];

        struct command_c_time   start_charging_time;
        unsigned char   charging_time[2];
        unsigned int    stop_charging_failure;
        unsigned int    soc;
        unsigned int    status;
        struct command_c_time   command_c_currenttime;
};

struct command_p_downtransactiondata{
        unsigned char   Batch[8];
        unsigned int    charger_interface;
        unsigned char   Card_num[8];
};

struct command_c_update{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   Program_ver[20];
        unsigned char   Program_down_addr[100];
};

struct command_p_updateprogress{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   Program_ver[10];
};

struct command_c_updateprogress{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   Program_ver[10];
        unsigned int   progress;
};

struct command_c_infsync{
        unsigned char   Operation_sequence_num[4];//操作序列号
        unsigned char   Equ_sequence_num[4];//设备序列号
        unsigned char   Program_ver[10];
        unsigned int    now_status;
        unsigned int    comm_mode;
        unsigned char   Hardware_ver[20];
};

struct command_p_infsync{
        unsigned char   Operation_sequence_num[4];//操作序列号
};

struct command_osn command_ack;//确认帧
struct command_osn command_deny;//否认帧
struct command_c_time command_c_thb;//充电桩心跳请求
struct command_c_time command_p_thb;//平台发送心跳包到充电桩
struct command_osn command_p_ver;//平台读取软件版本号
struct command_ver command_c_ver;//充电桩返回软件版本号
struct command_osn command_p_reboot;//平台下发重启充电桩
struct command_c_time command_c_login;//充电桩发送登录指令
struct command_c_time command_p_login;//充电桩返回重启电桩命令
struct command_set_parameter command_p_eleprice;//设置电费价格信息
struct command_set_parameter command_p_service;//设置服务费价格信息
struct command_set_update command_c_setinterval;//设置充电桩上报状态时间间隔
struct command_set_meterpara command_set_meterrate;//设置充电桩电表倍率
struct command_set_key command_set_key_inf;//设置充电桩加密密钥
struct command_osn command_p_clock;//查询充电桩时钟及当前执行电价
struct command_c_clock command_c_clock_inf;//返回充电桩时钟及当前执行电价
struct command_osn command_p_clock_service;//查询充电桩时钟及当前执行服务费
struct command_c_clock command_c_clock_service;//返回充电桩时钟及当前执行服务费
struct command_osn command_p_clock_price;//查询充电桩时钟及最终执行电价
struct command_c_clock command_c_clock_price;//返回充电桩时钟及最终执行电价
struct command_osn command_p_end_service;//查询充电桩时钟及最终执行服务费价格
struct command_c_clock command_c_end_service;//充电桩返回时钟及最终执行服务费价格
struct command_osn command_p_interval;//查询充电桩自动上报时间间隔
struct command_set_interval command_c_interval;//充电桩返回上报时间间隔
struct command_osn command_p_meterrate;//查询充电桩电表倍率
struct command_set_meterpara command_c_meterrate;//充电桩返回电表倍率
struct command_c_status command_c_status_inf;//充电桩上报实时状态
struct command_p_status command_p_status_inf;//查询充电桩实时状态
struct  command_c_s_t   command_c_s_t_inf;//充电桩启停操作(无卡)
struct  command_p_s_t   command_p_s_t_inf;//充电桩启停操作回调(无卡)  桩返回启停操作结果
struct command_c_upchargingdata command_c_upchargingdata_inf;//充电桩上报实时充电数据(无卡)
struct command_c_uptransactiondata  command_c_uptransactiondata_inf;//充电桩上报交易记录(无卡／有卡)
struct command_p_downtransactiondata command_p_downtransactiondata_inf;//平台返回充电桩交易记录应答
struct command_c_uptransactiondata  command_p_nocard_transactiondata_inf;//查询充电桩无卡交易记录
struct command_c_update command_c_update_inf;//平台发下发升级命令
struct command_p_updateprogress command_p_updateprogress_inf;//平台查询充电桩升级进度
struct command_c_updateprogress  command_c_updateprogress_inf;//充电桩升级进度应答
struct command_c_infsync    command_c_infsync_inf;//设备信息同步指令
struct command_p_infsync    command_p_infsync_inf;//平台召唤信息同步


//获取当前时间
int getcurrenttime(char *thiz, char *LengthL2);

/* 根据指令ID 获取对应的数据类型信息 */
int get_echong_ruler_info(int CommandID, struct echong_pack *outRulerInfo);
/* 通过桩编码 指令ID 数据域数据及长度 封帧 */
int pack_echong_frame_by_data(struct echong_AES_pack *in_aes_data, struct echong_pack *in_data, char *outBuffer, int *outLength);

int send_echong_frame();
int receive_echong_frame();

int analysis_echong_frame();

/* 通过桩编码 指令ID 数据域数据及长度 解析帧 */
int unpack_echong_frame_by_data(char *inpBuffer, int inBufferLength, struct echong_pack *outpFrame);

//int packet_echong_command_c_thb(char *thiz, char *LengthL1, char *LengthL2, char *LengthL3);
int packet_echong_command_c_thb(struct echong_pack *outRulerInfo);

int packet_echong_command_c_ver(struct command_ver * thiz);

void http_post_data();


#ifdef __cplusplus
}
#endif

#endif //_ECHONG_API_H_
