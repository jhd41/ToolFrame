#include "IEvalParser.h"
#include "MLoger.h"
#include "EvalNode.h"
#include "Eval.h"
#include "MEval.h"

NS_TOOL_FRAME_BEGIN

bool InitEvalParser(){return true;}//�����ƹ���������ȫ���ӵ�ִ�д��� 

//����������
//////////////////////////////////////////////////////////////////////////
CEvalActiveCreator::CEvalActiveCreator( const std::string& sActive,FnCreateFunParser fnCreator )
{
	SetCreator(fnCreator);
}

bool CEvalActiveCreator::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCall ) const
{
	ASSERT_LOG_ERROR(!sActive.empty() && pCall);

	FnCreateFunParser fnCreator = GetCreator();
	ASSERT_LOG_ERROR(fnCreator);

	IEvalParser* pParser = fnCreator(pCall);
	ASSERT_LOG_ERROR(pParser);

	ASSERT_LOG_ERROR(pParser->Init());
	ASSERT_LOG_ERROR(pParser->OnActive(sActive,nSrc,pParser));
	
	ToolFrame::Delete(pParser);
	return true;
}

CEvalActiveCallBack::CEvalActiveCallBack( const std::string& sActive,IEvalParser* pCallBack )
{
	SetCallBack(pCallBack);
}

bool CEvalActiveCallBack::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCall ) const
{
	IEvalParser* pCallBack = GetCallBack();
	ASSERT_LOG_ERROR(pCallBack);

	ASSERT_LOG_ERROR(pCallBack->OnActive(sActive,nSrc,pCall));
	return true;
}

IEvalParser::IEvalParser()
{
	SetParent(nullptr);
	SetEval(nullptr);
	SetScopeInfo(nullptr);
}

IEvalParser::IEvalParser(IEvalParser* pParent)
{
	ASSERT_LOG_ERROR(pParent);
	ASSERT_LOG_ERROR(pParent->GetEval());
	ASSERT_LOG_ERROR(pParent->GetScopeInfo());
	SetParent(pParent);
	SetEval(pParent->GetEval());
	SetScopeInfo(pParent->GetScopeInfo());
}

IEvalParser::~IEvalParser(void)
{
	UnRegistParser();
}

bool IEvalParser::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	LOG_ERROR();
	return false;
}

bool IEvalParser::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);
	ASSERT_LOG_ERROR(pCallBack);
	return false;
}

bool IEvalParser::Parse( const size_t nSrc )
{
	return false;
}

bool IEvalParser::RegistParser( const std::string& sActive,IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(!sActive.empty() && pParser);
	
	IEvalActiveNode* pActiveNode = new CEvalActiveCallBack(sActive,pParser);
	ASSERT_LOG_ERROR(pActiveNode);

	MapActiveNode& vParsers = ToolFrame::GetValueByKeyForce(_vActive,sActive.size());
	return ToolFrame::Insert(vParsers,sActive,pActiveNode);
}

bool IEvalParser::RegistParser( const std::string& sActive,FnCreateFunParser fnCreator )
{
	ASSERT_LOG_ERROR(!sActive.empty() && fnCreator);

	IEvalActiveNode* pActiveNode = new CEvalActiveCreator(sActive,fnCreator);
	ASSERT_LOG_ERROR(pActiveNode);

	MapActiveNode& vParsers = ToolFrame::GetValueByKeyForce(_vActive,sActive.size());
	return ToolFrame::Insert(vParsers,sActive,pActiveNode);
}

bool IEvalParser::UnRegistParser()
{
	if (_vActive.empty())return true;
	
	MapActiveParsers::iterator itrActive;
	foreach(itrActive,_vActive){
		MapActiveNode::iterator itrNode;
		MapActiveNode& vActive = itrActive->second;
		foreach(itrNode,vActive){
			IEvalActiveNode*& pActiveNode = itrNode->second;
			ASSERT_LOG_ERROR(pActiveNode);

			ToolFrame::Delete(pActiveNode);
		}
	}
	_vActive.clear();
	return true;
}

bool IEvalParser::ActiveParser( MapActiveNode& vActive,size_t nDes )
{
	bool bActived= false;
	MapActiveNode::const_iterator itr;
	foreach(itr,vActive){
		const std::string&		sActive	=		itr->first;
		const IEvalActiveNode*	pActiveNode=	itr->second;
		ASSERT_LOG_ERROR(pActiveNode);

		if (ToolFrame::IsBeginWith(GetEval()->GetExp(),sActive,nDes))
		{
			ASSERT_LOG_ERROR(pActiveNode->OnActive(sActive,nDes,this));
			bActived = true;

			if (GetEval()->IsError())
				break;
		}
	}

	return bActived;
}

bool IEvalParser::ParseActive(const size_t nSrc )
{
	//���ȳ��Խ�����ȷ�ء������ȷ�Ľ������� ��ô ֱ�Ӳ�ȥ���� ����ġ����Ƿ���C++����ġ�
	//��ν�ľ�ȷ�� ����ָ �ֶ�ġ�
	MapActiveParsers::reverse_iterator itr;
	foreachR(itr,_vActive){
 		if (ActiveParser(itr->second,nSrc))
			return true;
	}

	return false;
}

bool IEvalParser::ParseActive( const std::string& sActive,const size_t nSrc )
{
	MapActiveNode* pvActiveNode = ToolFrame::GetValuePtrByKey(_vActive,sActive.length());
	if (!pvActiveNode)return false;

	typedef std::pair<MapActiveNode::iterator,MapActiveNode::iterator> PairItrItr;
	PairItrItr pair = ToolFrame::EqualRange(*pvActiveNode,sActive);
	if (ToolFrame::IsEnd(pair))return false;
	
	MapActiveNode::const_iterator itr;
	foreachPair(itr,pair){
		const std::string&		sActiveCur	=	itr->first;
		const IEvalActiveNode*	pActiveNode =	itr->second;
		ASSERT_LOG_ERROR(pActiveNode);

		ASSERT_LOG_DEBUG_ERR(sActive == sActiveCur);

		ASSERT_LOG_ERROR(pActiveNode->OnActive(sActive,nSrc,this));
		
		if (GetEval()->IsError())return true;
	}

	return true;
}

bool IEvalParser::Init()
{
	return true;
}

CScopeInfo* IEvalParser::EnterNewScope(const std::string& sNewScopeName)
{
	ASSERT_LOG_ERROR(GetEval());
	ASSERT_LOG_ERROR(GetScopeInfo()->DeclareScope(sNewScopeName));
	CScopeInfo* pScope = GetScopeInfo()->GetScope(sNewScopeName);
	ASSERT_LOG_ERROR(pScope);
	this->SetScopeInfo(pScope);
	return pScope;
}

bool IEvalParser::LeaveNewScope( CScopeInfo* pScope )
{
	ASSERT_LOG_ERROR(pScope);
	this->SetScopeInfo(pScope->GetParent());
	ASSERT_LOG_ERROR(GetScopeInfo()->UndeclareScope(pScope->GetName()));
	return true;
}

//���ֽ�����
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserNumber);
CEvalParserNumber::CEvalParserNumber( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserNumber::~CEvalParserNumber( void )
{

}

bool CEvalParserNumber::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	ASSERT_LOG_ERROR(pParser->RegistParser("0",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("1",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("2",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("3",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("4",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("5",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("6",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("7",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("8",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser("9",CREATE_FUN_NAME));

	return true;
}

size_t CEvalParserNumber::FindNumberEnd( const std::string& sSrc,size_t uOffset )
{
	for (size_t uIndex = uOffset ;uIndex< sSrc.size();++uIndex)
	{
		char ch = sSrc.at(uIndex);
		if ( !((ch>='0' && ch <='9')|| (ch>='A' && ch<='F')||(ch>='a' && ch<='b') || (ch == '.')||(ch == 'x')||(ch == 'X')||(ch == 'o')||(ch == 'O')))
			return uIndex;
	}

	return std::string::npos;
}

bool CEvalParserNumber::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(GetEval());

	size_t uOffSet = FindNumberEnd(GetEval()->GetExp(),nSrc);
	size_t uEnd = std::string::npos == uOffSet ? GetEval()->GetExp().length() : uOffSet;
	std::string sNumber =  GetEval()->GetExp().substr(nSrc,uEnd - nSrc);

	double fData = 0.0f;
	if (!ToolFrame::ToValue(sNumber,fData))return false;

	CEvalNumber node(GetEval());

	node.SetValue(fData);

	ASSERT_LOG_ERROR(GetParent());
	ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sNumber.length(),this));

	return true;
}

//True False������
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserTrueFalse);
CEvalParserTrueFalse::CEvalParserTrueFalse( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserTrueFalse::~CEvalParserTrueFalse( void )
{

}

bool CEvalParserTrueFalse::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);
	pParser->RegistParser("true",CREATE_FUN_NAME);
	pParser->RegistParser("false",CREATE_FUN_NAME);
	return true;
}

bool CEvalParserTrueFalse::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == "true")
	{
		CEvalNumber node(GetEval());

		node.SetValue(1.0f);

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sActive.length(),this));
		return true;
	}
	if (sActive == "false")
	{
		CEvalNumber node(GetEval());

		node.SetValue(0.0f);

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sActive.length(),this));
		return true;
	}

	return false;
}

