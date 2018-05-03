#pragma once

#include "Macro.h"
#include "HTimeOut.h"
#include "TimeBar.h"
#include "TimeOut.h"
#include "TThreadSaftyMap.h"
#include "TimeElapse.h"
#include "TThreadSaftyList.h"

//��ʱ����
//����:
//��ӦƵ�����ɾ��������,��Ч�ĳ�ʱ�ص���
//ʱ������Ϊ����
//1.x��֮��ʱ ֻҪ����ͬ�����ĳ�ʱ�����綼��5�룬�����ĵ�ʱ��ƬΪ1������ ���� ��ͬ���������� ����ʱ�䡣
//2.x��ʱ��ʱ ֻҪ����ͬ��ʱ���ĳ�ʱ�����綼��9�㣬�����ĵ�ʱ��ƬΪ1.���� ���� ��ͬ��ʱ������ ���Ӳ���ʱ��,����ѭ��ʱ������ʱ��Ƭ��ȻΪ1.
//����Ϊx��֮��ʱ��ʵ�֣�
//ע��:�����Ч�ʺͳ�ʱ��ʱ���������й�,�͸����޹ء�
//��νʱ�������� ���� ��ʱ��ʱ��,���綼��5�볬ʱ����ô�����г�ǧ����� Ч����Ȼ���Ա�֤��
//��5���10�볬ʱ��ʱ��������������ͬ�������ʱ������
//˼·:
//�ο�����ɱtimebar�����д��֮��õ�����˼·�ͽ���
//��ʱ���з����㣬��һ�� ��map��Ϊtimebar������������1��Ϊʱ��������100��Ҳ����100��timebar��
//ÿ��timebar���涼��һ��list��
//���߼������һ��ʱ��ڵ�ʱ,����5�룬�������ҵ�5���timebar,Ȼ���ȡ��ǰʱ��,����timebar�����list��ĩβ��
//ɾ����ʱ�� ��������ɾ����ԭ�򣬽����Ƕ�node����һ��ɾ����ǡ�
//ϵͳ����process��ʱ��,������ǰ���е�timebar,timebar����ж�list�ڲ��ڵ�ĳ�ʱʱ���ͷ��ʼ�ж��Ƿ�ʱ,
//����ʱ������ص�����û��ʱ���򷵻�,���ٽ��жԵ�ǰlist���г�ʱ�жϡ��������ⲿ����һ��timebar��ͬ���Ĳ�����
//����:
//Map�����߱����ҿ��,��չ��ǿ���ŵ�,���ǲ��� ɾ���ǳ������������Ⱦͽ�����100��timebar,�Ժ�ֻ�в��Ҳ�����û�в����ɾ����
//timebar�ڲ�list������Ϊ��һ��һ�ε�,����5�볬ʱ,����Ķ���5��֮��Ҫ��ʱ�Ľڵ㣬���ǲ����ʱ��ȴ�ǲ�һ���ġ���� ���Ա�֤ ǰ������ ��Ȼ�Ⱥ��������ȳ�ʱ��
//���Ǽ��������Լ����뷨������mulitmap��ʱ���������Ȼ���ǰ����ʱ���㡣
//������������ʵ��Ƶ����ÿ�ζ�map�Ĳ���ɾ������ƽ��������Ĺ����滻Ϊ�ȶ���ÿ��100��timebar�ı�����
//��һ������map��find��list��push,pop��������������������Ƶ���Ķ�������

NS_TOOL_FRAME_BEGIN

typedef CSharePtr<CTimeBar>		CTimeBarPtr;
class CTimeOutQueue;

enum ETimeMode
{
	TIME_MODE_INVAILD,
	TIME_MODE_REAL,		//��ʵʱ��
	TIME_MODE_SEQ,		//˳��ʱ��
	TIME_MODE_MAX,
};

class ITimeOutQueue
{
public:
	virtual uint64	GetTimeNow()const;
	virtual uint64	SetTimeNow(uint64 uTimeNow);
	virtual int		GetTimeMode()const;
	virtual bool	Pause();	//��ͣ
	virtual bool	Resume();	//�ظ�
public:
	virtual CTimeOutQueue* GetTimeOutQueue()const;
	virtual bool	SetTimeOutQueue(CTimeOutQueue* pTimeOutQueue);
public:
	ITimeOutQueue();
	virtual ~ITimeOutQueue();
protected:
	int				_eTimeMode;			//ʱ��ģʽ
	CTimeOutQueue*	_pTimeOutQueue;
};

