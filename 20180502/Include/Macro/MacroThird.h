#pragma once
#include "Macro.h"

//��ע:ʹ���ַ��� ��������չ��

//�����ַ���(һ�ɴ�д)

static const std::string CHANNEL_WEB = "WEB";//��ҳ
static const std::string CHANNEL_OFFICIAL = "OFFICIAL";
static const std::string CHANNEL_PHONE = "PHONE";

static const std::string CHANNEL_XIANG = "XIANG";	//���뻥��

//ƽ̨����
static const std::string CHANNEL_IOS			= "IOS";
static const std::string CHANNEL_ANDROID		= "ANDROID";
static const std::string CHANNEL_WINDOWS		= "WINDOWS";
static const std::string CHANNEL_MARMALADE	= "MARMALADE";
static const std::string CHANNEL_LINUX		= "LINUX";
static const std::string CHANNEL_BADA		= "BADA";
static const std::string CHANNEL_BLACKBERRY	= "BLACKBERRY";
static const std::string CHANNEL_MAC			= "MAC";
static const std::string CHANNEL_NACL		= "NACL";
static const std::string CHANNEL_EMSCRIPTEN	= "EMSCRIPTEN";
static const std::string CHANNEL_TIZEN		= "TIZEN";
static const std::string CHANNEL_QT5			= "QT5";
static const std::string CHANNEL_WP8			= "WP8";
static const std::string CHANNEL_WINRT		= "WINRT";

//�˺�����
static const std::string CHANNEL_QQ = "QQ";
static const std::string CHANNEL_360 = "360";
static const std::string CHANNEL_BAIDU = "BAIDU";	//�ٶ�

//֧������
static const std::string CHANNEL_WEIXIN = "WEIXIN";			//΢��
static const std::string CHANNEL_ALIPAY = "ALIPAY";			//֧����
static const std::string CHANNEL_ALIPAY_WEB = "ALIPAYWEB";	//֧����

//����SDK
static const std::string CHANNEL_LFS = "LFS";		//�÷�ʦ

//Ӳ������
static const std::string CHANNEL_LENOVOOPENID = "LENOVOOPENID";	//����
static const std::string CHANNEL_OPPO = "OPPO";	//OPPO
static const std::string CHANNEL_VIVO = "VIVO";	//VIVO
static const std::string CHANNEL_COOLPAD = "COOLPAD";//����
static const std::string CHANNEL_JINLI = "JINLI";	//����
static const std::string CHANNEL_HUAWEI = "HUAWEI";	//��Ϊ
static const std::string CHANNEL_MEIZU = "MEIZU";	//����

//һ������
static const std::string CHANNEL_9GAME = "9GAME";	//9��
static const std::string CHANNEL_QIHOO = "QIHOO";		//�滢
static const std::string CHANNEL_YYB = "YYB";	//Ӧ�ñ�
static const std::string CHANNEL_BAIDUMOBILEGAME = "BAIDUMOBILEGAME";	//�ٶ��ƶ���Ϸ
static const std::string CHANNEL_XIAOMI = "XIAOMI";	//С��

//��������
static const std::string CHANNEL_4399 = "M4399";		//4399
static const std::string CHANNEL_DL = "DL"; //����
static const std::string CHANNEL_NUBIA = "NUBIA";		//Ŭ����
static const std::string CHANNEL_DOUYU = "DOUYU";		//����
static const std::string CHANNEL_ZHANQI = "ZHANQI";		//ս��
static const std::string CHANNEL_HTC = "HTC";		//HTC ����
static const std::string CHANNEL_TOUTIAO = "TOUTIAO";	//����ͷ��

//����Ԫ����
static const std::string CHANNEL_ACFUN = "ACFUN";	//AcFun
static const std::string CHANNEL_BILIBILI = "BILIBILI";	//��������
static const std::string CHANNEL_MUZHIWAN = "MUZHIWAN";	//Ĵָ��

//��β����
static const std::string CHANNEL_BSCN = "BSCN"; //����
static const std::string CHANNEL_X7SY = "X7SY"; //С������
static const std::string CHANNEL_5FUNC = "5FUN";		//��
static const std::string CHANNEL_SHUNWANG = "SHUNWANG";	//˳��
static const std::string CHANNEL_TT = "TT";	//TT����
static const std::string CHANNEL_SAMSUNG = "SAMSUNG";	//����
static const std::string CHANNEL_CCPLAY = "CCPLAY";	//�����Ϸ
static const std::string CHANNEL_LY = "LY";	//����

//��������
static const std::string CHANNEL_LJ = "LJ";		//�⾵
static const std::string CHANNEL_HUOSU = "HUOSU";	//����
static const std::string CHANNEL_YIJIE = "YIJIE";	//�׽�
static const std::string CHANNEL_ANYSDK = "ANYSDK";	//AnySdk

//֧������ EPayCurrency
static const std::string PAY_CURRENCY_CNY = "CNY";	//�����
static const std::string PAY_CURRENCY_USD = "USD";	//��Ԫ

//������ʽ
enum EConnectionMode{
	CONNECTION_MODE_INVAILD = 0,

	CONNECTION_MODE_WIFI,

	CONNECTION_MODE_2G,
	CONNECTION_MODE_3G,
	CONNECTION_MODE_4G,
	CONNECTION_MODE_5G,

	CONNECTION_MODE_MAX,
};
