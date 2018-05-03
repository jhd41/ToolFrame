#include "QuadTree.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CQuadTree::CQuadTree(void)
{
	_uCount = 0;
	_pNodeRoot = _vCreator.CreateObj();
}

CQuadTree::~CQuadTree(void)
{
}

bool CQuadTree::Init( const CRect2d& rRoot,const CPoint2d& ptCell )
{
	if (!_pNodeRoot)return false;
	_pNodeRoot->rect = rRoot;
	_rCell = ptCell;
	return true;
}

bool CQuadTree::AddObj( const CRect2d& rObj,const void* pObj )
{
	++_uCount;
	return !!AddObj(_pNodeRoot,rObj,(void*)pObj);
}

IQuadNode* CQuadTree::AddObj( IQuadNode* pNode, const CRect2d& rObj,void* pObj )
{
	if (!pNode)return nullptr;
	if (IsLeaf(pNode))
	{
		pNode->vObj.push_back(std::make_pair(rObj,pObj));
		return pNode;
	}
	
	//初始化节点
	if (pNode->vNode.empty())
		pNode->vNode.resize(4);

	const CRect2d& rParent = pNode->rect;
	CPoint2d ptMid = rParent.GetMidPoint();
	if (!pNode->vNode[0])
	{
		IQuadNode* pChild = _vCreator.CreateObj();
		ASSERT_LOG_DEBUG_ERR(pChild);
		pChild->pParent = pNode;
		pChild->nIndex = 0;
		pChild->rect.SetRect(rParent.GetLeftBottom().GetX(),ptMid.GetY(),ptMid.GetX(),rParent.GetRightTop().GetY());
		pNode->vNode[0] = pChild ;
	}
	if (!pNode->vNode[1])
	{
		IQuadNode* pChild = _vCreator.CreateObj();
		ASSERT_LOG_DEBUG_ERR(pChild);
		pChild->pParent = pNode;
		pChild->nIndex = 1;
		pChild->rect.SetRect(ptMid,rParent.GetRightTop());
		pNode->vNode[1] = pChild ;
	}
	if (!pNode->vNode[2])
	{
		IQuadNode* pChild = _vCreator.CreateObj();
		ASSERT_LOG_DEBUG_ERR(pChild);
		pChild->pParent = pNode;
		pChild->nIndex = 2;
		pChild->rect.SetRect(rParent.GetLeftBottom(),ptMid);
		pNode->vNode[2] = pChild ;
	}
	if (!pNode->vNode[3])
	{
		IQuadNode* pChild = _vCreator.CreateObj();
		ASSERT_LOG_DEBUG_ERR(pChild);
		pChild->pParent = pNode;
		pChild->nIndex = 3;
		pChild->rect.SetRect(ptMid.GetX(),rParent.GetLeftBottom().GetY(),rParent.GetRightTop().GetX(),ptMid.GetY());
		pNode->vNode[3] = pChild ;
	}

	//寻找适合的子结点
	IQuadNode* pChild = FindChildCanContainRect(pNode,rObj);
	if (!pChild)
	{
		//如果没有找到 添加到 当前节点上
		pNode->vObj.push_back(std::make_pair(rObj,pObj));
		return pNode;
	}

	return AddObj(pChild,rObj,pObj);
}

bool CQuadTree::IsLeaf( const IQuadNode* pNode ) const
{
	ASSERT_LOG_ERROR(pNode);
	return pNode->rect.GetSize() <= _rCell;
}

IQuadNode* CQuadTree::FindChildCanContainRect( IQuadNode* pParent,const CRect2d& rObj )const
{
	if (!pParent)return nullptr;
	if (pParent->vNode.empty())return nullptr;

	VectorTreeNode::const_iterator itr;
	foreach(itr,pParent->vNode){
		IQuadNode* pNode = *itr;
		if (pNode && pNode->rect.IsContain(rObj))
			return pNode;
	}
	return nullptr;
}

