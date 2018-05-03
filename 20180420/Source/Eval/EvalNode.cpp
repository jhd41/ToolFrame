#include "EvalNode.h"
#include "MLoger.h"
#include "Eval.h"
#include "MEval.h"

NS_TOOL_FRAME_BEGIN

//IEvalNode
//////////////////////////////////////////////////////////////////////////
IEvalNode::IEvalNode( CEval* pEval )
{
	ASSERT_LOG_ERROR(pEval);
	SetEval(pEval);
	SetPrasingDone(true);//默认解析完成
}

IEvalNode::~IEvalNode(void)
{

}

bool IEvalNode::Copy( const IEvalNode* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	COPY_CFIELD_REF(Eval,*pNode);
	COPY_CFIELD_BOOL(PrasingDone,	*pNode);

	_vScopeName = pNode->_vScopeName;

	return true;
}

CEvalOperator* IEvalNode::ToOperator()
{
	return nullptr;
}

const CEvalOperator* const IEvalNode::ToOperator() const
{
	return nullptr;
}

bool IEvalNode::SetScope( CScopeInfo* pScope )
{
	ASSERT_LOG_ERROR(pScope);
	ASSERT_LOG_ERROR(_vScopeName.empty());

	ASSERT_LOG_ERROR(GetEval());
	return GetEval()->GetScopeName(_vScopeName,pScope);
}

CScopeInfo* IEvalNode::GetScope() const
{
	return GetEval()->GetScopeByName(_vScopeName);
}

bool IEvalNode::IsTrue( IEvalNode* pNode )const
{
	ASSERT_LOG_ERROR(pNode);

	return !ToolFrame::IsEqual( pNode->GetReturnValue(),0.0f);
}

//CEvalOperator
//////////////////////////////////////////////////////////////////////////
CEvalOperator::CEvalOperator( CEval* pEval,EOperation eOperation )
:IEvalNode(pEval)
{
	_pOperationConfig = nullptr;

	SetNodeSingle(nullptr);
	SetNodeLeft(nullptr);
	SetNodeRight(nullptr);

	SetOperation(eOperation);
}

CEvalOperator::~CEvalOperator()
{
	CEval::Destory(GetNodeSingle());
	CEval::Destory(GetNodeLeft());
	CEval::Destory(GetNodeRight());
}

