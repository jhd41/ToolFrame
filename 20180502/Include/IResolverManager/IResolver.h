#pragma once

#include "MacroResolver.h"

NS_TOOL_FRAME_BEGIN
class IResolver;
class HResolver{
public:
	virtual bool OnResolverCreate(IResolver* pResolver){return true;}
	virtual bool OnResolverDestory(IResolver* pResolver){return true;}
	virtual bool OnResolverResetResolve(IResolver* pResolver){return true;}
public:
	HResolver(){}
	virtual ~HResolver(){}
};

class IResolver
{
	enum 
	{
		RESOLVER_BASE_INIT,
		RESOLVER_BASE_MAX,
	};
public:
	virtual bool IsResolveOver()const;
	virtual bool SetResolveRange(int nBegin,int nEnd);
	virtual bool ResetResolve();//���ý���׶�
	virtual bool SetResolveOver();//���׶�����Ϊ����
protected:
	virtual bool WaitSeconds(int nSeconds);	//�ȴ�N��
	virtual bool WaitSeconds(float fSeconds);	//�ȴ�N�� ���� 4.5��
	virtual bool WaitMillSec(uint64 uMillSec);//�ȴ�������
	virtual bool WaitForever();		//��Զ�ȴ�
	virtual bool ClearWait();		//����ȴ�
	virtual bool MarkResolveOver();		//������н������
	virtual bool IgnoreCheckResolve();//���κ��Լ��(��������׶�ѭ��)
	virtual bool PushAction(IResolver* pAc);
	virtual bool PushActionSelf();

	//�ڲ�����
public:
	virtual bool SetHandler(HResolver* hHandler);
	virtual HResolver* GetHandler()const;

	//����������ص�
public:
	virtual bool OnResolve();
	virtual bool OnResolveOnce();
	virtual bool OnTimeOut();
	virtual bool OnResolveBegin();	//���ÿ�ʼ
	virtual bool OnResolveOver();	//�������
public:
	IResolver(void);
	virtual ~IResolver(void);
private:
	CFIELD_INT(Resolve);
	CFIELD_INT(ResolveBegin);
	CFIELD_INT(ResolveEnd);
	CFIELD_PTR(IResolver*,Parent,p);
	CFIELD_PTR(IResolverManager*,ResolverMgr,p);
	CFIELD_BOOL(Resolving);		//�Ƿ��ڽ�����
	CFIELD_BOOL(ManagerCreate);	//����������
	CFIELD_BOOL(Removed);		//����Ƿ��Ƴ�
private:
	HResolver* _hHandler;
};

NS_TOOL_FRAME_END
