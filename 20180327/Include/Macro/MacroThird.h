#pragma once
#include "Macro.h"

//��ע:ʹ���ַ��� ��������չ��

//֧����ʽ EPayType
static const std::string PAY_TYPE_APPSTORE		= "IOS";	//ƻ��Ӧ����֧��
static const std::string PAY_TYPE_ALIPAY		= "ALIPAY";	//֧����
static const std::string PAY_TYPE_LJ			= "LJ";		//�⾵
static const std::string PAY_TYPE_WEIXIN		= "WEIXIN";	//΢��
static const std::string PAY_TYPE_9GAME			= "9GAME";	//9��

//֧������ EPayCurrency
static const std::string PAY_CURRENCY_CNY		= "CNY";	//�����
static const std::string PAY_CURRENCY_USD		= "USD";	//��Ԫ

//�����ַ���(һ�ɴ�д)
static const std::string CHANNEL_STRING_WEB			= "WEB";//��ҳ
static const std::string CHANNEL_STRING_IOS			= "IOS";
static const std::string CHANNEL_STRING_ANDROID		= "ANDROID";
static const std::string CHANNEL_STRING_WINDOWS		= "WINDOWS";
static const std::string CHANNEL_STRING_MARMALADE	= "MARMALADE";
static const std::string CHANNEL_STRING_LINUX		= "LINUX";
static const std::string CHANNEL_STRING_BADA		= "BADA";
static const std::string CHANNEL_STRING_BLACKBERRY	= "BLACKBERRY";
static const std::string CHANNEL_STRING_MAC			= "MAC";
static const std::string CHANNEL_STRING_NACL		= "NACL";
static const std::string CHANNEL_STRING_EMSCRIPTEN	= "EMSCRIPTEN";
static const std::string CHANNEL_STRING_TIZEN		= "TIZEN";
static const std::string CHANNEL_STRING_QT5			= "QT5";
static const std::string CHANNEL_STRING_WP8			= "WP8";
static const std::string CHANNEL_STRING_WINRT		= "WINRT";

static const std::string CHANNEL_STRING_OFFICIAL	= "OFFICIAL";
static const std::string CHANNEL_STRING_PHONE_NUMBER= "PHONE_NUMBER";
static const std::string CHANNEL_STRING_QQ			= "QQ";
static const std::string CHANNEL_STRING_360			= "360";
static const std::string CHANNEL_STRING_BAIDU		= "BAIDU";	//�ٶ�
static const std::string CHANNEL_STRING_BSCN		= "BSCN"; //����
static const std::string CHANNEL_STRING_X7SY		= "X7SY"; //С������
static const std::string CHANNEL_STRING_DL			= "DL"; //����

static const std::string CHANNEL_STRING_WEIXIN		= "WEIXIN";	//΢��
static const std::string CHANNEL_STRING_YYB			= "YYB";	//Ӧ�ñ�

static const std::string CHANNEL_STRING_9GAME		= "9GAME";	//9��
static const std::string CHANNEL_STRING_XIAOMI		= "XIAOMI";	//С��
static const std::string CHANNEL_STRING_XIANG		= "XIANG";	//���뻥��
static const std::string CHANNEL_STRING_ACFUN		= "ACFUN";	//AcFun

static const std::string CHANNEL_STRING_MEIZU			= "MEIZU";	//����
static const std::string CHANNEL_STRING_JINLI			= "JINLI";	//����
static const std::string CHANNEL_STRING_OPPO			= "OPPO";	//OPPO
static const std::string CHANNEL_STRING_VIVO			= "VIVO";	//VIVO
static const std::string CHANNEL_STRING_COOLPAD			= "COOLPAD";//����
static const std::string CHANNEL_STRING_LENOVOOPENID	= "LENOVOOPENID";	//����
static const std::string CHANNEL_STRING_HUAWEI			= "HUAWEI";	//��Ϊ
static const std::string CHANNEL_STRING_BAIDUMOBILEGAME = "BAIDUMOBILEGAME";	//�ٶ��ƶ���Ϸ


//ͨ����SDK�ַ��� �����ַ���Ҳ���Ե�SDK�ַ���ʹ��
static const std::string SDK_STRING_LJ				= "LJ";		//�⾵
static const std::string SDK_STRING_HUOSU			= "HUOSU";	//����
static const std::string SDK_STRING_YIJIE			= "YIJIE";	//�׽�
static const std::string SDK_STRING_ANYSDK			= "ANYSDK";	//AnySdk

//����
enum  EChannelType
{
	CHANNEL_TYPE_INVALD = 0,

	CHANNEL_IOS			= 1,	//IOS
	CHANNEL_ANDROID		= 2,	//��׿
	CHANNEL_WINDOWS		= 3,	//Windows
	CHANNEL_MARMALADE	= 4,	//MARMALADE(һ������ƽ̨)
	CHANNEL_LINUX		= 5,	//Linux
	CHANNEL_BADA		= 6,	//BADA (�����з������������ֻ�ƽ̨)
	CHANNEL_BLACKBERRY	= 7,	//��ݮ
	CHANNEL_MAC			= 8,	//ƻ��
	CHANNEL_NACL		= 9,
	CHANNEL_EMSCRIPTEN	= 10,
	CHANNEL_TIZEN		= 11,
	CHANNEL_QT5			= 12,
	CHANNEL_WP8			= 13,	//wphone
	CHANNEL_WINRT		= 14,	//Arm�汾win

	CHANNEL_ANONYMOUS_END,//�����˺��յ�


	CHANNEL_ACCOUNT_BEGIN= 100,	//ע���˻����

	CHANNEL_OFFICIAL	= 101,	//�ٷ�
	CHANNEL_PHONE_NUMBER= 102,	//�绰����
	CHANNEL_QQ			= 103,	//QQ	
	CHANNEL_360			= 104,	//360	
	CHANNEL_BAIDU		= 105,	//baidu

	CHANNEL_ACCOUNT_END,		//ע���˻��յ�

	CHANNEL_TYPE_MAX,
};

//������ʽ
enum EConnectionMode{
	CONNECTION_MODE_INVAILD = 0,

	CONNECTION_MODE_WIFI,

	CONNECTION_MODE_2G,
	CONNECTION_MODE_3G,
	CONNECTION_MODE_4G,

	CONNECTION_MODE_MAX,
};