IEvalNode* CEvalOperator::Clone()const
{
	CEvalOperator* pNode = new CEvalOperator(GetEval(),GetOperation());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

bool CEvalOperator::Copy( const CEvalOperator* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	if (pNode->GetNodeSingle())
		SetNodeSingle(pNode->GetNodeSingle()->Clone());
	if (pNode->GetNodeLeft())
		SetNodeLeft(pNode->GetNodeLeft()->Clone());
	if (pNode->GetNodeRight())
		SetNodeRight(pNode->GetNodeRight()->Clone());

	_pOperationConfig = pNode->_pOperationConfig;

	return true;
}

double CEvalOperator::GetReturnValue() const
{
	switch(GetOperation())
	{
	case OPERATION_PARENTHESES:
		{
			ASSERT_LOG_ERROR(GetNodeSingle());
			return GetNodeSingle()->GetReturnValue();
		}
		break;
	case OPERATION_POSITIVE:
		return GetNodeSingle()->GetReturnValue();
		break;
	case OPERATION_NEGATIVE:
		return - GetNodeSingle()->GetReturnValue();
		break;
	case OPERATION_INVERTER:
		return  ToolFrame::IsEqual(GetNodeSingle()->GetReturnValue(),0.0f);
		break;
		//自增运算符
	case OPERATION_INCREMENT_SUFFIX:
		{
			ASSERT_LOG_ERROR(GetNodeSingle());
			double fValue = GetNodeSingle()->GetReturnValue();
			Assignment(GetNodeSingle(),fValue + 1.0f);
			return fValue;
		}
		break;
	case OPERATION_DECREMENT_SUFFIX:
		{
			ASSERT_LOG_ERROR(GetNodeSingle());
			double fValue = GetNodeSingle()->GetReturnValue();
			Assignment(GetNodeSingle(),fValue - 1.0f);
			return fValue;
		}
		break;
	case OPERATION_INCREMENT_PERFIX:
		{
			ASSERT_LOG_ERROR(GetNodeSingle());
			return Assignment(GetNodeSingle(),GetNodeSingle()->GetReturnValue()+1.0f);
		}
		break;
	case OPERATION_DECREMENT_PERFIX:
		{
			ASSERT_LOG_ERROR(GetNodeSingle());
			return Assignment(GetNodeSingle(),GetNodeSingle()->GetReturnValue()-1.0f);
		}
		break;
		//赋值运算符
	case OPERATION_ASSIGNMENT:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			return Assignment(GetNodeLeft(),GetNodeRight()->GetReturnValue());
		}
		break;
	case OPERATION_ADD_ASS:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			return Assignment(GetNodeLeft(),GetNodeLeft()->GetReturnValue() + GetNodeRight()->GetReturnValue());
		}
		break;
	case OPERATION_SUB_ASS:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			return Assignment(GetNodeLeft(),GetNodeLeft()->GetReturnValue() - GetNodeRight()->GetReturnValue());
		}
		break;
	case OPERATION_MUL_ASS:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			return Assignment(GetNodeLeft(),GetNodeLeft()->GetReturnValue() * GetNodeRight()->GetReturnValue());
		}
		break;
	case OPERATION_DIV_ASS:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			return Assignment(GetNodeLeft(),GetNodeLeft()->GetReturnValue() / GetNodeRight()->GetReturnValue());
		}
		break;
	case OPERATION_MOD_ASS:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			int nValue1=0,nValue2=0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(GetNodeLeft()->GetReturnValue(),nValue1));
			ASSERT_LOG_ERROR(ToolFrame::ToValue(GetNodeRight()->GetReturnValue(),nValue2));

			return Assignment(GetNodeLeft(),nValue1 % nValue2);
		}
		break;

		//算术运算符
	case OPERATION_ADD:
		{
			return GetNodeLeft()->GetReturnValue() + GetNodeRight()->GetReturnValue();
		}
		break;
	case OPERATION_SUBTRACT:
		{
			return GetNodeLeft()->GetReturnValue() - GetNodeRight()->GetReturnValue();
		}
	case OPERATION_MULTIPLY:
		{
			return GetNodeLeft()->GetReturnValue() * GetNodeRight()->GetReturnValue();
		}
	case OPERATION_DIVIDE:
		{
			return GetNodeLeft()->GetReturnValue() / GetNodeRight()->GetReturnValue();
		}
	case OPERATION_MODULUS:
		{
			ASSERT_LOG_ERROR(GetNodeLeft());
			ASSERT_LOG_ERROR(GetNodeRight());
			int nValue1=0,nValue2=0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(GetNodeLeft()->GetReturnValue(),nValue1));
			ASSERT_LOG_ERROR(ToolFrame::ToValue(GetNodeRight()->GetReturnValue(),nValue2));

			return nValue1 % nValue2;
		}
		break;

		//逻辑比较符
	case OPERATION_LESS:
		{
			return GetNodeLeft()->GetReturnValue() < GetNodeRight()->GetReturnValue();
		}
		break;
	case OPERATION_LESS_EQUAL:
		{
			return GetNodeLeft()->GetReturnValue() <= GetNodeRight()->GetReturnValue();
		}
		break;
	case OPERATION_GREATER:
		{
			return GetNodeLeft()->GetReturnValue() > GetNodeRight()->GetReturnValue();
		}
		break;
	case OPERATION_GREATER_EQUAL:
		{
			return GetNodeLeft()->GetReturnValue() >= GetNodeRight()->GetReturnValue();
		}
		break;

	case OPERATION_EQUAL:
		{
			return ToolFrame::IsEqual(GetNodeLeft()->GetReturnValue(),GetNodeRight()->GetReturnValue());
		}
		break;
	case OPERATION_NOT_EQUAL:
		{
			return !ToolFrame::IsEqual(GetNodeLeft()->GetReturnValue(),GetNodeRight()->GetReturnValue());
		}
		break;

	case OPERATION_AND:
		{
			return IsTrue(GetNodeLeft()) && IsTrue(GetNodeRight());
		}
		break;
	case OPERATION_OR:
		{
			return IsTrue(GetNodeLeft()) || IsTrue(GetNodeRight());
		}
		break;
	}


	LOG_ERROR();
	return 0;
}

const CEvalOperator* const CEvalOperator::ToOperator() const
{
	return this;
}

CEvalOperator* CEvalOperator::ToOperator()
{
	return this;
}

void CEvalOperator::SetOperation( EOperation eOperation )
{
	ASSERT_LOG_ERROR(GetEval());
	ASSERT_LOG_ERROR(nullptr == _pOperationConfig);

	_pOperationConfig = ToolFrame::GetPtrValueByKey(MEval::Singleton().GetOperationConfig(),(int)eOperation);
	ASSERT_LOG_ERROR(_pOperationConfig);
}

