#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

#include "MacroCocos2dx.h"
#include "MacroDefineEx.h"

//ע��:
//Cocos2d���õ�������Ϊ����ԭ��
class TOOLFRAME_DLL ApiCocos2dx{
public:
	//�滻Widget
	static bool ReplaceNode(Node* pNode,Node* pNodeTarget);
	static bool ReplaceNode(Node* pNode,Node* pNodeTargetRoot,const std::string& sName);

	//����Widget
	static bool PositionNode(Node* pNode,Node* pNodePosition);
	static bool PositionNode(Node* pNode,Node* pNodePositionRoot,const std::string& sName);

	static bool		SetAccelerometerEnabled(bool bEnabled);//���豸��������Ӧ
	static float	GetAnimationInterval();//��ȡ����֡

	//���
	static bool Merge(VectorNode& vNode,const VectorSpineAnimation& vSrc);
	static bool Merge(VectorNode& vNode,Node* pNode);

	//ɾ��
	static bool Retain(Ref* ref);
	static bool Release(Ref* ref);
	static bool	ReleaseNextFrame(Ref* ref);

	//��Ļ
	//��ȡ��Ļ�м��
	static Point GetScreenCenterPoint();
	static Point GetScreenPoint(const Point& pt);//�ٷֱ�
	static Point GetScreenPoint(float fX,float fY);//�ٷֱ�

	//�����ڵ�
	static Scene* GetRunningSceneNode();

	//��ȡ�ӿ�
	static const Point GetVisibleRectLeftTop();
	static const Point GetVisibleRectRightTop();
	static const Point GetVisibleRectLeftDown();
	static const Point GetVisibleRectRightDown();

	//����
	static bool			IsOutScreen(const Node* pNode);

	//����
	static bool			ReplaceScene(Scene* pScene);//�����л�

	//�󶨺�
	static bool			IsIntersects(const Node* pNode1,const Node* pNode2);//�Ƿ��ཻ

	//��������Ϊ���ڵ�����
	static	bool SetPostionCenter(Node* pNode);


	//��������Ϊ���ڵ�İٷֱ� ����Ϊ 0.5 0.5
	static	bool SetPostionCenter(Node* pNode,const Point& pt);

	//�޸�������е�����λ��
	static bool FixPositionInPanel(Node* pPanel);

	//����ê��
	static	bool SetWorldAnchorPoint(Node* pNode,const Vec2& ptWorld);

	//���þ�������Ļ�м�
	static bool SetWorldPostionWithScreenCenter(Node* pNode);
	static bool SetWorldPostionWithScreenPoint(Node* pNode,float fX,float fY);///�������Ļ�İٷֱ�

	//���ð󶨺�
	static bool	SetWorldingBoundingWithOther(Node* pNode, Node* pOther);

	//����ê��
	static bool SetAnchorPoint(Node* pNode,const Vec2& pt);
	static bool SetAnchorPoint(Node* pNode,int x,int y);

	//��ȡê��
	static const Vec2& GetAnchorPoint(Node* pNode);

	//�޸�ê��
	static bool FixAnchorPoint(Node* pNode);

	//�����Ƿ�ɼ�
	static bool SetVisible(VectorNode& vNode,bool bVisible);

	//������ɫ
	static bool SetColor(Node* pNode,const Color3B& clr);
	static bool SetColor(VectorNode& vNode,const Color3B& clr);

	//�����ͼ����
	static CCTexture2D* CacheTexture(const std::string& sPath);

	//��������
	static Sprite* CreateSprite(const std::string& sPath);
	static Sprite* CreateSprite(CCTexture2D* pTexture);

	//����SpriteBatch
	static SpriteBatchNode* CreateSpriteBatch(const std::string& sPath);
	static SpriteBatchNode* CreateSpriteBatch(CCTexture2D* pTexture);

	//����Image
	static Image*	CreateImage(const Sprite* pSprite);
	static Image*	CreateImage( const std::string& sPath);

	//����������
	static LoadingBar*		CreateLoadingBar(const std::string& sPath);

	//������ͼ
	static TMXTiledMap*		CreateTiledMap(const std::string& sPath);

	//����Ƥ��
	static Skin*			CreateSkin(const std::string& sPath);

	//��Ӿ��鼯��
	static SpriteFrame*		CreateSpriteFrame(const std::string& sPath,const Rect& rRect);
	static bool				CacheSpriteFrames(const std::string& sPath);

	//������ͼ
	static bool				LoadTexture(Button* btn,			const std::string& sPath,ui::Widget::TextureResType texType = ui::Widget::TextureResType::LOCAL); 
	static bool				LoadTexture(LoadingBar* pBar,		const std::string& sPath,ui::Widget::TextureResType texType = ui::Widget::TextureResType::LOCAL); 
	static bool				LoadTexture(ImageView* pImageView,	const std::string& sPath,ui::Widget::TextureResType texType = ui::Widget::TextureResType::LOCAL); 
	//��ȡ͸��ֵ
	static int				GetOpacityWithPoint(const Sprite* pSprite, const Point& pt);
	static int				GetOpacityWithPoint(const Image* pImage, const Point& pt);
	static int				GetOpacityWithPoint(const ImageView* pImgView, const Point& pt);

	//�����ı�
	static bool	SetText(TextField* pText,const std::string& sText);
	static bool SetText(Text* pText,	 const std::string& sText);

	//������ͼ
	static bool SetTexture(Sprite* pSprite,const std::string& sPath);

	//����ȷ��Z-Order ����˳��
	static bool RezorderBySeq(Node* pNodeParent,VectorSprite& vNode );

	//����Z-Order ����˳��
	static bool SetZorderBySeq(Node* pNodeParent,VectorNode& vNode,int nZ=0);
	static bool SetZorderBySeq(Node* pNodeParent,VectorSprite& vNode,int nZ=0);

	//Release
	static bool Release(VectorNode& vNode);

	//��ȡ���������Ľڵ�
	static bool		FindTouchedNode( VectorNode& vNodeDes,VectorNode& vNodeSrc,CCTouch *pTouch );

	//�ж��Ƿ������˽ڵ�
	static bool		IsTouchedNode(const Node* pNode,const Touch* touch);
	static bool		IsTouchedNode(const Widget* pNode,const Touch* touch);

	//���� - ���ҽڵ�
	static Node*	FindTouchedNode(const VectorNode& vNode,const Touch* touch);
	static Widget*	FindTouchedNode(const VectorWidget& vNode,const Touch* touch);

	static Widget*	FindTouchedNode(const MapIntWidget& vNode,const Touch* touch);