//�򵥶�Ӧ�����(+ - * / % && ||...)
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(IEvalParserSimple);
IEvalParserSimple::MapStringOperation IEvalParserSimple::_vParser;
IEvalParserSimple::IEvalParserSimple( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

IEvalParserSimple::~IEvalParserSimple( void )
{

}
bool IEvalParserSimple::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	//��ʼ����������Ӧ��
	static bool bInitParser = InitParserOperation();//ֻ��Ҫ��ʼ��һ��
	
	std::string sActive;
	MapStringOperation::const_iterator itr;
	foreach(itr,_vParser){
		const std::string& sActiveCur = itr->first;
		if (sActiveCur != sActive)
		{
			pParser->RegistParser(sActiveCur,CREATE_FUN_NAME);

			sActive = sActiveCur;
		}
	}

	return true;
}

bool IEvalParserSimple::InitParserOperation()
{
	//���������
	ASSERT_LOG_ERROR(InitParserOperation("+",	OPERATION_ADD));
	ASSERT_LOG_ERROR(InitParserOperation("-",	OPERATION_SUBTRACT));
	ASSERT_LOG_ERROR(InitParserOperation("*",	OPERATION_MULTIPLY));
	ASSERT_LOG_ERROR(InitParserOperation("/",	OPERATION_DIVIDE));
	ASSERT_LOG_ERROR(InitParserOperation("%",	OPERATION_MODULUS));

	//�Ƚ������
	ASSERT_LOG_ERROR(InitParserOperation("<",	OPERATION_LESS));
	ASSERT_LOG_ERROR(InitParserOperation("<=",	OPERATION_LESS_EQUAL));
	ASSERT_LOG_ERROR(InitParserOperation(">",	OPERATION_GREATER));
	ASSERT_LOG_ERROR(InitParserOperation(">=",	OPERATION_GREATER_EQUAL));
	ASSERT_LOG_ERROR(InitParserOperation("==",	OPERATION_EQUAL));
	ASSERT_LOG_ERROR(InitParserOperation("!=",	OPERATION_NOT_EQUAL));

	//�߼������
	ASSERT_LOG_ERROR(InitParserOperation("!",	OPERATION_INVERTER));
	ASSERT_LOG_ERROR(InitParserOperation("&&",	OPERATION_AND));
	ASSERT_LOG_ERROR(InitParserOperation("||",	OPERATION_OR));

	//��ֵ�����
	ASSERT_LOG_ERROR(InitParserOperation("=",	OPERATION_ASSIGNMENT));
	ASSERT_LOG_ERROR(InitParserOperation("+=",	OPERATION_ADD_ASS));
	ASSERT_LOG_ERROR(InitParserOperation("-=",	OPERATION_SUB_ASS));
	ASSERT_LOG_ERROR(InitParserOperation("*=",	OPERATION_MUL_ASS));
	ASSERT_LOG_ERROR(InitParserOperation("/=",	OPERATION_DIV_ASS));
	ASSERT_LOG_ERROR(InitParserOperation("%=",	OPERATION_MOD_ASS));

	//�����Լ�
	ASSERT_LOG_ERROR(InitParserOperation("++",	OPERATION_INCREMENT_SUFFIX));
	ASSERT_LOG_ERROR(InitParserOperation("--",	OPERATION_DECREMENT_SUFFIX));
	ASSERT_LOG_ERROR(InitParserOperation("++",	OPERATION_INCREMENT_PERFIX));
	ASSERT_LOG_ERROR(InitParserOperation("--",	OPERATION_DECREMENT_PERFIX));

	//���� ��
	ASSERT_LOG_ERROR(InitParserOperation("+",	OPERATION_POSITIVE));
	ASSERT_LOG_ERROR(InitParserOperation("-",	OPERATION_NEGATIVE));

	//����
	ASSERT_LOG_ERROR(InitParserOperation(",",	OPERATION_COMMA));
	return true;
}

bool IEvalParserSimple::InitParserOperation(const std::string& sParser,EOperation eOperation )
{
	return ToolFrame::Insert(_vParser,sParser,eOperation);
}

bool IEvalParserSimple::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	typedef std::pair<MapStringOperation::const_iterator,MapStringOperation::const_iterator>	PairConstItrConstItr;
	PairConstItrConstItr pair =	ToolFrame::EqualRange(_vParser,sActive);
	ASSERT_LOG_ERROR(!ToolFrame::IsEnd(pair));

	MapStringOperation::const_iterator itr;
	foreachPair(itr,pair){
		EOperation eOperation = itr->second;

		ASSERT_LOG_ERROR(OPERATION_INVAILD != eOperation);

		CEvalOperator node(GetEval(),eOperation);

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sActive.length(),this));
	}

	return true;
}

//Բ���Ž�����
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserParentheses);

CEvalParserParentheses::CEvalParserParentheses( IEvalParser* pParent)
:IEvalParser(pParent)
{

}

CEvalParserParentheses::~CEvalParserParentheses( void )
{

}

bool CEvalParserParentheses::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	ASSERT_LOG_ERROR(pParser->RegistParser("(",CREATE_FUN_NAME));
	return true;
}

bool CEvalParserParentheses::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == "(")
	{
		CEvalParserExpression expression(this);
		ASSERT_LOG_ERROR(expression.Init());
		expression.RegistParser(")",this);

		expression.Parse(nSrc + sActive.length());

		return true;
	}
	if (sActive == ")")
	{
		CEvalParserExpression* pExpressionSub = nullptr;
		ToolFrame::DynamicCast(pExpressionSub,pCallBack);
		ASSERT_LOG_ERROR(pExpressionSub);

		IEvalNode* pNode = pExpressionSub->TryGetResult();
		if (!pNode)return true;

		CEvalOperator nodeParenTheses(GetEval(),OPERATION_PARENTHESES);

		nodeParenTheses.SetNodeSingle(pNode);

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&nodeParenTheses,nSrc + sActive.length(),this));

		nodeParenTheses.SetNodeSingle(nullptr);
		CEval::Destory(pNode);
		return true;
	}

	return false;
}

bool CEvalParserParentheses::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	return true;
}

//? :
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserTernary);
CEvalParserTernary::CEvalParserTernary( IEvalParser* pParent )
:IEvalParser(pParent)
{
}

CEvalParserTernary::~CEvalParserTernary( void )
{

}

bool CEvalParserTernary::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	ASSERT_LOG_ERROR(pParser->RegistParser("?",CREATE_FUN_NAME));
	ASSERT_LOG_ERROR(pParser->RegistParser(":",CREATE_FUN_NAME));
	return true;
}

bool CEvalParserTernary::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == "?")
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,GetParent());
		ASSERT_LOG_ERROR(pExpression);

		if (pExpression->GetParsingNode().empty())return true;

		CEvalTernary node(GetEval());
		node.SetIsBegin(true);
		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sActive.length(),this));

		return true;
	}
	if (sActive == ":")
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,GetParent());
		ASSERT_LOG_ERROR(pExpression);

		if (pExpression->GetParsingNode().empty())return true;

		if (!IsHasBegin(pExpression->GetParsingNode()))return true;

		CEvalTernary node(GetEval());
		node.SetIsBegin(false);
		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sActive.length(),this));
		return true;
	}

	return false;
}

bool CEvalParserTernary::IsHasBegin(const ListEvalNode& vNode )
{
	return ToolFrame::GetItrLast(vNode,IsBeginNode) != vNode.end();
}

bool CEvalParserTernary::IsBeginNode( ListEvalNode::const_iterator& itr )
{
	IEvalNode* pNode = *itr;
	ASSERT_LOG_ERROR(pNode);

	const CEvalTernary* pNodeTernary = nullptr;
	ToolFrame::DynamicCast(pNodeTernary,pNode);
	if (!pNodeTernary)return false;

	return pNodeTernary->IsIsBegin();
}

//����������
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserVariable);
CEvalParserVariable::CEvalParserVariable( IEvalParser* pParent)
:IEvalParser(pParent)
{

}

CEvalParserVariable::~CEvalParserVariable( void )
{

}

bool CEvalParserVariable::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	MapVarScope vVarScope;
	ASSERT_LOG_ERROR(InitVarScope(vVarScope,pParser->GetScopeInfo()));

	MapVarScope::const_iterator itr;
	foreach (itr,vVarScope)
	{
		const std::string& sNameVar = itr->first;
		ASSERT_LOG_ERROR(pParser->RegistParser(sNameVar,CREATE_FUN_NAME));
	}

	return true;
}

bool CEvalParserVariable::Init()
{
	return InitVarScope(_vVarScope,GetScopeInfo());
}

