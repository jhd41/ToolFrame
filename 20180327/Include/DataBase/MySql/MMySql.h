#pragma once

#include "MacroMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "TThreadSaftyList.h"
#include "TThreadSaftyMap.h"
#include "IMySqlProcess.h"
#include "ThreadGroup.h"
#include "CalCounter.h"
#include "MySqlWorkThread.h"
#include "TimeAvg.h"

NS_TOOL_FRAME_BEGIN

class MMySql
	:public HMySqlLog
{
	typedef TThreadSaftyListValue<IMySqlQueryPtr>			QueueRequest;
	typedef TThreadSaftyMapValue<std::string,QueueRequest>	MapRequest;

public:
	ST_INTANCE(MMySql);
public:
	IMySqlQueryPtr Query( IMySqlQueryPtr pQuery);
	IMySqlQueryPtr Query(const std::string& sDataBaseName,const std::string& sSql,IMySqlProcess* pDBProcess = nullptr);

	uint		 GetQueryCount()const;		//��ȡ��ѯ�е�����
	uint		 GetQueryTotal()const;		//��ȡ��ɲ�ѯ����
	uint		 GetQueryAvgTime()const;	//��ȡƽ��ִ��ʱ��	
	bool		 IsEmpty()const;			//�Ƿ��ת(������� �����߳̾�Ϊ��)
public:
	bool			Init();
	bool			AddDataBase(const std::string& sIp,uint uPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd,uint uConcurrent);//���һ�����ݿ� Ҫ�� ���ݿ����Ʋ����ظ�

	//�ⲿ��Ҫ����
public:
	IMySqlQueryPtr	Pop(const std::string& sDataBaseName);
	IMySqlQueryPtr	Push(IMySqlQueryPtr pQuery);		//ѹ���β
	IMySqlQueryPtr	PushFront(IMySqlQueryPtr pQuery);	//ѹ�����

	bool			OnQueryOver(IMySqlQueryPtr pSqlQuery);
public:
	MMySql(void);
	virtual ~MMySql(void);
private:
	MapRequest		_vRequest;
	CThreadGroup	_vThread;
	CCalCounter		_uQuerying;	//ִ���е�����
	CCalCounter		_uTotal;	//�ܹ���ɵ�����
	CTimeAvg		_uTimeAvg;	//ƽ��ִ��ʱ��
private:
	CFIELD_PTR(IMySqlProcess*,Process,p);
	CFIELD_PTR(HMySql*,Handler,h);
};

NS_TOOL_FRAME_END

#endif
