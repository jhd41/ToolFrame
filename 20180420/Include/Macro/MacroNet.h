#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "MLoger.h"

//网络错误代号
//备注:例如这里分连接失败 和 请求连接失败。
//区别是 请求连接失败 是代表 连接并没有执行 因其他异常而失败了。这通常是代码里有BUG
//连接失败 是代表 执行过连接之后 因为 网络或者 这种不可控因素 而失败了。这通常是不可抗力,非代码级别问题，例如 网线根本没接好
enum ENetErrCode{
	NET_ERRCODE_INVAILD=0,
	NET_ERRCODE_ACTIVE,				//主动断开
	NET_ERRCODE_CONNECT,			//连接失败
	NET_ERRCODE_RECV,				//接收失败
	NET_ERRCODE_SEND,				//发送失败
	NET_ERRCODE_REQ_RECV,			//请求接收失败
	NET_ERRCODE_REQ_SEND,			//请求发送失败
	NET_ERRCODE_REQ_CLOSE,			//请求关闭
	NET_ERRCODE_REQ_SEND_BUFF_FULL,	//发送缓冲区满
	NET_ERRCODE_REQ_RECV_BUFF_FULL,	//接收缓冲区满
	NET_ERRCODE_LENGTH_LIMIT,		//长度超过极限
	NET_ERRCODE_VAILD_PACK,			//无效包
	NET_ERRCODE_RECVED_ERR,			//上层收包处理返回错误
	NET_ERRCODE_HEART_TIMEOUT,		//(上层逻辑)心跳超时
	NET_ERRCODE_USER_RECONNECT_FAILD,//(上层逻辑)自动重连失败
	NET_ERRCODE_REFUSED,			//(上层逻辑)服务器拒绝服务

	NET_ERRCODE_MAX,
};

//连接类型
enum ELinkType{
	LINK_TYPE_INVAILD = 0,
	LINK_TYPE_NET_TCP,	//互联网Tcp方式连接
	LINK_TYPE_NET_UDP,	//互联网Udp方式连接
	LINK_TYPE_MEM,		//内存
	LINK_TYPE_BLUETOOTH,//蓝牙
	LINK_TYPE_MAX,
};