bool CEvalParserVariable::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(GetEval());

	const std::string& sVarName = sActive;
	CScopeInfo* pScope = GetScope(sVarName);
	ASSERT_LOG_ERROR(pScope);

	CEvalVariable node(GetEval());
	ASSERT_LOG_ERROR(node.SetScope(pScope));
	ASSERT_LOG_ERROR(node.SetVarName(sActive));

	ASSERT_LOG_DEBUG_ERR(node.GetScope());

	ASSERT_LOG_ERROR(GetParent());
	ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc + sActive.length(),this));

	return true;
}

bool CEvalParserVariable::InitVarScope(MapVarScope& vVarScope,CScopeInfo* pScopeInfo)
{
	ASSERT_LOG_ERROR(vVarScope.empty() && pScopeInfo);
	while(pScopeInfo){
		const MapNameVar& vVar = pScopeInfo->GetVar();
		MapNameVar::const_iterator itr;
		foreach (itr,vVar){
			const std::string& sNameVar = itr->first;
			ASSERT_LOG_ERROR(!sNameVar.empty());
			if (!ToolFrame::IsHasKey(vVarScope,sNameVar))
				ToolFrame::Insert(vVarScope,sNameVar,pScopeInfo);
		}
		pScopeInfo = pScopeInfo->GetParent();
	}
	return true;
}

CScopeInfo* CEvalParserVariable::GetScope( const std::string& sVarName )
{
	return ToolFrame::GetPtrValueByKey(_vVarScope,sVarName);
}

//����������
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserFunction);
CEvalParserFunction::CEvalParserFunction( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserFunction::~CEvalParserFunction( void )
{

}

bool CEvalParserFunction::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	MapFuncScope vFuncScope;
	ASSERT_LOG_ERROR(InitFuncScope(vFuncScope,pParser->GetScopeInfo()));
	
	MapFuncScope::const_iterator itr;
	foreach(itr,vFuncScope){
		const std::string& sFuncName = itr->first;
		ASSERT_LOG_ERROR(pParser->RegistParser(sFuncName,CREATE_FUN_NAME));
	}

	return true;
}

bool CEvalParserFunction::Init()
{
	return InitFuncScope(_vFuncScope,GetScopeInfo());
}

bool CEvalParserFunction::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(!sActive.empty());

	//�������ƴ���
	if (ToolFrame::IsHasKey(_vFuncScope,sActive))
	{
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"(",nSrc + sActive.length());
		if (std::string::npos == uPos)return true;

		const std::string& sFuncName = sActive;
		CEvalParserFunctionSub func(GetParent(),sFuncName,GetScope(sFuncName));
		ASSERT_LOG_ERROR(func.Init());

		func.Parse(uPos);

		return true;
	}
	
	return false;
}

bool CEvalParserFunction::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(GetParent());
	return GetParent()->OnParseDone(pNode,nSrc,this);
}

bool CEvalParserFunction::InitFuncScope(MapFuncScope& vFuncScope,CScopeInfo* pScopeInfo)
{
	ASSERT_LOG_ERROR(vFuncScope.empty() && pScopeInfo);
	while(pScopeInfo){
		const MapNameFun& vFunc = pScopeInfo->GetFun();
		MapNameFun::const_iterator itr;
		foreach (itr,vFunc){
			const std::string& sNameFunc = itr->first;
			ASSERT_LOG_ERROR(!sNameFunc.empty());
			if (!ToolFrame::IsHasKey(vFuncScope,sNameFunc))
				ToolFrame::Insert(vFuncScope,sNameFunc,pScopeInfo);
		}
		pScopeInfo = pScopeInfo->GetParent();
	}
	return true;
}

CScopeInfo* CEvalParserFunction::GetScope( const std::string& sFuncName )
{
	return ToolFrame::GetPtrValueByKey(_vFuncScope,sFuncName);
}

//��������������
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_EXPRESSION_INIT(CEvalParserDeclareVariable);
CEvalParserDeclareVariable::CEvalParserDeclareVariable( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserDeclareVariable::~CEvalParserDeclareVariable( void )
{

}

bool CEvalParserDeclareVariable::InitParser(IEvalParser* pParser)
{
	ASSERT_LOG_ERROR(pParser);

	const MapNameType& vType = pParser->GetScopeInfo()->GetType();
	MapNameType::const_iterator itr;
	foreach(itr,vType){
		const std::string& sTypeName = itr->first;
		ASSERT_LOG_ERROR(!sTypeName.empty());

		ASSERT_LOG_ERROR(pParser->RegistParser(sTypeName,CREATE_FUN_NAME));
	}

	return true;
}

bool CEvalParserDeclareVariable::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	CEvalParserDeclareVariableSub evalDeclareVariableSub(GetParent(),sActive);
	ASSERT_LOG_ERROR(evalDeclareVariableSub.Init());
	evalDeclareVariableSub.Parse(nSrc + sActive.length());

	return true;
}

bool CEvalParserDeclareVariable::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(GetParent());
	return GetParent()->OnParseDone(pNode,nSrc,this);
}

//���ʽ������
//////////////////////////////////////////////////////////////////////////
CEvalParserExpression::CEvalParserExpression( IEvalParser* pParent )
:IEvalParser(pParent)
{
}

CEvalParserExpression::~CEvalParserExpression( void )
{

}

bool CEvalParserExpression::Init()
{
	ASSERT_LOG_ERROR(GetEval());

	MInitExpression::const_iterator itr;
	foreach(itr,MInitExpression::Singleton().GetVector()){
		FnInitParser fnInitParser = *itr;
		ASSERT_LOG_ERROR(fnInitParser);
		ASSERT_LOG_ERROR(fnInitParser(this));
	}

	return true;
}

const ListEvalNode& CEvalParserExpression::GetParsingNode() const
{
	return _vNodeParsing;
}

ListEvalNode& CEvalParserExpression::GetParsingNode()
{
	return _vNodeParsing;
}

bool CEvalParserExpression::AddParsingNode( IEvalNode* pNode )
{
	ASSERT_LOG_ERROR(pNode);
	return ToolFrame::Insert(_vNodeParsing,pNode);
}

bool CEvalParserExpression::PopParsingNode()
{
	return ToolFrame::EraseBack(_vNodeParsing);
}

bool CEvalParserExpression::SimpleLinkCheck( const ListEvalNode& vNode )
{
	if (vNode.empty())return true;

	//ֻ��һ���ڵ�ʱ
	if (vNode.size() == 1)
	{
		IEvalNode* pNode = nullptr;
		ASSERT_LOG_ERROR(ToolFrame::GetValueByIndex(vNode,(int)vNode.size() - 1,pNode));
		ASSERT_LOG_ERROR(pNode);

		if (!pNode->IsPrasingDone())return true;

		if (IsNeedLeftNode(pNode))return false;
	}

	//�����������ڵ��Ƿ�Ϸ�
	if (vNode.size() >= 2)
	{
		//��������ڵ��Ƿ� �� �����Ҫ�ұ� �ұ���Ҫ���
		IEvalNode* pNodeLeft	=ToolFrame::GetValueByIndex(vNode,(int)vNode.size() - 2);
		IEvalNode* pNodeRight	=ToolFrame::GetValueByIndex(vNode,(int)vNode.size() - 1);

		ASSERT_LOG_ERROR(pNodeLeft);
		ASSERT_LOG_ERROR(pNodeRight);

		if (!pNodeLeft->IsPrasingDone())return true;
		if (!pNodeRight->IsPrasingDone())return true;

		//������Ҫ�ǲ����ܵ�
		if (IsNeedRightNode(pNodeLeft) && IsNeedLeftNode(pNodeRight))return false;
		//���಻��ҪҲ�ǲ����ܵ�
		if (!IsNeedRightNode(pNodeLeft) && !IsNeedLeftNode(pNodeRight))return false;
	}

	return true;
}


bool CEvalParserExpression::Parse( const size_t nSrc )
{
	if (GetEval()->IsError())return false;
	if (!SimpleLinkCheck(GetParsingNode()))return false;

	size_t nDes = ToolFrame::SkipInvisibleChar(GetEval()->GetExp(),nSrc);
	if (std::string::npos == nDes){
		IEvalNode* pNode = TryGetResult();
		if (!pNode)return true;

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(pNode,nDes,this));

		CEval::Destory(pNode);
		return true;
	}

	return ParseActive(nDes);
}

EAssociativity CEvalParserExpression::GetAssociativity( int nPrecedence ) const
{
	const MapIntInt& vPrecedenceAssociativity = MEval::Singleton().GetPriorityAssociativity();
	return (EAssociativity)ToolFrame::GetValueByKey(vPrecedenceAssociativity,nPrecedence,(int)ASSOCIATIVITY_LEFT);
}
const CEvalOperationConfig* CEvalParserExpression::GetOperationConfig( EOperation eOperation ) const
{
	return ToolFrame::GetPtrValueByKey(MEval::Singleton().GetOperationConfig(),(int)eOperation);
}

