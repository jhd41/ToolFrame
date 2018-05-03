#include "StoreColor.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"

CStoreColor::CStoreColor(void)
{
}

CStoreColor::~CStoreColor(void)
{
	Restore();
}

bool CStoreColor::SetNode( Node* pNode,const Color3B& clr )
{
	if (!pNode)return false;

	VectorNode vNode;
	vNode.push_back(pNode);
	return SetNode(vNode,clr);
}

bool CStoreColor::SetNode( VectorNode& vNode,const Color3B& clr )
{
	Restore();
	Store(vNode);
	
	ApiCocos2dx::SetColor(vNode,clr);
	return true;
}
bool CStoreColor::Store( Node* pNode )
{
	if (!pNode)return false;

	VectorNode vNode;
	vNode.push_back(pNode);
	return Store(vNode);
}

bool CStoreColor::Store( VectorNode& vNode )
{
	VectorNode::iterator itr;
	foreach(itr,vNode)
	{
		Node* pNode = *itr;
		if (!pNode)return false;

		_vNode.push_back(pNode);
		_vColor.push_back(pNode->getColor());
	}

	return true;
}

bool CStoreColor::Restore()
{
	if (_vNode.empty())return false;

	VectorNode::iterator	itrNode;
	VectorColor3B::iterator itrColor;
	foreachDouble(itrNode,_vNode,itrColor,_vColor){
		Node* pNode = *itrNode;
		if (!pNode)return false;
			
		pNode->setColor(*itrColor);
	}

	_vNode.clear();
	_vColor.clear();
	return true;
}

bool CStoreColor::Clear()
{
	_vNode.clear();
	_vColor.clear();
	return true;
}

#endif //MACRO_LIB_COCOS2D
