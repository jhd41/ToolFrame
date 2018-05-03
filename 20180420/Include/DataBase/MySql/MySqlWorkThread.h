#pragma once

#include "MacroMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "MySqlClient.h"
#include "IThreadTask.h"
#include "IThreadNew.h"
#include "HMySql.h"

NS_TOOL_FRAME_BEGIN

//���ݿ��߳�
class CMySqlWorkThread
	:public IThreadNew
{
public:
	virtual bool SetHandler(HMySql* hHandler);
	virtual bool SetDataBase(const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd);
	virtual bool SetTimeWaitConnect(uint uTime);//���ӵȴ�ʱ��
	virtual bool SetTimeExcute(uint uTime);		//����ִ��ʱ��
	virtual uint GetTimeWaitConnect()const;
	virtual uint GetTimeExcute()const;
public:
	const CMySqlClient& GetDbClient()const;
private:
	virtual	bool InitThread();
	virtual bool RunOnceThread();//ϵͳ����
private:
	virtual bool QuerySql();//��ѯSql ���� �Ƿ���SQL��ִ��
public:
	CMySqlWorkThread(void);
	virtual ~CMySqlWorkThread(void);
private:
	CMySqlClient	_dbClient;
	CMySqlResults	_dbRecord;			//�����
	HMySql*			_hHandler;			//������
	uint			_uTimeWaitConnect;	//���ӵȴ�ʱ��
	uint			_uTimeExcute;		//����ִ��ʱ��
};

NS_TOOL_FRAME_END


#endif