bool CEvalParserExpression::Link( ListEvalNode& vNode )const
{
	if (vNode.empty())return false;

	for (int nPrecedence = MEval::GetPrecedenceMin() ;nPrecedence<=  MEval::GetPrecedenceMax();++nPrecedence)
	{
		const EAssociativity eAssociativity = this->GetAssociativity(nPrecedence);

		//���ݽ�Ϸ����������
		for(ListEvalNode::iterator itrNode = GetItrBegin(eAssociativity,vNode);itrNode != vNode.end();itrNode = GetItrNext(eAssociativity,itrNode,vNode)){
			IEvalNode* pNode = *itrNode;
			ASSERT_LOG_ERROR(pNode);

			if (!pNode->IsPrasingDone())return false;

			CEvalOperator* pNodeOperator=pNode->ToOperator();
			if (pNodeOperator){
				const CEvalOperationConfig* pOperationConfig = this->GetOperationConfig(pNodeOperator->GetOperation());
				ASSERT_LOG_ERROR(pOperationConfig);

				if (nPrecedence == pOperationConfig->GetPrecedence()){
					const EAryOperation eAryOperation = pOperationConfig->GetAryOperation();

					//��ص�����ɺ� ���� itrNode Ϊ��ǰ�ڵ�ĵ�����
					switch(eAryOperation)
					{
					case ARYOPERATION_NO:
						{

						}
						break;
					case ARYOPERATION_1:
						{
							switch(eAssociativity)
							{
							case ASSOCIATIVITY_LEFT:
								{
									ListEvalNode::iterator itr = ToolFrame::GetItrFront(itrNode,vNode);
									if (itr == vNode.end())
										return false;

									//���ӱ�������
									IEvalNode* pNodeLeft = *itr;
									ASSERT_LOG_ERROR(pNodeLeft);

									//���ò����
									ASSERT_LOG_ERROR(!pNodeOperator->GetNodeSingle());
									pNodeOperator->SetNodeSingle(pNodeLeft);
									itrNode = ToolFrame::EraseByItr(vNode,itr);
								}
								break;
							case ASSOCIATIVITY_RIGHT:
								{
									ListEvalNode::iterator itr = ToolFrame::GetItrNext(itrNode,vNode);
									if (itr == vNode.end())
										return false;

									IEvalNode* pNodeRight = *itr;
									ASSERT_LOG_ERROR(pNodeRight);

									//���ò����
									ASSERT_LOG_ERROR(!pNodeOperator->GetNodeSingle());
									pNodeOperator->SetNodeSingle(pNodeRight);
									itrNode = ToolFrame::EraseByItr(vNode,itr);
									ASSERT_LOG_ERROR(!vNode.empty());
									--itrNode;
								}
								break;
							default:
								{
									LOG_ERROR();
									return false;
								}
							}
						}
						break;
					case ARYOPERATION_2:
						{
							ListEvalNode::iterator itrFront = ToolFrame::GetItrFront(itrNode,vNode);
							if (itrFront == vNode.end())
								return false;

							IEvalNode* pNodeLeft = *itrFront;
							ASSERT_LOG_ERROR(pNodeLeft);

							//���ò����
							ASSERT_LOG_ERROR(!pNodeOperator->GetNodeLeft());
							pNodeOperator->SetNodeLeft(pNodeLeft);
							itrNode = ToolFrame::EraseByItr(vNode,itrFront);

							ListEvalNode::iterator itrRight =  ToolFrame::GetItrNext(itrNode,vNode);
							if (itrRight == vNode.end())
								return false;

							IEvalNode* pNodeRight = *itrRight;
							ASSERT_LOG_ERROR(pNodeRight);

							//���ò����
							ASSERT_LOG_ERROR(!pNodeOperator->GetNodeRight());
							pNodeOperator->SetNodeRight(pNodeRight);
							itrNode = ToolFrame::EraseByItr(vNode,itrRight);
							ASSERT_LOG_ERROR(!vNode.empty());
							--itrNode;
						}
						break;
					case ARYOPERATION_3:
						{
							CEvalTernary* pNodeTernaryEnd = nullptr;
							ToolFrame::DynamicCast(pNodeTernaryEnd,pNodeOperator);
							ASSERT_LOG_ERROR(pNodeTernaryEnd);

							if (pNodeTernaryEnd->IsIsBegin())return false;

							//�ҳ�����Ҫ�Ľڵ�
							ListEvalNode::iterator itrFalse=  ToolFrame::GetItrNext(itrNode,vNode);
							if (itrFalse == vNode.end())return false;

							ListEvalNode::iterator itrTrue =  ToolFrame::GetItrFront(itrNode,vNode);
							if (itrTrue == vNode.end())return false;

							ListEvalNode::iterator itrTeranary=  ToolFrame::GetItrFront(itrTrue,vNode);
							if (itrTeranary == vNode.end())return false;

							ListEvalNode::iterator itrExp=  ToolFrame::GetItrFront(itrTeranary,vNode);
							if (itrExp == vNode.end())return false;

							//�����м�Ľڵ��ǲ��� ?��
							CEvalTernary* pNodeTernaryBegin = nullptr;
							ToolFrame::DynamicCast(pNodeTernaryBegin,*itrTeranary);
							ASSERT_LOG_ERROR(pNodeTernaryBegin);

							if (!pNodeTernaryBegin->IsIsBegin())return false;

							CEval::Destory(pNodeTernaryBegin);

							pNodeTernaryEnd->SetNodeExp(*itrExp);
							pNodeTernaryEnd->SetNodeTrue(*itrTrue);
							pNodeTernaryEnd->SetNodeFalse(*itrFalse);
							itrNode = ToolFrame::EraseByItr(vNode,itrExp,itrFalse,false,false);
							if (vNode.empty())
							{
								ASSERT_LOG_ERROR(itrNode == vNode.end());
								vNode.push_back(pNodeTernaryEnd);
								itrNode = vNode.begin();
							}else{
								--itrNode;
								vNode.push_back(pNodeTernaryEnd);
								++itrNode;
							}
						}
						break;
					default:
						return false;
					}
				}
			}
		}
	}
	return vNode.size() == 1;
}
bool CEvalParserExpression::IsNeedLeftNode( const IEvalNode* pNode ) 
{
	ASSERT_LOG_ERROR(pNode);

	const CEvalOperator* pOperator = pNode->ToOperator(); 
	if (!pOperator)return false;

	if (ARYOPERATION_2 == pOperator->GetAryOperation())return true;
	if (ARYOPERATION_1 == pOperator->GetAryOperation() && ASSOCIATIVITY_LEFT == pOperator->GetAssociativity())return true;
	if (ARYOPERATION_3 == pOperator->GetAryOperation())return true;

	return false;
}

bool CEvalParserExpression::IsNeedRightNode( const IEvalNode* pNode ) 
{
	ASSERT_LOG_ERROR(pNode);

	const CEvalOperator* pOperator = pNode->ToOperator(); 
	if (!pOperator)return false;

	if (ARYOPERATION_2 == pOperator->GetAryOperation())return true;
	if (ARYOPERATION_1 == pOperator->GetAryOperation() && ASSOCIATIVITY_RIGHT == pOperator->GetAssociativity())return true;
	if (ARYOPERATION_3 == pOperator->GetAryOperation())return true;

	return false;
}
ListEvalNode::iterator CEvalParserExpression::GetItrBegin( const EAssociativity eAssociativity,ListEvalNode& vNode )
{
	switch(eAssociativity)
	{
	case ASSOCIATIVITY_INVAILD:
		return ToolFrame::GetItrBegin(vNode);
		break;
	case ASSOCIATIVITY_LEFT:
		return ToolFrame::GetItrBegin(vNode);
		break;
	case ASSOCIATIVITY_RIGHT:
		return ToolFrame::GetItrLast(vNode);
		break;
	default:
		{
			LOG_ERROR();
			return ListEvalNode::iterator();
		}
	}
}

ListEvalNode::iterator CEvalParserExpression::GetItrNext( const EAssociativity eAssociativity,ListEvalNode::iterator& itr,ListEvalNode& vNode )
{
	switch(eAssociativity)
	{
	case ASSOCIATIVITY_INVAILD:
		return ToolFrame::GetItrNext(itr,vNode);
		break;
	case ASSOCIATIVITY_LEFT:
		return ToolFrame::GetItrNext(itr,vNode);
		break;
	case ASSOCIATIVITY_RIGHT:
		return ToolFrame::GetItrFront(itr,vNode);
		break;
	default:
		{
			LOG_ERROR();
			return ListEvalNode::iterator();
		}
	}
}

ListEvalNode::iterator CEvalParserExpression::GetItrFront( const EAssociativity eAssociativity,ListEvalNode::iterator& itr,ListEvalNode& vNode )
{
	switch(eAssociativity)
	{
	case ASSOCIATIVITY_INVAILD:
		return ToolFrame::GetItrFront(itr,vNode);
		break;
	case ASSOCIATIVITY_LEFT:
		return ToolFrame::GetItrFront(itr,vNode);
		break;
	case ASSOCIATIVITY_RIGHT:
		return ToolFrame::GetItrNext(itr,vNode);
		break;
	default:
		{
			LOG_ERROR();
			return ListEvalNode::iterator();
		}
	}
}

