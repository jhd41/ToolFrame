#pragma once

#include "Macro.h"
#include "HTimeOut.h"
#include "TThreadSaftyList.h"

NS_TOOL_FRAME_BEGIN
class CTimeOutQueue;
class CTimeBar
{
	typedef TThreadSaftyListValue<CTimeNodePtr> QueueTime;
public:
	bool		IsEmpty()const;
	bool		PushTime(CTimeNodePtr& pTime);
	bool		AddOutTime(uint64 uTimePaused);//���ӳ�ʱʱ��

	//ϵͳ����
public:
	bool		Process(uint64 uTimeNow,uint64 uTimeProcess);//���� ��ʱ���������Ƿ� ����Ҫ��������
public:
	CTimeBar(void);
	virtual ~CTimeBar(void);
private:
	QueueTime	_vQueue;
private:
	CFIELD_PTR(CTimeOutQueue*,Parent,p);
};

NS_TOOL_FRAME_END
