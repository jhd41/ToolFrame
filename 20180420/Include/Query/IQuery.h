#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"

#include "TimeElapse.h"
#include "IPool.h"
#include "HTimeOut.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN

DEFINE_SHARE_PTR(IQuery, IQueryPtr);

typedef std::vector<IQueryPtr> VectorQueryPtr;

class IQuery
	:public boost::enable_shared_from_this<IQuery>
	,public IPoolZero
	,public HTimeOut
{
	DEBUG_CLASS;
public:
	virtual bool OnQueryTimeOut();//��ʱ�ص�
public:
	CFIELD_UINT(ID);			//ϵͳ�����ID��
	CFIELD_UINT(Type);			//��ѯ����(����ɸѡ��ѯִ����)
	CFIELD_UINT(TypeSub);		//��ѯ����(����ɸѡ��ѯִ����)
	CFIELD_UINT64(QueryElapse);	//��ѯ���ŵ�ʱ��
	CFIELD_UINT(TimeOut);		//���ò�ѯ��ʱʱ��(���� 0Ϊ����) (����ѯʱ�Ѿ���ʱ�򲻲�ѯ)
	CFIELD_STRING(Tag);			//��ѯ���(�ڲ���,�ⲿ��Ҫ���� ����ģʽ�� ����Init()ʱ�Զ���ֵ)

	CFIELD_INT(ArgInt);			//��������
	CFIELD_UINT(ArgUint);		//��������
	CFIELD_STRING(ArgString);	//��������

	//ϵͳ���� �ⲿ��Ҫ����
public:
	virtual bool Init();
	virtual bool QueryBegin();
	virtual bool QueryEnd();
protected:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	IQuery();
	virtual ~IQuery();
private:
	CTimeElapse			_xElapse;		//ʱ������
	CTimeNodePtr		_pTimer;
};

NS_TOOL_FRAME_END
