#pragma once

#include "Macro.h"
#include "unzip.h"

//Zip�ļ�������

NS_TOOL_FRAME_BEGIN

class CZipFile
{
	//�ļ���Ϣ��
	struct XFileInfo
	{
		unz_file_pos	xPos;	//λ��
		unz_file_info	xInfo;	//�ļ�ͷ
		std::string		sName;	//�ļ���
	};

	typedef std::map<std::string, XFileInfo> MapFilePos;
	//��ѹ��������
public:
	bool Open(const std::string& sFile, const std::string& sPassWord);		//Open�����Close
	bool Close();															//�رվ�� �ͷ���Դ
	bool UnZipFile(const std::string& sDir);								//��ѹ��ָ��Ŀ¼
	bool Reset();															//���´� �ؽ�����

	//��ѹ�����ڵ��ļ����в���
public:
	bool OpenZipFile(const std::string& sFile);					//���õ�ǰ�������ļ�Ϊָ���ļ�(ѹ�����ڵ�����)

	bool LoadData(void* pData, size_t uLen);							//���ؽ�ѹ������
	bool LoadData(const std::string& sFile,void* pData, size_t uLen);	//�ҵ�����������

	const unz_file_info&	GetCurFileInfo()const;				//��ȡ��ǰ�ļ� �ļ���Ϣ
	const std::string&		GetCurFileName()const;				//��ȡ��ǰ�ļ� �ļ���
	uint32					GetCurFileUncompressedSize()const;	//��ȡ��ǰ�ļ� ��ѹ�����ļ���С

	//�ڲ�����
private:
	bool ReadFirstFile();										//��λ����һ���ļ�
	bool ReadNextFile();										//��λ����һ���ļ�
	bool OpenCurFilePassword(const std::string& sPassword);		//OpenCurFile�� ����CloseCurFile
	bool CloseCurFile();
	bool ReadCurFile(void* pData, size_t uLen);					//��ȡ��ǰ�ļ�����
	bool MakeIndex();											//��������
public:
	CZipFile();
	CZipFile(const std::string& sFile,const std::string& sPassWord="");
	virtual ~CZipFile(void);
private:
	unzFile			_unzFile;		//�ļ����

	std::string		_sFileName;		//Zip�ļ���
	std::string		_sPassWord;		//Zip����

	MapFilePos		_vFilePos;

	XFileInfo*		_pInfoCurrent;
};

NS_TOOL_FRAME_END