IEvalNode* CEvalParserExpression::TryGetResult() const
{
	if (GetParsingNode().empty())
		return	new CEvalNone(GetEval());

	ListEvalNode vClone;
	ASSERT_LOG_ERROR(CEval::Clone(vClone,GetParsingNode()));

	if (!Link(vClone) ){
		ASSERT_LOG_ERROR(CEval::Destory(vClone));
		return nullptr;
	}

	ASSERT_LOG_ERROR(vClone.size() == 1);
	return ToolFrame::GetFront(vClone);
}

bool CEvalParserExpression::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);
	ASSERT_LOG_ERROR(AddParsingNode(pNode));
	Parse(nSrc);
	ASSERT_LOG_ERROR(PopParsingNode());
	return true;
}

//����������
//////////////////////////////////////////////////////////////////////////
CEvalParserSegment::CEvalParserSegment( IEvalParser* pParent )
:IEvalParser(pParent)
{
}

CEvalParserSegment::~CEvalParserSegment( void )
{

}

bool CEvalParserSegment::Init()
{
	ASSERT_LOG_ERROR(GetEval());
	return true;
}

bool CEvalParserSegment::Parse( const size_t nSrc )
{
	size_t uPos = ToolFrame::SkipInvisibleChar(GetEval()->GetExp(),nSrc);
	if (std::string::npos == uPos)
	{
		CEvalSegment node(GetEval());
		ASSERT_LOG_ERROR(node.SetNode(_vNodeParsing));

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));
		return true;
	}

	//����
	CEvalParserSentence parse(this);
	ASSERT_LOG_ERROR(parse.Init());
	parse.Parse(nSrc);
	return true;
}

bool CEvalParserSegment::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);

	ASSERT_LOG_ERROR(Push(pNode));
	Parse(nSrc);
	ASSERT_LOG_ERROR(Pop());
	return true;
}

bool CEvalParserSegment::Push( IEvalNode* pNode )
{
	ASSERT_LOG_ERROR(pNode);
	ToolFrame::PushBack(_vNodeParsing,pNode);
	return true;
}

bool CEvalParserSegment::Pop()
{
	ASSERT_LOG_ERROR(!_vNodeParsing.empty());
	ToolFrame::PopBack(_vNodeParsing);
	return true;
}

//����������(��)
//////////////////////////////////////////////////////////////////////////
CEvalParserFunctionSub::CEvalParserFunctionSub( IEvalParser* pParent,const std::string& sFuncName,CScopeInfo* pScopeInfo )
:IEvalParser(pParent)
{
	ASSERT_LOG_ERROR(!sFuncName.empty() && pScopeInfo );

	_sFuncName = sFuncName;
	_pScopeInfo = pScopeInfo;
}

CEvalParserFunctionSub::~CEvalParserFunctionSub( void )
{

}

bool CEvalParserFunctionSub::Init()
{
	ASSERT_LOG_ERROR(GetEval());
	return true;	
}

bool CEvalParserFunctionSub::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == ")")
	{
		CEvalParserExpression*  pExpressionSub= nullptr;
		ToolFrame::DynamicCast(pExpressionSub,pCallBack);
		ASSERT_LOG_ERROR(pExpressionSub);

		ListEvalNode vNodeArgList;
		IEvalNode* pNodeArgList =	pExpressionSub->TryGetResult();
		if (!pNodeArgList)return false;
		ASSERT_LOG_ERROR(MakeArgList(vNodeArgList,pNodeArgList));

		//�����Ҹ�����
		ASSERT_LOG_ERROR(!_sFuncName.empty() && _pScopeInfo);
		PairConstItrMapNameFun pair = _pScopeInfo->GetFun(_sFuncName);
		ASSERT_LOG_ERROR(!ToolFrame::IsEnd(pair));

		MapNameFun::const_iterator itr = pair.first;
		const CFunTypeInfo& infoFunction = itr->second;

		CEvalFunction nodeFunction(GetEval());

		nodeFunction.SetFunction(&infoFunction);
		nodeFunction.SetArgs(vNodeArgList);

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&nodeFunction,nSrc + sActive.length(),this));

		CEval::Destory(vNodeArgList);
		return true;
	}

	return false;
}

bool CEvalParserFunctionSub::Parse( const size_t nSrc )
{
	CEvalParserExpression expression(this);

	ASSERT_LOG_ERROR(expression.Init());
	expression.RegistParser(")",this);

	expression.Parse(nSrc);

	return true;
}

bool CEvalParserFunctionSub::MakeArgList( ListEvalNode& vNode,IEvalNode* pNodeArgList )
{
	ASSERT_LOG_ERROR(pNodeArgList);

	CEvalNone* pNodeNone = nullptr;
	ToolFrame::DynamicCast(pNodeNone,pNodeArgList);
	if (pNodeNone)
	{
		CEval::Destory(pNodeNone);
		ASSERT_LOG_ERROR(vNode.empty());
		return true;
	}

	while(pNodeArgList){
		IEvalNode* pNodeArg = GetArg(pNodeArgList);
		ASSERT_LOG_ERROR(pNodeArg);
		ToolFrame::PushBack(vNode,pNodeArg);

		IEvalNode* pNodeArgListNext = NextArglist(pNodeArgList);
		if (pNodeArgListNext)
		{
			//ɾ����ǰ�Ķ��Žڵ�
			ASSERT_LOG_DEBUG_ERR(IsComma(pNodeArgList));

			CEvalOperator* pNodeOperator = pNodeArgList->ToOperator();
			ASSERT_LOG_ERROR(pNodeOperator);
			ASSERT_LOG_DEBUG_ERR(OPERATION_COMMA == pNodeOperator->GetOperation());

			pNodeOperator->SetNodeLeft(nullptr);
			pNodeOperator->SetNodeRight(nullptr);

			CEval::Destory(pNodeOperator);
		}
		pNodeArgList = pNodeArgListNext;
	}

	return true;
}

bool CEvalParserFunctionSub::IsComma( IEvalNode* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	CEvalOperator* pNodeOperator = pNode->ToOperator();
	if (!pNodeOperator)return false;

	return OPERATION_COMMA == pNodeOperator->GetOperation();
}

IEvalNode* CEvalParserFunctionSub::GetArg( IEvalNode* pNode )
{
	ASSERT_LOG_ERROR(pNode);

	if (!IsComma(pNode))return pNode;

	CEvalOperator* pNodeOperator = pNode->ToOperator();
	ASSERT_LOG_ERROR(pNodeOperator);
	ASSERT_LOG_DEBUG_ERR(OPERATION_COMMA == pNodeOperator->GetOperation());

	pNode = pNodeOperator->GetNodeLeft();
	ASSERT_LOG_DEBUG_ERR(!IsComma(pNode));

	return pNode;
}

IEvalNode* CEvalParserFunctionSub::NextArglist( IEvalNode* pNode )
{
	if (!pNode)return nullptr;

	if (!IsComma(pNode))return nullptr;

	CEvalOperator* pNodeOperator = pNode->ToOperator();
	ASSERT_LOG_ERROR(pNodeOperator);
	ASSERT_LOG_DEBUG_ERR(OPERATION_COMMA == pNodeOperator->GetOperation());

	return pNodeOperator->GetNodeRight();
}

bool CEvalParserFunctionSub::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	return true;
}

//����������(��)
//////////////////////////////////////////////////////////////////////////
CEvalParserDeclareVariableSub::CEvalParserDeclareVariableSub( IEvalParser* pParent,const std::string& sVarType )
:IEvalParser(pParent)
{
	_sVarType = sVarType;
}

CEvalParserDeclareVariableSub::~CEvalParserDeclareVariableSub( void )
{

}

bool CEvalParserDeclareVariableSub::Init()
{
	return true;
}

bool CEvalParserDeclareVariableSub::Parse( const size_t nSrc )
{
	return ParseVar(nSrc);
}

bool CEvalParserDeclareVariableSub::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == ";")
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;

		CEval::Destory(pNode);

		return ParseDone(nSrc);
	}
	if (sActive == ",")
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;
		CEval::Destory(pNode);

		return ParseVar(nSrc + sActive.length());
	}

	return false;
}

bool CEvalParserDeclareVariableSub::IsVarNameChar( char ch )
{
	return ch == '_' || (ch >='A' && ch <='Z')|| (ch >='a' && ch <='z') || (ch >='0' && ch <='9');
}

