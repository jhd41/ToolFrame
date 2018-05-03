#pragma once
#include "MacroCocos2dx.h"
#include "IMsgStream.h"
#include "AnimationQueue.h"
#include "TouchGroup.h"
#include "InputEventListener.h"

//ҳ��
//Ϊ�˱�֤ҳ��Ĳ�ι�ϵһ�£����е�ҳ��Ľڵ��γɵ�����ֻΪҳ���ι�ϵ����ÿ��ҳ���и����ӽ�����ҳ��ĸ��ڵ�����������Դ�Ĺ��غ���ʾ
//����ʱ������ ��ֹ����ظ����

#ifdef MACRO_LIB_COCOS2D

class CSceneFrameMgr;
class TOOLFRAME_DLL IPage
	:public Ref
	,public HAnimationQueue
	,public HTouchListener
	,public HInputEventListener
{
public:
	enum ERootZorder
	{
		ZORDER_RES_ROOT		= 0,//��Դ���
		ZORDER_PAGE_ROOT	= 1,//ҳ����
	};
	typedef std::vector<IPage*>	VectorPage;
public:
	virtual bool	Init();									//��ʼ��
	virtual bool	CallBackPage();							//�ص�
	virtual bool	MarkUpdated(bool bChildren = true);		//�����Ҫ����
	virtual CAnimationQueue&		GetAnimationQueue();
	virtual const CAnimationQueue&	GetAnimationQueue()const;
	virtual bool	IsInited()const;						//�Ƿ��ʼ��
	virtual bool	IsEntered()const;						//�Ƿ��Ѿ�չʾ
	virtual bool	IsTopPage()const;
	virtual bool	IsHasChildren()const;
	virtual bool	MarkRemoveFromeParent();
	virtual Node*	GetRootNode()const;								//��ȡ��Դ���ڵ�(���ⲿ��Դ����)
	
	virtual bool	SetLoadDelay(uint uDelay);						//���õ�ǰҳ �����ӳ�ʱ��
	virtual uint	GetLoadDelay()const;							//��ȡ��ǰҳ �����ӳ�ʱ��

	virtual bool	SetTouchEventEnabled(bool bEnabled);			//���õ�ǰҳ �����¼�����״̬
	virtual bool	IsTouchEventEnabled()const;						//��ȡ��ǰҳ �����¼�����״̬

	virtual CTouchGroup&		GetTouchGroup();
	virtual const CTouchGroup&	GetTouchGroup()const;

	virtual	CInputEventListener&		GetInputListener();
	virtual const CInputEventListener&	GetInputListener()const;

	//ȫ�ֺ���
	virtual bool	ListenKeyboard(bool bEnabled);					//�򿪼���
	virtual bool	ListenAccelerometer(bool bEnabled);				//��������Ӧ
	virtual bool	ListenTouch(bool bEnabled,bool bShare = false);	//�򿪴���

	virtual bool	IsListenKeyboard()const;
	virtual bool	IsListenAccelerometer()const;
	virtual bool	IsListenTouch()const;

	virtual bool	IsTimeLoadDelay() const;						//�Ƿ��Ǽ���ʱ����(Ĭ��300����)
	virtual bool	SetGlobalTouchEnabled(bool bEnabled);			//��ȫ���Ƿ���Դ���
	virtual bool	IsGlobalTouchEnabled()const;					//ȫ�ֿɷ���

	template<typename T>
	T*	CreateChildPage(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	template<typename T>
	T*	ReplaceThisPage(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");

	virtual bool		QueueClose();	//���붯������ �ر��Լ�
	virtual bool		QueueCallBack();//���붯������ CallBack

	//�Զ������
	virtual bool		SetPageType(int ePageType);//����ҳ������ �����ϲ��߼��жϸ�ҳ�������
	virtual int			GetPageType()const;

	//����ֵ
	virtual bool				CleanReturnArg();
	virtual bool				SetReturnType(int eReturnType);
	virtual bool				SetReturnArgInt1(int nArg);
	virtual bool				SetReturnArgInt2(int nArg);
	virtual bool				SetReturnArgString1(const std::string& sArg);
	virtual bool				SetReturnArgString2(const std::string& sArg);
	virtual int					GetReturnType()const;
	virtual int					GetReturnArgInt1()const;
	virtual int					GetReturnArgInt2()const;
	virtual const std::string&	GetReturnArgString1()const;
	virtual const std::string&	GetReturnArgString2()const;
public:
	virtual bool		Destory();						//����(�ⲿ��Ҫ����)
	virtual bool		AddChild(IPage* pPage);
	virtual bool		RemoveChild(IPage* pPage,bool bCleanUp = true);
	virtual Node*		GetRootPage()const;				//��ȡҳ����ڵ�(�ڲ�ʹ�� �ⲿ�����ܲ�Ҫ����)
	virtual bool		SetPageZOrder(int nZOrder);		//����ҳ��ĸ��ڵ�ZOrder����ش���ZORDER_PAGE_ROOT �鿴 ERootZorder 
	virtual int			GetPageZOrder()const;
	virtual const VectorPage& GetChildPage()const;

	template<typename T>
	T*		FindPage()const;
protected:
	virtual Node*		GetSceneNode()const;
	
	virtual Node*		LoadUIFile(const std::string& sFileName,int nZOder=0);
	virtual Node*		FindNode(const std::string& sName)const;
	template<typename T>
	bool				FindNode(T*& t, const std::string& sName)const;
	virtual bool		SetVisible(const std::string& sName,bool bVisible);
	virtual bool		SetEnabled(const std::string& sName,bool bEnabled);
	virtual bool		AddTouchEvent(Node* pWidget);
	virtual bool		AddTouchEvent(Node* pRootWidget,const std::string& sName);
	virtual bool		AddTouchEvent(VectorNode& vButton);
	virtual bool		AddTouchEvent(const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(const Node* pRootWidget,const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(VectorCheckBox& vCheckBox,const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(VectorCheckBox& vCheckBox,const Widget* pRootWidget,const std::string& sName);
	
	virtual bool		SetContentSize(const std::string& sName,const Size& size);
	virtual bool		SetSizeWidthWithResidue(const std::string& sName,const std::string& sArg1="",const std::string& sArg2="",const std::string& sArg3="",const std::string& sArg4="",const std::string& sArg5="");
	virtual bool		SetSizeHeightWithResidue(const std::string& sName,const std::string& sArg1="",const std::string& sArg2="",const std::string& sArg3="",const std::string& sArg4="",const std::string& sArg5="");
	virtual bool		SetSizeWithResidue(bool bWidth,const std::string& sName,const std::string& sArg1,const std::string& sArg2="",const std::string& sArg3="",const std::string& sArg4="",const std::string& sArg5="");

	virtual const Size& GetContentSize(const std::string& sName)const;
	virtual bool		IsOutOfScreen(const VectorString& vWidget,bool bWidth)const;//�Ƿ񳬹���Ļ
	virtual bool		IsOutOfScreen(bool bWidth,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");

	virtual bool		ChangeParentNode(const std::string& sChild,const std::string& sParent,bool bCleanUp = true);
	
	virtual bool		AddUpdateEveryFrame(bool bPaused = false);
	virtual bool		RemoveUpdateEveryFrame();
	virtual bool		AddTimeUpdate(float fInterval, uint uRepeat, float fDelay, bool bPaused = false);
	virtual bool		RemoveTimeUpdate();
	
	virtual bool		RemovePageChildren(bool bCleanUp = true);	//�Ƴ�ҳ�������ӽڵ�(����������ҳ���Լ���Դ)
	virtual bool		RemoveResChildren(bool bCleanUp = true);	//�Ƴ���ǰҳ��������Դ(��������ҳ��)
	virtual bool		RemoveFromeParent(bool bDestory = true);

	//�����¼�
public:
	virtual bool		FireEventEnter();
	virtual bool		FireEventExit();
	virtual bool		FireEventEnterTransitionDidFinish();

	//�㲥
	virtual bool		FireEventRecv(UINT uClientID,ToolFrame::IMsgStream& msgStream);
	virtual bool		FireEventConnected(uint uClientID);
	virtual bool		FireEventDisconnected(uint uClientID);
	virtual bool		FireEventConnectFailed(uint uClientID);
	virtual bool		FireEventOnPause();
	virtual bool		FireEventOnResume();
	virtual bool		FireEventOnScreenSizeChanged(int nWidth, int nHeight);

	//����ʵ��
protected:
	virtual bool OnFireEvent();

	virtual bool OnInit();		//��ʼ��
	virtual bool OnDestory();	//������
	virtual bool OnShow();		//��ʾ
	virtual bool OnCallBackPage(IPage* pPage);
	virtual bool OnTouchEvent		(Ref *pSender, TouchEventType type);
	virtual bool OnCheckBoxChanged	(Ref* pSender, CheckBoxEventType type);
	virtual bool OnUpdate(float dt);
	virtual bool OnTimeUpdate(float dt);
	virtual bool OnEnter();						//������ʾ
	virtual bool OnExit();						//�����뿪
	virtual bool OnEnterTransitionDidFinish();	//��ת�任���
	virtual bool OnConnected(uint uClientID);
	virtual bool OnDisconnected(uint uClientID);
	virtual bool OnConnectFailed(uint uClientID);
	virtual bool OnRecv(uint uClientID,ToolFrame::IMsgStream& msgStream);		//Э�����(��������true)
	virtual bool OnAcceleration(Acceleration* pAcceleration, Event* pEvent);	//�����¼��ص�(��������true)
	virtual bool OnKeyPressed(EventKeyboard::KeyCode eKeyCode, Event* pEvent);	//�����¼��ص�(��������true)
	virtual bool OnKeyReleased(EventKeyboard::KeyCode eKeyCode, Event* pEvent);	//�ͷ��¼��ص�(��������true)
	virtual bool OnTouchBegan(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);

	virtual bool OnPause();											//��ͣ
	virtual bool OnResume();										//�ص���Ϸ
	virtual bool OnScreenSizeChanged(int newWidth, int newHeight);	//��Ļ�ߴ�ı�
private:
	virtual bool Show();		//��ʾ
	virtual bool SetUpdated(bool bUpdated);
	virtual bool IsUpdated()const;
private:
	void touchEvent(Ref *pSender, TouchEventType type);
	void checkboxEvent(Ref* pSender, CheckBoxEventType type);
	bool OnQueueClose();
	bool OnQueueCallBack();
	bool AddSceneManager(IPage* pPage);
public:
	virtual void update(float dt);
	virtual void timeupdate(float dt);
private:
	CFIELD_PTR(IPage*,Parent,p);
	CFIELD_INT(UserDataInt);
	CFIELD_INT(UserDataInt2);
	CFIELD_INT(UserDataInt3);
	CFIELD_STRING(UserDataString);
	CFIELD_STRING(UserDataString2);
	CFIELD_PTR(void*,UserDataPtr,p);
	CFIELD_INT(State);
	CFIELD_PTR(CSceneFrameMgr*,SceneMgr,p);
public:
	IPage(void);
	virtual ~IPage(void);
private:
	bool					_bInited;
	bool					_bEntered;
	bool					_bEnterTransitionDidFinished;
	bool					_bUpdated;
	bool					_bDestoryed;
	Node*					_pRootPage;		//ҳ��ĸ�	�����ĸ�
	Node*					_pRootRes;		//��Դ�ĸ�	������Դ��
	CAnimationQueue			_vAnimationQueue;
	VectorPage				_vPage;
	bool					_bRemoveThis;
	uint					_uLoadDelay;				//��ǰҳ�����ӳ�ʱ��
	bool					_bEnabledTouchEvent;		//��ǰҳ�����¼�����

	int						_ePageType;

	int						_eReturnType;
	int						_nReturnArg1;
	int						_nReturnArg2;
	std::string				_sReturnArg1;
	std::string				_sReturnArg2;

	CInputEventListener		_xEventListener;
	CTouchGroup				_xTouchGroup;
};

template<typename T>
T* IPage::ReplaceThisPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	IPage* pPage = GetParent();
	if (!pPage)return nullptr;

	RemoveFromeParent();
	return pPage->CreateChildPage<T>(nUserDataInt,nUserDataInt2,sUserDataString);
}

template<typename T>
T* IPage::FindPage() const
{
	VectorPage::const_iterator itr;
	foreach(itr, _vPage) {
		T* pPage = dynamic_cast<T*>(*itr);
		if (pPage)
			return pPage;
	}

	return nullptr;
}

template<typename T>
bool IPage::FindNode( T*& t, const std::string& sName )const
{
	t = dynamic_cast<T*>(FindNode(sName));
	return !!t;
}

template<typename T>
T* IPage::CreateChildPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	T* pPage = new T();
	if (!pPage)return nullptr;

	pPage->SetSceneMgr(GetSceneMgr());
	pPage->SetUserDataInt(nUserDataInt);
	pPage->SetUserDataInt2(nUserDataInt2);
	pPage->SetUserDataString(sUserDataString);
	
	this->AddChild(pPage);
	pPage->release();

	AddSceneManager(pPage);
	return pPage;
}

#endif //MACRO_LIB_COCOS2D
