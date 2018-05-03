#include "StoreVisible.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"

CStoreVisible::CStoreVisible(void)
{
}

CStoreVisible::~CStoreVisible(void)
{
	Restore();
}

bool CStoreVisible::SetNode( Node* pNode,bool bVisible )
{
	if (!pNode)return false;

	VectorNode vNode;
	vNode.push_back(pNode);
	return SetNode(vNode,bVisible);
}

bool CStoreVisible::SetNode( VectorNode& vNode,bool bVisible )
{
	Restore();
	Store(vNode);
	ApiCocos2dx::SetVisible(vNode,bVisible);
	return true;
}
bool CStoreVisible::Store( Node* pNode )
{
	if (!pNode)return false;

	VectorNode vNode;
	vNode.push_back(pNode);
	return Store(vNode);
}

bool CStoreVisible::Store( VectorNode& vNode )
{
	VectorNode::iterator itr;
	foreach(itr,vNode)
	{
		Node* pNode = *itr;
		if (!pNode)return false;

		_vNode.push_back(pNode);
		_vVisible.push_back(pNode->isVisible());
	}

	return true;
}
bool CStoreVisible::Restore()
{
	if (_vNode.empty())return false;

	VectorNode::iterator itrNode;
	VectorBool::iterator itrVisible;
	foreachDouble(itrNode,_vNode,itrVisible,_vVisible){
		Node* pNode = *itrNode;
		if (!pNode)return false;
			
		pNode->setVisible(*itrVisible);
	}

	_vNode.clear();
	_vVisible.clear();
	return true;
}

bool CStoreVisible::Clear()
{
	_vNode.clear();
	_vVisible.clear();
	return true;
}

#endif //MACRO_LIB_COCOS2D