bool CEvalParserDeclareVariableSub::ParseVar( const size_t nSrc )
{
	size_t uVarBegin = ToolFrame::SkipInvisibleChar(GetEval()->GetExp(),nSrc);
	if (std::string::npos == uVarBegin)return false;

	size_t uVarEnd = ToolFrame::SkipChar(GetEval()->GetExp(),uVarBegin,IsVarNameChar);
	if (std::string::npos == uVarEnd)return false;
	const std::string sVarName = GetEval()->GetExp().substr(uVarBegin,uVarEnd - uVarBegin);
	if (!IsVarNameVaild(sVarName))return false;

	ASSERT_LOG_ERROR(InsertVar(sVarName,nullptr));

	//�жϺ����ǲ��ǡ�=������','����';'��
	size_t uPosVarBehind = ToolFrame::SkipInvisibleChar(GetEval()->GetExp(),uVarEnd);
	if (std::string::npos == uPosVarBehind)return false;

	if (ToolFrame::IsBeginWith(GetEval()->GetExp(),"=",uPosVarBehind))
	{
		CEvalParserExpression expression(this);
		ASSERT_LOG_ERROR(expression.Init());

		expression.RegistParser(",",this);
		expression.RegistParser(";",this);

		ASSERT_LOG_ERROR(InsertVar(sVarName,&expression));

		expression.Parse(uPosVarBehind + sizeof('='));
		return true;
	}
	if (ToolFrame::IsBeginWith(GetEval()->GetExp(),",",uPosVarBehind))
	{
		return ParseVar(uPosVarBehind + sizeof(','));
	}
	if (ToolFrame::IsBeginWith(GetEval()->GetExp(),";",uPosVarBehind))
	{
		return ParseDone(uPosVarBehind);
	}

	return false;
}

bool CEvalParserDeclareVariableSub::IsVarNameVaild( const std::string& sVarName )
{
	if (GetScopeInfo()->IsExistVar(sVarName))return false;

	return FindVarItr(sVarName) == GetVars().end();
}

bool CEvalParserDeclareVariableSub::ParseDone( const size_t nSrc )
{
	CEvalDeclareVariable node(GetEval());
	ASSERT_LOG_ERROR(node.SetScope(GetScopeInfo()));
	node.SetVarType(_sVarType);

	ASSERT_LOG_DEBUG_ERR(node.GetScope());

	//��ӽڵ�����
	{
		VectorPairVar::iterator itr;
		foreach(itr,GetVars()){
			PairExpression& pair = *itr;
			const std::string& sVarName = pair.first;
			IEvalNode* pNode = nullptr;
			CEvalParserExpression* pExpression = pair.second;
			if (pExpression)
			{
				pNode = pExpression->TryGetResult();
				ASSERT_LOG_ERROR(pNode);
			}

			node.InsertVar(sVarName,pNode);
		}
	}

	//��ӱ�������
	{
		VectorPairVar::iterator itr;
		foreach(itr,GetVars()){
			PairExpression& pair = *itr;
			const std::string& sVarName = pair.first;
			ASSERT_LOG_ERROR(GetScopeInfo()->DeclareVar(_sVarType,sVarName,0));
		}
	}

	//����
	ASSERT_LOG_ERROR(GetParent());
	ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc,this));

	//ע����������
	{
		VectorPairVar::iterator itr;
		foreach(itr,GetVars()){
			PairExpression& pair = *itr;
			const std::string& sVarName = pair.first;
			ASSERT_LOG_ERROR(GetScopeInfo()->UndeclareVar(sVarName));
		}
	}

	return true;
}

bool CEvalParserDeclareVariableSub::InsertVar( const std::string& sVarName,CEvalParserExpression* pExpression )
{
	ItrPairVar itr = FindVarItr(sVarName);
	if (itr != GetVars().end())
	{
		PairExpression& pPairVar = *itr;
		ASSERT_LOG_ERROR(pExpression && !pPairVar.second);
		pPairVar.second = pExpression;
		return true;
	}

	GetVars().push_back(std::make_pair(sVarName,pExpression));
	return true;
}

bool CEvalParserDeclareVariableSub::RemoveVar( const std::string& sVarName )
{
	ItrPairVar itr = FindVarItr(sVarName);
	if (itr == GetVars().end())return false;

	GetVars().erase(itr);
	return true;
}

CEvalParserDeclareVariableSub::ItrPairVar CEvalParserDeclareVariableSub::FindVarItr( const std::string& sVarName )
{
	ItrPairVar itr;
	foreach(itr,GetVars()){
		PairExpression& pair = *itr;
		if (sVarName == pair.first)
			return itr;
	}

	return GetVars().end();
}

bool CEvalParserDeclareVariableSub::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	return true;
}

//��������
//////////////////////////////////////////////////////////////////////////
CEvalParserSentence::CEvalParserSentence(IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserSentence::~CEvalParserSentence( void )
{

}

bool CEvalParserSentence::Init()
{
	ASSERT_LOG_ERROR(GetEval());

	MInitSentence::const_iterator itr;
	foreach(itr,MInitSentence::Singleton().GetVector()){
		FnInitParser fnInitParser = *itr;
		ASSERT_LOG_ERROR(fnInitParser);
		ASSERT_LOG_ERROR(fnInitParser(this));
	}

	return true;
}

bool CEvalParserSentence::Parse( const size_t nSrc )
{
	size_t uPos = ToolFrame::SkipInvisibleChar(GetEval()->GetExp(),nSrc);
	if (std::string::npos == uPos)return true;

	const std::string sKeyWord = ToolFrame::PickChar(GetEval()->GetExp(),uPos,KeyWordRule);
	if (!ParseActive(sKeyWord,uPos)){
		//���ؼ�������������ֹ���
		//1.�ֺŽ�β
		//2.{}������

		if (ToolFrame::IsBeginWith(GetEval()->GetExp(),"{",uPos))
		{
			CEvalParserSentenceBrace parse(this);
			ASSERT_LOG_ERROR(parse.Init());

			return parse.Parse(uPos);
		}

		CEvalParserSentenceSemicolon parse(this);
		ASSERT_LOG_ERROR(parse.Init());

		parse.Parse(uPos);
	}
	return true;
}

bool CEvalParserSentence::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);
	ASSERT_LOG_ERROR(GetParent());
	ASSERT_LOG_ERROR(GetParent()->OnParseDone(pNode,nSrc,this));
	return true;
}

bool CEvalParserSentence::KeyWordRule( char ch )
{
	return  (ch >='A' && ch <='Z')|| (ch >='a' && ch <='z') || (ch >='0' && ch <='9');
}

//��������(��,��;�ŷָ�)
//////////////////////////////////////////////////////////////////////////
CEvalParserSentenceSemicolon::CEvalParserSentenceSemicolon( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserSentenceSemicolon::~CEvalParserSentenceSemicolon( void )
{

}

bool CEvalParserSentenceSemicolon::Init()
{
	ASSERT_LOG_ERROR(GetEval());
	return true;
}

bool CEvalParserSentenceSemicolon::Parse( const size_t nSrc )
{
	CEvalParserExpression expression(this);

	ASSERT_LOG_ERROR(expression.Init());
	expression.RegistParser(";",this);

	return expression.Parse(nSrc);
}

bool CEvalParserSentenceSemicolon::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pCallBack);
	if (sActive == ";")
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(pNode,nSrc + sActive.length(),this));

		CEval::Destory(pNode);
		return true;
	}

	return false;
}

bool CEvalParserSentenceSemicolon::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	return true;
}

//��������(��,��{}�Ű���)
//////////////////////////////////////////////////////////////////////////
CEvalParserSentenceBrace::CEvalParserSentenceBrace( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserSentenceBrace::~CEvalParserSentenceBrace( void )
{

}

bool CEvalParserSentenceBrace::Init()
{
	ASSERT_LOG_ERROR(GetEval());
	return true;
}

bool CEvalParserSentenceBrace::Parse( const size_t nSrc )
{
	size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"{",nSrc);
	if (std::string::npos == uPos)return true;

	CScopeInfo* pScope = EnterNewScope(GetEval()->MakeNewScopeName());
	ASSERT_LOG_ERROR(pScope);

	ParseSentence(uPos);

	ASSERT_LOG_ERROR(LeaveNewScope(pScope));
	return true;
}

bool CEvalParserSentenceBrace::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode);

	size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"}",nSrc);
	if (std::string::npos != uPos)
	{
		ASSERT_LOG_ERROR(Push(pNode));

		CEvalBrace node(GetEval());
		ASSERT_LOG_ERROR(node.SetScope(GetScopeInfo()->GetParent()));
		ASSERT_LOG_ERROR(node.SetNode(_vNodeParsing,GetScopeInfo()->GetName()));

		ASSERT_LOG_DEBUG_ERR(node.GetScope());

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));

		ASSERT_LOG_ERROR(Pop());
		return true;
	}

	ASSERT_LOG_ERROR(Push(pNode));
	ParseSentence(nSrc);
	ASSERT_LOG_ERROR(Pop());
	return true;
}

bool CEvalParserSentenceBrace::Push( IEvalNode* pNode )
{
	ASSERT_LOG_ERROR(pNode);
	ToolFrame::PushBack(_vNodeParsing,pNode);
	return true;
}

bool CEvalParserSentenceBrace::Pop()
{
	ASSERT_LOG_ERROR(!_vNodeParsing.empty());
	ToolFrame::PopBack(_vNodeParsing);
	return true;
}

bool CEvalParserSentenceBrace::ParseSentence( const size_t nSrc )
{
	CEvalParserSentence parse(this);
	ASSERT_LOG_ERROR(parse.Init());
	return parse.Parse(nSrc);
}

//Eval�ܻص��ӿ�
//////////////////////////////////////////////////////////////////////////
CEvalParserCallBack::CEvalParserCallBack()
{

}

