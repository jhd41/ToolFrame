#pragma once

#pragma warning(disable:4996)
#pragma warning(disable:4099)
#pragma warning(disable:4244)
#pragma warning(disable:4251)

// #pragma warning(disable:4819)

#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

//����cocos2dxͷ�ļ�
#include "cocos2d.h"
#include "CCArmature.h"
#include "CCTouch.h"

#include "cocos-ext.h"

//CocoStudio
#include "cocostudio/CocoStudio.h"

#include "UIWidget.h"
#include "UILayout.h"
#include "UIButton.h"
#include "UICheckBox.h"
#include "UIImageView.h"
#include "UILoadingBar.h"
#include "UIListView.h"
#include "UIScrollView.h"
#include "UIPageView.h"
#include "UIText.h"
#include "UITextAtlas.h"
#include "UITextField.h"
#include "UIHelper.h"
#include "UISlider.h"
#include "UITextBMFont.h"

//Spine
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"

//AudioEngine
#include "AudioEngine.h"

//���崴������
#define COCOS2DX_CREATE(classname)		public: static classname* Create(){classname* p= new classname();p->autorelease(); return p;}
#define COCOS2DX_CREATE_INIT(classname)	public: static classname* Create(){classname* p= new classname();if(p && p->init()){p->autorelease();}else{ CC_SAFE_DELETE(p);}; return p;}

//���峣��
enum{
	Z_ORDER_MAX = MACRO_INT_MAX,
};

//��������
typedef std::vector<cocos2d::Ref*>				VectorRef;
typedef std::vector<cocos2d::Node*>				VectorNode;
typedef std::vector<cocos2d::Sprite* >			VectorSprite;
typedef std::vector<cocos2d::Point>				VectorPoint;
typedef std::vector<cocos2d::Touch*>			VectorTouch;

typedef std::map<std::string,cocos2d::Node*>	MapStringNode;
typedef std::multimap<int,cocos2d::Node*>		MultiMapIntNode;
typedef std::map<std::string,cocos2d::Node*>	MapStringNode;

//CocoStudio
typedef std::vector<cocos2d::ui::Widget*>		VectorWidget;
typedef std::map<int,cocos2d::ui::Widget*>		MapIntWidget;
typedef std::vector<cocos2d::ui::CheckBox*>		VectorCheckBox;
typedef std::vector<cocos2d::ui::Button*>		VectorButton;
typedef std::vector<cocos2d::ui::TextAtlas*>	VectorTextAtlas;
typedef std::vector<cocos2d::ui::LoadingBar*>	VectorLoadingBar;
typedef std::vector<cocos2d::ui::Layout*>		VectorLayout;

//Spine
typedef std::vector<spine::SkeletonAnimation*>	VectorSpineAnimation;
typedef std::map<std::string,spSkeletonData*>	MapStringSkeletonData;
typedef std::map<std::string,spAtlas*>			MapStringAtlas;

//�����ֶ�
#define CFIELD_COLOR3D(arg)			CFIELD_REF(cocos2d::ccColor3B,arg,clr)

//��д����:
//Panel(���)		-> PNL
//TextField(�����)	-> TF
//Label(�ı���)		-> LB
//TextButton(��ť)	-> BTN
//CheckBox(��ѡ��)	-> CB
//ImageView(ͼƬ)	-> IMG

//������ӵĶ�����Ч
enum ECocosAction
{
	COCOS_ACTION_INVAILD,

	COCOS_ACTION_SET_VALUE,			//����ֵ
	COCOS_ACTION_SHAKE,				//��
	COCOS_ACTION_ARMATURE_MONITOR,	//����Armature
	COCOS_ACTION_SPINE_MONITOR,		//����Spine
	
	COCOS_ACTION_ROTATE_TO,		//��ת��
	COCOS_ACTION_SCALE_TO,		//���ŵ�
	COCOS_ACTION_FADE_TO,		//͸����
	COCOS_ACTION_MOVE_TO,		//�ƶ���
	COCOS_ACTION_SKEW_TO,		//Ť����
	COCOS_ACTION_JUMP_TO,		//������
	COCOS_ACTION_TINT_TO,		//Ⱦɫ��

	COCOS_ACTION_MAX,
};

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace spine;

//���庯��ָ��
typedef std::function<bool(Armature* pArmature)>																									FnActionArmatureOver;
typedef std::function<bool(Armature* pArmature, MovementEventType eEventType, const std::string& sName)>											FnActionArmatureMovement;

typedef std::function<bool(SkeletonAnimation* pAnimation, spTrackEntry* entry, spEvent* event,const std::string& sEvent,const std::string& sEventArg)>	FnActionSpineEvent;
typedef std::function<bool(SkeletonAnimation* pAnimation)>																							FnActionSpineOver;

#endif //MACRO_LIB_COCOS2D
