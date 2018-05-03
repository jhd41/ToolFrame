#pragma once
#include "MacroCocos2dx.h"

//节点颜色存储
#ifdef MACRO_LIB_COCOS2D

class CStoreColor
{
	typedef std::vector<Color3B> VectorColor3B;
public:
	bool	SetNode(Node* pNode,const Color3B& clr);
	bool	SetNode(VectorNode& vNode,const Color3B& clr);
	bool	Store(Node* pNode);
	bool	Store(VectorNode& vNode);
	bool	Restore();//还原
	bool	Clear();
public:
	CStoreColor(void);
	virtual ~CStoreColor(void);
private:
	VectorNode		_vNode;
	VectorColor3B	_vColor;//开始的颜色
};

#endif //MACRO_LIB_COCOS2D