//////////////////////////////////////////////////////////////////////////
class CTimeOutQueueReal
	:public ITimeOutQueue
{
public:
	virtual uint64	GetTimeNow()const;
	virtual bool	Pause();	//��ͣ
	virtual bool	Resume();	//�ظ�
public:
	CTimeOutQueueReal();
	virtual ~CTimeOutQueueReal();
private:
	CTimeElapse		_tTimeElapse;		//��ͣʱ��
};
//////////////////////////////////////////////////////////////////////////
class CTimeOutQueueSeq
	:public ITimeOutQueue
{
public:
	virtual uint64	GetTimeNow()const;
	virtual uint64	SetTimeNow(uint64 uTimeNow);
	virtual bool	Pause();	//��ͣ
	virtual bool	Resume();	//�ظ�
public:
	CTimeOutQueueSeq();
	virtual ~CTimeOutQueueSeq();
private:
	uint64			_uSeqTimeNow;		//˳��ʱ�� ��ǰʱ��
};

//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL CTimeOutQueue
{
public:
	typedef TThreadSaftyMapValue<uint64,CTimeBarPtr>	MapTimeBar;
	typedef TThreadSaftyListValue<CTimeNodePtr>		QueueTimeOut;
	//�߼�����
public:
	CTimeNodePtr	CreateTimerByAfterSec(HTimeOut* pCallBack,time_t uTimeAfter,bool bLoop = false,time_t uTimeDelay=0);			//(���� ������֮��ʱ)��ȷ����
	CTimeNodePtr	CreateTimerByAfterMil(HTimeOut* pCallBack,UINT64 uTimeAfter,bool bLoop = false,UINT64 uTimeDelay=0);			//��ȷ������
	CTimeNodePtr	CreateTimerByPointSec(HTimeOut* pCallBack,time_t uTimePoint,bool bLoop = false,UINT64 uTimeDelay=0);//(���� ʲôʱ��� ��ʱ)��ȷ����
	CTimeNodePtr	CreateTimerByPointMil(HTimeOut* pCallBack,UINT64 uTimePoint,bool bLoop = false,UINT64 uTimeDelay=0);//��ȷ������
	bool			RemoveTimer(CTimeNodePtr& pTimeNode);
	
	bool			Pause();	//��ͣ
	bool			Resume();	//�ظ�
	bool			IsPausing()const;//�Ƿ�����ͣ��
	bool			ClearEmptyTimebar();	//������õ�ʱ������������

	uint64			SetModeTimeNow(uint64 uTimeNow);
	uint64			GetModeTimeNow()const;	//��ȡģʽ�µ�ǰʱ��			

	bool			SetInterface(ETimeMode eTimeMode);	//����ʱ��ģʽ(Ĭ��:��ʵʱ��)
	bool			SetInterface(ITimeOutQueue* pTimeOutQueue);

	ITimeOutQueue*	GetInterface()const;
	int				GetTimeMode()const;
	
	//ϵͳ����
public:
	bool		ProcessTestTimeOut(uint64 uTimeProcess);						//��������Ƿ�ʱ�Ե�ǰʱ����Ϊ�ο�ʱ��(�����Ƿ�ʱ)
	bool		ProcessTestTimeOut(uint64 uTimeNow,uint64 uTimeProcess);		//��������Ƿ�ʱ(�����Ƿ�ʱ)
	bool		ProcessTimeOut(uint64 uTimeProcess);							//�����Ѿ���ʱ�Ķ���(�����Ƿ������ȷ����)

	//�ⲿ��Ҫ����
	friend class CTimeBar;
private:
	bool		AddTimerAfter(CTimeNodePtr& pTimeNode,UINT64 uTimeAfter);
	bool		AddTimerPoint(CTimeNodePtr& pTimeNode,UINT64 uTimePoint);
	
	bool		ClearEmptyTimebarAfter();
	bool		ClearEmptyTimebarPoint();
	
	bool		ProcessTestTimeOutAfter( uint64 uTimeNow,const CTimeOut& tTimeOut );
	bool		ProcessTestTimeOutPoint( uint64 uTimeNow,const CTimeOut& tTimeOut );
	bool		ClearTimeOutTimeBarPoint(uint64 uTimeNow);//����Ѿ���ʱ��ʱ�����

	bool		AddTimeOut(CTimeNodePtr ptr);

	bool		DeleteInterface();
public:
	bool		ResumeAfter(uint64 uTimePaused);
	bool		ResumePoint(uint64 uTimePaused);
public:
	CTimeOutQueue(void);
	virtual ~CTimeOutQueue(void);
private:
	MapTimeBar		_vTimeBarAfter;		//���ڽ����еĽڵ����
	MapTimeBar		_vTimeBarPoint;		//���ڽ����еĽڵ����
	QueueTimeOut	_vTimeOut;			//�Ѿ���ʱ�Ľڵ�

	ITimeOutQueue*	_pTimeOutQueue;		//�ӿ�
	bool			_bPaused;			//��ͣ���
};

NS_TOOL_FRAME_END
