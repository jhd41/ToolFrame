#pragma once
#include "LuaEngine.h"
#include "IResolverManager.h"
#include "EventTrigger.h"

NS_TOOL_FRAME_BEGIN

class CResolverCoreManager
	:public IResolverManager
	,public HEventTrigger
{
public:
	virtual bool Init();
	virtual bool ProcessOne(uint64 uMillSeconds = 0);			//����һ���׶� �����Ƿ���(����Flase���� ����Ҫ����)
	virtual bool IsProcessed()const;		//�Ƿ��Ѿ��������

	//Lua
public:
	virtual bool				InitLua();
	virtual bool				LoadLua(const std::string& sLua);
	virtual bool				LoadLuaFile(const std::string& sFile);
	virtual CLuaEngine&			GetLuaEngine();
	virtual const CLuaEngine&	GetLuaEngine()const;
	virtual bool				SetEventPost(bool bPost);//ʹ��Post��ʽ�����¼�(Ĭ��flase)
	virtual bool				IsEventPost()const;		//�Ƿ�ʹ��Post��ʽ�����¼�
	virtual bool				ResetLuaEngine();		//����Lua����

	//LuaApi
public:
	bool			ApiTrace(std::string sMsg);			//��ӡ������Ϣ
	bool			ApiLogLuaDebug(std::string sMsg);	//��¼������־
	bool			ApiLogLuaError(std::string sMsg);	//��¼������־
	bool			ApiLogSystem(std::string sMsg);		//��¼ϵͳ��־

	bool			ApiTriggerEvent(std::string sEvent);				//�����¼�
	bool			ApiTriggerEventWithInt(std::string sEvent,int nInt);//�����¼�(����)
	bool			ApiTriggerEventWithString(std::string sEvent,std::string sArg);//�����¼�(����)

	bool			ApiClearEventArg();					//����¼�����

	std::string		ApiGetEventName();					//��ȡ�¼�����
	int				ApiGetEventInt();					//����¼�����:Int ��ͬ ApiGetEventInt1
	int				ApiGetEventInt1();					//����¼�����1:Int
	int				ApiGetEventInt2();					//����¼�����2:Int
	int				ApiGetEventInt3();					//����¼�����3:Int
	std::string		ApiGetEventString();				//����¼�����:String ��ͬ ApiGetEventString1
	std::string		ApiGetEventString1();				//����¼�����1:String
	std::string		ApiGetEventString2();				//����¼�����2:String
	std::string		ApiGetEventString3();				//����¼�����3:String

	bool			ApiActionLua(uint uIndex);			//����Lua���㶯��
	bool			ApiActionGameOver();				//������Ϸ��������

//Event
public:
	virtual	bool TriggleEvent(const std::string& sEventName);
	virtual bool TriggleEvent(const std::string& sEventName,int nEventInt);
	virtual bool TriggleEvent(const std::string& sEventName,int nEventInt1,int nEventInt2);
	virtual bool TriggleEvent(const std::string& sEventName,int nEventInt1,int nEventInt2,int nEventInt3);
	virtual bool TriggleEvent(const std::string& sEventName,const std::string& sEventString);
	virtual bool TriggleEvent(const std::string& sEventName,const std::string& sEventString1,const std::string& sEventString2);
	virtual bool TriggleEvent(const std::string& sEventName,const std::string& sEventString1,const std::string& sEventString2,const std::string& sEventString3);
	virtual	bool TriggleEvent(const std::string& sEventName,void* pAc);
	virtual	bool TriggleEvent(const XEvent& xEvent);

	virtual bool ClearEventArg();
	
	//ע���¼�
public:
	virtual bool EnableTriggerEvent(bool bEnabled);	//�����ܹ������¼�Ĭ�� ����
	virtual bool IsEnableTriggerEvent()const;		//�Ƿ��ܹ������¼�Ĭ�� ����

	//ָ���¼����ʹ�����
	virtual bool RegistEvent(const std::string& sEvent,HEventTrigger* hEvent);
	virtual bool UnregistEvent(const std::string& sEvent,HEventTrigger* hEvent);

	//�����¼����ʹ�����
	virtual bool RegistAllEvent(HEventTrigger* hEvent);
	virtual bool UnregistAllEvent(HEventTrigger* hEvent);

	//��ȫ�ͷ����иô�����ע������¼�
	virtual int	SafeUnregistEvent(HEventTrigger* hEvent);
protected:
	virtual bool OnEvent(const std::string& sEvent,const XEvent& xEvent);
private:
	bool TriggleLuaEvent( const std::string& sEventName );
private:
	XEvent _xEvent;
public:
	CResolverCoreManager(void);
	virtual ~CResolverCoreManager(void);
protected:
	CLuaEngine*		_pLuaEngine;		//Lua����
	CEventTrigger	_mgrEvent;		//�¼�������
	bool			_bPost;
};

NS_TOOL_FRAME_END