	static Node*	FindTouchedNode(const Touch* touch,Node* pNode);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3,Node* pNode4);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3,Node* pNode4,Node* pNode5);

	//ģ�����������
	static int& GetTouchBlurDistance();//��ô���ģ���������
	static int& SetTouchBlurDistance(int nTouchFar);
	static bool IsTouchBlur(Touch* touch);//�Ƿ�������ģ������
	static bool IsTouchBlur(Touch* touch,int nDistance);

	//�������
	static Size	Plus(const Size& a,const Size& b);
	static Size&	SelfPlus(Size& self,const Size& other);
	static Size				Max(const Size& rSize1,const Size& rSize2);

	//�������
	static Point	Plus(const Point& a,const Point& b);
	//�������
	static Point	Subtract(const Point& a,const Point& b);

	//������ ���
	static Node*	FindNodeByBoundingBoxMostWide(const VectorNode& vNode);
	static Node*	FindNodeByBoundingBoxMostHigh(const VectorNode& vNode);
	static Node*	FindNodeByBoundingBoxMostWide(const Vector<Node*>& vNode);
	static Node*	FindNodeByBoundingBoxMostHigh(const Vector<Node*>& vNode);

	//�������
	static bool		IsEmpty(CCArray* pArray);
	static Node*	FindFirstNode( CCArray* pArray);
	static Node*	FindLastNode( CCArray* pArray);
	static Node*	FindNodeAtIndex(CCArray* pArray,UINT uIndex);
	static UINT		GetCount(CCArray* pArray);

	//��ȡ�󶨺�����
	static Point	GetCenterByBoundingBox(Node* pNode);

	//��ȡ��������
	static Point	GetRectCenterPoint(const Rect& rRect);

	//����ߴ� �ڵ�ߴ�->����ߴ�
	static Size		CalWorldSize(const Size& rSizeNode,const Node* pNode);

	//����ߴ� ����ߴ�->�ڵ�ߴ�
	static Size		CalSizeInParent(const Size& rSizeWorld,Node* pNode);

	//�����ڸ��ڵ��ϵ�����
	static Point	CalPointInParent(const Point& ptWorld,Node* pNode);

	//����ȡ�ڽڵ��ϵ�����
	static Point	CalPointInNode(const Point& ptWorld,Node* pNode);

	//������ʾ˳������
	static bool	SortByTop(VectorNode& vNodes);

	//��ø��ڵ�ָ�뼯��
	static bool	GetParentNodes(VectorNode& vNodes,Node* pNode);

	//����Node By Tag
	static Node*	FindNodeByTag(const VectorNode& vNode,int nTag );
	static Widget*	FindNodeByTag(const VectorWidget& vNode,int nTag );

	//���ҽڵ�
	static Node*	FindNode(const Node* pNode,const std::string& sName);
	template<typename T>
	static T*		FindNode(const Node* pNode,const std::string& sName);
	template<typename T>
	static bool		FindNode(T*& pFind,const Node* pNode,const std::string& sName);

	//���� Z -Order
	static bool		SetZOrder(Node* pNode,int nZOrder);

	//������ݳߴ�
	static const Size& GetContentSize(const Node* pNode);

	//��ýڵ�����λ��
	static Point	GetWorldPostion(const Node* pNode);

	//��ýڵ�����ĵ�����λ��
	static Point	GetWorldCenter(const Node* pNode);
	static Point	GetWorldCenter(const Node* pNode,const Point& pt);
	
	//��ýڵ�����
	static Point	GetContentSizeCenter(const Node* pNode);
	static Point	GetContentSizeCenter(const Node* pNode,const Point& pt);

	//������һ���ڵ����������λ������ ��ǰ�ڵ�
	static bool		SetWorldCenterWithOther(Node* pNode,const Node* pOther);

	//���ýڵ�����λ��
	static bool		SetWorldPostion(Node* pNode,const Point& ptWorld);
	//���ýڵ�����λ��
	static bool		SetWorldPostion(Node* pNode,const Node* pOther);

	//��ȡ
	static Vec2		GetWorldAnchorPointInPoints(Node* pNode);

	//��ýڵ�󶨺�����λ��
	static Rect	GetWorldBoundingBox(const Node* pNode);

	//���ýڵ�󶨺�����λ��
	static bool		SetWorldBoundingBox(Node* pNode,const Rect& rWorld);//ͨ��ֱ�Ӱ󶨺н�������
	static bool		SetWorldBoundingBox(Node* pNode,const Rect& rWorld, const Point& ptWorldPosition);//���������е�����(�������� ��ʹ�� ê�� ���м��� ͨ���������)

	//�Ƿ�ӵ�к���
	static bool				IsChildEmpty(const Node* pNode);

	//��ú��ӵĸ���
	static UINT				GetChildCount(Node* pNode);

	//��õ�Index������
	static Node*	FindChildByIndex(Node* pNode,uint uIndex);

	//���Һ���(Tag)
	static	Node*	FindChildByTag(const Node* pWidget,int nTag);

	//�Ƴ�����
	static	bool			RemoveChildren(VectorNode& vNode,bool bClean =true);
	static	bool			RemoveChildren(VectorWidget& vNode,bool bClean =true);

	//�Ƴ�����(Tag)
	static	bool			RemoveChildByTag( Node* pWidget,int tag, bool cleanup = true);
	static	bool			RemoveChildByTag(VectorNode& vNode,int nTag,bool bClean =true);
	
	//�Ƴ����к���
	static	bool			RemoveAllChildren( Node* pWidget);

	//��õ�ǰ�ӽڵ�������Z-Order
	static int				GetChildZOrderMax(const Node* pNode);

	//������ڵ㶥��
	static bool				AddChildTop(Node* pParent,Node* pChild);

	//�ҵ����ڵ�
	static Node*			FindRootNode(Node* pNode);

	//�����������
	//static CCRenderTexture* CreateStroke(CCLabelTTF* pNode,float fFontSize,const ccColor3B& ccColor);

	//��ת
	static bool Flip(Node* pNode,bool bHorizontal=false,bool bVertical=false);//ˮƽ��ת����ֱ��ת

	//��������
	static bool		SetString(LabelTTF* pNode,const std::string& sString);

	//ת����ɫֵ
	static ccColor3B ToColor(UINT32 uColor);

	static std::string	LoadFile( const std::string& sFileName );//cocos2dx�����loadfile һ�㲻Ҫ��

	static std::string GetWriteableDir();

	//���û���ʱ��Ĵ�С(Ŀǰcocos2d-x�ƺ����ڿ�ƽ̨��BUG��˶��װһ��)
	static bool SetPointSize(float fSize);

	//����ָ��Widget����(�±��1��ʼ)
	template<typename T>
	static bool FindNode(std::vector<T*>& vWidget, const Node* pRootWidget,const std::string& sName);
	template<typename T>
	static bool FindNode(std::vector<T*>& vWidget, const Node* pRootWidget,const std::string& sName,int nCount );//У����ȷ��

	//����ָ��Widget By Tag
	static Widget* FindWidgetByTag(const VectorWidget& vWidget,int nTag);

	//Ϊ��ť�������ͳһ�ص�
	static bool	AddTouchEvent(Node* pWidget,Ref* target,SEL_TouchEvent selector);
	static bool	AddTouchEvent(VectorNode& vWidget,Ref* target,SEL_TouchEvent selector);	
	static bool AddTouchEvent(Node* pWidgetRoot,const std::string& sName,Ref* target,SEL_TouchEvent selector);
	static bool	AddTouchEvent(Node* pWidget,Widget::ccWidgetTouchCallback fnCallBack);
	
	//��ť
	static bool SetClickCallBack(Widget* pNode, Widget::ccWidgetClickCallback fn);
	static bool SetClickCallBack(Node* pRoot, const std::string& sName, Widget::ccWidgetClickCallback fn);
	static bool SetTouchCallBack(Widget* pNode, Widget::ccWidgetTouchCallback fn);
	static bool SetTouchCallBack(Node* pRoot, const std::string& sName, Widget::ccWidgetTouchCallback fn);

	//����UI�ļ�
	static Node* LoadUIFile(const std::string& sFileName);

	//�л�������
	static bool	SwitchScreen(); 
	static bool	SwitchScreen(bool bLandscape);

	//�Ƿ����
	static bool	IsLandscape(); 
 
	//�������ݴ�СΪ��Ļ��С
	static bool SetContentSizeWithScreenSize(Node* pNode);

	//������Ƴߴ�(������ֱ���֧��)
	static bool SetDesignResolutionSize(float fWidth = 0.0f,float fHeight = 0.0f);

	//��ȡ��Ƴߴ�
	static const Size& GetDesignResolutionSize();

	//������ʣ��ߴ�(��Ƴߴ� ��ȥ �����еĽڵ� �ߴ�)
	static Size CalDesignResolutionSizeResidue(const Node* pRoot,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");
	static Size CalDesignResolutionSizeResidue(const Node* pRoot,const VectorString& vName);

	//����ܿ��
	static Size CalSize(const Node* pRoot,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");
	static Size CalSize(const Node* pRoot,const VectorString& vName);

	//���ý�����ݿ��Ϊ��Ƴߴ�
	static bool SetContentSize(Node* pNode,const Size& size);
	static bool SetContentSizeWithDesignSize(Node* pNode);
	static bool SetContentSizeWithDesignSize(Node* pNode,bool bWidth);
	static bool SetContentSizeWithChildrenSum(Node* pWidget,bool bWidth);
	static bool SetContentSizeWithChildrenMax(Node* pWidget,bool bWidth);
	static bool SetContentSizeWithChildren(Node* pWidget,bool bWidth);

	//��������
	static bool			SetName(Widget* pWidget,const std::string& sName);

	//��ȡ����
	static std::string	GetName(const Widget* pWidget);
	static std::string	GetName(const Ref* pObj);

	//��ȡ�ߴ�
	static const Size&	GetSize(Widget* pWidget);

	//��ȡ�ߴ�����
	static Point		GetSizeCenter(Widget* pWidget);

	//Ч��
	static bool StopAllAction(Node* pNode);
	static bool StopAction(Node* pNode,Action* pAction);
	static bool StopActionByTag(Node* pNode,int nTag);

	static Action* FindActionByTag(Node* pNode,int nTag);
	template<typename T>
	static T* FindActionByTag(Node* pNode,int nTag);

	static int GetActionsCount(Node* pNode);//ͳ��Action����

	//Ч��	- ����Ч��
	static bool ActionRotateTo(Node* pNode,float fAngle,float fDuration = 1.f);//��ת��
	static bool ActionRotateBy(Node* pNode,float fAngle,float fDuration = 1.f);//��ת
	static bool ActionScaleTo(Node* pNode,float fScale,float fDuration = 1.f);//���ŵ�
	static bool ActionScaleBy(Node* pNode,float fScale,float fDuration = 1.f);//����
	static bool ActionFadeTo(Node* pNode,GLubyte opacity,float fDuration = 1.f);//͸����
	static bool ActionFadeIn(Node* pNode,float fDuration = 1.f);				//����
	static bool ActionFadeOut(Node* pNode,float fDuration = 1.f);				//����
	static bool ActionMoveTo(Node* pNode,const Vec2& ptPostion,float fDuration = 1.f);//�ƶ���
	static bool ActionMoveBy(Node* pNode,const Vec2& ptPostion,float fDuration = 1.f);//�ƶ���
	static bool ActionSkewTo(Node* pNode,float sx,float sy,float fDuration = 1.f);//Ť����
	static bool ActionSkewBy(Node* pNode,float sx,float sy,float fDuration = 1.f);//Ť��
	static bool ActionJumpTo(Node* pNode,const Vec2& ptPostion,float fHeight,int nJumps,float fDuration = 1.f);//������
	static bool ActionJumpBy(Node* pNode,const Vec2& ptPostion,float fHeight,int nJumps,float fDuration = 1.f);//����
	static bool ActionBlink(Node* pNode,int nBlinks,float fDuration = 1.f);//��˸
	static bool	ActionTintTo(Node* pNode,GLubyte red, GLubyte green, GLubyte blue,float fDuration = 1.f);//Ⱦɫ(�޸Ķ���ɫ Ĭ�ϰ�ɫ)
	static bool	ActionTintBy(Node* pNode,GLubyte red, GLubyte green, GLubyte blue,float fDuration = 1.f);//Ⱦɫ(�޸Ķ���ɫ Ĭ�ϰ�ɫ)

	//���÷���Ч��
	static bool	ActionsTurnOver(Node* pSrc,Node* pDes,float fTurnTime,float fDelayTime);
	static bool ActionsTurn(Node* pNode,float fDuration = 0.3f);//��ת

	//������ʾͼƬ������LOGO
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath );
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath ,SEL_CallFunc fnCallBack);
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath1 ,const std::string& sPath2);
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath1 ,const std::string& sPath2,SEL_CallFunc fnCallBack);

	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const VectorString& vPath );
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const VectorString& vPath ,SEL_CallFunc fnCallBack);

	//Ч�� - ���뵭�� �ı�ڵ�
	static bool ActionsChangeNodeFade(Node* pSrc,Node* pDes,float fTime=2.0f);

	//Ч�� - ��ֵ����
	static bool	ActionsSetValue(LoadingBar* pNode,const float& nValue,float fDuration = 1.f);
	static bool	ActionsSetValue(Text* pNode,const int& nValue,float fDuration = 1.f);
	static bool	ActionsSetValue(Text* pNode,const float& fValue,float fDuration = 1.f);
	static bool	ActionsSetValue(Text* pNode,const std::string& sValue,float fDuration = 1.f);
	static bool	ActionsSetValue(TextAtlas* pNode,const int& nValue,float fDuration = 1.f);
	template<typename T,typename TValue>
	static bool	ActionsSetValue(Node* pNode,const TValue& fValue,float fDuration = 1.f);
	template<typename T,typename TValue>
	static bool	ActionsSetValue(const std::string& sName,const Node* pRootWidget,const TValue& fValue,float fDuration = 1.f);

	//��(���ȣ�Ƶ��)
	static bool ActionsShake(Node* pNode,float fduration,int nStrength,int nFrequency,const Vec2& ptDirect);
	static bool ActionsShake(Node* pNode,float fduration,int nStrength,int nFrequency=1);

	//��ȡ��������
	static Rect	 GetVisibleRect();
	static Point GetVisibleCenter();
	static Size  GetVisibleSize();

	//�Ƿ񳬹���Ļ
	static bool IsOutOfScreen(const Node* pRoot,bool bWidth,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");
	static bool IsOutOfScreen(const Node* pRoot,const VectorString& vWidget,bool bWidth);

	//���û�������
	static bool SetRotation(Node* pNode,float fRotation);
	static bool SetOpacity(Node* pNode,GLubyte uOpacity,bool bChildren = true);

	static float GetRotation(Node* pNode);

	//�Ƴ��ڵ�
	static bool RemoveFromParentAndCleanup(Node* pNode,bool bCleanUp = true);
	static bool RemoveFromParentAndCleanup(VectorNode& vNode,bool bCleanUp = true,bool bClearVector = true);
	static bool RemoveFromParentAndCleanup(VectorWidget& vWidget,bool bCleanUp = true,bool bClearVector = true);
	static bool RemoveFromParentAndCleanupNextFrame(Node* pNode ,bool bCleanUp = true);//��һ֡ ɾ��

	//�Ƴ��ڵ� - Tag
	static bool RemoveFromParentByTag(VectorNode& vNode,int nTag,bool bClean =true);
	static bool RemoveFromParentByTag(VectorWidget& vNode,int nTag,bool bClean =true);

	static int	RemoveFromParentAllByTag(VectorNode& vNode,int nTag,bool bClean =true);
	static int	RemoveFromParentAllByTag(VectorWidget& vNode,int nTag,bool bClean =true);

	//�ı丸�ڵ�
	static bool ChangeParentNode(Node* pNode,Node* pParent ,bool bKeepWorld = true,bool bCleanUp = true,int nZOrder = 0);//�ı丸�ڵ�
	static bool ChangeParentNode( const Node* pRoot,const std::string& sChild,const std::string& sParent,bool bKeepWorld = true,bool bCleanUp = true);
	static bool ChangeParentNode(VectorNode& vNode,const VectorNode& vParent,bool bKeepWorld = true,bool bCleanUp = true);
	static bool ChangeParentNode(VectorNode& vNode,Node* pParent,bool bKeepWorld = true,bool bCleanUp = true);

	//�ڵ����(����Ӧ�ã������ֲ��ɼ� �򲻻�Ӧ�ò���)
	static bool UpdateNode(Node* pNode,float fDelta = 0.f);
	static bool VisitNode(Node* pNode);
	static bool UpdateVisitNode(Node* pNode,float fDelta = 0.f);

	static bool SetScale(Node* pTarget,float fScale);
	static bool SetScale(Node* pTarget,float fScaleX,float fScaleY);

	static bool SetPostion(Node* pTarget,const Point& ptPostion);
	static bool SetPostion(Node* pTarget,const Node* pSrc);
	static bool SetPostion(Node* pTarget,float fX,float fY);

	static bool SetPostionZero(Node* pTarget);

	static bool SetPostionOffset(Node* pTarget,const Point& ptPostion);

	static const Point& GetPostion(Node* pTarget);

	static bool IsVisible(Node* pWidget);

	static bool SetVisible(Node* pWidget,bool bVisible);
	static bool SetVisible(Widget* pWidget,bool bVisible);//���ýڵ�ɴ������� ���غ� ������������Ҫ���¿�����������Ч
	static bool SetVisible(const VectorNode& vWidget,bool bVisible);
	static bool SetVisible(Node* pRootWidget,const std::string& sName,bool bVisible);
	static bool SetVisible(Node* pRootWidget,const std::string& sName,int nCount,bool bVisible);

	static bool SetGroupVisible(Node* pRootWidget,const std::string& sName,int nCount,int nValue);//С���������ֵ��nValue��Ա���ɼ������򶼲��ɼ�

	static bool IsChecked(Widget* pRootWidget,const std::string& sName);//���û�ҵ�Ҳ����false,Ҳ����˵ �����trueһ���ǶԵ�
	static bool IsChecked(CheckBox* pWidget);

	static bool SetChecked(Widget* pRoot,const std::string& sName,bool bChecked);
	static bool SetChecked( CheckBox* pWidget ,bool bChecked);

	static bool	SetChecked(VectorCheckBox& vCheckBox,bool bChecked);
	static bool	SetSingleChoices(ListView* pLvTeam,const Ref* pSender,const std::string& sCheckBoxName);

	static bool SetEnabled(Node* pWidget,bool bEnabled);
	static bool SetEnabled(Node* pRootWidget,const std::string& sName,bool bEnabled);
	static bool SetEnabled(Ref* pSender,bool bEnabled);

	static bool SetTouchEnabled(Node* pNode, bool bEnabled);

	static bool SetTag(Node* pNode,int nTag);
	static bool SetTag(Node* pRootWidget,const std::string& sName,int nTag);

	static int	GetTag(const Node* pNode);
	static int	GetTag(const Node* pRootWidget,const std::string& sName);
	static int	GetTag(const Ref* pSender);

	static bool	SetTag(Action* pAction,int nTag);

	static bool SetTagWhithIndex(const VectorNode& vNode,int nIndexBegin =0);//����˳������ÿ���ڵ��Tag 
	static bool SetTagWhithIndex(const VectorWidget& vNode,int nIndexBegin =0);//����˳������ÿ���ڵ��Tag 

	static bool	SetLayoutParameter(Node* pDes,const Node* pSrc,LayoutParameter::Type eLayout);//LAYOUT_PARAMETER_RELATIVE
	static bool	SetLayoutParameter(Node* pDes,const Node* pSrc);//LAYOUT_PARAMETER_RELATIVE

																
	static  bool InsertBackNode(Node* pSrc, Node* pBack);//���һ�������ڵ�

	//ģ���¡
	static Node*	Clone(const Node* pSrc,bool bVisible = true);//��¡
	static Node*	Clone(const Node* pSrc,const Node* pTargetPostion,bool bVisible = true);//��¡��������Ŀ������
	template<typename T>
	static T*		Clone(const Node* pSrc,bool bVisible = true);
	template<typename T>
	static T*		Clone(const Node* pSrc,const Node* pTargetPostion,bool bVisible = true);

	static bool	InitTemplate(Node* pNode,bool bIgnoreContentAdaptWithSize=true);//��ʼ��ģ��
	static bool SetIgnoreContentAdaptWithSize(Node* pNode, bool bIgnoreContentAdaptWithSize = true, bool bChildren = true);

	//����ֵ
	static bool SetValue(Layout* pWidget,const std::string& sPath,Widget::TextureResType texType = Widget::TextureResType::LOCAL);
	static bool SetValue(TextField* pWidget,const std::string& sValue);
	static bool SetValue(Button* pWidget,const char* szValue,Widget::TextureResType texType = Widget::TextureResType::LOCAL);
	static bool SetValue(Button* pWidget,const std::string& sValue,Widget::TextureResType texType = Widget::TextureResType::LOCAL);
	static bool SetValue(Text* pWidget,const std::string& sValue);
	static bool SetValue(Text* pWidget,const int& nValue);
	static bool SetValue(Text* pWidget,const float& fValue);
	static bool SetValue(TextAtlas* pWidget,int nValue);
	static bool SetValue(TextAtlas* pWidget,const std::string& sValue);
	static bool SetValue(TextAtlas* pWidget,int nValue,const std::string& sTexturePath);
	static bool SetValue(TextAtlas* pWidget,const std::string& sValue,const std::string& sTexturePath);
	static bool SetValue(LabelBMFont* pWidget,int nValue);
	static bool SetValue(LabelBMFont* pWidget,const std::string& sValue);
	static bool SetValue(LabelBMFont* pWidget,int nValue,const std::string& sFontPath);
	static bool SetValue(LabelBMFont* pWidget,const std::string& sValue,const std::string& sFontPath);
	static bool SetValue(TextBMFont* pWidget,int nValue);
	static bool SetValue(TextBMFont* pWidget,const std::string& sValue);
	static bool SetValue(TextBMFont* pWidget,int nValue,const std::string& sFontPath);
	static bool SetValue(TextBMFont* pWidget,const std::string& sValue,const std::string& sFontPath);
	static bool SetValue(LoadingBar* pWidget,int nValue);
	static bool SetValue(LoadingBar* pWidget,float fValue);
	static bool SetValue(LoadingBar* pWidget,int nCur,int nMax);
	static bool SetValue(ImageView* pWidget,const std::string& sPath,Widget::TextureResType texType = Widget::TextureResType::LOCAL);
	static bool SetValue(CheckBox* pWidget,bool bChecked);

	template<typename T,typename TValue>
	static bool SetValue( Node* pNode,const TValue& tValue );

	template<typename T,typename TValue>
	static bool SetValue( const std::string& sName,Node* pRootWidget,const TValue& tValue );
	template<typename T,typename TValue>
	static bool SetValue(const std::string& sName, Ref* pRootWidget,const TValue& tValue );

	//��ȡֵ
	static bool GetValue(const TextField* pWidget,std::string& sValue);
	static bool GetValue(const TextAtlas* pWidget,int& nValue);
	static bool GetValue(const TextAtlas* pWidget,std::string& sValue);
	static bool GetValue(const Text* pWidget,std::string& sValue);
	static bool GetValue(const Text* pWidget,int& nValue);
	static bool GetValue(const Text* pWidget,float& fValue);
	static bool GetValue(const LoadingBar* pWidget,float& fValue);
	static bool	GetValue(const LoadingBar* pWidget,int& nValue);
	//static bool GetValue(const ImageView* pWidget,std::string& sValue);//��ȡ����ͼƬ·��

	template<typename T, typename TValue>
	static bool GetValue(const Node* pNode,TValue& fValue);
	template<typename T, typename TValue>
	static bool GetValue(const Widget* pRootWidget,const std::string& sName,TValue& tValue );

	static int			CalLines(const std::string& sString,int nWidth,int nFontSize);//��������(�����������ַ�)
	static bool			AutoHeight(Text* pNode,int nSpaceHeight=8,int nSpaceWidth=0);	//�����ı�����Ӧ�����߶�(��Ȳ���)

	static bool			Clear(ListView* pLv);
	static bool			PushBack(ListView* pLv,Node* pNode);

	static bool			Clear(PageView* pPv);
	static bool			PushBack(PageView* pPageView,Node* pNode);
	static Layout*		GetCurPage(PageView* pPv);
	static bool			ScrollToNext( PageView* pPv ,bool bNext = true,bool bCircle=true);

	//PageView
	static bool			PageAddImage( PageView* pPageView,const std::string& sImgPath,int nIndex = -1,bool bChangeSize = true);//�����ҳ��
	static bool			PageResetImage(PageView* pPageView);
	static bool			IsCurLastPage(PageView* pPageView);//�ж��Ƿ�Ϊ���һҳ

	static CheckBox*	AddEventListenerCheckBox(CheckBox* pCheckBox,Ref* target,SEL_SelectedStateEvent selector);
	static CheckBox*	AddEventListenerCheckBox(const Node* pRootWidget,const std::string& sName,Ref* target,SEL_SelectedStateEvent selector);

	//���
	static bool			SetGray(Node* pNode,bool bGray,bool bChildren = true);
	static bool			SetGray(Node* pRoot,const std::string& sName, bool bGray, bool bChildren = true);
	static bool			SetGray(VectorNode& vNode, bool bGray, bool bChildren = true);

	//ImageView
	static ImageView*	CreateImageView(const std::string& sFile,Widget::TextureResType texType = Widget::TextureResType::LOCAL);

	//����
	static bool			CacheArmatureFile(const std::string& sFileName);
	static Armature*	CreateArmature(const std::string& sName);
	static Armature*	CreateArmatureByFileName(const std::string& sName);

	//���� - ��֡
	static bool			IsEmptyMovement(const Armature* pArmature,const std::string& sName);
	static bool			IsEmptyMovement(const ArmatureAnimation* pAnimation,const std::string& sName);//�Ƿ��֡

	//���� - ��ȫ����
	static Armature*	PlayArmature( const std::string& sFileName, int nLoop = -1);
	static Armature*	PlayArmature( const std::string& sFileName,	const std::string& sName,	int nLoop = -1);
	static Armature*	PlayArmature( const std::string& sFileName,	const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static Armature*	PlayArmature( const std::string& sFileName,	const VectorString& vName,	int nLoop = -1);//��ȫ���� ���������ܲ��ŵ��������ţ�����������ʱ �����Ѿ��ڲ� �򲻲�
	
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName, int nLoop = -1);
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName,	const std::string& sName,	int nLoop = -1);
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName,	const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName,	const VectorString& vName,	int nLoop = -1);//��ȫ���� ���������ܲ��ŵ��������ţ�����������ʱ �����Ѿ��ڲ� �򲻲�

	static bool			PlayArmature( Armature* pArmature,			int nLoop = -1);
	static bool			PlayArmature( Armature* pArmature,			const std::string& sName,	int nLoop = -1);
	static bool			PlayArmature( Armature* pArmature,			const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static bool			PlayArmature( Armature* pArmature,			const VectorString& vName,	int nLoop = -1);//��ȫ���� ���������ܲ��ŵ��������ţ�����������ʱ �����Ѿ��ڲ� �򲻲�
	
	static bool			PlayArmature( ArmatureAnimation* pArmature,			int nLoop = -1);
	static bool			PlayArmature( ArmatureAnimation* pArmature,	const std::string& sName,	int nLoop = -1);
	static bool			PlayArmature( ArmatureAnimation* pArmature,	const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static bool			PlayArmature( ArmatureAnimation* pArmature,	const VectorString& vName,	int nLoop = -1);//��ȫ���� ���������ܲ��ŵ��������ţ�����������ʱ �����Ѿ��ڲ� �򲻲�

	static const std::string&	GetMovementName(const Armature* pArmature,int nIndex);
	static const std::string&	GetMovementName(const ArmatureAnimation* pArmature,int nIndex);
	static const VectorString&	GetMovementName(const Armature* pArmature);
	static const VectorString&	GetMovementName(const ArmatureAnimation* pArmature);
	static bool					GetMovementName(VectorString& vMovementName,const Armature* pArmature,const VectorInt& vIndex);
	static bool					GetMovementName(VectorString& vMovementName,const ArmatureAnimation* pArmature,const VectorInt& vIndex);

	static bool			IsHasMovementID(const Armature* pArmature,const std::string& sMovementID);//�Ƿ���ڸö���
	static bool			IsHasMovementID(const ArmatureAnimation* pArmature,const std::string& sMovementID);//�Ƿ���ڸö���

	static std::string	GetCurMovementID(const Armature* pArmature);
	static std::string	GetCurMovementID(const ArmatureAnimation* pArmature);

	static bool			IsCurMovementID(const Armature* pArmature,const std::string& sMovementID);
	static bool			IsCurMovementID(const ArmatureAnimation* pArmature,const std::string& sMovementID);

	static bool			AddDisplay(Armature* pArmature,const std::string& sBone,Node* pNode,int nIndex = -1,bool bRemoveFromParent = true ,bool bCleanUp = true);
	static bool			RemoveDisplay(Armature* pArmature,const std::string& sBone,int nIndex=0);
	static bool			ChangeDisplay(Armature* pArmature,const std::string& sBone,int nIndex=0,bool bForce = true);
	static bool			ReplaceDisplay(Armature* pArmature,const std::string& sBone,Node* pNode,bool bRemoveFromParent = false,bool bCleanUp = true);
	static bool			SetSpeed(Armature* pArmature,float fSpeed = 1.0f);
	static bool			AddBone(Armature* pArmature,const std::string& sParentBone,const std::string& sNewBone,Node* pNode);
	static const VectorString& GetAnimationMovementNames(const Armature* pArmature);			//���ӰƬ��������
	static const VectorString& GetAnimationMovementNames(const ArmatureAnimation* pArmature);	//���ӰƬ��������
	static size_t		GetAnimationCount(const Armature* pArmature);						//��ö����ĸ���
	static size_t		GetAnimationCount(const ArmatureAnimation* pArmature);				//��ö����ĸ���
	static int			GetAnimationFrameCount(const Armature* pArmature);					//��ö�������֡��
	static int			GetAnimationFrameCount(const ArmatureAnimation* pArmature);			//��ö�������֡��
	static int			GetAnimationCurrentFrameIndex(const Armature* pArmature);			//��ö�������֡��
	static int			GetAnimationCurrentFrameIndex(const ArmatureAnimation* pArmature);	//��ö�������֡��
	static bool			GotoAndPlay( Armature* pArmature,			int nFrameIndex);		//��ת��ָ��֡����Ϊ-1����ת�����һ֡
	static bool			GotoAndPlay( ArmatureAnimation* pArmature,	int nFrameIndex);		//��ת��ָ��֡����Ϊ-1����ת�����һ֡
	static bool			GotoAndPause( Armature* pArmature,			int nFrameIndex);		//��ת��ָ��֡����Ϊ-1����ת�����һ֡
	static bool			GotoAndPause( ArmatureAnimation* pArmature,	int nFrameIndex);		//��ת��ָ��֡����Ϊ-1����ת�����һ֡
	static bool			SetCallFuncNull(Armature* pArmature);
	static bool			SetCallFuncNull(ArmatureAnimation* pArmature);

	static Armature*	SetAnimationCallBackMovement(Armature* pArmature,FnActionArmatureMovement fnMovement);
	static Armature*	SetAnimationCallBackOver(Armature* pArmature, FnActionArmatureOver fnOver);
	//����
	static ParticleSystemQuad*	PlayParticle(const std::string& sFile);

	//��Ƶ
	static int			PlayAudio(const std::string& sPath, bool bLoop = false, float fVolume = 1.0f);//���ܾ�������
	
	static bool			SetAudioLoop(int nAudioID, bool bLoop);
	static bool			SetAudioVolume(int nAudioID, float fVolume);
	static bool			SetAudioPause(int nAudioID, bool bPause = true);
	static bool			SetAudioStop(int nAudioID);
	static bool			SetAudioCurrentTime(int nAudioID,float fSecond);
	static bool			SetAudioFinishCallback(int nAudioID, const std::function<void(int, const std::string&)>& callback);
	static bool			SetAudioMute(int nAudioID, bool bMute = true);//����ĳ��Ƶ����

	static bool			IsAudioLoop(int nAudioID);
	static float		GetAudioVolume(int nAudioID);
	static float		GetAudioCurrentTime(int nAudioID);
	static float		GetAudioDuration(int nAudioID);
	static int			GetAudioState(int nAudioID);
	
	static bool			SetAudioPauseAll(bool bPause = true);
	static bool			SetAudioStopAll();

	static bool			AudioUncache(const std::string& sPath);
	static bool			AudioUncacheAll();

	//��Ƶ����(�������)
	static int			PlaySound(const std::string& sPath, bool bLoop = false, float fVolume = 1.0f);	//�������� �ܾ�������
	static int			PlayMusic(const std::string& sPath, bool bLoop = true, float fVolume = 1.0f);		//���ű������� �Ὣǰһ����������ֹͣ �ܾ�������

	static bool			StopSound(int nAudioID);//ֹͣ����
	static bool			StopMusic();			//ֹͣ��������

	static bool			SetSoundMute(bool bMute);//����ȫ�־���
	static bool			SetMusicMute(bool bMute);//���ñ������־���

	static bool			IsSoundMute();		//�Ƿ�ȫ�־���
	static bool			IsMusicMute();		//�Ƿ񱳾����־���

	static int			GetMusicAudioID();	//��ȡ��������AudioID

	//�����Ƿ��Զ����ջ���
	static bool			SetAutoPurgeCache(bool bAuto);
	static bool			IsAutoPurgeCache();

	static bool			PurgeCachedData();	//�������л��������

	static bool			PurgeTextureCache(bool bRemoveAll = true);		//������ͼ����
	static bool			PurgeSpriteFramesCache(bool bRemoveAll = true);	//������ͼ����
	static bool			PurgeActionCache();								//����������
	static bool			PurgeArmatureCache();							//����������

	static Rect			TranWinRect(const Size& szie);//�����ƽ̨��ʾ����
	static Rect			TranWinRect(const Rect& rect);//�����ƽ̨��ʾ����
	static Rect			TranWinRect(const Node* pNode);

	//��ͼ
	static bool			ScreenShot(const std::string& sFileName);
	//ϵͳ
	static bool			Exit();
	static bool			SleepFreeTime();

	//�ж��Ƿ�Ϊָ��Widget
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3,const std::string& sName4);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3,const std::string& sName4,const std::string& sName5);

	static bool			IsTargetWidgetBegin(const Ref* pObj,const std::string& sName);//ֻ���ǰ�����ַ�
	static bool			IsTargetWidgetRange(const Ref* pObj,const std::string& sName,int nBegin,int nEnd);

	static int			GetWidgetNameIndex(const Ref* pObj,const std::string& sName,int nInvaild = -1);

	//�����¼�
	static bool			FireTouchedWithUI(const Vec2& ptUI);//UI����ϵ(�ݹ����)
	static bool			FireTouchedWithGL(const Vec2& ptGL);//GL����ϵ
	static bool			PostTouchedWithUI(const Vec2& ptUI);//UI����ϵ(������Ϣ���̶߳���)
	static bool			PostTouchedWithGL(const Vec2& ptGL);//GL����ϵ

	static bool			CloneFireTouched(const Ref* pObj);//��¡�����¼�
	static bool			ClonePostTouched(const Ref* pObj);//��¡�����¼�

	static const Vec2&	GetTouchBeganPosition(const Ref* pObj);//��ȡ����ʱ������(GL����ϵ)
	static const Vec2&	GetTouchEndPosition(const Ref* pObj);
	static const Vec2&	GetTouchBeganPosition(const Widget* pWidget);//��ȡ����ʱ������
	static const Vec2&	GetTouchEndPosition(const Widget* pWidget);

	//���� - ������
	static bool			SetStroke(LabelTTF* pText,	const Color4B &clrFont, float fSize);
	static bool			SetStroke(Label* pText,		const Color4B &clrFont, float fSize);
	static bool			SetStroke(Text* pText,		const Color4B &clrFont, float fSize);

	//���� - �����Ӱ
	static bool			SetShadow( LabelTTF* pText, const Color4B& clrShadow = Color4B::BLACK,const Size& fSize = Size(2,-2), float fBlur= 0 );
	static bool			SetShadow( Label* pText,	const Color4B& clrShadow = Color4B::BLACK,const Size& fSize = Size(2,-2), float fBlur= 0 );
	static bool			SetShadow( Text* pText,		const Color4B& clrShadow = Color4B::BLACK,const Size& fSize = Size(2,-2), float fBlur= 0 );

	//���� - ȥ����Ч
	static bool			RemoveEffect(LabelTTF* pText);
	static bool			RemoveEffect(Label* pText);
	static bool			RemoveEffect(Text* pText);

	static	bool		IsHitted(const Node* pNode,Touch *touch, Event *unusedEvent);			//�Ƿ���

	static	bool		IsAncestorsEnabled(const Widget* pWidget);//�Ƿ������������ڶ�Enabled
	static	bool		IsAncestorsVisible(const Node* pNode);
	static	bool		IsHitted(const Widget* pWidget,Touch *touch, Event *unusedEvent);			//�Ƿ���
	static	bool		IsAllHitted(const Widget* pWidget,const std::vector<Touch*>& vTouch, Event *unusedEvent);
	static	float		CalDistanceSquared(const Vec2& pt1,const Vec2& pt2);//���������ƽ�� �ٶȿ��� ��������
	static	bool		IsDistanceLessThan(const Vec2& pt1,const Vec2& pt2,float fDistance);//��������Ƿ�С�� ָ������
	static	bool		IsDistanceGreaterThan(const Vec2& pt1,const Vec2& pt2,float fDistance);//��������Ƿ�С�� ָ������

	static	bool		MakeInRect(Node* pNode,const Vec2& ptOffset,const Rect& rRect);
	static	bool		MakeInRect(Node* pNode,const Rect& rRect);
	static	bool		MakeInScreen(Node* pNode,const Vec2& ptOffset);//ʹ�ýڵ�����Ļ��
	static	bool		MakeInScreen(Node* pNode);//ʹ�ýڵ�����Ļ��

	//�����Զ���ͼƬ
	static	Sprite*		MakeSpriteAnnularSector (float fRadius1,float fRadius2,float fAngel,const Color4F& rFill,int nSegments = 40);//�����Ȼ�����
	static	Sprite*		MakeSpriteLine ( const ToolFrame::VectorPoint2d& vPoint, float fRadius, const Color4F& clr );	//��������

	static	Vec2		ToVec(const ToolFrame::CPoint2d& pt);
	static	ToolFrame::CPoint2d ToPoint2d(const Vec2& vec2);

	//��ת
	static bool			SetFlippedX(Node* pNode,bool bFlipped);
	static bool			SetFlippedY(Node* pNode,bool bFlipped);
	static bool			IsFlippedX(Node* pNode);
	static bool			IsFlippedY(Node* pNode);

	//Spine

	//����Spine Atlas
	static spAtlas* CacheSpineAtlas(const std::string& atlasFile);

	//����Spine��������
	static spSkeletonData* CacheSpineSkeletonData(const std::string& skeletonDataFile, const std::string& atlasFile, float scale=1.0f);

	//������ SpineAtlas
	static bool PurgeSpineAtlasCache();

	//������ SpineSkeletonData
	static bool PurgeSpineSkeletonDataCache();

	//����Spine����
	static SkeletonAnimation* CreateSpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile, float scale=1.0f);

	//���Ŷ���
	static SkeletonAnimation* PlaySpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName1,const std::string& sName2,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile,const VectorString& vName,int nLoop=-1,float fDelay=0.f);
	
	static SkeletonAnimation* PlaySpineAnimation(SkeletonAnimation* pAnimation,const std::string& sName,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(SkeletonAnimation* pAnimation,const std::string& sName1,const std::string& sName2,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(SkeletonAnimation* pAnimation,const VectorString& vName,int nLoop=-1,float fDelay=0.f);

	static SkeletonAnimation* PlaySpineAnimation(const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName1,const std::string& sName2,int nLoop=-1,float fDelay=0.f);
	static SkeletonAnimation* PlaySpineAnimation(const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,const VectorString& vName,int nLoop=-1,float fDelay=0.f);

	static SkeletonAnimation* SetSpineCallBackEvent(SkeletonAnimation* pAnimation, FnActionSpineEvent fnEvent);		//�����¼��ص�
	static SkeletonAnimation* SetSpineCallBackEventErr(SkeletonAnimation* pAnimation, FnActionSpineEvent fnEvent);	//�����¼��ص�����ʧ��ʱ �ص�
	static SkeletonAnimation* SetSpineCallBackOver(SkeletonAnimation* pAnimation, FnActionSpineOver fnOver);		//���ý����ص�
	static SkeletonAnimation* SetSpineRemove(SkeletonAnimation* pAnimation,bool bRemove);							//�����Ƴ����

	//����
	struct XCommandArg
	{
		Node*				pNodeShake;		//�𶯽ڵ�
		std::string			sLocalDir;		//��ǰĿ¼
	};
	static bool RunCommand(std::string sEvent,std::string sEventArg, const XCommandArg* pArg = nullptr);//ִ������

	static bool				  SpineSkipBy(SkeletonAnimation* pAnimation,float fTimeNext);//����X���

	static bool				SetSpeed(SkeletonAnimation* pArmature,float fSpeed = 1.0f);

	static bool			GetSpineAnimationName(VectorString& vName,const SkeletonAnimation* pAnimation);
	static std::string	GetSpineAnimationNameCur( SkeletonAnimation* pAnimation,int nTrackIndex =0 );

	static const spAnimation* FindAnimationByName(const SkeletonAnimation* pAnimation,const std::string& sName);
	static float		GetAnimationDuration(const SkeletonAnimation* pAnimation, const std::string& sName);

	static bool			SetCallFuncNull(SkeletonAnimation* pArmature);

	static SkeletonAnimation* BindSpineNode(SkeletonAnimation* pAnimation,const std::string& sBone,Node* pNode);
private:
	//������ʾ����
	static Sprite*		ApiEffectSpriteShow(float fVisibleTime,float fFade, float fDelay,const std::string& sPath );
	static void			CallBackRemoveSelfLoop(Armature *armature, MovementEventType movementType, const std::string& movementID);
	static void			CallBackRemoveSelf(Armature *armature, MovementEventType movementType, const std::string& movementID);

	static void			DrawSolidSector(DrawNode* pNode ,const Vec2 &orign,const float fBeginAngle, const float radius1, const float radius2, const float fAngelFanShaped, const int segments, const Color4F &color);	
private:
	static bool			g_bAutoPurgeCache;//�Զ����ջ�����

	static MapStringSkeletonData	g_vSpineSkeletonData;
	static MapStringAtlas			g_vSpineAtlas;

	static bool						g_bSoundMute;	//ȫ����������
	static bool						g_bMusicMute;	//�������־���

	static int						g_nAudioMusic;	//��ǰ��������AudioID
};

template<typename T>
bool ApiCocos2dx::FindNode( std::vector<T*>& vWidget, const Node* pRootWidget,const std::string& sName,int nCount )
{
	if (!pRootWidget)return false;

	for (int nIndex = 1;nIndex <= nCount;++nIndex)
	{
		T* pWidget=nullptr;
		if (!FindNode(pWidget,pRootWidget,MAKE_STRING(sName<<nIndex)))return false;

		vWidget.push_back(pWidget);
	}
	return true;
}

template<typename T>
bool ApiCocos2dx::FindNode( std::vector<T*>& vWidget, const Node* pRootWidget,const std::string& sName )
{
	if (!pRootWidget)return false;

	int nIndex = 1;
	while (true)
	{
		T* pWidget = nullptr;
		if (!FindNode(pWidget,pRootWidget,MAKE_STRING(sName<<nIndex)))return true;

		vWidget.push_back(pWidget);
		++nIndex;
	}

	return true;
}

template<typename T>
T* ApiCocos2dx::FindActionByTag( Node* pNode,int nTag )
{
	if (!pNode)return nullptr;
	
	return dynamic_cast<T*>(pNode->getActionByTag(nTag));
}

template<typename T,typename TValue>
bool ApiCocos2dx::SetValue( Node* pNode,const TValue& tValue )
{
	if (!pNode)return false;

	T* pTarget = dynamic_cast<T*>(pNode);
	if (!pTarget)return false;

	return SetValue(pTarget,tValue);
}

template<typename T,typename TValue>
bool ApiCocos2dx::SetValue( const std::string& sName, Ref* pRootWidget,const TValue& tValue )
{
	T* pWidget=nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,dynamic_cast<Node*>(pRootWidget),sName))return false;
	return ApiCocos2dx::SetValue(pWidget,tValue);
}

