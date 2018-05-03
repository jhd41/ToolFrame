#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

#include "MacroCocos2dx.h"
#include "MacroDefineEx.h"

//注记:
//Cocos2d采用的是左下为坐标原点
class TOOLFRAME_DLL ApiCocos2dx{
public:
	//替换Widget
	static bool ReplaceNode(Node* pNode,Node* pNodeTarget);
	static bool ReplaceNode(Node* pNode,Node* pNodeTargetRoot,const std::string& sName);

	//放置Widget
	static bool PositionNode(Node* pNode,Node* pNodePosition);
	static bool PositionNode(Node* pNode,Node* pNodePositionRoot,const std::string& sName);

	static bool		SetAccelerometerEnabled(bool bEnabled);//打开设备的重力感应
	static float	GetAnimationInterval();//获取动画帧

	//混合
	static bool Merge(VectorNode& vNode,const VectorSpineAnimation& vSrc);
	static bool Merge(VectorNode& vNode,Node* pNode);

	//删除
	static bool Retain(Ref* ref);
	static bool Release(Ref* ref);
	static bool	ReleaseNextFrame(Ref* ref);

	//屏幕
	//获取屏幕中间点
	static Point GetScreenCenterPoint();
	static Point GetScreenPoint(const Point& pt);//百分比
	static Point GetScreenPoint(float fX,float fY);//百分比

	//场景节点
	static Scene* GetRunningSceneNode();

	//获取视口
	static const Point GetVisibleRectLeftTop();
	static const Point GetVisibleRectRightTop();
	static const Point GetVisibleRectLeftDown();
	static const Point GetVisibleRectRightDown();

	//出屏
	static bool			IsOutScreen(const Node* pNode);

	//场景
	static bool			ReplaceScene(Scene* pScene);//场景切换

	//绑定盒
	static bool			IsIntersects(const Node* pNode1,const Node* pNode2);//是否相交

	//设置坐标为父节点中心
	static	bool SetPostionCenter(Node* pNode);


	//设置坐标为父节点的百分比 中心为 0.5 0.5
	static	bool SetPostionCenter(Node* pNode,const Point& pt);

	//修复在面板中的坐标位置
	static bool FixPositionInPanel(Node* pPanel);

	//设置锚点
	static	bool SetWorldAnchorPoint(Node* pNode,const Vec2& ptWorld);

	//设置精灵在屏幕中间
	static bool SetWorldPostionWithScreenCenter(Node* pNode);
	static bool SetWorldPostionWithScreenPoint(Node* pNode,float fX,float fY);///相对于屏幕的百分比

	//设置绑定盒
	static bool	SetWorldingBoundingWithOther(Node* pNode, Node* pOther);

	//设置锚点
	static bool SetAnchorPoint(Node* pNode,const Vec2& pt);
	static bool SetAnchorPoint(Node* pNode,int x,int y);

	//获取锚点
	static const Vec2& GetAnchorPoint(Node* pNode);

	//修复锚点
	static bool FixAnchorPoint(Node* pNode);

	//设置是否可见
	static bool SetVisible(VectorNode& vNode,bool bVisible);

	//设置颜色
	static bool SetColor(Node* pNode,const Color3B& clr);
	static bool SetColor(VectorNode& vNode,const Color3B& clr);

	//添加贴图缓存
	static CCTexture2D* CacheTexture(const std::string& sPath);

	//创建精灵
	static Sprite* CreateSprite(const std::string& sPath);
	static Sprite* CreateSprite(CCTexture2D* pTexture);

	//创建SpriteBatch
	static SpriteBatchNode* CreateSpriteBatch(const std::string& sPath);
	static SpriteBatchNode* CreateSpriteBatch(CCTexture2D* pTexture);

	//创建Image
	static Image*	CreateImage(const Sprite* pSprite);
	static Image*	CreateImage( const std::string& sPath);

	//创建进度条
	static LoadingBar*		CreateLoadingBar(const std::string& sPath);

	//创建地图
	static TMXTiledMap*		CreateTiledMap(const std::string& sPath);

	//创建皮肤
	static Skin*			CreateSkin(const std::string& sPath);

	//添加精灵集合
	static SpriteFrame*		CreateSpriteFrame(const std::string& sPath,const Rect& rRect);
	static bool				CacheSpriteFrames(const std::string& sPath);

	//加载贴图
	static bool				LoadTexture(Button* btn,			const std::string& sPath,ui::Widget::TextureResType texType = ui::Widget::TextureResType::LOCAL); 
	static bool				LoadTexture(LoadingBar* pBar,		const std::string& sPath,ui::Widget::TextureResType texType = ui::Widget::TextureResType::LOCAL); 
	static bool				LoadTexture(ImageView* pImageView,	const std::string& sPath,ui::Widget::TextureResType texType = ui::Widget::TextureResType::LOCAL); 
	//获取透明值
	static int				GetOpacityWithPoint(const Sprite* pSprite, const Point& pt);
	static int				GetOpacityWithPoint(const Image* pImage, const Point& pt);
	static int				GetOpacityWithPoint(const ImageView* pImgView, const Point& pt);

	//设置文本
	static bool	SetText(TextField* pText,const std::string& sText);
	static bool SetText(Text* pText,	 const std::string& sText);

	//设置贴图
	static bool SetTexture(Sprite* pSprite,const std::string& sPath);

	//重新确定Z-Order 按照顺序
	static bool RezorderBySeq(Node* pNodeParent,VectorSprite& vNode );

