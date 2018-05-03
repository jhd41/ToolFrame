#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//��ע:
//������Ψһִ���࣬����ֻ�ڵ�һ������ʱ����ʲô�ı�ǡ�

NS_TOOL_FRAME_BEGIN
class CMark
{
public:
	bool IsMarked(int nMark = INVALID_ID)const;
	bool TryMark(int nMark = INVALID_ID);//���Ա�ǵ�һ��ִ�У�����flase�����Ѿ�ִ�й�
	bool Clear(int nMark = INVALID_ID);
	bool ClearAll();
public:
	CMark(void);
	virtual ~CMark(void);
private:
	SetInt _vMark;
	mutable CMutexReadWrite _mutex;
};

NS_TOOL_FRAME_END
