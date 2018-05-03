#pragma once

#include "Macro.h"
#include "unzip.h"

//Zip文件管理器

NS_TOOL_FRAME_BEGIN

class CZipFile
{
	//文件信息块
	struct XFileInfo
	{
		unz_file_pos	xPos;	//位置
		unz_file_info	xInfo;	//文件头
		std::string		sName;	//文件名
	};

	typedef std::map<std::string, XFileInfo> MapFilePos;
	//对压缩包操作
public:
	bool Open(const std::string& sFile, const std::string& sPassWord);		//Open后必须Close
	bool Close();															//关闭句柄 释放资源
	bool UnZipFile(const std::string& sDir);								//解压到指定目录
	bool Reset();															//重新打开 重建索引

	//对压缩包内的文件进行操作
public:
	bool OpenZipFile(const std::string& sFile);					//设置当前操作的文件为指定文件(压缩包内的名称)

	bool LoadData(void* pData, size_t uLen);							//加载解压后数据
	bool LoadData(const std::string& sFile,void* pData, size_t uLen);	//找到并加载数据

	const unz_file_info&	GetCurFileInfo()const;				//获取当前文件 文件信息
	const std::string&		GetCurFileName()const;				//获取当前文件 文件名
	uint32					GetCurFileUncompressedSize()const;	//获取当前文件 解压缩后文件大小

	//内部函数
private:
	bool ReadFirstFile();										//定位到第一个文件
	bool ReadNextFile();										//定位到下一个文件
	bool OpenCurFilePassword(const std::string& sPassword);		//OpenCurFile后 必须CloseCurFile
	bool CloseCurFile();
	bool ReadCurFile(void* pData, size_t uLen);					//读取当前文件数据
	bool MakeIndex();											//创建索引
public:
	CZipFile();
	CZipFile(const std::string& sFile,const std::string& sPassWord="");
	virtual ~CZipFile(void);
private:
	unzFile			_unzFile;		//文件句柄

	std::string		_sFileName;		//Zip文件名
	std::string		_sPassWord;		//Zip密码

	MapFilePos		_vFilePos;

	XFileInfo*		_pInfoCurrent;
};

NS_TOOL_FRAME_END
