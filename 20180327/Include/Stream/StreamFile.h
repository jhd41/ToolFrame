#pragma once
#include "Macro.h"
#include "IStreamBase.h"
#include "StreamBinary.h"

//文件流.本类是一个对流的补充,本类与标准文件流不同的是本类支持跨平台

NS_TOOL_FRAME_BEGIN

class CStreamFile
	:public CStreamBinary
{
public:
	enum EOperator{
		OP_INVAID=0,
		OP_IN,	//读取文件
		OP_OUT,	//写文件
		OP_MAX,
	};

	//不可被拷贝
	NO_COPY_VIRTUAL(CStreamFile);
public:
	bool Open(const std::string& sPath,EOperator eOp, int eDirType = DIR_TYPE_INVALID);//默认打开可写目录 方便文件存储
	bool Close();
public:
	CStreamFile(void);
	CStreamFile(const std::string& sPath,EOperator eOp, int eDirType = DIR_TYPE_INVALID);
	virtual ~CStreamFile(void);
private:
	std::string	 _sPath;
	int			 _eDirType;
	EOperator	 _eOp;
};

NS_TOOL_FRAME_END