IQuadNode* CQuadTree::FindNode( IQuadNode* pNode,const CRect2d& rect ) const
{
	//先查找在不在本节点内
	if (!pNode->vObj.empty())
	{
		ListObj::const_iterator itr;
		foreach(itr,pNode->vObj){
			if (itr->first == rect)
				return pNode;
		}
	}

	IQuadNode* pChild = FindChildCanContainRect(pNode,rect);
	if (!pChild)return nullptr;
	return FindNode(pChild,rect);
}

bool CQuadTree::Erase( const CRect2d& rObj,void* pObj )
{
	IQuadNode* pNode = FindNode(_pNodeRoot,rObj);
	if (!pNode)return false;

	ListObj::iterator itr;
	foreach(itr,pNode->vObj){
		if (itr->first == rObj && itr->second == pObj)
		{
			pNode->vObj.erase(itr);
			--_uCount;
			return true;
		}
	}
	
	return false;
}

uint CQuadTree::Erase( void* pObj,int nCount /*= 1*/ )
{
	return Erase(_pNodeRoot,pObj,nCount);
}

uint CQuadTree::Erase( IQuadNode* pParent,void* pObj,int nCount )
{
	if (!pParent)return 0;

	int nEraseCount=0;
	//擦除当前节点
	{
		ListObj::iterator itr = pParent->vObj.begin();
		while (itr != pParent->vObj.end())
		{
			void* pTarget = itr->second;
			if (pTarget != pObj){
				++itr;
				continue;
			}
			itr = ToolFrame::EraseByItr(pParent->vObj,itr);
			++nEraseCount;
			if (nCount != -1 && ++nEraseCount >= nCount)
				return nEraseCount;
		}
	}

	//擦除子节点
	{
		VectorTreeNode::const_iterator itr;
		foreach(itr,pParent->vNode){
			IQuadNode* pNode = *itr;
			nEraseCount += Erase(pNode,pObj,nCount - nEraseCount);
			if (nCount != -1 && ++nEraseCount >= nCount)
				return nEraseCount;
		}
	}

	return nEraseCount;
}

bool CQuadTree::Find( ListVoidPtr& vObj,const CRect2d& rect ) const
{
	Find(vObj,_pNodeRoot,rect);
	return !vObj.empty();
}

bool CQuadTree::Find( ListVoidPtr& vObj,IQuadNode* pParent,const CRect2d& rect ) const
{
	if (!pParent)return false;

	//当前节点的物体进行碰撞检测
	if (!pParent->vObj.empty())
	{
		ListObj::const_iterator itr;
		foreach(itr,pParent->vObj){
			if (itr->first.IsIntersect(rect))
				vObj.push_back(itr->second);
		}
	}

	//子节点进行碰撞检测
	if (!pParent->vNode.empty())
	{
		VectorTreeNode::const_iterator itr;
		foreach(itr,pParent->vNode){
			IQuadNode* pChild = *itr;
			ASSERT_LOG_ERROR(pChild);

			CRect2d rSub;
			if (pChild->rect.CalIntersect(rSub,rect))
				Find(vObj,pChild,rSub);
		}
	}

	return nullptr;
}

size_t CQuadTree::GetSize() const
{
	return _uCount;
}

size_t CQuadTree::GetNodeSize() const
{
	return _vCreator.GetSize();
}

bool CQuadTree::ClearEmptyNode()
{
	while (ClearOneEmptyNode());
	return true;
}

bool CQuadTree::ClearOneEmptyNode()
{
	TObjCreator<IQuadNode>::iterator itr;
	foreach(itr,_vCreator){
		IQuadNode* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);

		if (pNode != _pNodeRoot && pNode->vObj.empty() && (pNode->vNode.empty() || ToolFrame::IsSameValue(pNode->vNode,(const IQuadNode*)nullptr)))
		{
			pNode->pParent->vNode[pNode->nIndex] = nullptr;

			_vCreator.DeleteObj(pNode);
			return true;
		}
	}

	return false;
}

NS_TOOL_FRAME_END