EOperation CEvalOperator::GetOperation() const
{
	ASSERT_LOG_ERROR(_pOperationConfig);
	return _pOperationConfig->GetOperation();
}

EAssociativity CEvalOperator::GetAssociativity() const
{
	ASSERT_LOG_ERROR(GetEval());
	ASSERT_LOG_ERROR(_pOperationConfig);

	const MapIntInt& vPrecedenceAssociativity = MEval::Singleton().GetPriorityAssociativity();
	return (EAssociativity)ToolFrame::GetValueByKey(vPrecedenceAssociativity,_pOperationConfig->GetPrecedence(),(int)ASSOCIATIVITY_LEFT);
}

EAryOperation CEvalOperator::GetAryOperation() const
{
	ASSERT_LOG_ERROR(_pOperationConfig);
	return _pOperationConfig->GetAryOperation();
}

double CEvalOperator::Assignment( IEvalNode* pNode , double fValue ) const
{
	CEvalVariable* pNodeVaribale= nullptr;
	ToolFrame::DynamicCast(pNodeVaribale,pNode);
	ASSERT_LOG_ERROR(pNodeVaribale);

	CRefTypeInfo* pInfo = pNodeVaribale->GetVarRefType();
	ASSERT_LOG_ERROR(pInfo);

	ASSERT_LOG_ERROR(!pInfo->IsConst());
	pInfo->SetValue(fValue);

	return fValue;
}

//CEvalFunction
//////////////////////////////////////////////////////////////////////////
CEvalFunction::CEvalFunction( CEval* pEval )
:CEvalOperator(pEval,OPERATION_FUNCTION_CALL)
{
	SetFunction(nullptr);
}

CEvalFunction::~CEvalFunction()
{
	CEval::Destory(_vNodeArgs);
}

