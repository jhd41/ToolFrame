#pragma once
#include "MacroAnalytics.h"

#include "ToolFrame.h"
#include "IAnalytics.h"

//�������������
//��ע:��Ϸ������ OnStartUp ���뾡�� ������Ҫ�������˺ţ��������� �� �������˺�Ϊ�� �����û������
//�����Ϸ��Ҫ��¼ �� ��¼�� ���� OnLogin ������ ������ֱ�ӵ��� SetAnonymous����
//IAnalytics���󱻴�������֮ʱ �Ѿ������� MAnalytics �Ĺ�����
//Channel ����ָ�����û���������(��һ�ε�¼ʱ���ƹ�������������Ϊ�û���Ϊ���� �û���������Ϊ����Ϊ�û���������������)

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL MAnalytics
{
public:
	typedef std::vector<IAnalytics*> VectorAnalytics;
public:
	ST_INTANCE(MAnalytics);
public:
	bool					Regist(IAnalytics* pAnalytics);	//ע��
	bool					UnRegist(IAnalytics* pAnalytics);
	VectorAnalytics&		GetAnalytics();					//��ȡ���еķ�����
	const VectorAnalytics&	GetAnalytics()const;
public:
	//�˻�����
	bool SetAnonymous();//���������˺�(������� OnLogin)

	bool SetLevel(int nLevel);													//���ü���
	bool SetGender(EGender eGender);											//�����Ա�
	bool SetAge(int nAge);														//��������
	bool SetGameServer(const std::string& sServerName);							//��������
	bool SetChannelID(const std::string& sChannel);								//��������
	bool OnLogin(const std::string& sUserID, const std::string& sAccount,const std::string& sChannelID);	//��½
	bool OnLogout();															//�ǳ�

	bool OnStartUp();	//����
	bool OnPause();		//��ͣ
	bool OnResume();	//�ص���Ϸ
	bool OnExit();		//�˳�

	//֧��
	bool OnPayReq(const std::string& sOrderID,const std::string& sItemID,uint uItemCount,uint uMoney,const std::string& sPayCurrency,const std::string& sPayType,uint uVirtualCurrency=0);//֧��(֧����ʽEPayType ����ECurrency ��� ��λ��) sProductID(�û��Զ���)
	bool OnPayed(const std::string& sOrderID,const std::string& sPaySource="",const std::string& sArg="");
	bool OnPayFaild(const std::string& sOrderID,const std::string& sReason="",const std::string& sArg="");

	//����ҷ��� ��� �� ����
	bool OnVirtualCurrencyGain(const std::string& sCurrencyType,uint uCount,const std::string& sSource="");															//����� ����,��������Դ
	bool OnVirtualCurrencyUsed(const std::string& sCurrencyType,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");	//����� ����,������;��(����ʹ�� ��ʯ 3�� ������Ʒ ����3��5�ŵ���)

	//��Ʒ���� ��� �� ����
	bool OnItemRecv(const std::string& sItemID,uint uCount,const std::string& sSource="");														//��Ʒ
	bool OnItemUsed(const std::string& sItemID,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");

	//��չ�ӿ�
	bool OnEvent(const std::string& sEvent);
	bool OnEvent(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	bool OnEvent(const std::string& sEvent, const MapStringString& vKeyValue);					//ʵ��ִ��

	template<typename TValue>
	bool OnEvent(const std::string& sEvent, const std::string& sKey, const TValue& tValue);

	bool OnEventBegin(const std::string& sEvent);
	bool OnEventBegin(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	bool OnEventBegin(const std::string& sEvent, const MapStringString& vKeyValue);
	bool OnEventEnd(const std::string& sEvent);
	bool OnEventEnd(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	bool OnEventEnd(const std::string& sEvent, const MapStringString& vKeyValue);

	//����
	bool OnTaskBegin(const std::string& sTaskName);		//����ʼ
	bool OnTaskCompleted(const std::string& sTaskName);	//�������
	bool OnTaskFailed(const std::string& sTaskName,const std::string& sReason);//����ʧ�� ʧ��ԭ��

	//��ҵȼ�
	bool OnLevelUp(int nLevel);

	//�û�����
	bool OnAdvice(int eAdviceType, const std::string& sName, const std::string& sTel, const std::string& sContent, const std::string& sQQ);

	//ϵͳ
	bool SetLogEnabled(bool bEnable);//����־����
public:
	MAnalytics(void);
	virtual ~MAnalytics(void);
private:
	VectorAnalytics _vAnalytics;
};

template<typename TValue>
bool MAnalytics::OnEvent( const std::string& sEvent,const std::string& sKey,const TValue& tValue )
{
	return OnEvent(sEvent,sKey,ToolFrame::ToString(tValue));
}


NS_TOOL_FRAME_END