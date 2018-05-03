#pragma once
#include "Macro.h"

//由于获取Mac地址的Api逐个被系统出于保护隐私的理由禁用，因此采用非常简单的随机数的方式进行随机
//该类会生成冲撞几率极低的一个随机字符串DeviceID，用于唯一识别设备
//生成的ID会 被存储在 存档目录 以及 公共目录区域
//若 公共目录与存档目录存储的ID不一致，以 公共目录为准 因为公共目录才是唯一，缺点是 可以被外部修改 但若以存档目录为准，若多个App的存档目录都有自己的设备ID 号，则 设备唯一性 实质被架空
 
NS_TOOL_FRAME_BEGIN

class CDeviceID
{
public:
	const std::string&	GetID();										//获取唯一识别码
	bool				SetFileName(const std::string& sFileName);		//设置保存的存档文件名称
	bool				SetCharacter(const VectorString& vCharacter);	//设置随机的字符集
	bool				SetCount(uint uCount);							//设置随机的数量(默认40)
public:
	const std::string& GetFileName()const;
private:
	std::string GenerateID();		//实际生成ID
	std::string GenerateCRC(const std::string& sID);//生成CRC校验码
	std::string FindStoredID();		//查找存储的ID
	bool		StoreID(const std::string& sID);//存储ID
	bool		InitDefaultCharacter();//初始化默认字符集
	std::string CheckStoredID(const std::string& sString);//检查CRC是否正确，如果正确返回ID
public:
	CDeviceID(void);
	virtual ~CDeviceID(void);
private:
	std::string		_sID;		//ID
	std::string		_sFileName;	//文件名
	std::string		_sExtDir;	//扩展存储器文件夹名称
	VectorString	_vCharacter;//字符集
	uint			_uCount;	//随机数量
};

NS_TOOL_FRAME_END
