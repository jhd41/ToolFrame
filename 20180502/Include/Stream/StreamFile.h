#pragma once
#include "Macro.h"
#include "IStreamBase.h"
#include "StreamBinary.h"

//�ļ���.������һ�������Ĳ���,�������׼�ļ�����ͬ���Ǳ���֧�ֿ�ƽ̨

NS_TOOL_FRAME_BEGIN

class CStreamFile
	:public CStreamBinary
{
public:
	enum EOperator{
		OP_INVAID=0,
		OP_IN,	//��ȡ�ļ�
		OP_OUT,	//д�ļ�
		OP_MAX,
	};

	//���ɱ�����
	NO_COPY_VIRTUAL(CStreamFile);
public:
	bool Open(const std::string& sPath,EOperator eOp, int eDirType = DIR_TYPE_INVALID);//Ĭ�ϴ򿪿�дĿ¼ �����ļ��洢
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
