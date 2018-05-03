#pragma once
#include "MacroCocos2dx.h"

//节点颜色存储
#ifdef MACRO_LIB_COCOS2D

class CStoreVisible
{
public:
	bool	SetNode(Node* pNode,bool bVisible);
	bool	SetNode(VectorNode& vNode,bool bVisible);

	bool	Store(Node* pNode);
	bool	Store(VectorNode& vNode);

	bool	Restore();//还原
	bool	Clear();
public:
	CStoreVisible(void);
	virtual ~CStoreVisible(void);
private:
	VectorNode	_vNode;
	VectorBool	_vVisible;//开始的颜色
};

#endif //MACRO_LIB_COCOS2D