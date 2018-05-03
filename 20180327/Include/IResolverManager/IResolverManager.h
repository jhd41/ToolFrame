#pragma once

#include "MacroResolver.h"

#include "IResolver.h"
#include "HTimeOut.h"
#include "TimeOutQueue.h"

//������������
//ά�ֽ������Ķ�ջ�ṹ Ĭ��ʹ�� ȫ�ֳ�ʱ����

NS_TOOL_FRAME_BEGIN

class HResolverManager{
public:
	virtual bool OnResolveTimeOut		(IResolverManager* pMgrResolver, const CTimeNodePtr& pTimeNode);						//���㳬ʱ(�����Ƕ��̻߳ص�)
	virtual bool OnResolveOver			(IResolverManager* pMgrResolver);						//�������
public:
	virtual bool OnResolveErrTimeOut	(IResolverManager* pMgrResolver, IResolver* pAc);	//��������ʱû�б���ȷ����
	virtual bool OnResolveErrLoop		(IResolverManager* pMgrResolver, IResolver* pAc);	//������ѭ������
	virtual bool OnResolveErrOutOfSize	(IResolverManager* pMgrResolver, IResolver* pAc);	//���������������涨��С(���ݹ�)
	virtual bool OnResolveErrEmpty		(IResolverManager* pMgrResolver, IResolver* pAc);	//�������ѿ�
	virtual bool OnResolveErrProcessTimeOut(IResolverManager* pMgrResolver, IResolver* pAc);//����������ʱ ������ѭ����
public:
	HResolverManager(){}
	virtual ~HResolverManager(){}
};

class HResolverManagerLog 
	:public HResolverManager
{
public:
	virtual bool OnResolveErrTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)override;		//��������ʱû�б���ȷ����
	virtual bool OnResolveErrLoop(IResolverManager* pMgrResolver, IResolver* pAc)override;			//������ѭ������
	virtual bool OnResolveErrOutOfSize(IResolverManager* pMgrResolver, IResolver* pAc)override;		//���������������涨��С(���ݹ�)
	virtual bool OnResolveErrEmpty(IResolverManager* pMgrResolver, IResolver* pAc)override;			//�������ѿ�
	virtual bool OnResolveErrProcessTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)override;//����������ʱ ������ѭ����
public:
	HResolverManagerLog() {}
	virtual ~HResolverManagerLog() {}
};

