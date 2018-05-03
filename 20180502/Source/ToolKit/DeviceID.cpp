#include "DeviceID.h"
#include "ToolFrame.h"
#include "MLoger.h"
#include "ApiIOS.h"

//����IOSϵͳ������һ������Ŀ¼���κεط����ʣ�����IOS����Կ�״� ����������� �� �û�д����˿���������㿪��

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

	//������������
	_sID = FindStoredID();
	if (!_sID.empty()) {
		//д����������
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
	//���û���ַ������ʼ��Ĭ���ַ���
	if (_vCharacter.empty() && !InitDefaultCharacter())return "";

	std::stringstream sStream;
	//����һ�������
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
	//�ȴ�Կ�״��� �� �� ���ض�
	std::string sID = CheckStoredID(ApiIOS::ReadChain("TFSystemDeviceID"));
	if (!sID.empty())return sID;

	return CheckStoredID(ToolFrame::LoadFile(_sFileName, DIR_TYPE_ARCHIVE));
#endif

	//���� ����Ŀ¼���浵Ŀ¼��˳�����β���
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

	//�������� '0'-'9'
	for (uint uIndex = 0;uIndex<10;++uIndex)
	{
		char ch = '0' + uIndex;
		ToolFrame::InsertString(_vCharacter, ch);
	}

	//������ĸ 'a'-'z'
	for (uint uIndex = 0; uIndex < 26; ++uIndex)
	{
		char ch = 'a' + uIndex;
		ToolFrame::InsertString(_vCharacter, ch);
	}

	return true;
}

NS_TOOL_FRAME_END
