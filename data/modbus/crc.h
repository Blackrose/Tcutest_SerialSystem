/*=============================
作用：crc检验

=============================*/

#ifndef LINLONG_CRC
#define LINLONG_CRC


class Crc
{
public:
	static const char G_auchCRCHi[400];
	static const char G_auchCRCLo[400];
	static unsigned int CRC16(char* str,unsigned int len);
};

#endif