class IResolverManager
	:public HTimeOut
	,public HResolver
	,public HResolverManagerLog
{
	friend class IResolver;
public:
	bool				SetHandler(HResolverManager* hHandler);
	bool				SetResolverSizeMax(uint uResolverSizeMax);			//���ý��������������� Ĭ��50
	bool				SetProcessNeverTimeout(bool bNeverTimeOut = true);	//���ý���������ʱ(Ĭ��:Debug���� Release�ر�)

	template<typename T>
	T*					CreateTopResolver(IResolver* pAcParent);

	virtual bool		Process(uint64 uMillSeconds = 3000);	//����ֱ��ʱ�䲻��(0Ϊ����ʱ��)
	virtual bool		ProcessOne(uint64 uMillSeconds = 3000);	//����һ���׶� �����Ƿ���(����Flase���� ����Ҫ����)
	virtual bool		IsProcessed()const;						//�Ƿ��Ѿ��������

	virtual bool		Close();								//ֻ�ܵ���һ��,�����Ƿ����ɾ��(ͨ���ⲿ���ù���)
	virtual bool		IsEmpty()const;							//�������ѿ�
	virtual size_t		GetResolverSize()const;					//��ȡ����������
	virtual size_t		GetResolverSizeMax()const;				//��ȡ���������޸���

	virtual bool		ResolveTimeOut(const CTimeNodePtr& pTimeNode);	//���㳬ʱ(������������ʲô)
	virtual bool		TimeOut();										//ִ�г�ʱ����(������������ʲô)

	virtual CTimeOutQueue*			GetGlobalTimeOutQueue();		//��ȡȫ��ʱ����
	virtual const CTimeOutQueue*	GetGlobalTimeOutQueue()const;	//��ȡȫ��ʱ����
	virtual CTimeOutQueue*			GetLocalTimeOutQueue();			//��ȡ����ʱ����
	virtual const CTimeOutQueue*	GetLocalTimeOutQueue()const;	//��ȡ����ʱ����

	virtual bool		SetUserPtr(void* pUserPtr);
	template<typename T>
	T*					GetUserPtr()const;
	
	//����ʱ��
public:
	virtual bool		LocalTimeProcess(uint64 uMillSeconds = 0);//����ʱ�� �����Ƿ� ���账��(true ��Ҫ��false ����Ҫ) (��ʹ��ϵͳʱ�䣬�����账��)
	virtual bool		LocalPause();				//ʱ����ͣ
	virtual bool		LocalResume();				//ʱ�����
	virtual uint64		LocalSetTimeNow(uint64 uTimeNow);//���õ�ǰʱ��	
	virtual uint64		LocalGetTimeNow()const;

	//ȫ��ʱ��
public:
	//����(�ⲿ����ʱ ������)
	virtual IResolver*	FindTopResolver()const;		//��ȡջ���Ľ�����
	virtual IResolver*	FindRootResolver()const;	//��ȡջ�׵Ľ�����
	virtual bool		WaitSeconds(int nSeconds);	//�ȴ�N�� ��0Ҳ�����̳�ʱ
	virtual bool		WaitSeconds(float fSeconds);//�ȴ�N�� ���� 4.5��
	virtual bool		WaitMillSec(uint64 uMillSec);//�ȴ�������
	virtual bool		WaitForever();				//��Զ�ȴ�
	virtual bool		ClearWait();
	virtual bool		IgnoreCheckResolve();		//���κ��Լ��(��������׶�ѭ��)
	virtual bool		MarkResolveOver();			//��ǽ����Ѿ����
	virtual bool		IsResolveOver()const;		//�жϽ����Ƿ����
private:
	CFIELD_BOOL(Waiting);
	CFIELD_BOOL(CheckResolve);//���׶��Ƿ�ı�
protected:
	virtual bool		RemoveResolver(IResolver* pAction);
	virtual	bool		RemoveTimer();
	template<typename T>
	T*					CreateResolver(IResolver* pAcParent);
	virtual	bool		DestoryResolver(IResolver* pResolver);
	virtual bool		CallBackResolveOver();							//�������

	//IResolve����
protected:
	virtual bool PushResolver(IResolver* pAction,IResolver* pParent,bool bReset = true);
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);	//��һ�߳����

	//������Ը��Ǹ���ĺ���
protected:
	virtual bool OnResolverCreate(IResolver* pResolver);
	virtual bool OnResolverDestory(IResolver* pResolver);
	virtual bool OnResolverResetResolve(IResolver* pResolver);

public:
	IResolverManager(void);
	virtual ~IResolverManager(void);
protected:
	VectorResolverEx		_vResolver;
	size_t					_uResolverSizeMax;
	CTimeNodePtr			_pGlobalTimer;
	
	bool					_bResolveOver;
	bool					_bCallBackOver;

	void*					_pUserPtr;

	CTimeOutQueue			_xLocalTimeOutQueue;//�����ĳ�ʱ����
	HResolverManager*		_hHandler;
	bool					_bProcessNeverTimeout;
};

template<typename T>
T* IResolverManager::GetUserPtr()const
{
	return static_cast<T*>(_pUserPtr);
}

template<typename T>
T* IResolverManager::CreateTopResolver(IResolver* pAcParent)
{
	T* pResolver = CreateResolver<T>(pAcParent);
	if (!pResolver)return nullptr;
	
	PushResolver(pResolver,pAcParent);
	return pResolver;
}

template<typename T>
T* IResolverManager::CreateResolver(IResolver* pAcParent)
{
	T* pResolver = new T();
	if (!pResolver)return nullptr;
	pResolver->SetManagerCreate(true);
	pResolver->SetResolverMgr(this);
	pResolver->SetParent(pAcParent);
	return pResolver;
}

NS_TOOL_FRAME_END