IEvalNode* CEvalFunction::Clone() const
{
	CEvalFunction* pNode = new CEvalFunction(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalFunction::GetReturnValue() const
{
	const CFunTypeInfo* pFunction = GetFunction();
	ASSERT_LOG_ERROR(pFunction);

	switch(_vNodeArgs.size())
	{
	case 0:
		{
			EvalFunction0 fnFunction0 = pFunction->GetFunction0();
			ASSERT_LOG_ERROR(fnFunction0);

			return fnFunction0();
		}
		break;
	case 1:
		{
			EvalFunction1 fnFunction1 = pFunction->GetFunction1();
			ASSERT_LOG_ERROR(fnFunction1);

			return fnFunction1(ToolFrame::GetValueByIndex(_vNodeArgs,0)->GetReturnValue());
		}
		break;
	case 2:
		{
			EvalFunction2 fnFunction2 = pFunction->GetFunction2();
			ASSERT_LOG_ERROR(fnFunction2);

			return fnFunction2(ToolFrame::GetValueByIndex(_vNodeArgs,0)->GetReturnValue(),ToolFrame::GetValueByIndex(_vNodeArgs,1)->GetReturnValue());
		}
		break;
	default:
		{
			LOG_ERROR();
		}
	}
	return 0.0f;
}

bool CEvalFunction::Copy( const CEvalFunction* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->CEvalOperator::Copy(pNode));

	COPY_CFIELD_REF(Function,*pNode);

	//复制参数表
	ASSERT_LOG_ERROR(_vNodeArgs.empty());
	ASSERT_LOG_ERROR(CEval::Clone(_vNodeArgs,pNode->_vNodeArgs));
	return true;
}

void CEvalFunction::SetArgs( ListEvalNode& vNodeArgs )
{
	ASSERT_LOG_ERROR(_vNodeArgs.empty());
	ASSERT_LOG_ERROR(CEval::Clone(_vNodeArgs,vNodeArgs));
}

//////////////////////////////////////////////////////////////////////////
CEvalDeclareVariable::CEvalDeclareVariable( CEval* pEval )
:IEvalNode(pEval)
{

}

CEvalDeclareVariable::~CEvalDeclareVariable()
{

}

bool CEvalDeclareVariable::Copy( const CEvalDeclareVariable* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	COPY_CFIELD_REF(VarType,*pNode);

	VectorVar::const_iterator itr;
	foreach(itr,pNode->GetVars()){
		const PairVar& pair = *itr;

		const std::string& sVarName=pair.first;
		const IEvalNode* pNodeSrc = pair.second;
		IEvalNode* pNode = nullptr;
		if (pNodeSrc)
		{
			pNode = pNodeSrc->Clone();
			ASSERT_LOG_ERROR(pNode);
		}

		InsertVar(sVarName,pNode);
	}

	return true;
}

IEvalNode* CEvalDeclareVariable::Clone() const
{
	CEvalDeclareVariable* pNode = new CEvalDeclareVariable(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalDeclareVariable::GetReturnValue() const
{
	CScopeInfo* pScope = GetScope();
	ASSERT_LOG_ERROR(pScope);

	double fInit = 0.0f;

	VectorVar::const_iterator itr;
	foreach(itr,GetVars()){
		const PairVar& pair = *itr;

		const std::string& sVarName=pair.first;
		const IEvalNode* pNode = pair.second;

		fInit = pNode ? pNode->GetReturnValue() : 0.0f;

		ASSERT_LOG_ERROR(pScope->DeclareVar(GetVarType(),sVarName,fInit));
	}

	return fInit;
}

bool CEvalDeclareVariable::InsertVar( const std::string& sVarName,IEvalNode* pNode )
{
	GetVars().push_back(std::make_pair(sVarName,pNode));
	return true;
}

//空节点
//////////////////////////////////////////////////////////////////////////
CEvalNone::CEvalNone( CEval* pEval )
:IEvalNode(pEval)
{

}

CEvalNone::~CEvalNone()
{

}

IEvalNode* CEvalNone::Clone() const
{
	CEvalNone* pNode = new CEvalNone(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalNone::GetReturnValue() const
{
	return 0.0f;
}

bool CEvalNone::Copy( const CEvalNone* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	return true;
}

//数字节点
//////////////////////////////////////////////////////////////////////////
CEvalNumber::CEvalNumber( CEval* pEval )
:IEvalNode(pEval)
{
	SetValue(0.0f);
}

CEvalNumber::~CEvalNumber()
{

}

IEvalNode* CEvalNumber::Clone() const
{
	CEvalNumber* pNode = new CEvalNumber(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalNumber::GetReturnValue() const
{
	return GetValue();
}

bool CEvalNumber::Copy( const CEvalNumber* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));
	COPY_CFIELD_REF(Value,*pNode);

	return true;
}

//变量节点
//////////////////////////////////////////////////////////////////////////
CEvalVariable::CEvalVariable( CEval* pEval )
:IEvalNode(pEval)
{

}

CEvalVariable::~CEvalVariable()
{

}

IEvalNode* CEvalVariable::Clone() const
{
	CEvalVariable* pNode = new CEvalVariable(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalVariable::GetReturnValue() const
{
	const CRefTypeInfo* pInfo = GetVarRefType();
	ASSERT_LOG_ERROR(pInfo);
	return pInfo->GetValue();
}

bool CEvalVariable::Copy( const CEvalVariable* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));
	_sVarName	= pNode->_sVarName;

	return true;
}

bool CEvalVariable::SetVarName( const std::string& sVarName )
{
	ASSERT_LOG_ERROR(!sVarName.empty());
	ASSERT_LOG_ERROR(_sVarName.empty());
	_sVarName = sVarName;
	return true;
}

CRefTypeInfo* CEvalVariable::GetVarRefType() const
{
	CScopeInfo* pScope = GetScope();
	ASSERT_LOG_ERROR(pScope);

	return pScope->GetVar(_sVarName);
}

//语句节点
//////////////////////////////////////////////////////////////////////////
CEvalSegment::CEvalSegment( CEval* pEval )
:IEvalNode(pEval)
{

}

CEvalSegment::~CEvalSegment()
{
	CEval::Destory(_vNode);
}

IEvalNode* CEvalSegment::Clone() const
{
	CEvalSegment* pNode = new CEvalSegment(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalSegment::GetReturnValue() const
{
	double fResult = 0.0f;
	if (_vNode.empty())return false;
	ListEvalNode::const_iterator itr;
	foreach(itr,_vNode){
		const IEvalNode* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);

		fResult = pNode->GetReturnValue();
	}

	return fResult;
}

bool CEvalSegment::Copy( const CEvalSegment* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	ASSERT_LOG_ERROR(CEval::Clone(_vNode,pNode->_vNode));
	return true;
}

bool CEvalSegment::SetNode( ListEvalNode& vNode )
{
	ASSERT_LOG_ERROR(_vNode.empty());
	if (!_vNode.empty())return false;
	ASSERT_LOG_ERROR(CEval::Clone(_vNode,vNode));
	return true;
}

//If Else语句
//////////////////////////////////////////////////////////////////////////
CEvalIfElse::CEvalIfElse( CEval* pEval )
:IEvalNode(pEval)
{
	_pNodeExp = nullptr;
	_pNodeTrue= nullptr;
	_pNodeFalse=nullptr;
}

CEvalIfElse::~CEvalIfElse()
{
	CEval::Destory(_pNodeExp);
	CEval::Destory(_pNodeTrue);
	CEval::Destory(_pNodeFalse);
}

void CEvalIfElse::SetNode( IEvalNode* pNodeExp,IEvalNode* pNodeTrue,IEvalNode* pNodeFalse )
{
	ASSERT_LOG_ERROR(pNodeExp && pNodeTrue);

	ASSERT_LOG_ERROR(!_pNodeExp);
	_pNodeExp = pNodeExp->Clone();

	ASSERT_LOG_ERROR(!_pNodeTrue);
	_pNodeTrue = pNodeTrue->Clone();

	ASSERT_LOG_ERROR(!_pNodeFalse);
	if (pNodeFalse)
		_pNodeFalse = pNodeFalse->Clone();
}

IEvalNode* CEvalIfElse::Clone() const
{
	CEvalIfElse* pNode = new CEvalIfElse(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalIfElse::GetReturnValue() const
{
	ASSERT_LOG_ERROR(_pNodeExp && _pNodeTrue);
	if (IsTrue(_pNodeExp))
	{
		return _pNodeTrue->GetReturnValue();
	}else{
		if (!_pNodeFalse)return 0.0f;

		return _pNodeFalse->GetReturnValue();
	}

	LOG_ERROR();
	return 0.0f;
}

bool CEvalIfElse::Copy( const CEvalIfElse* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	ASSERT_LOG_ERROR(!_pNodeExp && !_pNodeTrue && !_pNodeFalse);
	if (pNode->_pNodeExp)_pNodeExp		= pNode->_pNodeExp->Clone();
	if (pNode->_pNodeTrue)_pNodeTrue	= pNode->_pNodeTrue->Clone();
	if (pNode->_pNodeFalse)_pNodeFalse	= pNode->_pNodeFalse->Clone();

	return true;
}

//多语句节点
//////////////////////////////////////////////////////////////////////////
CEvalBrace::CEvalBrace( CEval* pEval )
:IEvalNode(pEval)
{

}

CEvalBrace::~CEvalBrace()
{
	CEval::Destory(_vNode);
}

bool CEvalBrace::SetNode( ListEvalNode& vNode,const std::string& sScopeName )
{
	ASSERT_LOG_ERROR(!sScopeName.empty());
	ASSERT_LOG_ERROR(_vNode.empty());
	ASSERT_LOG_ERROR(CEval::Clone(_vNode,vNode));
	_sScopeName = sScopeName;
	return true;
}

IEvalNode* CEvalBrace::Clone() const
{
	CEvalBrace* pNode = new CEvalBrace(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalBrace::GetReturnValue() const
{
	ASSERT_LOG_ERROR(!_sScopeName.empty());

	CScopeInfo* pScope = GetScope();
	ASSERT_LOG_ERROR(pScope);
	ASSERT_LOG_ERROR(pScope->DeclareScope(_sScopeName));

	double fResult = 0.0f;
	if (_vNode.empty())return false;
	ListEvalNode::const_iterator itr;
	foreach(itr,_vNode){
		const IEvalNode* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);

		fResult = pNode->GetReturnValue();
	}

	pScope->UndeclareScope(_sScopeName);

	return fResult;
}

bool CEvalBrace::Copy( const CEvalBrace* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	ASSERT_LOG_ERROR(CEval::Clone(_vNode,pNode->_vNode));
	_sScopeName = pNode->_sScopeName;
	return true;
}

//////////////////////////////////////////////////////////////////////////
CEvalFor::CEvalFor( CEval* pEval )
:IEvalNode(pEval)
{
	_pNodeExp1	= nullptr;
	_pNodeExp2	= nullptr;
	_pNodeExp3	= nullptr;
	_pNodeLoop= nullptr;
}

CEvalFor::~CEvalFor()
{
	CEval::Destory(_pNodeExp1);
	CEval::Destory(_pNodeExp2);
	CEval::Destory(_pNodeExp3);
	CEval::Destory(_pNodeLoop);
}

bool CEvalFor::SetNode( const std::string& sNewScopeName,IEvalNode* pNodeExp1,IEvalNode* pNodeExp2,IEvalNode* pNodeExp3,IEvalNode* pNodeLoop )
{
	ASSERT_LOG_ERROR(!sNewScopeName.empty() && pNodeExp1 && pNodeExp2 && pNodeExp3 && pNodeLoop);
	ASSERT_LOG_ERROR(_sNewScopeName.empty() && !_pNodeExp1 && !_pNodeExp2 && !_pNodeExp3 && !_pNodeLoop);

	_sNewScopeName = sNewScopeName;

	_pNodeExp1	= pNodeExp1->Clone();
	_pNodeExp2	= pNodeExp2->Clone();
	_pNodeExp3	= pNodeExp3->Clone();
	_pNodeLoop	= pNodeLoop->Clone();

	return true;
}

IEvalNode* CEvalFor::Clone() const
{
	CEvalFor* pNode = new CEvalFor(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalFor::GetReturnValue() const
{
	ASSERT_LOG_ERROR(!_sNewScopeName.empty() && _pNodeExp1 && _pNodeExp2 && _pNodeExp3 && _pNodeLoop);
	CScopeInfo* pScope = GetScope();
	ASSERT_LOG_ERROR(pScope);
	ASSERT_LOG_ERROR(pScope->DeclareScope(_sNewScopeName));

	CScopeInfo* pExpScope = pScope->GetScope(_sNewScopeName);
	ASSERT_LOG_ERROR(pExpScope);

	for (_pNodeExp1->GetReturnValue();IsExpTrue(_pNodeExp2);_pNodeExp3->GetReturnValue())
	{
		pExpScope->DeclareScope(_sNewScopeName);
		_pNodeLoop->GetReturnValue();
		pExpScope->UndeclareScope(_sNewScopeName);

	}

	pScope->UndeclareScope(_sNewScopeName);

	return 0.0f;
}

bool CEvalFor::Copy( const CEvalFor* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	if (pNode->_pNodeExp1)
		_pNodeExp1 = pNode->_pNodeExp1->Clone();
	if (pNode->_pNodeExp2)
		_pNodeExp2 = pNode->_pNodeExp2->Clone();
	if (pNode->_pNodeExp3)
		_pNodeExp3 = pNode->_pNodeExp3->Clone();
	if (pNode->_pNodeLoop)
		_pNodeLoop = pNode->_pNodeLoop->Clone();

	_sNewScopeName = pNode->_sNewScopeName;
	return true;
}

bool CEvalFor::IsExpTrue( IEvalNode* pNode )const
{
	ASSERT_LOG_ERROR(pNode);

	CEvalNone* pNodeNone=nullptr;
	ToolFrame::DynamicCast(pNodeNone,pNode);
	if (pNodeNone)return true; //如果没填 为真


	return IEvalNode::IsTrue(pNode);
}

//do..while..语句
//////////////////////////////////////////////////////////////////////////
CEvalDoWhile::CEvalDoWhile( CEval* pEval )
:IEvalNode(pEval)
{
	_pNodeExp = nullptr;
	_pNodeLoop= nullptr;
}

CEvalDoWhile::~CEvalDoWhile()
{
	CEval::Destory(_pNodeExp);
	CEval::Destory(_pNodeLoop);
}

bool CEvalDoWhile::SetNode( const std::string& sNewScopeName,IEvalNode* pNodeExp,IEvalNode* pNodeLoop )
{
	ASSERT_LOG_ERROR(!sNewScopeName.empty() && pNodeExp && pNodeLoop);
	ASSERT_LOG_ERROR(!_pNodeExp && !_pNodeLoop);
	_pNodeExp  = pNodeExp->Clone();
	_pNodeLoop = pNodeLoop->Clone();
	_sNewScopeName = sNewScopeName;
	return true;
}

bool CEvalDoWhile::Copy( const CEvalDoWhile* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	if (pNode->_pNodeExp)
		_pNodeExp = pNode->_pNodeExp->Clone();
	if (pNode->_pNodeLoop)
		_pNodeLoop = pNode->_pNodeLoop->Clone();

	_sNewScopeName = pNode->_sNewScopeName;

	return true;
}

IEvalNode* CEvalDoWhile::Clone() const
{
	CEvalDoWhile* pNode = new CEvalDoWhile(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalDoWhile::GetReturnValue() const
{
	ASSERT_LOG_ERROR(_pNodeExp && _pNodeLoop);
 	CScopeInfo* pScope = GetScope();
 	ASSERT_LOG_ERROR(pScope);
 
 	do 
 	{
 		pScope->DeclareScope(_sNewScopeName);
 		_pNodeLoop->GetReturnValue();
 		pScope->UndeclareScope(_sNewScopeName);
 	} while (IsTrue(_pNodeExp));
 
	return 0.0f;
}

//while语句
//////////////////////////////////////////////////////////////////////////
CEvalWhile::CEvalWhile( CEval* pEval )
:IEvalNode(pEval)
{
	_pNodeExp = nullptr;
	_pNodeLoop = nullptr;
}

CEvalWhile::~CEvalWhile()
{
	CEval::Destory(_pNodeExp);
	CEval::Destory(_pNodeLoop);
}

bool CEvalWhile::SetNode( const std::string& sNewScopeName,IEvalNode* pNodeExp,IEvalNode* pNodeLoop )
{
	ASSERT_LOG_ERROR(pNodeExp && pNodeLoop);
	ASSERT_LOG_ERROR(!_pNodeExp && !_pNodeLoop);
	_pNodeExp  = pNodeExp->Clone();
	_pNodeLoop = pNodeLoop->Clone();
	_sNewScopeName = sNewScopeName;
	return true;
}

bool CEvalWhile::Copy( const CEvalWhile* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	if (pNode->_pNodeExp)
		_pNodeExp = pNode->_pNodeExp->Clone();
	if (pNode->_pNodeLoop)
		_pNodeLoop = pNode->_pNodeLoop->Clone();

	_sNewScopeName = pNode->_sNewScopeName;

	return true;
}

IEvalNode* CEvalWhile::Clone() const
{
	CEvalWhile* pNode = new CEvalWhile(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalWhile::GetReturnValue() const
{
	ASSERT_LOG_ERROR(_pNodeExp && _pNodeLoop);

	CScopeInfo* pScope = GetScope();
	ASSERT_LOG_ERROR(pScope);
	ASSERT_LOG_ERROR(pScope->DeclareScope(_sNewScopeName));
	CScopeInfo* pExpScope = pScope->GetScope(_sNewScopeName);
	ASSERT_LOG_ERROR(pExpScope);

	while (IsTrue(_pNodeExp)){
		pExpScope->DeclareScope(_sNewScopeName);
		_pNodeLoop->GetReturnValue();
		pExpScope->UndeclareScope(_sNewScopeName);
	}

	pScope->UndeclareScope(_sNewScopeName);

	return 0.0f;
}

//? : 
//////////////////////////////////////////////////////////////////////////
CEvalTernary::CEvalTernary( CEval* pEval )
:CEvalOperator(pEval,OPERATION_TERNARY_CONDITIONAL)
{
	SetIsBegin(false);
	SetNodeExp(nullptr);
	SetNodeTrue(nullptr);
	SetNodeFalse(nullptr);
}

CEvalTernary::~CEvalTernary()
{
	CEval::Destory(GetNodeExp());
	CEval::Destory(GetNodeTrue());
	CEval::Destory(GetNodeFalse());
}

IEvalNode* CEvalTernary::Clone() const
{
	CEvalTernary* pNode = new CEvalTernary(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalTernary::GetReturnValue() const
{
	ASSERT_LOG_ERROR(GetNodeExp() && GetNodeTrue() && GetNodeFalse());

	return IsTrue(GetNodeExp()) ? GetNodeTrue()->GetReturnValue() : GetNodeFalse()->GetReturnValue();
}

bool CEvalTernary::Copy( const CEvalTernary* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->CEvalOperator::Copy(pNode));

	SetIsBegin(pNode->IsIsBegin());

	if (pNode->GetNodeExp())
		SetNodeExp(pNode->GetNodeExp()->Clone());

	if (pNode->GetNodeTrue())
		SetNodeTrue(pNode->GetNodeTrue()->Clone());

	if (pNode->GetNodeFalse())
		SetNodeFalse(pNode->GetNodeFalse()->Clone());

	return true;
}

//break
//////////////////////////////////////////////////////////////////////////
CEvalbreak::CEvalbreak( CEval* pEval )
:IEvalNode(pEval)
{

}

CEvalbreak::~CEvalbreak()
{

}

IEvalNode* CEvalbreak::Clone() const
{
	CEvalbreak* pNode = new CEvalbreak(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

double CEvalbreak::GetReturnValue() const
{
	return 1.0f;
}

bool CEvalbreak::Copy( const CEvalbreak* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	return true;
}

//switch
//////////////////////////////////////////////////////////////////////////
CEvalSwitch::CEvalSwitch( CEval* pEval )
:IEvalNode(pEval)
{
	_pNodeExp = nullptr;
}

CEvalSwitch::~CEvalSwitch()
{
	Destory(_vCaseSentence);
	CEval::Destory(_vSetenceDefault);
}

IEvalNode* CEvalSwitch::Clone() const
{
	CEvalSwitch* pNode = new CEvalSwitch(GetEval());
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(pNode->Copy(this));

	return pNode;
}

bool CEvalSwitch::Clone( ListCaseSetence& vDes,const ListCaseSetence& vSrc )
{
	ASSERT_LOG_ERROR(vDes.empty());
	ListCaseSetence::const_iterator itr;
	foreach(itr,vSrc){
		const PairCaseSetence& pair = *itr;
		const IEvalNode*	pCase = pair.first;
		const ListEvalNode&	vNode = pair.second;
		ASSERT_LOG_ERROR(pCase);

		IEvalNode* pCaseClone = pCase->Clone();
		ASSERT_LOG_ERROR(pCaseClone);
		ListEvalNode vNodeClone;
		CEval::Clone(vNodeClone,vNode);
		ToolFrame::PushBack(vDes,std::make_pair(pCaseClone,vNodeClone));
	}
	return true;
}

double CEvalSwitch::GetReturnValue() const
{
	ASSERT_LOG_ERROR(_pNodeExp && !_vCaseSentence.empty());

	//case
	ListCaseSetence::const_iterator itr = ToolFrame::GetItrBegin(_vCaseSentence,FindCase,_pNodeExp->GetReturnValue());
	while(itr != _vCaseSentence.end()){
		RunSentence(itr->second);
		++itr;
	}
	
	//default
	RunSentence(_vSetenceDefault);
	return 1.0f;
}

bool CEvalSwitch::Copy( const CEvalSwitch* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(this->IEvalNode::Copy(pNode));

	ASSERT_LOG_ERROR(pNode->_pNodeExp);
	ASSERT_LOG_ERROR(!_pNodeExp && _vCaseSentence.empty() && _vSetenceDefault.empty());

	_pNodeExp  = pNode->_pNodeExp->Clone();
	ASSERT_LOG_ERROR(Clone(_vCaseSentence,pNode->_vCaseSentence));
	ASSERT_LOG_ERROR(CEval::Clone(_vSetenceDefault,pNode->_vSetenceDefault));

	return true;
}

bool CEvalSwitch::SetNode( IEvalNode* pExp,const ListCaseSetence& vCaseSentence,ListEvalNode& vDefault )
{
	ASSERT_LOG_ERROR(pExp && !vCaseSentence.empty());
	ASSERT_LOG_ERROR(!_pNodeExp && _vCaseSentence.empty() && _vSetenceDefault.empty());

	_pNodeExp  = pExp->Clone();
	ASSERT_LOG_ERROR(Clone(_vCaseSentence,vCaseSentence));
	ASSERT_LOG_ERROR(CEval::Clone(_vSetenceDefault,vDefault));

	return true;
}

bool CEvalSwitch::Destory( ListCaseSetence& vCase )
{
	ListCaseSetence::iterator itr;
	foreach(itr,vCase){
		PairCaseSetence& pair = *itr;
		IEvalNode*	pCase = pair.first;
		ListEvalNode&	vNode = pair.second;

		CEval::Destory(pCase);
		CEval::Destory(vNode);
	}
	vCase.clear();
	return true;
}

bool CEvalSwitch::FindCase( ListCaseSetence::const_iterator& itr,const double& fCase)
{
	const PairCaseSetence& pair = *itr;
	const IEvalNode*	pCase = pair.first;
	const ListEvalNode&	vNode = pair.second;
	ASSERT_LOG_ERROR(pCase);

	return ToolFrame::IsEqual(fCase,pCase->GetReturnValue());
}

bool CEvalSwitch::RunSentence( const ListEvalNode& vSentence )const
{
	if (vSentence.empty())return true;

	ListEvalNode::const_iterator itr;
	foreach(itr,vSentence){
		const IEvalNode* pSetence = *itr;
		ASSERT_LOG_ERROR(pSetence);
		pSetence->GetReturnValue();	
	}
	return true;
}

NS_TOOL_FRAME_END