CEvalParserCallBack::~CEvalParserCallBack( void )
{

}

bool CEvalParserCallBack::Init()
{
	ASSERT_LOG_ERROR(GetEval());
	return true;
}

bool CEvalParserCallBack::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	return GetEval()->OnParseDone(pNode,nSrc,pCallBack);
}

//If��������
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_SENTENCE_INIT(CEvalParserIfElse);
CEvalParserIfElse::CEvalParserIfElse( IEvalParser* pParent  )
:IEvalParser(pParent)
{
	_pNodeExp = nullptr;
	_pNodeTrue = nullptr;
	_pNodeFalse = nullptr;
}

CEvalParserIfElse::~CEvalParserIfElse( void )
{

}

bool CEvalParserIfElse::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);

	return pParser->RegistParser("if",CREATE_FUN_NAME);
}

bool CEvalParserIfElse::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pCallBack);
	ASSERT_LOG_ERROR(pNode);
	CEvalParserExpression* pExpress = nullptr;
	ToolFrame::DynamicCast(pExpress,pCallBack);
	if (pExpress)
	{
		return true;
	}
	CEvalParserSentence* pSentence = nullptr;
	ToolFrame::DynamicCast(pSentence,pCallBack);
	if (pSentence)
	{
		if (!_pNodeTrue)
		{
			ASSERT_LOG_ERROR(nullptr == _pNodeTrue);
			_pNodeTrue = pNode;

			size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"else",nSrc);
			if (std::string::npos != uPos)
			{
				CEvalParserSentence sentence(this);
				ASSERT_LOG_ERROR(sentence.Init());
				sentence.Parse(uPos);
			}else{
				ASSERT_LOG_ERROR(_pNodeExp && _pNodeTrue && !_pNodeFalse);
				CEvalIfElse node(GetEval());
				node.SetNode(_pNodeExp,_pNodeTrue,_pNodeFalse);

				ASSERT_LOG_ERROR(GetParent());
				ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));
			}

			_pNodeTrue = nullptr;
			return true;
		}else{
			ASSERT_LOG_ERROR(!_pNodeFalse);
			_pNodeFalse = pNode;

			ASSERT_LOG_ERROR(_pNodeExp && _pNodeTrue && _pNodeFalse);

			CEvalIfElse node(GetEval());
			node.SetNode(_pNodeExp,_pNodeTrue,_pNodeFalse);

			ASSERT_LOG_ERROR(GetParent());
			ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc,this));
			_pNodeFalse = nullptr;
			return true;
		}

	}
	return false;
}

bool CEvalParserIfElse::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pCallBack);

	if (sActive == "if")
	{
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"if",nSrc);
		if (std::string::npos == uPos)return true;

		uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"(",uPos);
		if (std::string::npos == uPos)return true;

		CEvalParserExpression expression(this);

		ASSERT_LOG_ERROR(expression.Init());
		expression.RegistParser(")",this);

		expression.Parse(uPos);

		return true;
	}

	if (sActive == ")")
	{
		CEvalParserExpression* pExpression=nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNodeExp =	pExpression->TryGetResult();
		if (!pNodeExp)return true;

		ASSERT_LOG_ERROR(nullptr == _pNodeExp);
		_pNodeExp = pNodeExp;

		CEvalParserSentence sentence(this);
		ASSERT_LOG_ERROR(sentence.Init());
		sentence.Parse(nSrc + sActive.length());

		_pNodeExp = nullptr;
		CEval::Destory(pNodeExp);
		return true;
	}
	return false;
}
//for��������
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_SENTENCE_INIT(CEvalParserFor);
CEvalParserFor::CEvalParserFor( IEvalParser* pParent )
:IEvalParser(pParent)
{
	_pNodeExp1 = nullptr;
	_pNodeExp2 = nullptr;
	_pNodeExp3 = nullptr;
	_pNodeLoop = nullptr;
}

CEvalParserFor::~CEvalParserFor( void )
{

}

bool CEvalParserFor::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);

	return pParser->RegistParser("for",CREATE_FUN_NAME);
}

bool CEvalParserFor::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == "for")
	{
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"for",nSrc);
		if (std::string::npos == uPos)return true;

		uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"(",uPos);
		if (std::string::npos == uPos)return true;

		CScopeInfo*	pScope = EnterNewScope(GetEval()->MakeNewScopeName());
		ASSERT_LOG_ERROR(pScope);

		CEvalParserExpression expression(this);
		ASSERT_LOG_ERROR(expression.Init());
		expression.RegistParser(";",this);
		expression.Parse(uPos);

		ASSERT_LOG_ERROR(LeaveNewScope(pScope));
		return true;
	}
	if (sActive == ";" || sActive == ")")
	{
		CEvalParserExpression* pExp = nullptr;
		ToolFrame::DynamicCast(pExp , pCallBack);
		ASSERT_LOG_ERROR(pExp);

		IEvalNode* pNode = pExp->TryGetResult();
		if (!pNode)return true;

		if (nullptr == _pNodeExp1)
		{
			_pNodeExp1 = pNode;

			CEvalParserExpression expression(this);

			ASSERT_LOG_ERROR(expression.Init());
			expression.RegistParser(";",this);

			expression.Parse(nSrc + sActive.length());

			_pNodeExp1 = nullptr;
			return true;
		}
		if (nullptr == _pNodeExp2)
		{
			_pNodeExp2 = pNode;

			CEvalParserExpression expression(this);

			ASSERT_LOG_ERROR(expression.Init());
			expression.RegistParser(")",this);

			expression.Parse(nSrc + sActive.length());

			_pNodeExp2 = nullptr;
			return true;
		}
		if (nullptr == _pNodeExp3)
		{
			_pNodeExp3 = pNode;

			ASSERT_LOG_ERROR(!_pNodeLoop);

			//���岿���������ǵ����������򣬺͸��ڵ�����������һ��
			CScopeInfo* pScope = EnterNewScope(GetScopeInfo()->GetName());
			ASSERT_LOG_ERROR(pScope);

			CEvalParserSentence sentence(this);
			ASSERT_LOG_ERROR(sentence.Init());
			sentence.Parse(nSrc + sActive.length());

			ASSERT_LOG_ERROR(LeaveNewScope(pScope));
			_pNodeExp3 = nullptr;
			return true;
		}
	}
	return false;
}

bool CEvalParserFor::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode && pCallBack);

	if (!(_pNodeExp1 && _pNodeExp2 && _pNodeExp3))return true;

	_pNodeLoop = pNode;

	CEvalFor node(GetEval());
	node.SetScope(GetScopeInfo()->GetParent()->GetParent());
	node.SetNode(GetScopeInfo()->GetName(),_pNodeExp1,_pNodeExp2,_pNodeExp3,_pNodeLoop);

	ASSERT_LOG_ERROR(GetParent());
	ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc,this));

	_pNodeLoop = nullptr;
	return true;
}

//do..while();
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_SENTENCE_INIT(CEvalParserDoWhile);
CEvalParserDoWhile::CEvalParserDoWhile( IEvalParser* pParent )
:IEvalParser(pParent)
{
	_pNodeExp = nullptr;
	_pNodeLoop = nullptr;
}

CEvalParserDoWhile::~CEvalParserDoWhile( void )
{

}

bool CEvalParserDoWhile::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);

	return pParser->RegistParser("do",CREATE_FUN_NAME);
}

bool CEvalParserDoWhile::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if ("do" == sActive)
	{
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"do",nSrc);
		if (std::string::npos == uPos)return true;

		CScopeInfo* pScope = EnterNewScope(GetEval()->MakeNewScopeName());
		ASSERT_LOG_ERROR(pScope);

		CEvalParserSentence sentence(this);
		ASSERT_LOG_ERROR(sentence.Init());
		sentence.Parse(uPos);

		ASSERT_LOG_ERROR(LeaveNewScope(pScope));

		return true;
	}
	if (")" == sActive)
	{
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),";",nSrc + sActive.length());
		if (std::string::npos == uPos)return true;

		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;

		_pNodeExp = pNode;

		CEvalDoWhile node(GetEval());
		node.SetScope(GetScopeInfo()->GetParent());
		ASSERT_LOG_ERROR(node.SetNode(GetScopeInfo()->GetName(),_pNodeExp,_pNodeLoop));

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));

		_pNodeExp = nullptr;
		return true;
	}

	return true;
}

bool CEvalParserDoWhile::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode && pCallBack);

	if (nullptr == _pNodeLoop)
	{
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"while",nSrc);
		if (std::string::npos == uPos)return true;

		uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"(",uPos);
		if (std::string::npos == uPos)return true;

		_pNodeLoop = pNode;

		CEvalParserExpression expression(this);
		ASSERT_LOG_ERROR(expression.Init());
		expression.RegistParser(")",this);
		expression.Parse(uPos);

		_pNodeLoop = nullptr;
		return true;
	}

	return true;
}

//while(); ���
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_SENTENCE_INIT(CEvalParserWhile);
CEvalParserWhile::CEvalParserWhile( IEvalParser* pParent )
:IEvalParser(pParent)
{
	_pNodeExp = nullptr;
	_pNodeLoop = nullptr;
}

