#pragma once
#include "Macro.h"

//备注:使用字符串 更具有扩展性

//支付方式 EPayType
static const std::string PAY_TYPE_APPSTORE		= "IOS";	//苹果应用内支付
static const std::string PAY_TYPE_ALIPAY		= "ALIPAY";	//支付宝
static const std::string PAY_TYPE_LJ			= "LJ";		//棱镜
static const std::string PAY_TYPE_WEIXIN		= "WEIXIN";	//微信
static const std::string PAY_TYPE_9GAME			= "9GAME";	//9游

//支付币种 EPayCurrency
static const std::string PAY_CURRENCY_CNY		= "CNY";	//人民币
static const std::string PAY_CURRENCY_USD		= "USD";	//美元

//渠道字符串(一律大写)
static const std::string CHANNEL_STRING_WEB			= "WEB";//网页
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
static const std::string CHANNEL_STRING_BAIDU		= "BAIDU";	//百度
static const std::string CHANNEL_STRING_BSCN		= "BSCN"; //蓝叠
static const std::string CHANNEL_STRING_X7SY		= "X7SY"; //小七手游
static const std::string CHANNEL_STRING_DL			= "DL"; //当乐

static const std::string CHANNEL_STRING_WEIXIN		= "WEIXIN";	//微信
static const std::string CHANNEL_STRING_YYB			= "YYB";	//应用宝

static const std::string CHANNEL_STRING_9GAME		= "9GAME";	//9游
static const std::string CHANNEL_STRING_XIAOMI		= "XIAOMI";	//小米
static const std::string CHANNEL_STRING_XIANG		= "XIANG";	//想想互娱
static const std::string CHANNEL_STRING_ACFUN		= "ACFUN";	//AcFun

static const std::string CHANNEL_STRING_MEIZU			= "MEIZU";	//魅族
static const std::string CHANNEL_STRING_JINLI			= "JINLI";	//金立
static const std::string CHANNEL_STRING_OPPO			= "OPPO";	//OPPO
static const std::string CHANNEL_STRING_VIVO			= "VIVO";	//VIVO
static const std::string CHANNEL_STRING_COOLPAD			= "COOLPAD";//酷派
static const std::string CHANNEL_STRING_LENOVOOPENID	= "LENOVOOPENID";	//联想
static const std::string CHANNEL_STRING_HUAWEI			= "HUAWEI";	//华为
static const std::string CHANNEL_STRING_BAIDUMOBILEGAME = "BAIDUMOBILEGAME";	//百度移动游戏


//通用型SDK字符串 渠道字符串也可以当SDK字符串使用
static const std::string SDK_STRING_LJ				= "LJ";		//棱镜
static const std::string SDK_STRING_HUOSU			= "HUOSU";	//火速
static const std::string SDK_STRING_YIJIE			= "YIJIE";	//易接
static const std::string SDK_STRING_ANYSDK			= "ANYSDK";	//AnySdk

//渠道
enum  EChannelType
{
	CHANNEL_TYPE_INVALD = 0,

	CHANNEL_IOS			= 1,	//IOS
	CHANNEL_ANDROID		= 2,	//安卓
	CHANNEL_WINDOWS		= 3,	//Windows
	CHANNEL_MARMALADE	= 4,	//MARMALADE(一个开发平台)
	CHANNEL_LINUX		= 5,	//Linux
	CHANNEL_BADA		= 6,	//BADA (三星研发的新型智能手机平台)
	CHANNEL_BLACKBERRY	= 7,	//黑莓
	CHANNEL_MAC			= 8,	//苹果
	CHANNEL_NACL		= 9,
	CHANNEL_EMSCRIPTEN	= 10,
	CHANNEL_TIZEN		= 11,
	CHANNEL_QT5			= 12,
	CHANNEL_WP8			= 13,	//wphone
	CHANNEL_WINRT		= 14,	//Arm版本win

	CHANNEL_ANONYMOUS_END,//匿名账号终点


	CHANNEL_ACCOUNT_BEGIN= 100,	//注册账户起点

	CHANNEL_OFFICIAL	= 101,	//官方
	CHANNEL_PHONE_NUMBER= 102,	//电话号码
	CHANNEL_QQ			= 103,	//QQ	
	CHANNEL_360			= 104,	//360	
	CHANNEL_BAIDU		= 105,	//baidu

	CHANNEL_ACCOUNT_END,		//注册账户终点

	CHANNEL_TYPE_MAX,
};

//联网方式
enum EConnectionMode{
	CONNECTION_MODE_INVAILD = 0,

	CONNECTION_MODE_WIFI,

	CONNECTION_MODE_2G,
	CONNECTION_MODE_3G,
	CONNECTION_MODE_4G,

	CONNECTION_MODE_MAX,
};
