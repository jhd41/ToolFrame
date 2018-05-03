#pragma once
#include "Macro.h"

//���ڻ�ȡMac��ַ��Api�����ϵͳ���ڱ�����˽�����ɽ��ã���˲��÷ǳ��򵥵�������ķ�ʽ�������
//��������ɳ�ײ���ʼ��͵�һ������ַ���DeviceID������Ψһʶ���豸
//���ɵ�ID�� ���洢�� �浵Ŀ¼ �Լ� ����Ŀ¼����
//�� ����Ŀ¼��浵Ŀ¼�洢��ID��һ�£��� ����Ŀ¼Ϊ׼ ��Ϊ����Ŀ¼����Ψһ��ȱ���� ���Ա��ⲿ�޸� �����Դ浵Ŀ¼Ϊ׼�������App�Ĵ浵Ŀ¼�����Լ����豸ID �ţ��� �豸Ψһ�� ʵ�ʱ��ܿ�
 
NS_TOOL_FRAME_BEGIN

class CDeviceID
{
public:
	const std::string&	GetID();										//��ȡΨһʶ����
	bool				SetFileName(const std::string& sFileName);		//���ñ���Ĵ浵�ļ�����
	bool				SetCharacter(const VectorString& vCharacter);	//����������ַ���
	bool				SetCount(uint uCount);							//�������������(Ĭ��40)
public:
	const std::string& GetFileName()const;
private:
	std::string GenerateID();		//ʵ������ID
	std::string GenerateCRC(const std::string& sID);//����CRCУ����
	std::string FindStoredID();		//���Ҵ洢��ID
	bool		StoreID(const std::string& sID);//�洢ID
	bool		InitDefaultCharacter();//��ʼ��Ĭ���ַ���
	std::string CheckStoredID(const std::string& sString);//���CRC�Ƿ���ȷ�������ȷ����ID
public:
	CDeviceID(void);
	virtual ~CDeviceID(void);
private:
	std::string		_sID;		//ID
	std::string		_sFileName;	//�ļ���
	std::string		_sExtDir;	//��չ�洢���ļ�������
	VectorString	_vCharacter;//�ַ���
	uint			_uCount;	//�������
};

NS_TOOL_FRAME_END
