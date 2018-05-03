#pragma once
#include "Macro.h"

//备注:使用字符串 更具有扩展性

//渠道字符串(一律大写)

static const std::string CHANNEL_WEB = "WEB";//网页
static const std::string CHANNEL_OFFICIAL = "OFFICIAL";
static const std::string CHANNEL_PHONE = "PHONE";

static const std::string CHANNEL_XIANG = "XIANG";	//想想互娱

//平台渠道
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

//账号渠道
static const std::string CHANNEL_QQ = "QQ";
static const std::string CHANNEL_360 = "360";
static const std::string CHANNEL_BAIDU = "BAIDU";	//百度

//支付渠道
static const std::string CHANNEL_WEIXIN = "WEIXIN";			//微信
static const std::string CHANNEL_ALIPAY = "ALIPAY";			//支付宝
static const std::string CHANNEL_ALIPAY_WEB = "ALIPAYWEB";	//支付宝

//无需SDK
static const std::string CHANNEL_LFS = "LFS";		//旅法师

//硬核渠道
static const std::string CHANNEL_LENOVOOPENID = "LENOVOOPENID";	//联想
static const std::string CHANNEL_OPPO = "OPPO";	//OPPO
static const std::string CHANNEL_VIVO = "VIVO";	//VIVO
static const std::string CHANNEL_COOLPAD = "COOLPAD";//酷派
static const std::string CHANNEL_JINLI = "JINLI";	//金立
static const std::string CHANNEL_HUAWEI = "HUAWEI";	//华为
static const std::string CHANNEL_MEIZU = "MEIZU";	//魅族

//一级渠道
static const std::string CHANNEL_9GAME = "9GAME";	//9游
static const std::string CHANNEL_QIHOO = "QIHOO";		//奇虎
static const std::string CHANNEL_YYB = "YYB";	//应用宝
static const std::string CHANNEL_BAIDUMOBILEGAME = "BAIDUMOBILEGAME";	//百度移动游戏
static const std::string CHANNEL_XIAOMI = "XIAOMI";	//小米

//二级渠道
static const std::string CHANNEL_4399 = "M4399";		//4399
static const std::string CHANNEL_DL = "DL"; //当乐
static const std::string CHANNEL_NUBIA = "NUBIA";		//努比亚
static const std::string CHANNEL_DOUYU = "DOUYU";		//斗鱼
static const std::string CHANNEL_ZHANQI = "ZHANQI";		//战旗
static const std::string CHANNEL_HTC = "HTC";		//HTC 聚乐
static const std::string CHANNEL_TOUTIAO = "TOUTIAO";	//今日头条

//二次元渠道
static const std::string CHANNEL_ACFUN = "ACFUN";	//AcFun
static const std::string CHANNEL_BILIBILI = "BILIBILI";	//哔哩哔哩
static const std::string CHANNEL_MUZHIWAN = "MUZHIWAN";	//拇指玩

//长尾渠道
static const std::string CHANNEL_BSCN = "BSCN"; //蓝叠
static const std::string CHANNEL_X7SY = "X7SY"; //小七手游
static const std::string CHANNEL_5FUNC = "5FUN";		//悟饭
static const std::string CHANNEL_SHUNWANG = "SHUNWANG";	//顺网
static const std::string CHANNEL_TT = "TT";	//TT语音
static const std::string CHANNEL_SAMSUNG = "SAMSUNG";	//三星
static const std::string CHANNEL_CCPLAY = "CCPLAY";	//虫虫游戏
static const std::string CHANNEL_LY = "LY";	//乐游

//接入渠道
static const std::string CHANNEL_LJ = "LJ";		//棱镜
static const std::string CHANNEL_HUOSU = "HUOSU";	//火速
static const std::string CHANNEL_YIJIE = "YIJIE";	//易接
static const std::string CHANNEL_ANYSDK = "ANYSDK";	//AnySdk

//支付币种 EPayCurrency
static const std::string PAY_CURRENCY_CNY = "CNY";	//人民币
static const std::string PAY_CURRENCY_USD = "USD";	//美元

//联网方式
enum EConnectionMode{
	CONNECTION_MODE_INVAILD = 0,

	CONNECTION_MODE_WIFI,

	CONNECTION_MODE_2G,
	CONNECTION_MODE_3G,
	CONNECTION_MODE_4G,
	CONNECTION_MODE_5G,

	CONNECTION_MODE_MAX,
};
