#include "Eval.h"
#include "ToolFrame.h"
#include "MLoger.h"
#include "MEval.h"

NS_TOOL_FRAME_BEGIN

CEval::CEval(void)
{
	_nRandID = 0;
	_pNode = nullptr;
	_parserCallBack.SetEval(this);
	_parserCallBack.SetScopeInfo(&GetDefaultScope());

	SetError(false);
	SetParseDone(false);
}

CEval::~CEval(void)
{
}

//思路:先 将 表达式拆解为 一个个的元素。

bool CEval::Expression( const std::string& sExp )
{
	Clear();
	_sExp =sExp;

	CEvalParserExpression node(&_parserCallBack);

	ASSERT_LOG_ERROR(node.Init());
	node.Parse(0);

	return IsParseDone() && !IsError();
}

bool CEval::Script( const std::string& sExp )
{
	Clear();
	_sExp =sExp;

	CEvalParserSegment node(&_parserCallBack);

	ASSERT_LOG_ERROR(node.Init());
	node.Parse(0);

	return IsParseDone() && !IsError();
}

const std::string& CEval::GetExp() const
{
	return _sExp;
}

bool CEval::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	if (IsParseDone())
	{
		SetError(true);
		return true;
	}

	ASSERT_LOG_ERROR(pNode);

	_pNode = pNode->Clone();
	ASSERT_LOG_ERROR(_pNode);

	SetParseDone(true);
	return true;
}

void CEval::Clear()
{
	if (_pNode)Destory(_pNode);
	
	_sExp = "";

	SetParseDone(false);
	SetError(false);
}

double CEval::GetReturnValue() const
{
	ASSERT_LOG_ERROR(_pNode);
	return _pNode->GetReturnValue();
}

bool CEval::Execute() const
{
	ASSERT_LOG_ERROR(_pNode);
	_pNode->GetReturnValue();

	return true;
}

bool CEval::Clone( ListEvalNode& vNodeDes,const ListEvalNode& vNodeSrc )
{
	ASSERT_LOG_ERROR( vNodeDes.empty());
	if (ToolFrame::IsSelf(vNodeSrc,vNodeDes))return false;
	if (vNodeSrc.empty())return true;

	ListEvalNode::const_iterator itr;
	foreach(itr,vNodeSrc){
		const IEvalNode* pNodeSrc = *itr;
		ASSERT_LOG_ERROR(pNodeSrc);

		IEvalNode* pNodeDes = pNodeSrc->Clone();
		ASSERT_LOG_ERROR(pNodeDes);

		ASSERT_LOG_ERROR(ToolFrame::Insert(vNodeDes,pNodeDes));
	}

	return true;
}

bool CEval::Destory( ListEvalNode& vNodeDes )
{
	ToolFrame::Delete(vNodeDes);
	return true;
}

bool CEval::Destory( IEvalNode*  pNode )
{
	ToolFrame::Delete(pNode);
	return true;
}

bool CEval::GetScopeName( VectorString& vScopeName,CScopeInfo* pScope ) const
{
	ASSERT_LOG_ERROR(vScopeName.empty() && pScope);
	while(pScope != &GetDefaultScope()){
		const std::string& sName = pScope->GetName();
		ASSERT_LOG_ERROR(!sName.empty());
		ASSERT_LOG_ERROR(ToolFrame::Insert(vScopeName,sName));
		pScope = pScope->GetParent();
		ASSERT_LOG_ERROR(pScope);
	}
	return true;
}

CScopeInfo* CEval::GetScopeByName( const VectorString& vScopeName )
{
	CScopeInfo* pScope = &GetDefaultScope();
	ASSERT_LOG_ERROR(pScope);
	if (vScopeName.empty()) return pScope;
	
	VectorString::const_reverse_iterator itr;
	foreachR(itr,vScopeName){
		const std::string& sScopeName = *itr;
		ASSERT_LOG_ERROR(!sScopeName.empty());

		pScope = pScope->GetScope(sScopeName);
		if (!pScope)return nullptr;
	}

	return pScope;
}

std::string CEval::MakeNewScopeName()
{
	std::stringstream sStram;
	sStram<<"___default"<<_nRandID++;

	return sStram.str();
}

NS_TOOL_FRAME_END
