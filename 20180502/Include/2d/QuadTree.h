#pragma once
#include "Macro.h"
#include "Rect2d.h"
#include "TObjCreator.h"

//������4�����ķ�ʽ���д洢ɢ���ƽ��ռ�
//����������Ҫ�洢������Ǻ��������Ĵ�С ��Լ ����Ϊ21����(21000��)��
//���� ���� ���� ���� Ҷ�ӵ�Ԫ ��100��*100�� û���ξ��ܹ����ҵ� ����Ҷ�ӽڵ㡣
//ÿ����Ҷ�ӽڵ� ֻ�������Σ�Ҷ�ӽڵ�������� �Լ� ��λ�����б�

NS_TOOL_FRAME_BEGIN

//�ڵ�
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
	bool Init(const CRect2d& rRoot,const CPoint2d& ptCell);	//���ø��ڵ������С ��Ԫ���С
	bool AddObj(const CRect2d& rObj,const void* pObj);		//��ӽڵ�
	bool Find(ListVoidPtr& vObj,const CRect2d& rect)const;	//���Ҹ������ڵ�Ԫ��
	bool Erase(const CRect2d& rObj,void* pObj);				//ɾ��
	uint Erase(void* pObj,int nCount = 1);					//ɾ��(��Ч�� ���ز�������)
	size_t GetSize()const;									//��ȡԪ�صĸ���
	size_t GetNodeSize()const;								//��ȡ�ڵ�ĸ���
	bool ClearEmptyNode();									//�����Ч�ڵ�
private:
	bool		IsLeaf(const IQuadNode* pNode)const;
	IQuadNode*	AddObj(IQuadNode* pNode, const CRect2d& rObj,void* pObj);		//��ӽڵ�
	IQuadNode*	FindChildCanContainRect(IQuadNode* pParent,const CRect2d& rObj)const;//Ѱ�ҿ������ɵ��ӽڵ�
	IQuadNode*	FindNode(IQuadNode* pNode,const CRect2d& rect)const;	
	bool		Find(ListVoidPtr& vObj,IQuadNode* pParent,const CRect2d& rect)const;	//���Ҹ������ڵ�Ԫ��//����ָ���������ڽڵ�
	bool		ClearOneEmptyNode();
	uint		Erase(IQuadNode* pParent,void* pObj,int nCount);
public:
	CQuadTree(void);
	virtual ~CQuadTree(void);
private:
	IQuadNode*				_pNodeRoot;	//���ڵ�
	CPoint2d				_rCell;		//��Ԫ���С
	TObjCreator<IQuadNode>	_vCreator;	//�ڵ㴴����(�����ڴ����)
	size_t					_uCount;	//Ԫ�ظ���
};

NS_TOOL_FRAME_END
	