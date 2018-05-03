#include "DeviceID.h"
#include "ToolFrame.h"
#include "MLoger.h"
#include "ApiIOS.h"

//由于IOS系统不存在一个公共目录供任何地方访问，但是IOS存在钥匙串 这个公共区域 供 用户写，因此可以利用这点开发

NS_TOOL_FRAME_BEGIN

CDeviceID::CDeviceID(void)
{
	_sFileName	= "DeviceID.sj";
	_sExtDir	= "System/";
	_uCount		= 40;
}

CDeviceID::~CDeviceID(void)
{

}

const std::string& CDeviceID::GetID() 
{
	if (!_sID.empty())return _sID;

	//查找所有区域
	_sID = FindStoredID();
	if (!_sID.empty()) {
		//写回所有区域
		StoreID(_sID);
		return _sID;
	}
		
	_sID = GenerateID();
	StoreID(_sID);
	return _sID;
}

bool CDeviceID::SetFileName(const std::string& sFileName)
{
	_sFileName = sFileName;
	return true;
}

bool CDeviceID::SetCharacter(const VectorString& vCharacter)
{
	_vCharacter = vCharacter;
	return true;
}

bool CDeviceID::SetCount(uint uCount)
{
	_uCount = uCount;
	return true;
}

const std::string& CDeviceID::GetFileName() const
{
	return _sFileName;
}

std::string CDeviceID::GenerateID()
{
	//如果没有字符集则初始化默认字符集
	if (_vCharacter.empty() && !InitDefaultCharacter())return "";

	std::stringstream sStream;
	//创建一个随机数
	for (uint uIndex=0;uIndex<_uCount;++uIndex)
	{
		sStream<<ToolFrame::RandValue(_vCharacter);
	}

	return sStream.str();
}

std::string CDeviceID::GenerateCRC(const std::string& sID)
{
	uint32 uCRC = 0xCBCEBCAA;
	std::string::const_iterator itr;
	foreach(itr, sID) {
		char ch = *itr;
		uCRC += ch;
		uCRC ^= ch;
		uCRC += ch;
	}
	return ToolFrame::ToString(uCRC);
}

std::string CDeviceID::CheckStoredID(const std::string& sString)
{
	VectorString vString;
	ToolFrame::SplitString(vString, sString, "\n");
	if (vString.size() != 2)return "";

	std::string sCRC = GenerateCRC(vString[0]);
	if (sCRC != vString[1])
		return "";

	return vString[0];
}

std::string CDeviceID::FindStoredID()
{
	
#if MACRO_TARGET_OS == MACRO_OS_IOS
	//先从钥匙串读 再 从 本地读
	std::string sID = CheckStoredID(ApiIOS::ReadChain("TFSystemDeviceID"));
	if (!sID.empty())return sID;

	return CheckStoredID(ToolFrame::LoadFile(_sFileName, DIR_TYPE_ARCHIVE));
#endif

	//按照 公共目录，存档目录的顺序依次查找
	//std::string sID = CheckStoredID(ToolFrame::LoadFile(_sExtDir + _sFileName, DIR_TYPE_EXT_ROOT));
	//if (!sID.empty())return sID;

	//return CheckStoredID(ToolFrame::LoadFile(_sFileName, DIR_TYPE_ARCHIVE));
}

bool CDeviceID::StoreID(const std::string& sID)
{
	if (sID.empty())return false;

	std::string sCRC = GenerateCRC(sID);
	ASSERT_LOG_ERROR(!sCRC.empty());

	std::stringstream sStream;
	sStream << sID << "\n" << sCRC;

	std::string sStore = sStream.str();
	

#if MACRO_TARGET_OS == MACRO_OS_IOS
	ApiIOS::StoreChain("TFSystemDeviceID", sStore);
	ToolFrame::SaveFile(_sFileName, sStore, DIR_TYPE_ARCHIVE);
	return true;
#endif

	ToolFrame::SaveFile(_sExtDir + _sFileName, sStore, DIR_TYPE_EXT_ROOT);
	ToolFrame::SaveFile(_sFileName, sStore, DIR_TYPE_ARCHIVE);
	return true;
}

bool CDeviceID::InitDefaultCharacter()
{
	_vCharacter.clear();

	//插入数字 '0'-'9'
	for (uint uIndex = 0;uIndex<10;++uIndex)
	{
		char ch = '0' + uIndex;
		ToolFrame::InsertString(_vCharacter, ch);
	}

	//插入字母 'a'-'z'
	for (uint uIndex = 0; uIndex < 26; ++uIndex)
	{
		char ch = 'a' + uIndex;
		ToolFrame::InsertString(_vCharacter, ch);
	}

	return true;
}

NS_TOOL_FRAME_END