CEvalParserWhile::~CEvalParserWhile( void )
{

}

bool CEvalParserWhile::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);

	return pParser->RegistParser("while",CREATE_FUN_NAME);
}

bool CEvalParserWhile::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if ("while" == sActive){
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"while",nSrc);
		if (std::string::npos == uPos)return true;

		uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"(",uPos);
		if (std::string::npos == uPos)return true;

		CScopeInfo* pScope = EnterNewScope(GetEval()->MakeNewScopeName());
		ASSERT_LOG_ERROR(pScope);

		CEvalParserExpression expression(this);
		ASSERT_LOG_ERROR(expression.Init());
		expression.RegistParser(")",this);
 		expression.Parse(uPos);

		LeaveNewScope(pScope);

		return true;
	}
	if (")" == sActive)
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;

		ASSERT_LOG_ERROR(nullptr == _pNodeExp);
		_pNodeExp = pNode;

		CScopeInfo* pScope = EnterNewScope(GetScopeInfo()->GetName());
		ASSERT_LOG_ERROR(pScope);

		CEvalParserSentence sentence(this);
		ASSERT_LOG_ERROR(sentence.Init());
		sentence.Parse(nSrc + sActive.length());

		LeaveNewScope(pScope);

		_pNodeExp = nullptr;

		return true;
	}

	return false;
}

bool CEvalParserWhile::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	if ( nullptr ==_pNodeExp)return true;

	ASSERT_LOG_ERROR(nullptr == _pNodeLoop);

	_pNodeLoop = pNode;

	CEvalWhile node(GetEval());
	node.SetScope(GetScopeInfo()->GetParent()->GetParent());
	ASSERT_LOG_ERROR(node.SetNode(GetScopeInfo()->GetName(),_pNodeExp,_pNodeLoop));

	ASSERT_LOG_ERROR(GetParent());
	ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,nSrc,this));

	_pNodeLoop = nullptr;

	return true;
}

//break; ���
//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_SENTENCE_INIT(CEvalParserBreak);
CEvalParserBreak::CEvalParserBreak( IEvalParser* pParent )
:IEvalParser(pParent)
{

}

CEvalParserBreak::~CEvalParserBreak( void )
{

}

bool CEvalParserBreak::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);

	return pParser->RegistParser("break",CREATE_FUN_NAME);
}

bool CEvalParserBreak::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	if (sActive == "break")
	{
		return true;
		//break
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"break",nSrc);
		if (std::string::npos == uPos)return true;

		uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),";",uPos);
		if (std::string::npos == uPos)return true;

		CEvalbreak node(GetEval());

		ASSERT_LOG_ERROR(GetParent());
		ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
REGIST_PARSER_SENTENCE_INIT(CEvalParserSwitch);
CEvalParserSwitch::CEvalParserSwitch( IEvalParser* pParent )
:IEvalParser(pParent)
{
	_pNodeExp = nullptr;
	_pExpCase = nullptr;
}

CEvalParserSwitch::~CEvalParserSwitch( void )
{

}

bool CEvalParserSwitch::InitParser( IEvalParser* pParser )
{
	ASSERT_LOG_ERROR(pParser);

	return pParser->RegistParser("switch",CREATE_FUN_NAME);
}

/*
switch   (expression)   
{   
case   constant-expression:   
statement   
jump-statement   
[default:   
statement   
jump-statement]   
}   
*/

bool CEvalParserSwitch::ParseCase( const size_t nSrc )
{
	size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"case",nSrc);
	if (std::string::npos == uPos)return true;

	CEvalParserExpression expression(this);
	ASSERT_LOG_ERROR(expression.Init());
	expression.RegistParser(":",this);
	return expression.Parse(uPos);
}

bool CEvalParserSwitch::OnActive( const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pCallBack);
	if (sActive == "switch")
	{
		//switch
		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"(",nSrc + sActive.length());
		if (std::string::npos == uPos)return true;

		CEvalParserExpression expression(this);
		ASSERT_LOG_ERROR(expression.Init());
		expression.RegistParser(")",this);

		expression.Parse(uPos);
		return true;
	}
	if (sActive == ")")
	{
		CEvalParserExpression* pExpression = nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;

		size_t uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"{",nSrc + sActive.length());
		if (std::string::npos == uPos)return true;

		//�������ٰ���һ��case
		if (std::string::npos == ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"case",uPos))return true;

		_pNodeExp = pNode;

		ParseCase(uPos);

		_pNodeExp = nullptr;
		CEval::Destory(pNode);
		return true;
	}
	if (sActive == ":")
	{
		//case exp : exp
		CEvalParserExpression* pExpression=nullptr;
		ToolFrame::DynamicCast(pExpression,pCallBack);
		ASSERT_LOG_ERROR(pExpression);

		IEvalNode* pNode = pExpression->TryGetResult();
		if (!pNode)return true;

		ASSERT_LOG_ERROR(!_pExpCase);

		_pExpCase = pNode;

		ASSERT_LOG_ERROR(TestCaseParsingOver(nSrc+sActive.length()));

		ASSERT_LOG_ERROR(_pExpCase);
		_pExpCase = nullptr;

		CEval::Destory(pNode);
		return true;
	}

	return false;
}

bool CEvalParserSwitch::OnParseDone( IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack )
{
	ASSERT_LOG_ERROR(pNode && pCallBack);

	CEvalParserExpression* pExpression = nullptr;
	ToolFrame::DynamicCast(pExpression,pCallBack);
	if (pExpression)
	{
		return true;
	}

	CEvalParserSentence* pSentence = nullptr;
	ToolFrame::DynamicCast(pSentence,pCallBack);
	if (pSentence)
	{
		ToolFrame::PushBack(_vSetence,pNode);

		ASSERT_LOG_ERROR(TestCaseParsingOver(nSrc));
	
		ToolFrame::PopBack(_vSetence);
		return true;
	}

	return false;
}

bool CEvalParserSwitch::IsValidCaseSentence( IEvalNode* pExpCase,const ListEvalNode& vSetence )
{
	return nullptr != pExpCase;//case ��Ϊ�� �Ϳ���
}

bool CEvalParserSwitch::StoreParsingCase()
{
	if (!_pExpCase)return false;

	ToolFrame::PushBack(_vCaseSentence,std::make_pair(_pExpCase,_vSetence));	

	_pExpCase = nullptr;
	_vSetence.clear();
	return true;
}

bool CEvalParserSwitch::RestoreParsingCase()
{
	if (_vCaseSentence.empty())return true;
	
	PairCaseSetence pair = ToolFrame::PopBack(_vCaseSentence);
	_pExpCase = pair.first;
	_vSetence = pair.second;

	return true;
}

bool CEvalParserSwitch::TestCaseParsingOver( const size_t nSrc )
{
	size_t uPos = std::string::npos;

	uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"case",nSrc);
	if (std::string::npos != uPos)
	{
		//�����ǰ���������ʱ,����ǰ�����е�_pExpCase _vSetence ѹ��case����
		//���ҽ������еĽڵ�����Ա�������һ��case
		if (IsValidCaseSentence(_pExpCase,_vSetence))
		{
			ASSERT_LOG_ERROR(StoreParsingCase());

			CEvalParserExpression expression(this);
			ASSERT_LOG_ERROR(expression.Init());
			expression.RegistParser(":",this);
			expression.Parse(uPos);

			ASSERT_LOG_ERROR(RestoreParsingCase());
		}

		return true;
	}

	uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"default",nSrc);
	if (std::string::npos != uPos)
	{
		uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),":",uPos);
		if (std::string::npos != uPos && IsValidCaseSentence(_pExpCase,_vSetence)){
			ASSERT_LOG_ERROR(StoreParsingCase());

			CEvalParserSentence sentence(this);
			ASSERT_LOG_ERROR(sentence.Init());
			sentence.Parse(uPos);

			ASSERT_LOG_ERROR(RestoreParsingCase());
		}

		return true;
	}

	uPos = ToolFrame::IsVisibleCharBeginWith(GetEval()->GetExp(),"}",nSrc);
	if (std::string::npos != uPos){
		if (IsValidCaseSentence(_pExpCase,_vSetence))
		{
			ASSERT_LOG_ERROR(StoreParsingCase());

			CEvalSwitch node(GetEval());
			node.SetNode(_pNodeExp,_vCaseSentence,_vSetence);
			ASSERT_LOG_ERROR(GetParent());
			ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));

			ASSERT_LOG_ERROR(RestoreParsingCase());
		}else{
			CEvalSwitch node(GetEval());
			node.SetNode(_pNodeExp,_vCaseSentence,_vSetence);
			ASSERT_LOG_ERROR(GetParent());
			ASSERT_LOG_ERROR(GetParent()->OnParseDone(&node,uPos,this));
		}

		return true;
	}

	//����������һ�����
	CEvalParserSentence sentence(this);
	ASSERT_LOG_ERROR(sentence.Init());
	sentence.Parse(nSrc);
	return true;
}

NS_TOOL_FRAME_END
