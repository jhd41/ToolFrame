#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

#include "MacroCocos2dx.h"

NS_TOOL_FRAME_BEGIN

//注记:本类完成多个CCSprite呈现。以锚点(0.5,0.5 中心)编写
//目前为了方便起见只支持每个单元都同样大小 且 每个单元小于等于显示区域
//自己本身继承CCNode作为一个节点 也同样受到 特效 以及自己 影响
//通过自己的孩子节点来进行排序
class CNodeList
	:public	CCNodeRGBA
{
	COCOS2DX_CREATE(CNodeList);
public:
	enum{
		ALIGN_INVAID=0,

		ALIGN_HORIZONTAL_CENTER,	//水平居中对齐
		ALIGN_HORIZONTAL_AVG,		//水平均分
		ALIGN_HORIZONTAL_FULL,		//水平铺满
		
		ALIGN_VERTICAL_CENTER,		//竖直居中
		ALIGN_VERTICAL_AVG,			//竖直均分
		ALIGN_VERTICAL_FULL,		//竖直铺满
	};

public:
	bool	SetSize(const CCSize& rSize);
	bool	SetWithRect(const CCRect& rect);
	
	void	SetMoveArg(float fMoveTime,float fMoveRate);
public:
	virtual void addChild(CCNode * child);
	virtual void addChild(CCNode * child, int zOrder);
	virtual void addChild(CCNode * child, int zOrder, int tag);
	virtual void removeChild(CCNode* child, bool cleanup);
	virtual void reorderChild(CCNode * child, int zOrder);

private:
	void	Update(float dt);
public:
	//可以不调用
	bool	Adjust();		//匹配屏幕 调整精灵坐标
	bool	Cut();			//裁剪屏幕
private:

	bool	AdjustLeft();				//左对齐
	bool	AdjustRight();				//右对齐

	bool	AdjustCenterHorizontal();	//水平居中
	bool	AdjustAvgHorizonta();		//水平均分

	bool	AdjustCenterVertical();		//竖直居中
	bool	AdjustAvgVertical();		//竖直均分

	bool	AdjustFullHorizontal();		//水平填充
	bool	AdjustFullVertical();		//竖直填充

	//辅助函数
public:
	void	SetAdjustScreenCenter();
	void	SetSizeWhithScreenSize();

private:
	CCSize	CalTotalSize();//获取内容总尺寸
	bool	MoveTo(const VectorPoint& vPoint);//将卡牌移动至指定地点

	bool	CalPosTileHorizontal(VectorPoint& vPoint,const CCPoint& ptOffset =CCPoint(0,0) );	//计算水平平铺的坐标
	bool	CalPosAvgHorizontal(VectorPoint& vPoint);											//计算水平均分的坐标

	bool	CalPosTileVertical(VectorPoint& vPoint,const CCPoint& ptOffset =CCPoint(0,0) );		//计算竖直平铺的坐标
	bool	CalPosAvgVertical(VectorPoint& vPoint);												//计算竖直均分的坐标

	bool	CalPosFullHorizontal(VectorPoint& vPoint);											//计算水平填充满的各个坐标
	bool	CalPosFullVertical(VectorPoint& vPoint);											//计算竖直填充满的各个坐标

	//获得内容大小
	CCSize	GetNeedSize(int eAlign);

	CCSize	GetNeedSizeHorizontalTile();//获得水平平铺方式需求大小
	CCSize	GetNeedSizeHorizontalAvg();	//获得水平均分方式需求大小
	CCSize	GetNeedSizeHorizontalFull();//获得水平填充方式需求大小
	CCSize	GetNeedSizeVerticalTile();	//获得竖直平铺方式需求大小
	CCSize	GetNeedSizeVerticalAvg();	//获得竖直均分方式需求大小
	CCSize	GetNeedSizeVerticalFull();	//获得竖直填充方式需求大小

	//自适应大小
	void	SetAdaptive(const CCSize& rNeed);
	float	GetAdaptiveRate(const CCSize& rContent,const CCSize& rNeed);
	CCSize	GetAdaptiveSize(const CCSize& rContent,const CCSize& rNeed);

	//判断是否足够空间
	bool	IsEnoughSpace(const CCSize& rNeed);
	bool	IsEnoughSpace(const CCSize& rContent,const CCSize& rNeed);

	bool	AdjustEnoughSpace(CCSize& rNeed,int eAlign);

	//获取子节点
	bool	IsChildEmpty();					//子节点是否空
	UINT	GetChildCount();				//获取子节点数量
	CCNode*	FindChildAtIndex(UINT nIndex);	//获取子节点 通过索引
	CCNode*	FindChildLast();					//获取最后一个子节点
	CCNode* FindChildByBoundingBoxMostHigh();//获取绑定盒最高的子节点
	CCNode* FindChildByBoundingBoxMostWide();//获取绑定盒最宽的子节点
	
	//设置内容大小
	bool	Cut(CCSize rNeed);
private:
	CNodeList(void);
	virtual ~CNodeList(void);
private:
	CFIELD_INT(Align);		//对齐方式
	CFIELD_BOOL(Adaptive);	//自适应
	CFIELD_BOOL(AutoCut);	//自动裁剪
private:
	float			_fMoveTime;		//移动的时间
	float			_fMoveRate;		//移动的加速度
	bool			_bDirtyAdjust;	//脏数据 用于计算坐标
	CCSize	_rStandard;		//裁剪参数 标准大小
};


NS_TOOL_FRAME_END

#endif //MACRO_LIB_COCOS2D
