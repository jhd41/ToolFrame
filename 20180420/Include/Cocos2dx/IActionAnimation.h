#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"
#include "ApiCocos2dx.h"
#include "HAnimationQueue.h"
#include "ActionIntervalEx.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class CAnimationQueue;
class CAnimationQueueMulit;
class IActionAnimation
	:public Ref
{
public:
	enum EActionType
	{
		ACTION_INVAILD = 0,

		ACTION_ADD_TARGET,				//��Ӳ���Ŀ��
		ACTION_ADD_TARGET_FIND,			//��Ӳ���Ŀ��

		ACTION_CLEAR_TARGET,			//�������Ŀ��
		ACTION_CLEAR_TARGET_ALL,		//�������Ŀ��

		ACTION_SET_CUR_TARGET,			//���õ�ǰ����Ŀ��
		ACTION_REMOVE_CUR_TARGET,		//�Ƴ���ǰĿ��

		ACTION_STORE_CUR_TARGET,		//�洢��ǰ��Ŀ��
		ACTION_RESTORE_CUR_TARGET,		//��ԭ��ǰ��Ŀ��Ϊ�洢Ŀ��

		ACTION_SET_POSTION,				//λ��
		ACTION_SET_Z_ORDER,				//Z-Order
		ACTION_SET_VALUE,				//����ֵ
		ACTION_SET_VISIBLE,				//���ÿɼ�
		ACTION_SET_ENABLE,				//���ÿ���
		ACTION_SET_ROTATION,			//������ת
		ACTION_SET_OPACITY,				//����͸����
		ACTION_SET_SCALE,				//���ô�С
		ACTION_SET_SPEED,				//���ò����ٶ�

		ACTION_ACTIONS_SET_VALUE,		//��Ч����ֵ

		ACTION_REMOVE_FROM_PARENT,		//�Ƴ�
		ACTION_CHANGE_PARENT,			//�滻���ڵ�

		ACTION_CLONE,					//��¡
		ACTION_SET_WORLD_POSTION_NODE,	//��������λ��
		ACTION_SET_WORLD_POSTION_POINT,	//��������λ��

		ACTION_MOVE_TO,					//�ƶ���
		ACTION_MOVE_BY,					//�ƶ�
		ACTION_DELAY,					//�ӳ�
		ACTION_FADE_IN,					//����ʾ
		ACTION_FADE_OUT,				//����ʧ

		ACTION_FADE_IN_EX,				//����ʾ
		ACTION_FADE_OUT_EX,				//����ʧ

		ACTION_ANIMATION_CREATE,			//����
		ACTION_ANIMATION_PLAY_BY_NAME,		//����
		ACTION_ANIMATION_PLAY_FILE_BY_NAME,	//�����ļ�
		ACTION_ANIMATION_PLAY_TO_FRAME,		//������ָ��֡
		ACTION_ANIMATION_BONE,				//������ʾ
		ACTION_ANIMATION_BONE_CLONE,		//������ʾ(��¡����)
		ACTION_ANIMATION_BONE_ADD,			//��������
		ACTION_ANIMATION_DISPLAY_ADD,		//������ʾ
		ACTION_ANIMATION_DISPLAY_REMOVE,	//�Ƴ���ʾ
		ACTION_ANIMATION_DISPLAY_CHANGE,	//�ı���ʾ

		ACTION_SPINE_PLAY_BY_NAME,		//����

		ACTION_SOUND_PLAY_MUSIC,		//��������
		ACTION_SOUND_PLAY_EFFECT,		//������Ч

		ACTION_CALL_BACK,				//�ص�
		ACTION_CALL_BACK_FUNCTION,		//�ص�

		ACTION_MULIT_QUEUE,				//�����

		ACTION_NEXT_FRAME,				//��һ֡
	};
public:
	virtual bool OnExecute(){return false;}
	virtual bool OnDestory(){return false;}
	virtual bool OnAnimationSpeed(int nSpeed){return false;}
public:
	IActionAnimation(void);
	virtual ~IActionAnimation(void);
private:
	CFIELD_INT(ActionType);
	CFIELD_PTR(CAnimationQueue*,Queue,p);
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationAddTarget
	:public IActionAnimation
{
public:
	bool Init(Node* pNode, int nIndex);
public:
	virtual bool OnExecute();
public:
	IActionAnimationAddTarget(void);
	virtual ~IActionAnimationAddTarget(void);
private:
	Node*	_pNode;
	int		_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationAddTargetFind
	:public	IActionAnimation
{
public:
	bool Init( Widget* pWidget,const std::string& sName,int nIndex);
public:
	virtual bool OnExecute();
public:
	IActionAnimationAddTargetFind(void);
	virtual ~IActionAnimationAddTargetFind(void);
private:
	int			_nIndex;
	std::string _sName;
	Widget*		_pWidget;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationClearTarget
	:public	IActionAnimation
{
public:
	bool Init(int nIndex);
public:
	virtual bool OnExecute();
public:
	IActionAnimationClearTarget(void);
	virtual ~IActionAnimationClearTarget(void);
private:
	int		_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationClearTargetAll
	:public	IActionAnimation
{
public:
	bool Init();
public:
	virtual bool OnExecute();
public:
	IActionAnimationClearTargetAll(void);
	virtual ~IActionAnimationClearTargetAll(void);
private:
	Node*	_pNode;
	int		_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetCurTarget
	:public	IActionAnimation
{
public:
	bool Init(int nIndex);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetCurTarget(void);
	virtual ~IActionAnimationSetCurTarget(void);
private:
	int		_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationRemoveCurTarget
	:public	IActionAnimation
{
public:
	bool Init();
public:
	virtual bool OnExecute();
public:
	IActionAnimationRemoveCurTarget(void);
	virtual ~IActionAnimationRemoveCurTarget(void);
private:

};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationStoreCurTarget
	:public	IActionAnimation
{
public:
	bool Init();
public:
	virtual bool OnExecute();
public:
	IActionAnimationStoreCurTarget(void);
	virtual ~IActionAnimationStoreCurTarget(void);
private:
	Node*	_pNode;
	int		_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationReStoreCurTarget
	:public	IActionAnimation
{
public:
	bool Init();
public:
	virtual bool OnExecute();
public:
	IActionAnimationReStoreCurTarget(void);
	virtual ~IActionAnimationReStoreCurTarget(void);
private:
	Node*	_pNode;
	int		_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetPostion
	:public	IActionAnimation
{
public:
	bool Init(const Point& ptPostion);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetPostion(void);
	virtual ~IActionAnimationSetPostion(void);
private:
	Point	_ptPostion;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetZOrder
	:public	IActionAnimation
{
public:
	bool Init(int nZOrder);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetZOrder(void);
	virtual ~IActionAnimationSetZOrder(void);
private:
	int _nZOrder;
};

//////////////////////////////////////////////////////////////////////////
template<typename T,typename TValue>
class IActionAnimationSetValue
	:public	IActionAnimation
{
public:
	bool Init(const TValue& tValue){
		_tValue = tValue;
		return true;
	}
public:
	virtual bool OnExecute(){
		return ApiCocos2dx::SetValue<T>(GetQueue()->GetTargetCur(),_tValue);
	}
public:
	IActionAnimationSetValue(void){SetActionType(ACTION_SET_VALUE);}
	virtual ~IActionAnimationSetValue(void){}
private:
	TValue		_tValue;
};

//////////////////////////////////////////////////////////////////////////
template<typename T,typename TValue>
class IActionAnimationActionsSetValue
	:public	IActionAnimation
{
public:
	bool Init(const TValue& tValue,float fDuration){
		_tValue = tValue;
		_fDuration=fDuration;
		return true;
	}
public:
	virtual bool OnExecute(){
		return ApiCocos2dx::ActionsSetValue<T>(GetQueue()->GetTargetCur(),_tValue,_fDuration);
	}
public:
	IActionAnimationActionsSetValue(void){SetActionType(ACTION_ACTIONS_SET_VALUE);}
	virtual ~IActionAnimationActionsSetValue(void){}
private:
	TValue		_tValue;
	float		_fDuration;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetVisible
	:public	IActionAnimation
{
public:
	bool Init(bool bVisible);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetVisible(void);
	virtual ~IActionAnimationSetVisible(void);
private:
	bool	_bVisible;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetEnable
	:public	IActionAnimation
{
public:
	bool Init(bool bEnabled);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetEnable(void);
	virtual ~IActionAnimationSetEnable(void);
private:
	bool _bEnabled;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetRotation
	:public	IActionAnimation
{
public:
	bool Init(float fRotation);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetRotation(void);
	virtual ~IActionAnimationSetRotation(void);
private:
	float _fRotation;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetOpacity
	:public	IActionAnimation
{
public:
	bool Init(GLubyte uOpacity,bool bChildren);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetOpacity(void);
	virtual ~IActionAnimationSetOpacity(void);
private:
	GLubyte	_uOpacity;
	bool	_bChildren;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetScale
	:public	IActionAnimation
{
public:
	bool Init(float fScaleX,float fScaleY);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetScale(void);
	virtual ~IActionAnimationSetScale(void);
private:
	float _fScaleX;
	float _fScaleY;
};
//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetScaleXY
	:public	IActionAnimation
{
public:
	bool Init(float fScaleX,float fScaleY);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetScaleXY(void);
	virtual ~IActionAnimationSetScaleXY(void);
private:
	float _fScaleX;
	float _fScaleY;
};
//////////////////////////////////////////////////////////////////////////
class IActionAnimationRemoveFromParent
	:public	IActionAnimation
{
public:
	bool Init(bool bCleanUp);
public:
	virtual bool OnExecute();
public:
	IActionAnimationRemoveFromParent(void);
	virtual ~IActionAnimationRemoveFromParent(void);
private:
	bool _bCleanUp;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationChangeParent
	:public	IActionAnimation
{
public:
	bool Init(Node* pNodeParent, bool bCleanUp);
public:
	virtual bool OnExecute();
public:
	IActionAnimationChangeParent(void);
	virtual ~IActionAnimationChangeParent(void);
private:
	Node*	_pNodeParent;
	bool	_bCleanUp;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationClone
	:public	IActionAnimation
{
public:
	bool Init(Widget* pWidget);
public:
	virtual bool OnExecute();
public:
	IActionAnimationClone(void);
	virtual ~IActionAnimationClone(void);
private:
	Widget* _pWidget;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetWorldPostionNode
	:public	IActionAnimation
{
public:
	bool Init(const Node* pNodePostion);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetWorldPostionNode(void);
	virtual ~IActionAnimationSetWorldPostionNode(void);
private:
	const Node*  _pNodePostion;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationSetWorldPostionPoint
	:public	IActionAnimation
{
public:
	bool Init(Point ptPostion);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSetWorldPostionPoint(void);
	virtual ~IActionAnimationSetWorldPostionPoint(void);
private:
	Point	_ptPostion;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationMoveTo
	:public	IActionAnimation
{
public:
	bool Init(const Point& ptPostion,float fDuration);
public:
	virtual bool OnExecute();
public:
	IActionAnimationMoveTo(void);
	virtual ~IActionAnimationMoveTo(void);
private:
	void	CallBackFuncN(Node* pNode);
private:
	float _fDuration;
	Point _ptPostion;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationMoveBy
	:public	IActionAnimation
{
public:
	bool Init(const Point& ptPostion,float fDuration);
public:
	virtual bool OnExecute();
private:
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationMoveBy(void);
	virtual ~IActionAnimationMoveBy(void);
private:
	float	_fDuration;
	Point _ptPostion;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationDelay
	:public	IActionAnimation
{
public:
	bool Init( float fDuration);
public:
	virtual bool OnExecute();
private:
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationDelay(void);
	virtual ~IActionAnimationDelay(void);
private:
	 float	_fDuration;
	 Node*	_pNode;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationFadeIn
	:public	IActionAnimation
{
public:
	bool Init(float fDuration);
public:
	virtual bool OnExecute();
private:
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationFadeIn(void);
	virtual ~IActionAnimationFadeIn(void);
private:
	float _fDuration;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationFadeOut
	:public	IActionAnimation
{
public:
	bool Init(float fDuration);
private:
	virtual bool OnExecute();
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationFadeOut(void);
	virtual ~IActionAnimationFadeOut(void);
private:
	float _fDuration;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationFadeInEx
	:public	IActionAnimation
{
public:
	bool Init(float fDuration);
public:
	virtual bool OnExecute();
private:
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationFadeInEx(void);
	virtual ~IActionAnimationFadeInEx(void);
private:
	float _fDuration;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationFadeOutEx
	:public	IActionAnimation
{
public:
	bool Init(float fDuration);
public:
	virtual bool OnExecute();
private:
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationFadeOutEx(void);
	virtual ~IActionAnimationFadeOutEx(void);
private:
	float _fDuration;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationCreate
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sFileName,const Point& ptPostion);
public:
	virtual bool OnExecute();
public:
	IActionAnimationCreate(void);
	virtual ~IActionAnimationCreate(void);
private:
	std::string _sFileName;
	Point		_ptPostion;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationPlayByName
	:public	IActionAnimation
{
public:
	bool Init(const VectorString& vName,int nLoop);
public:
	virtual bool OnExecute();
	virtual bool OnDestory();
public:
	virtual bool OnActionArmatureOver( Armature* pArmature );
public:
	IActionAnimationPlayByName(void);
	virtual ~IActionAnimationPlayByName(void);
	
private:
	VectorString	_vName;
	int				_nLoop;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationPlayFileByName
	:public	IActionAnimation
{
public:
	bool Init(const Point& ptPostion,const std::string& sFileName,const VectorString& vName,int nLoop);
public:
	virtual bool OnExecute();
	virtual bool OnDestory();
public:
	virtual bool OnActionArmatureOver(Armature* pArmature);
public:
	IActionAnimationPlayFileByName(void);
	virtual ~IActionAnimationPlayFileByName(void);
private:
	Point	_ptPostion;
	std::string		_sFileName;
	VectorString	_vName;
	int				_nLoop;

	Armature*		_pArmature;
};


//////////////////////////////////////////////////////////////////////////
//���ŵ�ָ��֡
class IActionAnimationPlayToFrame
	:public	IActionAnimation
{
public:
	bool Init(int nTarget);
public:
	virtual bool OnExecute();
	virtual bool OnDestory();
public:
	void update( float dt );
public:
	IActionAnimationPlayToFrame(void);
	virtual ~IActionAnimationPlayToFrame(void);
private:
	int		_nFrameTarget;	//Ŀ��֡
	int		_nFrameBegin;	//��ʼ֡
	float	_fTimePass;		//ʱ������
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationBoneAdd
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sParentBone,const std::string& sNewBone,Node* pNode );
public:
	virtual bool OnExecute();
	virtual bool OnDestory();
public:
	IActionAnimationBoneAdd(void);
	virtual ~IActionAnimationBoneAdd(void);
private:
	std::string _sParentBone;
	std::string _sNewBone;
	Node*		_pNode;
};


//////////////////////////////////////////////////////////////////////////
class IActionAnimationDisplayAdd
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sName,int nDisplayIndex ,int nTargetIndex);
public:
	virtual bool OnExecute();
public:
	IActionAnimationDisplayAdd(void);
	virtual ~IActionAnimationDisplayAdd(void);
private:
	std::string _sName;
	int			_nDisplayIndex;
	int			_nTargetIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationDisplayRemove
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sName,int nIndex);
public:
	virtual bool OnExecute();
public:
	IActionAnimationDisplayRemove(void);
	virtual ~IActionAnimationDisplayRemove(void);
private:
	std::string _sName;
	int			_nIndex;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationDisplayChange
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sName,int nIndex,bool bForce);
public:
	virtual bool OnExecute();
public:
	IActionAnimationDisplayChange(void);
	virtual ~IActionAnimationDisplayChange(void);
private:
	std::string _sName;
	int			_nIndex;
	bool		_bForce;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationPlayMusic
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sFilePath,bool bLoop);
public:
	virtual bool OnExecute();
public:
	IActionAnimationPlayMusic(void);
	virtual ~IActionAnimationPlayMusic(void);
private:
	std::string _sFilePath;
	bool		_bLoop;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationPlaySound
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sFilePath,bool bLoop);
public:
	virtual bool OnExecute();
public:
	IActionAnimationPlaySound(void);
	virtual ~IActionAnimationPlaySound(void);
private:
	std::string _sFilePath;
	bool		_bLoop;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationCallBack
	:public	IActionAnimation
{
public:
	bool Init(int nUserInt);
public:
	virtual bool OnExecute();
public:
	IActionAnimationCallBack(void);
	virtual ~IActionAnimationCallBack(void);
private:
	int			_nUserInt;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationMulitQueue
	:public	IActionAnimation
	,public HAnimationQueue
{
public:
	bool Init(CAnimationQueue* pParent);
	CAnimationQueueMulit* GetMulitQueue();
public:
	virtual bool OnExecute();
	virtual bool OnAnimationSpeed(int nSpeed);
	virtual bool OnDestory();
private:
	virtual bool OnAnimationComplete();		//���еĶ����
public:
	IActionAnimationMulitQueue(void);
	virtual ~IActionAnimationMulitQueue(void);
private:
	CAnimationQueueMulit* _pQueue;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationNextFrame
	:public	IActionAnimation
{
public:
	bool Init(float fDuration,const Point& ptPostion,float fRotation,GLubyte uOpacity,float fScale,const std::string& sAnimationName);
public:
	virtual bool OnExecute();
private:
	void CallBackFuncN( Node* pNode );
public:
	IActionAnimationNextFrame(void);
	virtual ~IActionAnimationNextFrame(void);
private:
	float		_fDuration;
	Point		_ptPostion;
	float		_fRotation;
	GLubyte		_uOpacity;
	float		_fScale;
	std::string _sAnimationName;
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationExit
	:public	IActionAnimation
{
public:
	bool Init();
public:
	virtual bool OnExecute();
public:
	IActionAnimationExit(void);
	virtual ~IActionAnimationExit(void);
};

//////////////////////////////////////////////////////////////////////////
class IActionAnimationOpenUrl
	:public	IActionAnimation
{
public:
	bool Init(const std::string& sUrl);
public:
	virtual bool OnExecute();
public:
	IActionAnimationOpenUrl(void);
	virtual ~IActionAnimationOpenUrl(void);
private:
	std::string _sUrl;
};

//////////////////////////////////////////////////////////////////////////
class IActionSpinePlayByName
	:public	IActionAnimation
{
public:
	bool Init(const VectorString& vName ,int nLoop,float fDelay);
public:
	virtual bool OnExecute();
	virtual bool OnDestory();
private:
	bool CallBackOver(SkeletonAnimation* pAnimation);
public:
	IActionSpinePlayByName(void);
	virtual ~IActionSpinePlayByName(void);
private:
	VectorString	_vName;
	int				_nLoop;
	float			_fDelay;
};
//////////////////////////////////////////////////////////////////////////
class IActionAnimationSpeed
	:public	IActionAnimation
{
public:
	bool Init(float fSpeed);
public:
	virtual bool OnExecute();
public:
	IActionAnimationSpeed(void);
	virtual ~IActionAnimationSpeed(void);
private:
	float	_fSpeed;
};
//////////////////////////////////////////////////////////////////////////
template<typename T>
class IActionAnimationCallBackFunction
	:public	IActionAnimation
{
public:
	bool Init(const T& tFun){
		_tFun = tFun;
		return true;
	}
public:
	virtual bool OnExecute(){
		_tFun();
		return true;
	}
public:
	IActionAnimationCallBackFunction(void){SetActionType(ACTION_CALL_BACK_FUNCTION);}
	virtual ~IActionAnimationCallBackFunction(void){}
private:
	T _tFun;
};

#endif //MACRO_LIB_COCOS2D
