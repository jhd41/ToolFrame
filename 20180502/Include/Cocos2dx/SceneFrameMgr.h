#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "ISceneFrame.h"

class TOOLFRAME_DLL HSceneFrameMgr
{
public:
	virtual bool OnSceneChanged(){return false;}				//�����л�
	virtual bool OnRootPageChanged(){return false;}				//��ҳ���л�
	virtual bool OnNewPageAdd(IPage* pPage){return false;}		//����ҳ������
	virtual bool OnNewPageInited(IPage* pPage){return false;}	//����ҳ���ʼ�����
	virtual bool OnNewPageAllInited() { return false; }			//��������ҳ���ʼ�����
public:
	HSceneFrameMgr(){}
	virtual ~HSceneFrameMgr(){}
};

class TOOLFRAME_DLL CSceneFrameMgr
{
	typedef std::vector<IPage*>	VectorPage;
public:
	virtual bool	SetHandler(HSceneFrameMgr* hHandler);
public:
	//��������ҳ���л� ����(�����ͷ���Դ) 
	template<typename T>
	IPage*			ReplaceRootPage(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	
	//�����л�(����Ч)
	template<typename T>//���������Ѿ������� �򷵻ؿ�(����Ч)
	ISceneFrame*	ReplaceScene(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	template<typename T>//ǿ���滻������ ���ж��Ƿ��뵱ǰ������ͬ
	ISceneFrame*	ReplaceSceneForce(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");

	//��������(���� ʹ����Ч)
	template<typename T>//���������Ѿ������� �򷵻ؿ�(����Ч)
	ISceneFrame*	CreateScene(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	template<typename T>//ǿ�ƴ��� ���ж��Ƿ��뵱ǰ������ͬ
	ISceneFrame*	CreateSceneForce(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");	

	//�����л� ִ��
	ISceneFrame*	ReplaceSceneForce(ISceneFrame* pScene);//�л�����(����Ч)
	ISceneFrame*	ReplaceSceneForce(ISceneFrame* pScene,TransitionScene* pTransition);//�л�����(ʹ����Ч)

	//ҳ�����
	virtual bool	AddNewPage(IPage* pPage);						//�����ҳ��
	virtual bool	RemoveNewPage(IPage* pPage);					//�Ƴ���ҳ��
	virtual	bool	TryInitPage();									//��ʼ��ҳ��
	virtual bool	IsHasNewPage()const;							//�Ƿ񻹴���δ��ʼ����ҳ��

	virtual bool	MarkSceneChanging();							//��ǳ����л���
	virtual bool	OnSceneChanged();								//�����л����
	virtual bool	IsSceneChanging()const;							//�Ƿ񳡾��л���

	virtual bool	SetTouchEnabled(bool bEnabled);					//��ȫ���Ƿ���Դ���
	virtual bool	IsTouchEnabled()const;							//�ɷ���

	virtual uint64	GetGlobalTimeLoad()const;						//��ȡ���һ��ҳ�����ʱ��
	virtual bool	SetGlobalLoadDelayEnabled(bool bEnabled=true);	//�Ƿ�������ʱ������ Ĭ��true
	virtual bool	SetGlobalLoadDelay(uint uDelay);				//���ü��ص���ʱʱ��
	virtual uint	GetGlobalLoadDelay()const;						//��ȡ������ʱʱ��

	virtual bool	IsGlobalTimeLoadEnabled()const;					//�Ƿ���Լ���ʱ������
	virtual bool	IsTimeLoadDelay(uint uLoadDelay) const;			//�Ƿ��Ǽ���ʱ����(Ĭ��300����)
	virtual bool	IsIgnoreTouchNode(const IPage* pPage, Ref *pSender, TouchEventType type );//�Ƿ��Ǻ��Դ����Ľڵ�;
public:
	ISceneFrame*	GetScene()const;
	IPage*			GetRootPage()const;
public:
	CSceneFrameMgr(void);
	virtual ~CSceneFrameMgr(void);
public:
	ISceneFrame*		_pRunningScene;
	HSceneFrameMgr*		_hHandler;

	bool				_bSceneChanging;

	VectorPage			_vInitPage;					//����ʼ��ҳ��

	bool				_bTouchEnabled;				//�Ƿ���Դ���(ȫ�ֱ���)
	bool				_bGlobalLoadDelayEnabled;	//�Ƿ�Ҫ�м�����ʱ
	uint				_uGlobalLoadDelay;			//������ʱʱ��
	uint64				_uGlobalTimeLoad;			//���һ�μ���ҳ���ʱ��(�������� �������� ���´��������ͬҳ�� )
	VectorRef			_vGlobalIgnoreTouch;		//���Դ����Ľڵ�
};

template<typename T>
ISceneFrame* CSceneFrameMgr::ReplaceScene( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	//���򴴽��³���ѹ�볡���滻
	ISceneFrame* pSceneFrame = CreateScene<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	if (!pSceneFrame)return nullptr;
	return ReplaceSceneForce(pSceneFrame);
}

template<typename T>
//�������� ���������Ѿ������� �򷵻ؿ�
ISceneFrame* CSceneFrameMgr::CreateScene( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	//��������Լ������������ �� ֱ�ӷ���
	if (_pRunningScene)
	{
		T* pPage = dynamic_cast<T*>(_pRunningScene->GetRootPage());
		if (pPage)return nullptr;
	}

	return CreateSceneForce<T>(nUserDataInt,nUserDataInt2,sUserDataString);
}

template<typename T>
ISceneFrame* CSceneFrameMgr::CreateSceneForce( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	ISceneFrame* pSceneFrame = ISceneFrame::Create();
	if (!pSceneFrame)return nullptr;

	pSceneFrame->SetSceneMgr(this);
	pSceneFrame->ReplaceRootPage<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	return pSceneFrame;
}

template<typename T>
IPage* CSceneFrameMgr::ReplaceRootPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	if (!_pRunningScene)return nullptr;

	IPage* pPage = _pRunningScene->ReplaceRootPage<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	if (!pPage)return pPage;

	if (_hHandler)
		_hHandler->OnRootPageChanged();

	return pPage;
}

template<typename T>
ISceneFrame* CSceneFrameMgr::ReplaceSceneForce( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	//���򴴽��³���ѹ�볡���滻
	ISceneFrame* pSceneFrame = CreateSceneForce<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	if (!pSceneFrame)return nullptr;
	return ReplaceSceneForce(pSceneFrame);
}

#endif //MACRO_LIB_COCOS2D
