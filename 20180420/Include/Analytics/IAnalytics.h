#pragma once
#include "MacroAnalytics.h"
#include "IAnyObj.h"

NS_TOOL_FRAME_BEGIN

//ͳ�ƽӿ�
class TOOLFRAME_DLL IAnalytics
	:public IAnyObj
{
	//�ⲿ�ӿڵ���
public:
	virtual bool Init();			//�����ʼ��
	virtual bool IsInited()const;	//�Ƿ��Ѿ���ʼ��

	//����̳�
public://�˻�����
	virtual bool SetAnonymous();//���������˺�
	virtual bool OnLogin();		//��½
	virtual bool OnLogout();	//�ǳ�
public:
	virtual bool OnInit();		//��ʼ��

	virtual bool OnStartUp();	//����	
	virtual bool OnPause();		//��ͣ
	virtual bool OnResume();	//�ص���Ϸ
	virtual bool OnExit();		//�뿪

	//֧��
	virtual bool OnPayReq(const std::string& sOrderID,const std::string& sItemID,uint uItemCount,uint uMoney,const std::string& sPayCurrency,const std::string& sPayType,uint uVirtualCurrency=0);//֧��(֧����ʽEPayType ����ECurrency ��� ��λ��) sProductID(�û��Զ���)
	virtual bool OnPayed(const std::string& sOrderID,const std::string& sPaySource="",const std::string& sArg="");
	virtual bool OnPayFaild(const std::string& sOrderID,const std::string& sReason="",const std::string& sArg="");
	
	//����ҷ��� ��� �� ����
	virtual bool OnVirtualCurrencyGain(const std::string& sCurrencyType,uint uCount,const std::string& sSource="");															//����� ����,��������Դ
	virtual bool OnVirtualCurrencyUsed(const std::string& sCurrencyType,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");	//����� ����,������;��(����ʹ�� ��ʯ 3�� ������Ʒ ����3��5�ŵ���)

	//��Ʒ���� ��� �� ����
	virtual bool OnItemRecv(const std::string& sItemID,uint uCount,const std::string& sSource="");														//��Ʒ
	virtual bool OnItemUsed(const std::string& sItemID,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");

	//��չ�ӿ�
	virtual bool OnEvent(const std::string& sEvent);
	virtual bool OnEvent(const std::string& sEvent,const std::string& sKey,const std::string& sValue);
	virtual bool OnEvent(const std::string& sEvent,const MapStringString& vKeyValue);					//ʵ��ִ��

	virtual bool OnEventBegin(const std::string& sEvent);
	virtual bool OnEventBegin(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	virtual bool OnEventBegin(const std::string& sEvent, const MapStringString& vKeyValue);
	virtual bool OnEventEnd(const std::string& sEvent);
	virtual bool OnEventEnd(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	virtual bool OnEventEnd(const std::string& sEvent, const MapStringString& vKeyValue);

	//����
	virtual bool OnTaskBegin(const std::string& sTaskName);		//����ʼ
	virtual bool OnTaskCompleted(const std::string& sTaskName);	//�������
	virtual bool OnTaskFailed(const std::string& sTaskName,const std::string& sReason);//����ʧ�� ʧ��ԭ��

	//��ҵȼ�
	virtual bool OnLevelUp(int nLevel);

	//�û�����
	virtual bool OnAdvice(int eAdviceType, const std::string& sName, const std::string& sTel, const std::string& sContent, const std::string& sQQ);
	
	//�û���־
	virtual bool OnLog(int eLogType, const std::string& sContent, const std::string& sArg1 = "", const std::string& sArg2 = "", const std::string& sArg3 = "", const std::string& sArg4 = "", const std::string& sArg5 = "", int32 nArgValue = 0);

	//ϵͳ
	virtual bool SetLogEnabled(bool bEnable);//����־����

	//����App��Ϣ
	virtual bool SetAppID(const std::string& sAppID);
	virtual bool SetAppVer(const std::string& sAppVer);

	//�����˺���Ϣ
	virtual bool SetUserID(const std::string& sUserID);
	virtual bool SetAccount(const std::string& sAccount);
	virtual bool SetAccountChannelID(const std::string& sAccountChannelID);
	virtual bool SetLevel(int nLevel);
	virtual bool SetGender(EGender eGender);											//�����Ա�
	virtual bool SetAge(int nAge);														//��������
	virtual bool SetGameServer(const std::string& sGameServer);							//��������
	virtual bool SetChannelID(const std::string& sChannelID);							//��������
public:
	IAnalytics(void);
	virtual ~IAnalytics(void);
protected:
	//App��Ϣ
	std::string _sAppID;		//Ӧ��ID
	std::string _sChannelID;	//����
	std::string	_sAppVer;		//�汾

	//�˺���Ϣ
	std::string _sUserID;				//�û�ID
	std::string _sAccount;				//�˺�ID
	std::string _sAccountChannelID;		//�˺�����ID
	int			_nLevel;				//�ȼ�
	EGender		_eGender;				//�Ա�
	int			_nAge;					//���
	std::string _sGameServer;			//����

	bool		_bInited;		//��ʼ�� ���
};

NS_TOOL_FRAME_END