template<typename T,typename TValue>
bool ApiCocos2dx::SetValue( const std::string& sName,Node* pRootWidget,const TValue& tValue )
{
	T* pWidget=nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,pRootWidget,sName))return false;
	return ApiCocos2dx::SetValue(pWidget,tValue);
}

template<typename T,typename TValue>
bool ApiCocos2dx::ActionsSetValue( const std::string& sName,const Node* pRootWidget,const TValue& fValue,float fDuration /*= 1.f*/ )
{
	T* pWidget=nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,pRootWidget,sName))return false;
	return ActionsSetValue(pWidget,fValue,fDuration);
}

template<typename T,typename TValue>
bool ApiCocos2dx::ActionsSetValue(Node* pNode,const TValue& fValue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;
	T* pNodeTarget = dynamic_cast<T*>(pNode);
	if (!pNodeTarget)return false;
	
	return ActionsSetValue(pNodeTarget,fValue,fDuration);
}

template<typename T, typename TValue>
bool ApiCocos2dx::GetValue( const Node* pNode,TValue& fValue )
{
	return GetValue(dynamic_cast<const T*>(pNode) ,fValue);
}

template<typename T, typename TValue>
bool ApiCocos2dx::GetValue( const Widget* pRootWidget,const std::string& sName,TValue& tValue )
{
	T* pWidget=nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,pRootWidget,sName))return false;
	if (!pWidget)return false;
	return GetValue(pWidget,tValue);
}

template<typename T>
T* ApiCocos2dx::Clone( const Node* pSrc,bool bVisible /*= true*/ )
{
	return dynamic_cast<T*>(Clone(pSrc,bVisible));
}

template<typename T>
T*	ApiCocos2dx::Clone(const Node* pSrc,const Node* pTargetPostion,bool bVisible){
	return dynamic_cast<T*>(Clone(pSrc,pTargetPostion,bVisible));
}

template<typename T>
T*	ApiCocos2dx::FindNode(const Node* pNode,const std::string& sName){
	Node* pFind = ApiCocos2dx::FindNode(pNode,sName);
	if (!pFind)return nullptr;
	return dynamic_cast<T*>(pFind);
}


template<typename T>
bool ApiCocos2dx::FindNode( T*& pFind,const Node* pNode,const std::string& sName )
{
	pFind = ApiCocos2dx::FindNode<T>(pNode,sName);
	return !!pFind;
}

#endif //MACRO_LIB_COCOS2D