	//设置Z-Order 按照顺序
	static bool SetZorderBySeq(Node* pNodeParent,VectorNode& vNode,int nZ=0);
	static bool SetZorderBySeq(Node* pNodeParent,VectorSprite& vNode,int nZ=0);

	//Release
	static bool Release(VectorNode& vNode);

	//获取被触碰到的节点
	static bool		FindTouchedNode( VectorNode& vNodeDes,VectorNode& vNodeSrc,CCTouch *pTouch );

	//判断是否碰到了节点
	static bool		IsTouchedNode(const Node* pNode,const Touch* touch);
	static bool		IsTouchedNode(const Widget* pNode,const Touch* touch);

	//触碰 - 查找节点
	static Node*	FindTouchedNode(const VectorNode& vNode,const Touch* touch);
	static Widget*	FindTouchedNode(const VectorWidget& vNode,const Touch* touch);

	static Widget*	FindTouchedNode(const MapIntWidget& vNode,const Touch* touch);

	static Node*	FindTouchedNode(const Touch* touch,Node* pNode);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3,Node* pNode4);
	static Node*	FindTouchedNode(const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3,Node* pNode4,Node* pNode5);

	//模糊处理触碰起点
	static int& GetTouchBlurDistance();//获得触碰模糊处理距离
	static int& SetTouchBlurDistance(int nTouchFar);
	static bool IsTouchBlur(Touch* touch);//是否触碰超过模糊距离
	static bool IsTouchBlur(Touch* touch,int nDistance);

	//矩形相加
	static Size	Plus(const Size& a,const Size& b);
	static Size&	SelfPlus(Size& self,const Size& other);
	static Size				Max(const Size& rSize1,const Size& rSize2);

	//坐标相加
	static Point	Plus(const Point& a,const Point& b);
	//坐标相减
	static Point	Subtract(const Point& a,const Point& b);

	//获得最宽 最高
	static Node*	FindNodeByBoundingBoxMostWide(const VectorNode& vNode);
	static Node*	FindNodeByBoundingBoxMostHigh(const VectorNode& vNode);
	static Node*	FindNodeByBoundingBoxMostWide(const Vector<Node*>& vNode);
	static Node*	FindNodeByBoundingBoxMostHigh(const Vector<Node*>& vNode);

	//数组操作
	static bool		IsEmpty(CCArray* pArray);
	static Node*	FindFirstNode( CCArray* pArray);
	static Node*	FindLastNode( CCArray* pArray);
	static Node*	FindNodeAtIndex(CCArray* pArray,UINT uIndex);
	static UINT		GetCount(CCArray* pArray);

	//获取绑定盒中心
	static Point	GetCenterByBoundingBox(Node* pNode);

	//获取矩形中心
	static Point	GetRectCenterPoint(const Rect& rRect);

	//计算尺寸 节点尺寸->世界尺寸
	static Size		CalWorldSize(const Size& rSizeNode,const Node* pNode);

	//计算尺寸 世界尺寸->节点尺寸
	static Size		CalSizeInParent(const Size& rSizeWorld,Node* pNode);

	//计算在父节点上的坐标
	static Point	CalPointInParent(const Point& ptWorld,Node* pNode);

	//计算取在节点上的坐标
	static Point	CalPointInNode(const Point& ptWorld,Node* pNode);

	//按照显示顺序排序
	static bool	SortByTop(VectorNode& vNodes);

	//获得父节点指针集合
	static bool	GetParentNodes(VectorNode& vNodes,Node* pNode);

	//查找Node By Tag
	static Node*	FindNodeByTag(const VectorNode& vNode,int nTag );
	static Widget*	FindNodeByTag(const VectorWidget& vNode,int nTag );

	//查找节点
	static Node*	FindNode(const Node* pNode,const std::string& sName);
	template<typename T>
	static T*		FindNode(const Node* pNode,const std::string& sName);
	template<typename T>
	static bool		FindNode(T*& pFind,const Node* pNode,const std::string& sName);

	//设置 Z -Order
	static bool		SetZOrder(Node* pNode,int nZOrder);

	//获得内容尺寸
	static const Size& GetContentSize(const Node* pNode);

	//获得节点世界位置
	static Point	GetWorldPostion(const Node* pNode);

	//获得节点的中心的世界位置
	static Point	GetWorldCenter(const Node* pNode);
	static Point	GetWorldCenter(const Node* pNode,const Point& pt);
	
	//获得节点中心
	static Point	GetContentSizeCenter(const Node* pNode);
	static Point	GetContentSizeCenter(const Node* pNode,const Point& pt);

	//用另外一个节点的中心世界位置设置 当前节点
	static bool		SetWorldCenterWithOther(Node* pNode,const Node* pOther);

	//设置节点世界位置
	static bool		SetWorldPostion(Node* pNode,const Point& ptWorld);
	//设置节点世界位置
	static bool		SetWorldPostion(Node* pNode,const Node* pOther);

	//获取
	static Vec2		GetWorldAnchorPointInPoints(Node* pNode);

	//获得节点绑定盒世界位置
	static Rect	GetWorldBoundingBox(const Node* pNode);

	//设置节点绑定盒世界位置
	static bool		SetWorldBoundingBox(Node* pNode,const Rect& rWorld);//通过直接绑定盒进行设置
	static bool		SetWorldBoundingBox(Node* pNode,const Rect& rWorld, const Point& ptWorldPosition);//附带世界中的坐标(若不设置 会使用 锚点 进行计算 通常无需调用)

	//是否拥有孩子
	static bool				IsChildEmpty(const Node* pNode);

	//获得孩子的个数
	static UINT				GetChildCount(Node* pNode);

	//获得第Index个孩子
	static Node*	FindChildByIndex(Node* pNode,uint uIndex);

	//查找孩子(Tag)
	static	Node*	FindChildByTag(const Node* pWidget,int nTag);

	//移除孩子
	static	bool			RemoveChildren(VectorNode& vNode,bool bClean =true);
	static	bool			RemoveChildren(VectorWidget& vNode,bool bClean =true);

	//移除孩子(Tag)
	static	bool			RemoveChildByTag( Node* pWidget,int tag, bool cleanup = true);
	static	bool			RemoveChildByTag(VectorNode& vNode,int nTag,bool bClean =true);
	
	//移除所有孩子
	static	bool			RemoveAllChildren( Node* pWidget);

	//获得当前子节点中最大的Z-Order
	static int				GetChildZOrderMax(const Node* pNode);

	//添加至节点顶部
	static bool				AddChildTop(Node* pParent,Node* pChild);

	//找到根节点
	static Node*			FindRootNode(Node* pNode);

	//创建描边文字
	//static CCRenderTexture* CreateStroke(CCLabelTTF* pNode,float fFontSize,const ccColor3B& ccColor);

	//翻转
	static bool Flip(Node* pNode,bool bHorizontal=false,bool bVertical=false);//水平翻转，竖直翻转

	//设置文字
	static bool		SetString(LabelTTF* pNode,const std::string& sString);

	//转换颜色值
	static ccColor3B ToColor(UINT32 uColor);

	static std::string	LoadFile( const std::string& sFileName );//cocos2dx自身的loadfile 一般不要用

	static std::string GetWriteableDir();

	//设置绘制时点的大小(目前cocos2d-x似乎存在跨平台的BUG因此多包装一层)
	static bool SetPointSize(float fSize);

	//查找指定Widget数组(下标从1开始)
	template<typename T>
	static bool FindNode(std::vector<T*>& vWidget, const Node* pRootWidget,const std::string& sName);
	template<typename T>
	static bool FindNode(std::vector<T*>& vWidget, const Node* pRootWidget,const std::string& sName,int nCount );//校验正确性

	//查找指定Widget By Tag
	static Widget* FindWidgetByTag(const VectorWidget& vWidget,int nTag);

	//为按钮数组添加统一回调
	static bool	AddTouchEvent(Node* pWidget,Ref* target,SEL_TouchEvent selector);
	static bool	AddTouchEvent(VectorNode& vWidget,Ref* target,SEL_TouchEvent selector);	
	static bool AddTouchEvent(Node* pWidgetRoot,const std::string& sName,Ref* target,SEL_TouchEvent selector);
	static bool	AddTouchEvent(Node* pWidget,Widget::ccWidgetTouchCallback fnCallBack);
	
	//按钮
	static bool SetClickCallBack(Widget* pNode, Widget::ccWidgetClickCallback fn);
	static bool SetClickCallBack(Node* pRoot, const std::string& sName, Widget::ccWidgetClickCallback fn);
	static bool SetTouchCallBack(Widget* pNode, Widget::ccWidgetTouchCallback fn);
	static bool SetTouchCallBack(Node* pRoot, const std::string& sName, Widget::ccWidgetTouchCallback fn);

	//加载UI文件
	static Node* LoadUIFile(const std::string& sFileName);

	//切换横竖屏
	static bool	SwitchScreen(); 
	static bool	SwitchScreen(bool bLandscape);

	//是否横屏
	static bool	IsLandscape(); 
 
	//设置内容大小为屏幕大小
	static bool SetContentSizeWithScreenSize(Node* pNode);

	//设置设计尺寸(开启多分辨率支持)
	static bool SetDesignResolutionSize(float fWidth = 0.0f,float fHeight = 0.0f);

	//获取设计尺寸
	static const Size& GetDesignResolutionSize();

	//获得设计剩余尺寸(设计尺寸 减去 参数中的节点 尺寸)
	static Size CalDesignResolutionSizeResidue(const Node* pRoot,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");
	static Size CalDesignResolutionSizeResidue(const Node* pRoot,const VectorString& vName);

	//获得总宽度
	static Size CalSize(const Node* pRoot,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");
	static Size CalSize(const Node* pRoot,const VectorString& vName);

	//设置结点内容宽度为设计尺寸
	static bool SetContentSize(Node* pNode,const Size& size);
	static bool SetContentSizeWithDesignSize(Node* pNode);
	static bool SetContentSizeWithDesignSize(Node* pNode,bool bWidth);
	static bool SetContentSizeWithChildrenSum(Node* pWidget,bool bWidth);
	static bool SetContentSizeWithChildrenMax(Node* pWidget,bool bWidth);
	static bool SetContentSizeWithChildren(Node* pWidget,bool bWidth);

	//设置名字
	static bool			SetName(Widget* pWidget,const std::string& sName);

	//获取名字
	static std::string	GetName(const Widget* pWidget);
	static std::string	GetName(const Ref* pObj);

	//获取尺寸
	static const Size&	GetSize(Widget* pWidget);

	//获取尺寸中心
	static Point		GetSizeCenter(Widget* pWidget);

	//效果
	static bool StopAllAction(Node* pNode);
	static bool StopAction(Node* pNode,Action* pAction);
	static bool StopActionByTag(Node* pNode,int nTag);

	static Action* FindActionByTag(Node* pNode,int nTag);
	template<typename T>
	static T* FindActionByTag(Node* pNode,int nTag);

	static int GetActionsCount(Node* pNode);//统计Action数量

	//效果	- 基本效果
	static bool ActionRotateTo(Node* pNode,float fAngle,float fDuration = 1.f);//旋转到
	static bool ActionRotateBy(Node* pNode,float fAngle,float fDuration = 1.f);//旋转
	static bool ActionScaleTo(Node* pNode,float fScale,float fDuration = 1.f);//缩放到
	static bool ActionScaleBy(Node* pNode,float fScale,float fDuration = 1.f);//缩放
	static bool ActionFadeTo(Node* pNode,GLubyte opacity,float fDuration = 1.f);//透明到
	static bool ActionFadeIn(Node* pNode,float fDuration = 1.f);				//淡入
	static bool ActionFadeOut(Node* pNode,float fDuration = 1.f);				//淡出
	static bool ActionMoveTo(Node* pNode,const Vec2& ptPostion,float fDuration = 1.f);//移动到
	static bool ActionMoveBy(Node* pNode,const Vec2& ptPostion,float fDuration = 1.f);//移动到
	static bool ActionSkewTo(Node* pNode,float sx,float sy,float fDuration = 1.f);//扭曲到
	static bool ActionSkewBy(Node* pNode,float sx,float sy,float fDuration = 1.f);//扭曲
	static bool ActionJumpTo(Node* pNode,const Vec2& ptPostion,float fHeight,int nJumps,float fDuration = 1.f);//弹跳到
	static bool ActionJumpBy(Node* pNode,const Vec2& ptPostion,float fHeight,int nJumps,float fDuration = 1.f);//弹跳
	static bool ActionBlink(Node* pNode,int nBlinks,float fDuration = 1.f);//闪烁
	static bool	ActionTintTo(Node* pNode,GLubyte red, GLubyte green, GLubyte blue,float fDuration = 1.f);//染色(修改顶点色 默认白色)
	static bool	ActionTintBy(Node* pNode,GLubyte red, GLubyte green, GLubyte blue,float fDuration = 1.f);//染色(修改顶点色 默认白色)

	//设置翻面效果
	static bool	ActionsTurnOver(Node* pSrc,Node* pDes,float fTurnTime,float fDelayTime);
	static bool ActionsTurn(Node* pNode,float fDuration = 0.3f);//旋转

	//设置显示图片类似于LOGO
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath );
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath ,SEL_CallFunc fnCallBack);
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath1 ,const std::string& sPath2);
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath1 ,const std::string& sPath2,SEL_CallFunc fnCallBack);

	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const VectorString& vPath );
	static bool	ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const VectorString& vPath ,SEL_CallFunc fnCallBack);

	//效果 - 淡入淡出 改变节点
	static bool ActionsChangeNodeFade(Node* pSrc,Node* pDes,float fTime=2.0f);

	//效果 - 数值增加
	static bool	ActionsSetValue(LoadingBar* pNode,const float& nValue,float fDuration = 1.f);
	static bool	ActionsSetValue(Text* pNode,const int& nValue,float fDuration = 1.f);
	static bool	ActionsSetValue(Text* pNode,const float& fValue,float fDuration = 1.f);
	static bool	ActionsSetValue(Text* pNode,const std::string& sValue,float fDuration = 1.f);
	static bool	ActionsSetValue(TextAtlas* pNode,const int& nValue,float fDuration = 1.f);
	template<typename T,typename TValue>
	static bool	ActionsSetValue(Node* pNode,const TValue& fValue,float fDuration = 1.f);
	template<typename T,typename TValue>
	static bool	ActionsSetValue(const std::string& sName,const Node* pRootWidget,const TValue& fValue,float fDuration = 1.f);

	//振动(幅度，频率)
	static bool ActionsShake(Node* pNode,float fduration,int nStrength,int nFrequency,const Vec2& ptDirect);
	static bool ActionsShake(Node* pNode,float fduration,int nStrength,int nFrequency=1);

	//获取可视区域
	static Rect	 GetVisibleRect();
	static Point GetVisibleCenter();
	static Size  GetVisibleSize();

	//是否超过屏幕
	static bool IsOutOfScreen(const Node* pRoot,bool bWidth,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");
	static bool IsOutOfScreen(const Node* pRoot,const VectorString& vWidget,bool bWidth);

	//设置基本属性
	static bool SetRotation(Node* pNode,float fRotation);
	static bool SetOpacity(Node* pNode,GLubyte uOpacity,bool bChildren = true);

	static float GetRotation(Node* pNode);

	//移除节点
	static bool RemoveFromParentAndCleanup(Node* pNode,bool bCleanUp = true);
	static bool RemoveFromParentAndCleanup(VectorNode& vNode,bool bCleanUp = true,bool bClearVector = true);
	static bool RemoveFromParentAndCleanup(VectorWidget& vWidget,bool bCleanUp = true,bool bClearVector = true);
	static bool RemoveFromParentAndCleanupNextFrame(Node* pNode ,bool bCleanUp = true);//下一帧 删除

	//移除节点 - Tag
	static bool RemoveFromParentByTag(VectorNode& vNode,int nTag,bool bClean =true);
	static bool RemoveFromParentByTag(VectorWidget& vNode,int nTag,bool bClean =true);

	static int	RemoveFromParentAllByTag(VectorNode& vNode,int nTag,bool bClean =true);
	static int	RemoveFromParentAllByTag(VectorWidget& vNode,int nTag,bool bClean =true);

	//改变父节点
	static bool ChangeParentNode(Node* pNode,Node* pParent ,bool bKeepWorld = true,bool bCleanUp = true,int nZOrder = 0);//改变父节点
	static bool ChangeParentNode( const Node* pRoot,const std::string& sChild,const std::string& sParent,bool bKeepWorld = true,bool bCleanUp = true);
	static bool ChangeParentNode(VectorNode& vNode,const VectorNode& vParent,bool bKeepWorld = true,bool bCleanUp = true);
	static bool ChangeParentNode(VectorNode& vNode,Node* pParent,bool bKeepWorld = true,bool bCleanUp = true);

	//节点更新(布局应用，若布局不可见 则不会应用布局)
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
	static bool SetVisible(Widget* pWidget,bool bVisible);//若该节点可触摸，则 隐藏后 触摸不到，需要重新开启触摸才有效
	static bool SetVisible(const VectorNode& vWidget,bool bVisible);
	static bool SetVisible(Node* pRootWidget,const std::string& sName,bool bVisible);
	static bool SetVisible(Node* pRootWidget,const std::string& sName,int nCount,bool bVisible);

	static bool SetGroupVisible(Node* pRootWidget,const std::string& sName,int nCount,int nValue);//小于最大索引值的nValue成员都可见，否则都不可见

	static bool IsChecked(Widget* pRootWidget,const std::string& sName);//如果没找到也返回false,也就是说 如果是true一定是对的
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

	static bool SetTagWhithIndex(const VectorNode& vNode,int nIndexBegin =0);//按照顺序设置每个节点的Tag 
	static bool SetTagWhithIndex(const VectorWidget& vNode,int nIndexBegin =0);//按照顺序设置每个节点的Tag 

	static bool	SetLayoutParameter(Node* pDes,const Node* pSrc,LayoutParameter::Type eLayout);//LAYOUT_PARAMETER_RELATIVE
	static bool	SetLayoutParameter(Node* pDes,const Node* pSrc);//LAYOUT_PARAMETER_RELATIVE

																
	static  bool InsertBackNode(Node* pSrc, Node* pBack);//添加一个背景节点

	//模板克隆
	static Node*	Clone(const Node* pSrc,bool bVisible = true);//克隆
	static Node*	Clone(const Node* pSrc,const Node* pTargetPostion,bool bVisible = true);//克隆并放置在目标区域
	template<typename T>
	static T*		Clone(const Node* pSrc,bool bVisible = true);
	template<typename T>
	static T*		Clone(const Node* pSrc,const Node* pTargetPostion,bool bVisible = true);

	static bool	InitTemplate(Node* pNode,bool bIgnoreContentAdaptWithSize=true);//初始化模板
	static bool SetIgnoreContentAdaptWithSize(Node* pNode, bool bIgnoreContentAdaptWithSize = true, bool bChildren = true);

	//设置值
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

	//获取值
	static bool GetValue(const TextField* pWidget,std::string& sValue);
	static bool GetValue(const TextAtlas* pWidget,int& nValue);
	static bool GetValue(const TextAtlas* pWidget,std::string& sValue);
	static bool GetValue(const Text* pWidget,std::string& sValue);
	static bool GetValue(const Text* pWidget,int& nValue);
	static bool GetValue(const Text* pWidget,float& fValue);
	static bool GetValue(const LoadingBar* pWidget,float& fValue);
	static bool	GetValue(const LoadingBar* pWidget,int& nValue);
	//static bool GetValue(const ImageView* pWidget,std::string& sValue);//获取不到图片路径

	template<typename T, typename TValue>
	static bool GetValue(const Node* pNode,TValue& fValue);
	template<typename T, typename TValue>
	static bool GetValue(const Widget* pRootWidget,const std::string& sName,TValue& tValue );

	static int			CalLines(const std::string& sString,int nWidth,int nFontSize);//计算行数(考虑了中文字符)
	static bool			AutoHeight(Text* pNode,int nSpaceHeight=8,int nSpaceWidth=0);	//根据文本自适应调整高度(宽度不变)

	static bool			Clear(ListView* pLv);
	static bool			PushBack(ListView* pLv,Node* pNode);

	static bool			Clear(PageView* pPv);
	static bool			PushBack(PageView* pPageView,Node* pNode);
	static Layout*		GetCurPage(PageView* pPv);
	static bool			ScrollToNext( PageView* pPv ,bool bNext = true,bool bCircle=true);

	//PageView
	static bool			PageAddImage( PageView* pPageView,const std::string& sImgPath,int nIndex = -1,bool bChangeSize = true);//添加子页面
	static bool			PageResetImage(PageView* pPageView);
	static bool			IsCurLastPage(PageView* pPageView);//判断是否为最后一页

	static CheckBox*	AddEventListenerCheckBox(CheckBox* pCheckBox,Ref* target,SEL_SelectedStateEvent selector);
	static CheckBox*	AddEventListenerCheckBox(const Node* pRootWidget,const std::string& sName,Ref* target,SEL_SelectedStateEvent selector);

	//变灰
	static bool			SetGray(Node* pNode,bool bGray,bool bChildren = true);
	static bool			SetGray(Node* pRoot,const std::string& sName, bool bGray, bool bChildren = true);
	static bool			SetGray(VectorNode& vNode, bool bGray, bool bChildren = true);

	//ImageView
	static ImageView*	CreateImageView(const std::string& sFile,Widget::TextureResType texType = Widget::TextureResType::LOCAL);

	//动画
	static bool			CacheArmatureFile(const std::string& sFileName);
	static Armature*	CreateArmature(const std::string& sName);
	static Armature*	CreateArmatureByFileName(const std::string& sName);

	//动画 - 空帧
	static bool			IsEmptyMovement(const Armature* pArmature,const std::string& sName);
	static bool			IsEmptyMovement(const ArmatureAnimation* pAnimation,const std::string& sName);//是否空帧

	//动画 - 安全播放
	static Armature*	PlayArmature( const std::string& sFileName, int nLoop = -1);
	static Armature*	PlayArmature( const std::string& sFileName,	const std::string& sName,	int nLoop = -1);
	static Armature*	PlayArmature( const std::string& sFileName,	const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static Armature*	PlayArmature( const std::string& sFileName,	const VectorString& vName,	int nLoop = -1);//安全播放 若遇到不能播放的跳过播放，若不想重置时 遇到已经在播 则不播
	
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName, int nLoop = -1);
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName,	const std::string& sName,	int nLoop = -1);
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName,	const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static Armature*	PlayArmature( const Point& ptPostion,const std::string& sFileName,	const VectorString& vName,	int nLoop = -1);//安全播放 若遇到不能播放的跳过播放，若不想重置时 遇到已经在播 则不播

	static bool			PlayArmature( Armature* pArmature,			int nLoop = -1);
	static bool			PlayArmature( Armature* pArmature,			const std::string& sName,	int nLoop = -1);
	static bool			PlayArmature( Armature* pArmature,			const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static bool			PlayArmature( Armature* pArmature,			const VectorString& vName,	int nLoop = -1);//安全播放 若遇到不能播放的跳过播放，若不想重置时 遇到已经在播 则不播
	
	static bool			PlayArmature( ArmatureAnimation* pArmature,			int nLoop = -1);
	static bool			PlayArmature( ArmatureAnimation* pArmature,	const std::string& sName,	int nLoop = -1);
	static bool			PlayArmature( ArmatureAnimation* pArmature,	const std::string& sName1,	const std::string& sName2,int nLoop = -1);
	static bool			PlayArmature( ArmatureAnimation* pArmature,	const VectorString& vName,	int nLoop = -1);//安全播放 若遇到不能播放的跳过播放，若不想重置时 遇到已经在播 则不播

	static const std::string&	GetMovementName(const Armature* pArmature,int nIndex);
	static const std::string&	GetMovementName(const ArmatureAnimation* pArmature,int nIndex);
	static const VectorString&	GetMovementName(const Armature* pArmature);
	static const VectorString&	GetMovementName(const ArmatureAnimation* pArmature);
	static bool					GetMovementName(VectorString& vMovementName,const Armature* pArmature,const VectorInt& vIndex);
	static bool					GetMovementName(VectorString& vMovementName,const ArmatureAnimation* pArmature,const VectorInt& vIndex);

	static bool			IsHasMovementID(const Armature* pArmature,const std::string& sMovementID);//是否存在该动作
	static bool			IsHasMovementID(const ArmatureAnimation* pArmature,const std::string& sMovementID);//是否存在该动作

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
	static const VectorString& GetAnimationMovementNames(const Armature* pArmature);			//获得影片动作名称
	static const VectorString& GetAnimationMovementNames(const ArmatureAnimation* pArmature);	//获得影片动作名称
	static size_t		GetAnimationCount(const Armature* pArmature);						//获得动画的个数
	static size_t		GetAnimationCount(const ArmatureAnimation* pArmature);				//获得动画的个数
	static int			GetAnimationFrameCount(const Armature* pArmature);					//获得动画的总帧数
	static int			GetAnimationFrameCount(const ArmatureAnimation* pArmature);			//获得动画的总帧数
	static int			GetAnimationCurrentFrameIndex(const Armature* pArmature);			//获得动画的总帧数
	static int			GetAnimationCurrentFrameIndex(const ArmatureAnimation* pArmature);	//获得动画的总帧数
	static bool			GotoAndPlay( Armature* pArmature,			int nFrameIndex);		//跳转到指定帧，若为-1则跳转到最后一帧
	static bool			GotoAndPlay( ArmatureAnimation* pArmature,	int nFrameIndex);		//跳转到指定帧，若为-1则跳转到最后一帧
	static bool			GotoAndPause( Armature* pArmature,			int nFrameIndex);		//跳转到指定帧，若为-1则跳转到最后一帧
	static bool			GotoAndPause( ArmatureAnimation* pArmature,	int nFrameIndex);		//跳转到指定帧，若为-1则跳转到最后一帧
	static bool			SetCallFuncNull(Armature* pArmature);
	static bool			SetCallFuncNull(ArmatureAnimation* pArmature);

	static Armature*	SetAnimationCallBackMovement(Armature* pArmature,FnActionArmatureMovement fnMovement);
	static Armature*	SetAnimationCallBackOver(Armature* pArmature, FnActionArmatureOver fnOver);
	//粒子
	static ParticleSystemQuad*	PlayParticle(const std::string& sFile);

	//音频
	static int			PlayAudio(const std::string& sPath, bool bLoop = false, float fVolume = 1.0f);//不受静音控制
	
	static bool			SetAudioLoop(int nAudioID, bool bLoop);
	static bool			SetAudioVolume(int nAudioID, float fVolume);
	static bool			SetAudioPause(int nAudioID, bool bPause = true);
	static bool			SetAudioStop(int nAudioID);
	static bool			SetAudioCurrentTime(int nAudioID,float fSecond);
	static bool			SetAudioFinishCallback(int nAudioID, const std::function<void(int, const std::string&)>& callback);
	static bool			SetAudioMute(int nAudioID, bool bMute = true);//设置某音频静音

	static bool			IsAudioLoop(int nAudioID);
	static float		GetAudioVolume(int nAudioID);
	static float		GetAudioCurrentTime(int nAudioID);
	static float		GetAudioDuration(int nAudioID);
	static int			GetAudioState(int nAudioID);
	
	static bool			SetAudioPauseAll(bool bPause = true);
	static bool			SetAudioStopAll();

	static bool			AudioUncache(const std::string& sPath);
	static bool			AudioUncacheAll();

	//音频播放(常规调用)
	static int			PlaySound(const std::string& sPath, bool bLoop = false, float fVolume = 1.0f);	//播放声音 受静音控制
	static int			PlayMusic(const std::string& sPath, bool bLoop = true, float fVolume = 1.0f);		//播放背景音乐 会将前一个背景音乐停止 受静音控制

	static bool			StopSound(int nAudioID);//停止声音
	static bool			StopMusic();			//停止背景音乐

	static bool			SetSoundMute(bool bMute);//设置全局静音
	static bool			SetMusicMute(bool bMute);//设置背景音乐静音

	static bool			IsSoundMute();		//是否全局静音
	static bool			IsMusicMute();		//是否背景音乐静音

	static int			GetMusicAudioID();	//获取背景音乐AudioID

	//设置是否自动回收缓存
	static bool			SetAutoPurgeCache(bool bAuto);
	static bool			IsAutoPurgeCache();

	static bool			PurgeCachedData();	//回收所有缓存的数据

	static bool			PurgeTextureCache(bool bRemoveAll = true);		//清理贴图缓存
	static bool			PurgeSpriteFramesCache(bool bRemoveAll = true);	//清理组图缓存
	static bool			PurgeActionCache();								//清理动作缓存
	static bool			PurgeArmatureCache();							//清理动画缓存

	static Rect			TranWinRect(const Size& szie);//换算成平台显示区域
	static Rect			TranWinRect(const Rect& rect);//换算成平台显示区域
	static Rect			TranWinRect(const Node* pNode);

	//截图
	static bool			ScreenShot(const std::string& sFileName);
	//系统
	static bool			Exit();
	static bool			SleepFreeTime();

	//判断是否为指定Widget
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3,const std::string& sName4);
	static bool			IsTargetWidget(const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3,const std::string& sName4,const std::string& sName5);

	static bool			IsTargetWidgetBegin(const Ref* pObj,const std::string& sName);//只检查前几个字符
	static bool			IsTargetWidgetRange(const Ref* pObj,const std::string& sName,int nBegin,int nEnd);

	static int			GetWidgetNameIndex(const Ref* pObj,const std::string& sName,int nInvaild = -1);

	//触摸事件
	static bool			FireTouchedWithUI(const Vec2& ptUI);//UI坐标系(递归调用)
	static bool			FireTouchedWithGL(const Vec2& ptGL);//GL坐标系
	static bool			PostTouchedWithUI(const Vec2& ptUI);//UI坐标系(发送消息到线程队列)
	static bool			PostTouchedWithGL(const Vec2& ptGL);//GL坐标系

	static bool			CloneFireTouched(const Ref* pObj);//克隆触发事件
	static bool			ClonePostTouched(const Ref* pObj);//克隆触发事件

	static const Vec2&	GetTouchBeganPosition(const Ref* pObj);//获取触摸时的坐标(GL坐标系)
	static const Vec2&	GetTouchEndPosition(const Ref* pObj);
	static const Vec2&	GetTouchBeganPosition(const Widget* pWidget);//获取触摸时的坐标
	static const Vec2&	GetTouchEndPosition(const Widget* pWidget);

	//文字 - 添加描边
	static bool			SetStroke(LabelTTF* pText,	const Color4B &clrFont, float fSize);
	static bool			SetStroke(Label* pText,		const Color4B &clrFont, float fSize);
	static bool			SetStroke(Text* pText,		const Color4B &clrFont, float fSize);

	//文字 - 添加阴影
	static bool			SetShadow( LabelTTF* pText, const Color4B& clrShadow = Color4B::BLACK,const Size& fSize = Size(2,-2), float fBlur= 0 );
	static bool			SetShadow( Label* pText,	const Color4B& clrShadow = Color4B::BLACK,const Size& fSize = Size(2,-2), float fBlur= 0 );
	static bool			SetShadow( Text* pText,		const Color4B& clrShadow = Color4B::BLACK,const Size& fSize = Size(2,-2), float fBlur= 0 );

	//文字 - 去除特效
	static bool			RemoveEffect(LabelTTF* pText);
	static bool			RemoveEffect(Label* pText);
	static bool			RemoveEffect(Text* pText);

	static	bool		IsHitted(const Node* pNode,Touch *touch, Event *unusedEvent);			//是否点击

	static	bool		IsAncestorsEnabled(const Widget* pWidget);//是否连带所有祖宗都Enabled
	static	bool		IsAncestorsVisible(const Node* pNode);
	static	bool		IsHitted(const Widget* pWidget,Touch *touch, Event *unusedEvent);			//是否点击
	static	bool		IsAllHitted(const Widget* pWidget,const std::vector<Touch*>& vTouch, Event *unusedEvent);
	static	float		CalDistanceSquared(const Vec2& pt1,const Vec2& pt2);//两点间距离的平方 速度快于 两点间距离
	static	bool		IsDistanceLessThan(const Vec2& pt1,const Vec2& pt2,float fDistance);//两点间间距是否小于 指定距离
	static	bool		IsDistanceGreaterThan(const Vec2& pt1,const Vec2& pt2,float fDistance);//两点间间距是否小于 指定距离

	static	bool		MakeInRect(Node* pNode,const Vec2& ptOffset,const Rect& rRect);
	static	bool		MakeInRect(Node* pNode,const Rect& rRect);
	static	bool		MakeInScreen(Node* pNode,const Vec2& ptOffset);//使得节点在屏幕内
	static	bool		MakeInScreen(Node* pNode);//使得节点在屏幕内

	//创建自定义图片
	static	Sprite*		MakeSpriteAnnularSector (float fRadius1,float fRadius2,float fAngel,const Color4F& rFill,int nSegments = 40);//创建扇环精灵
	static	Sprite*		MakeSpriteLine ( const ToolFrame::VectorPoint2d& vPoint, float fRadius, const Color4F& clr );	//创建线列

	static	Vec2		ToVec(const ToolFrame::CPoint2d& pt);
	static	ToolFrame::CPoint2d ToPoint2d(const Vec2& vec2);

	//翻转
	static bool			SetFlippedX(Node* pNode,bool bFlipped);
	static bool			SetFlippedY(Node* pNode,bool bFlipped);
	static bool			IsFlippedX(Node* pNode);
	static bool			IsFlippedY(Node* pNode);

	//Spine

	//缓存Spine Atlas
	static spAtlas* CacheSpineAtlas(const std::string& atlasFile);

	//缓存Spine骨骼数据
	static spSkeletonData* CacheSpineSkeletonData(const std::string& skeletonDataFile, const std::string& atlasFile, float scale=1.0f);

	//清理缓存 SpineAtlas
	static bool PurgeSpineAtlasCache();

	//清理缓存 SpineSkeletonData
	static bool PurgeSpineSkeletonDataCache();

	//创建Spine动画
	static SkeletonAnimation* CreateSpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile, float scale=1.0f);

	//播放动画
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

	static SkeletonAnimation* SetSpineCallBackEvent(SkeletonAnimation* pAnimation, FnActionSpineEvent fnEvent);		//设置事件回调
	static SkeletonAnimation* SetSpineCallBackEventErr(SkeletonAnimation* pAnimation, FnActionSpineEvent fnEvent);	//设置事件回调返回失败时 回调
	static SkeletonAnimation* SetSpineCallBackOver(SkeletonAnimation* pAnimation, FnActionSpineOver fnOver);		//设置结束回调
	static SkeletonAnimation* SetSpineRemove(SkeletonAnimation* pAnimation,bool bRemove);							//设置移除标记

	//命令
	struct XCommandArg
	{
		Node*				pNodeShake;		//震动节点
		std::string			sLocalDir;		//当前目录
	};
	static bool RunCommand(std::string sEvent,std::string sEventArg, const XCommandArg* pArg = nullptr);//执行命令

	static bool				  SpineSkipBy(SkeletonAnimation* pAnimation,float fTimeNext);//跳到X秒后

	static bool				SetSpeed(SkeletonAnimation* pArmature,float fSpeed = 1.0f);

	static bool			GetSpineAnimationName(VectorString& vName,const SkeletonAnimation* pAnimation);
	static std::string	GetSpineAnimationNameCur( SkeletonAnimation* pAnimation,int nTrackIndex =0 );

	static const spAnimation* FindAnimationByName(const SkeletonAnimation* pAnimation,const std::string& sName);
	static float		GetAnimationDuration(const SkeletonAnimation* pAnimation, const std::string& sName);

	static bool			SetCallFuncNull(SkeletonAnimation* pArmature);

	static SkeletonAnimation* BindSpineNode(SkeletonAnimation* pAnimation,const std::string& sBone,Node* pNode);
private:
	//设置显示动作
	static Sprite*		ApiEffectSpriteShow(float fVisibleTime,float fFade, float fDelay,const std::string& sPath );
	static void			CallBackRemoveSelfLoop(Armature *armature, MovementEventType movementType, const std::string& movementID);
	static void			CallBackRemoveSelf(Armature *armature, MovementEventType movementType, const std::string& movementID);

	static void			DrawSolidSector(DrawNode* pNode ,const Vec2 &orign,const float fBeginAngle, const float radius1, const float radius2, const float fAngelFanShaped, const int segments, const Color4F &color);	
private:
	static bool			g_bAutoPurgeCache;//自动回收缓存标记

	static MapStringSkeletonData	g_vSpineSkeletonData;
	static MapStringAtlas			g_vSpineAtlas;

	static bool						g_bSoundMute;	//全局音量静音
	static bool						g_bMusicMute;	//背景音乐静音

	static int						g_nAudioMusic;	//当前背景音乐AudioID
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
