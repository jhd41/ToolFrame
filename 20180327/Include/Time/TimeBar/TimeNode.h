#pragma once

#include "Macro.h"
#include "MacroDefineEx.h"
#include "MacroDefineBoost.h"

#include "IPool.h"

NS_TOOL_FRAME_BEGIN

DECLARE_SHARE_PTR(CTimeNode);

class HTimeOut;
class CTimeNode
	:public IPoolZero
{
public:
	void				SetObj(void* pObj);
	void*				GetObj()const;
	void				SetUserDataInt(int nArg);
	int					GetUserDataInt()const;
	void				SetUserDataString(const std::string& sArg);
	const std::string&	GetUserDataString()const;

	//�ⲿ��Ҫ����
public:
	bool				Init(bool bLoop,uint64 uTimeDelay,HTimeOut* pCallBack);
	bool				SetInvaild();//ʹ����Ч
	void				SetTimeOut(uint64 uTimeOut);
	
	bool				IsEnable()const;
	bool				IsLoop()const;
	HTimeOut*			GetProcesser()const;
	uint64				GetTimeOut()const;
	uint64				GetTimeDelay()const;
	
	CMutexRecursive&	GetMutex()const;
public:
	CTimeNode();
	virtual ~CTimeNode();
private:
	mutable CMutexRecursive	_mutex;//���ڳ�ʱʱΪ�˱�֤��ȷ��Ҫ�������������� �ֿ��ܷ������� �Ƴ�ʱ��ڵ� ��˲��ɱ���� Ҫ�ظ����� ���࣬��� ֻ��ʹ�� �ݹ�����

	bool		_bEnable;	//�Ƿ���Ч
	uint64		_uTimeOut;	//��ʱʱ��
	bool		_bLoop;		//�Ƿ�ѭ��
	uint64		_uTimeDelay;//�ӳ�ʱ��
	HTimeOut*	_pProcesser;//��ʱ������
	
	void*		_pObj;		//�󶨵ĸ�������
	int			_nArg;		
	std::string _sArg;		
};

NS_TOOL_FRAME_END
