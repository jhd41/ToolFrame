#pragma once
#include "Macro.h"
#include "Rect2d.h"
#include "TObjCreator.h"

//我们以4叉树的方式进行存储散落的平面空间
//假设我们所要存储的面积是杭州市区的大小 大约 长宽为21公里(21000米)。
//假设 我们 定义 单个 叶子单元 是100米*100米 没几次就能够查找到 所需叶子节点。
//每个非叶子节点 只包含矩形，叶子节点包含矩形 以及 单位物体列表

NS_TOOL_FRAME_BEGIN

//节点
struct IQuadNode;
typedef std::map<int,IQuadNode*>				MapIntNode;
typedef std::vector<IQuadNode*>					VectorTreeNode;
typedef std::list<std::pair<CRect2d,void*> >	ListObj;

struct IQuadNode
{
	CRect2d			rect;
	VectorTreeNode	vNode;
	ListObj			vObj;
	IQuadNode*		pParent;
	int				nIndex;
	IQuadNode(){
		pParent = nullptr;
		nIndex = 0;
	}
};

class TOOLFRAME_DLL CQuadTree
{
public:
	bool Init(const CRect2d& rRoot,const CPoint2d& ptCell);	//设置根节点区域大小 单元格大小
	bool AddObj(const CRect2d& rObj,const void* pObj);		//添加节点
	bool Find(ListVoidPtr& vObj,const CRect2d& rect)const;	//查找该区域内的元素
	bool Erase(const CRect2d& rObj,void* pObj);				//删除
	uint Erase(void* pObj,int nCount = 1);					//删除(低效率 返回擦除个数)
	size_t GetSize()const;									//获取元素的个数
	size_t GetNodeSize()const;								//获取节点的个数
	bool ClearEmptyNode();									//清除无效节点
private:
	bool		IsLeaf(const IQuadNode* pNode)const;
	IQuadNode*	AddObj(IQuadNode* pNode, const CRect2d& rObj,void* pObj);		//添加节点
	IQuadNode*	FindChildCanContainRect(IQuadNode* pParent,const CRect2d& rObj)const;//寻找可以容纳的子节点
	IQuadNode*	FindNode(IQuadNode* pNode,const CRect2d& rect)const;	
	bool		Find(ListVoidPtr& vObj,IQuadNode* pParent,const CRect2d& rect)const;	//查找该区域内的元素//查找指定区域所在节点
	bool		ClearOneEmptyNode();
	uint		Erase(IQuadNode* pParent,void* pObj,int nCount);
public:
	CQuadTree(void);
	virtual ~CQuadTree(void);
private:
	IQuadNode*				_pNodeRoot;	//根节点
	CPoint2d				_rCell;		//单元格大小
	TObjCreator<IQuadNode>	_vCreator;	//节点创建器(用于内存回收)
	size_t					_uCount;	//元素个数
};

NS_TOOL_FRAME_END
	