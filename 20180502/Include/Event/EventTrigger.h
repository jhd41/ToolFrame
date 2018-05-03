#pragma once

#include "Macro.h"
#include "HEventTrigger.h"
#include "TThreadSaftyList.h"

//ע��:�¼�������
//����֧���������͵�ע��,1.ָ���¼� 2.�����¼�
//�ڴ���ʱ �ȴ���ָ���¼��Ĵ��������ٴ��������¼�������
NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CEventTrigger
{
	typedef TThreadSaftyList<XEvent>				QueueEvent;
public:
	typedef std::list<HEventTrigger*>				ListEventHandler;

	//Int�����¼�
	typedef std::map<int,ListEventHandler*>			MapIntHandler;//�¼�->������
	typedef std::map<HEventTrigger*,SetInt*>		MapHanderInt;//������->�¼�

	//String�����¼�
	typedef std::map<std::string,ListEventHandler*>	MapStringHandler;//�¼�->������
	typedef std::map<HEventTrigger*,SetString*>		MapHanderString;//������->�¼�

	//ȫ����
public:
	bool EnableTriggerEvent(bool bEnabled);	//�����ܹ������¼�Ĭ�� ����
	bool IsEnableTriggerEvent()const;		//�Ƿ��ܹ������¼�Ĭ�� ����
	
	//�����¼����ʹ�����
	bool RegistAll(HEventTrigger* hEvent);
	bool UnregistAll(HEventTrigger* hEvent);

	//��ȫ�ͷ����иô�����ע������¼�
	int	SafeUnregist(HEventTrigger* hEvent);

	//Int�¼���
public:
	//ָ���¼����ʹ�����
	bool Regist(int nEventType,HEventTrigger* hEvent);
	bool Unregist(int nEventType,HEventTrigger* hEvent);

	//��ǰ�߳��¼�
	bool FireEvent(int nEventType);
	bool FireEvent(int nEventType,const std::string& sArg);
	bool FireEvent(int nEventType,int nArg1);
	bool FireEvent(int nEventType,int nArg1,int nArg2);
	bool FireEvent(int nEventType,int nArg1,int nArg2,int nArg3);
	bool FireEvent(int nEventType,const std::string& sArg,int nArg1,int nArg2);
	bool FireEvent(int nEventType,const std::string& sArg,int nArg1,int nArg2,int nArg3,void* pArg);
	bool FireEvent(int nEventType,void* pArg);
	
	//�߳��¼�
	bool PostEvent(int nEventType);
	bool PostEvent(int nEventType,const std::string& sArg);
	bool PostEvent(int nEventType,int nArg1);
	bool PostEvent(int nEventType,int nArg1,int nArg2);
	bool PostEvent(int nEventType,int nArg1,int nArg2,int nArg3);
	bool PostEvent(int nEventType,const std::string& sArg,int nArg1,int nArg2);
	bool PostEvent(int nEventType,void* pArg);

	//String �¼���
public:
	//ָ���¼����ʹ�����
	bool Regist(const std::string& sEvent,HEventTrigger* hEvent);
	bool Unregist(const std::string& sEvent,HEventTrigger* hEvent);

	//��ǰ�߳��¼�
	bool FireEvent(const std::string& sEvent);
	bool FireEvent(const std::string& sEvent,const std::string& sArg);
	bool FireEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2);
	bool FireEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3);
	bool FireEvent(const std::string& sEvent,int nArg1);
	bool FireEvent(const std::string& sEvent,int nArg1,int nArg2);
	bool FireEvent(const std::string& sEvent,int nArg1,int nArg2,int nArg3);
	bool FireEvent(const std::string& sEvent,int nArg1, const std::string& sArg1);
	bool FireEvent(const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2);
	bool FireEvent(const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2,int nArg3,void* pArg);
	bool FireEvent(const std::string& sEvent,void* pArg);
	bool FireEvent(const XEvent& xEvent);

	//�߳��¼�
	bool PostEvent(const std::string& sEvent);
	bool PostEvent(const std::string& sEvent,const std::string& sArg);
	bool PostEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2);
	bool PostEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3);
	bool PostEvent(const std::string& sEvent,int nArg1);
	bool PostEvent(const std::string& sEvent,int nArg1,int nArg2);
	bool PostEvent(const std::string& sEvent,int nArg1,int nArg2,int nArg3);
	bool PostEvent(const std::string& sEvent,int nArg1,const std::string& sArg1);
	bool PostEvent(const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2);
	bool PostEvent(const std::string& sEvent,void* pArg);
	bool PostEvent(const XEvent& xEvent);
public:
	bool IsEventQueueEmpty()const;
	bool ProcessEvent(uint64 uTimeOut = 0);//�ⲿ�̵߳��� �Ա㴦��Ͷ�ݵ��¼� �����Ƿ�ʱ
private:
	bool FireEventVct(ListEventHandler& vHandlers, const XEvent& xEvent);
private:
	
	MapIntHandler	_vIntHandler;	//�¼�->������
	MapHanderInt	_vHandlerInt;	//������->�¼�

	MapStringHandler _vStringHandler;	//�¼�->������
	MapHanderString	_vHandlerString;	//������->�¼�

	ListEventHandler _vHandlerAll;	//�����¼�����Ҫ����������

	QueueEvent		_vEvent;
	CMutexRecursive	_mutex;

	bool			_bEnable;
public:
	CEventTrigger(void);
	virtual ~CEventTrigger(void);
};

NS_TOOL_FRAME_END
