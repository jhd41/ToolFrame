#include "BinaryTree.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
CBinaryTree::CBinaryTree(void)
{
	_uCount = 0;
	_pNodeRoot = _vCreator.CreateObj();
}


CBinaryTree::~CBinaryTree(void)
{
}

bool CBinaryTree::Init( const CSegment& rRoot,const float fCell )
{
	if (!_pNodeRoot)return false;
	_pNodeRoot->seg = rRoot;
	_fCell = fCell;
	return true;
}

bool CBinaryTree::AddObj( const CSegment& segObj,const void* pObj )
{
	++_uCount;
	return !!AddObj(_pNodeRoot,segObj,(void*)pObj);
}

IBinaryNode* CBinaryTree::AddObj( IBinaryNode* pNode, const CSegment& segObj,void* pObj )
{
	if (!pNode)return nullptr;
	if (IsLeaf(pNode))
	{
		pNode->vObj.push_back(std::make_pair(segObj,pObj));
		return pNode;
	}
	
	//初始化节点
	if (pNode->vNode.empty())
		pNode->vNode.resize(2);
	const CSegment& segParent = pNode->seg;
	float fMid = segParent.GetMidPosition();
	
	if (!pNode->vNode[0])
	{
		IBinaryNode* pChild = _vCreator.CreateObj();
		ASSERT_LOG_DEBUG_ERR(pChild);
		pChild->pParent = pNode;
		pChild->nIndex = 0;
		pChild->seg.SetSegment(segParent.GetBegin(),fMid);
		pNode->vNode[0] = pChild ;
	}
	if (!pNode->vNode[1])
	{
		IBinaryNode* pChild = _vCreator.CreateObj();
		ASSERT_LOG_DEBUG_ERR(pChild);
		pChild->pParent = pNode;
		pChild->nIndex = 1;
		pChild->seg.SetSegment(fMid+1,segParent.GetEnd());
		pNode->vNode[1] = pChild ;
	}

	//寻找适合的子结点
	IBinaryNode* pChild = FindChildCanContainSegment(pNode,segObj);
	if (!pChild)
	{
		//如果没有找到 添加到 当前节点上
		pNode->vObj.push_back(std::make_pair(segObj,pObj));
		return pNode;
	}

	return AddObj(pChild,segObj,pObj);
}

bool CBinaryTree::Find( ListVoidPtr& vObj,const CSegment& seg ) const
{
	Find(vObj,_pNodeRoot,seg);
	return !vObj.empty();
}

bool CBinaryTree::Find( ListVoidPtr& vObj,IBinaryNode* pParent,const CSegment& seg ) const
{
	if (!pParent)return false;

	//当前节点的物体进行碰撞检测
	if (!pParent->vObj.empty())
	{
		ListObj::const_iterator itr;
		foreach(itr,pParent->vObj){
			if (itr->first.IsIntersect(seg))
				vObj.push_back(itr->second);
		}
	}

	//子节点进行碰撞检测
	if (!pParent->vNode.empty())
	{
		VectorBinaryNode::const_iterator itr;
		foreach(itr,pParent->vNode){
			IBinaryNode* pChild = *itr;
			ASSERT_LOG_ERROR(pChild);

			CSegment segSub;
			if (pChild->seg.CalIntersect(segSub,seg))
				Find(vObj,pChild,segSub);
		}
	}

	return nullptr;
}

bool CBinaryTree::Erase( const CSegment& segObj,void* pObj )
{
	IBinaryNode* pNode = FindNode(_pNodeRoot,segObj);
	if (!pNode)return false;

	ListObj::iterator itr;
	foreach(itr,pNode->vObj){
		if (itr->first == segObj && itr->second == pObj)
		{
			pNode->vObj.erase(itr);
			--_uCount;
			return true;
		}
	}

	return false;
}

uint CBinaryTree::Erase( void* pObj,int nCount /*= 1*/ )
{
	return Erase(_pNodeRoot,pObj,nCount);
}

uint CBinaryTree::Erase( IBinaryNode* pParent,void* pObj,int nCount )
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
		VectorBinaryNode::const_iterator itr;
		foreach(itr,pParent->vNode){
			IBinaryNode* pNode = *itr;
			nEraseCount += Erase(pNode,pObj,nCount - nEraseCount);
			if (nCount != -1 && ++nEraseCount >= nCount)
				return nEraseCount;
		}
	}

	return nEraseCount;
}

size_t CBinaryTree::GetSize() const
{
	return _uCount;
}

size_t CBinaryTree::GetNodeSize() const
{
	return _vCreator.GetSize();
}

bool CBinaryTree::ClearEmptyNode()
{
	while (ClearOneEmptyNode());
	return true;
}

bool CBinaryTree::IsLeaf( const IBinaryNode* pNode ) const
{
	ASSERT_LOG_ERROR(pNode);
	return pNode->seg.GetLength() <= _fCell;
}

IBinaryNode* CBinaryTree::FindChildCanContainSegment( IBinaryNode* pParent,const CSegment& segObj ) const
{
	if (!pParent)return nullptr;
	if (pParent->vNode.empty())return nullptr;

	VectorBinaryNode::const_iterator itr;
	foreach(itr,pParent->vNode){
		IBinaryNode* pNode = *itr;
		if (pNode && pNode->seg.IsContain(segObj))
			return pNode;
	}
	return nullptr;
}

IBinaryNode* CBinaryTree::FindNode( IBinaryNode* pNode,const CSegment& seg ) const
{
	//先查找在不在本节点内
	if (!pNode->vObj.empty())
	{
		ListObj::const_iterator itr;
		foreach(itr,pNode->vObj){
			if (itr->first == seg)
				return pNode;
		}
	}

	IBinaryNode* pChild = FindChildCanContainSegment(pNode,seg);
	if (!pChild)return nullptr;
	return FindNode(pChild,seg);
}

bool CBinaryTree::ClearOneEmptyNode()
{
	TObjCreator<IBinaryNode>::iterator itr;
	foreach(itr,_vCreator){
		IBinaryNode* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);

		if (pNode != _pNodeRoot && pNode->vObj.empty() && (pNode->vNode.empty() || ToolFrame::IsSameValue(pNode->vNode,(const IBinaryNode*)nullptr)))
		{
			pNode->pParent->vNode[pNode->nIndex] = nullptr;

			_vCreator.DeleteObj(pNode);
			return true;
		}
	}

	return false;
}

NS_TOOL_FRAME_END