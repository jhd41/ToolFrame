#pragma once
#include "Macro.h"
#include "Segment.h"
#include "TObjCreator.h"

//在这里运用二叉树的形式存储一维线段
NS_TOOL_FRAME_BEGIN

//节点
struct IBinaryNode;
typedef std::map<int,IBinaryNode*>				MapIntBinaryNode;
typedef std::vector<IBinaryNode*>				VectorBinaryNode;
typedef std::list<std::pair<CSegment,void*> >	ListObj;

struct IBinaryNode
{
	CSegment			seg;
	VectorBinaryNode	vNode;
	ListObj				vObj;
	IBinaryNode*		pParent;
	int					nIndex;
	IBinaryNode(){
		pParent = nullptr;
		nIndex = 0;
	}
};
class TOOLFRAME_DLL CBinaryTree
{
public:
	bool Init(const CSegment& rRoot,const float fCell);		//设置根节点区域大小 单元格大小
	bool AddObj(const CSegment& segObj,const void* pObj);	//添加节点
	bool Find(ListVoidPtr& vObj,const CSegment& seg)const;	//查找该区域内的元素
	bool Erase(const CSegment& segObj,void* pObj);			//删除
	uint Erase(void* pObj,int nCount = 1);					//删除(低效率 返回擦除个数)
	size_t GetSize()const;									//获取元素的个数
	size_t GetNodeSize()const;								//获取节点的个数
	bool ClearEmptyNode();									//清除无效节点
private:
	bool			IsLeaf(const IBinaryNode* pNode)const;	//线段长度小于等于元线段，那么就是叶子节点
	IBinaryNode*	AddObj(IBinaryNode* pNode, const CSegment& segObj,void* pObj);			//添加节点
	IBinaryNode*	FindChildCanContainSegment(IBinaryNode* pParent,const CSegment& segObj)const;//寻找可以容纳的子节点
	IBinaryNode*	FindNode(IBinaryNode* pNode,const CSegment& seg)const;	
	bool			Find(ListVoidPtr& vObj,IBinaryNode* pParent,const CSegment& seg)const;	//查找该区域内的元素//查找指定区域所在节点
	bool			ClearOneEmptyNode();
	uint			Erase(IBinaryNode* pParent,void* pObj,int nCount);
public:
	CBinaryTree(void);
	virtual ~CBinaryTree(void);
private:
	IBinaryNode*				_pNodeRoot;	//根节点
	float						_fCell;		//单元线段大小
	TObjCreator<IBinaryNode>	_vCreator;	//节点创建器(用于内存回收)
	size_t						_uCount;	//元素个数
};

NS_TOOL_FRAME_END