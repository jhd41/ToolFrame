#pragma once
#include "Macro.h"
#include "EvalNode.h"
#include "MCreator.h"
#include "MVector.h"

NS_TOOL_FRAME_BEGIN

class CEval;
class IEvalParser;

class CEvalParserExpression;	//���ʽ����
class CEvalParserSentence;		//������

//���崴��������
typedef IEvalParser* IEvalParserPtr;
typedef IEvalParserPtr (*FnCreateFunParser)(IEvalParser* parent);
typedef bool (*FnInitParser)(IEvalParser* pParser);

typedef MVector<FnInitParser,CEvalParserExpression>		MInitExpression;
typedef MVector<FnInitParser,CEvalParserSentence>		MInitSentence;

//���崴������
#define	FUN_CREATER_PARSER(className)					FUN_CREATE_ARG1(className,IEvalParserPtr,IEvalParserPtr)

//ע�� ��ʼ������
#define REGIST_PARSER_EXPRESSION_INIT(className)		MVECTOR_REGIST_VALUE(className::InitParser,MInitExpression,	MInitExpression##className)
#define REGIST_PARSER_SENTENCE_INIT(className)			MVECTOR_REGIST_VALUE(className::InitParser,MInitSentence,	MInitSentence##className)

//����������
//////////////////////////////////////////////////////////////////////////
class IEvalActiveNode
{
public:
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCall)const =0 ;
};

class CEvalActiveCreator
	:public IEvalActiveNode
{
public:
	CEvalActiveCreator(const std::string& sActive,FnCreateFunParser fnCreator);
public:
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCall)const;
public:
	CFIELD_REF(FnCreateFunParser,Creator,fn);
};

class CEvalActiveCallBack
	:public IEvalActiveNode
{
public:
	CEvalActiveCallBack(const std::string& sActive,IEvalParser* pCallBack);
public:
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCall)const;
public:
	CFIELD_PTR(IEvalParser*,CallBack,p);
};

class IEvalParser
{
	typedef std::multimap<std::string,IEvalActiveNode*>	MapActiveNode;		//����ؼ��� �Լ� ����ڵ�
	typedef std::map<size_t,MapActiveNode>				MapActiveParsers;	//�ؼ��ֳ��� �Լ� ���Ա�
public:
	virtual	bool	Init();
	virtual bool	Parse(const size_t nSrc );//��ʼ����

	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	bool			RegistParser	(const std::string& sActive,IEvalParser* pParser);			//ע�������
	bool			RegistParser	(const std::string& sActive,FnCreateFunParser fnCreator);	//ע�������

	bool			UnRegistParser	();
protected:
	CScopeInfo*		EnterNewScope(const std::string& sNewScopeName);
	bool			LeaveNewScope(CScopeInfo* pScope);
public:
	bool			ParseActive(const size_t nSrc );
	bool			ActiveParser(MapActiveNode& vActive,size_t nDes);

	bool			ParseActive(const std::string& sActive,const size_t nSrc);//��ȷ��ȥ����
public:
	IEvalParser();
	IEvalParser(IEvalParser* pParent);
	virtual ~IEvalParser(void);
public:
	CFIELD_PTR(IEvalParser*,Parent,p);	//��������
	CFIELD_PTR(CEval*,Eval,p);
	CFIELD_PTR(CScopeInfo*,ScopeInfo,p);//��ǰ������������
	MapActiveParsers	_vActive;		//������
};

//���ʽ������
//////////////////////////////////////////////////////////////////////////
//���ֽ�����
class CEvalParserNumber
	:public IEvalParser
{
	FUN_CREATER_PARSER(CEvalParserNumber);
public:
	static	bool	InitParser(IEvalParser* pParser);
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
private:
	static size_t	FindNumberEnd( const std::string& sSrc,size_t uOffset );
public:
	CEvalParserNumber(IEvalParser* pParent);
	virtual ~CEvalParserNumber(void);
};
//True False������
class CEvalParserTrueFalse
	:public IEvalParser
{
	FUN_CREATER_PARSER(CEvalParserTrueFalse);
public:
	static	bool	InitParser(IEvalParser* pParser);
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserTrueFalse(IEvalParser* pParent);
	virtual ~CEvalParserTrueFalse(void);
};

//�򵥶�Ӧ�����(+ - * / % && ||...)
class IEvalParserSimple
	:public IEvalParser
{
	FUN_CREATER_PARSER(IEvalParserSimple);
public:
	static bool InitParser(IEvalParser* pParser);
	static bool	InitParserOperation(const std::string& sParser,EOperation eOperation);
public:
	static bool InitParserOperation();
public:
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
public:
	IEvalParserSimple(IEvalParser* pParent);
	virtual ~IEvalParserSimple(void);
private:
	typedef std::multimap<std::string,EOperation> MapStringOperation;
	static MapStringOperation	_vParser;
};

//Բ���Ž�����
class CEvalParserParentheses
	:public IEvalParser
{
	FUN_CREATER_PARSER(CEvalParserParentheses);
public:
	static	bool InitParser(IEvalParser* pParser);
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserParentheses(IEvalParser* pParent);
	virtual ~CEvalParserParentheses(void);
};

//? : ������
class CEvalParserTernary
	:public IEvalParser
{
	FUN_CREATER_PARSER(CEvalParserTernary);
public:
	static	bool InitParser(IEvalParser* pParser);
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
private:
	bool	IsHasBegin(const ListEvalNode& vNode);
private:
	static	bool IsBeginNode( ListEvalNode::const_iterator& itr);
public:
	CEvalParserTernary(IEvalParser* pParent);
	virtual ~CEvalParserTernary(void);
};

//����������
class CEvalParserVariable
	:public IEvalParser
{
	typedef std::map<std::string,CScopeInfo*>	MapVarScope;//������,����������
public:
	FUN_CREATER_PARSER(CEvalParserVariable);
public:
	static	bool InitParser(IEvalParser* pParser);
public:
	virtual	bool Init();
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
private:
	CScopeInfo*	GetScope(const std::string& sVarName);
public:
	static bool	InitVarScope(MapVarScope& vVarScope,CScopeInfo* pScopeInfo);
public:
	CEvalParserVariable(IEvalParser* pParent);
	virtual ~CEvalParserVariable(void);
private:
	MapVarScope	_vVarScope;
};

//����������(��)
class  CEvalParserFunctionSub
	:public IEvalParser
{
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );//��ʼ����
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
private:
	bool		MakeArgList(ListEvalNode& vNode,IEvalNode* pNodeArg);
	bool		IsComma(IEvalNode* pNode);
	IEvalNode*	GetArg(IEvalNode* pNode);
	IEvalNode*	NextArglist(IEvalNode* pNode);
public:
	CEvalParserFunctionSub(IEvalParser* pParent,const std::string& sFuncName,CScopeInfo* pScopeInfo);
	virtual ~CEvalParserFunctionSub(void);
private:
	std::string _sFuncName;		//��������
	CScopeInfo*	_pScopeInfo;	//������
};
//����������(��)
class CEvalParserFunction
	:public IEvalParser
{
	typedef std::map<std::string,CScopeInfo*>	MapFuncScope;//������,����������
public:
	FUN_CREATER_PARSER(CEvalParserFunction);
public:
	static	bool InitParser(IEvalParser* pParser);
public:
	virtual bool Init();
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
private:
	CScopeInfo*	GetScope(const std::string& sFuncName);
public:
	static bool		InitFuncScope(MapFuncScope& vFuncScope,CScopeInfo* pScopeInfo);
public:
	CEvalParserFunction(IEvalParser* pParent);
	virtual ~CEvalParserFunction(void);
private:
	MapFuncScope	_vFuncScope;
};

//��������������(��:�������ͺͺ�����ʽ�ĵ�Ԫ)
class  CEvalParserDeclareVariableSub
	:public IEvalParser
{
	typedef std::pair<std::string,CEvalParserExpression*> PairExpression;
	typedef std::vector<PairExpression> VectorPairVar;
	typedef VectorPairVar::iterator ItrPairVar;
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );//��ʼ����
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	static bool	IsVarNameChar(char ch);
private:
	bool ParseVar(const size_t nSrc );
	bool IsVarNameVaild(const std::string& sVarName);
	bool ParseDone(const size_t nSrc );
	bool InsertVar(const std::string& sVarName,CEvalParserExpression* pExpression);
	bool RemoveVar(const std::string& sVarName);

	ItrPairVar FindVarItr(const std::string& sVarName);
public:
	CEvalParserDeclareVariableSub(IEvalParser* pParent,const std::string& sVarType);
	virtual ~CEvalParserDeclareVariableSub(void);
private:
	std::string _sVarType;
	CFIELD_REF(VectorPairVar,Vars,v);
};

//��������������(��:���������Ĵ�������)
class CEvalParserDeclareVariable
	:public IEvalParser
{
public:
	FUN_CREATER_PARSER(CEvalParserDeclareVariable);
public:
	static	bool InitParser(IEvalParser* pParser);
public:
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserDeclareVariable(IEvalParser* pParent);
	virtual ~CEvalParserDeclareVariable(void);
};

//���ʽ������
class CEvalParserExpression
	:public IEvalParser
{
public:
	virtual IEvalNode*				TryGetResult()const;
public:
	const ListEvalNode&				GetParsingNode()const;							//��ȡ�Ѿ������ɹ��Ľڵ�����
	ListEvalNode&					GetParsingNode();	
	bool							AddParsingNode(IEvalNode* pNode);				//��ӵ��Ѿ������ɹ��Ľڵ�����
	bool							PopParsingNode();								//ɾ��ĩβ�Ľ����ɹ��Ľڵ�
public:
	virtual	bool					Init();
	virtual bool					Parse(const size_t nSrc );//��ʼ����
	virtual bool					OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
private:
	bool							Link(ListEvalNode& vNode)const;	//����
	EAssociativity					GetAssociativity( int nPrecedence ) const;
	const CEvalOperationConfig*		GetOperationConfig( EOperation eOperation ) const;
public:
	static ListEvalNode::iterator	GetItrBegin(const EAssociativity eAssociativity,ListEvalNode& vNode);
	static ListEvalNode::iterator	GetItrFront(const EAssociativity eAssociativity,ListEvalNode::iterator& itr,ListEvalNode& vNode);
	static ListEvalNode::iterator	GetItrNext(const EAssociativity eAssociativity,ListEvalNode::iterator& itr,ListEvalNode& vNode);
public:
	CEvalParserExpression(IEvalParser* pParent);
	virtual ~CEvalParserExpression(void);
private:
	static bool SimpleLinkCheck(const ListEvalNode& vNode);
	static bool IsNeedLeftNode( const IEvalNode* pNode ) ;
	static bool IsNeedRightNode( const IEvalNode* pNode ) ;
private:
	ListEvalNode	_vNodeParsing;		//����ʱ�ڵ�
};

//��������
//////////////////////////////////////////////////////////////////////////
//If��������
class CEvalParserIfElse
	:public IEvalParser
{
public:
	FUN_CREATER_PARSER(CEvalParserIfElse);
public:
	static	bool	InitParser(IEvalParser* pParser);
public:
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserIfElse(IEvalParser* pParent );
	virtual ~CEvalParserIfElse(void);
private:
	IEvalNode* _pNodeExp;	//���ʽ��ʱ���
	IEvalNode* _pNodeTrue;	
	IEvalNode* _pNodeFalse;
};

//for��������
class CEvalParserFor
	:public IEvalParser
{
public:
	FUN_CREATER_PARSER(CEvalParserFor);
public:
	static	bool	InitParser(IEvalParser* pParser);
public:
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserFor(IEvalParser* pParent );
	virtual ~CEvalParserFor(void);
private:
	IEvalNode* _pNodeExp1;
	IEvalNode* _pNodeExp2;
	IEvalNode* _pNodeExp3;
	IEvalNode* _pNodeLoop;
};

//do..while ���
class CEvalParserDoWhile
	:public IEvalParser                                                                                                                      
{
public:
	FUN_CREATER_PARSER(CEvalParserDoWhile);
public:
	static	bool	InitParser(IEvalParser* pParser);
public:
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserDoWhile(IEvalParser* pParent );
	virtual ~CEvalParserDoWhile(void);
private:
	IEvalNode* _pNodeExp;
	IEvalNode* _pNodeLoop;
};

//while(); ���
class CEvalParserWhile
	:public IEvalParser                                                                                                                      
{
public:
	FUN_CREATER_PARSER(CEvalParserWhile);
public:
	static	bool	InitParser(IEvalParser* pParser);
public:
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserWhile(IEvalParser* pParent );
	virtual ~CEvalParserWhile(void);
private:
	IEvalNode* _pNodeExp;
	IEvalNode* _pNodeLoop;
};

//break; ���
class CEvalParserBreak
	:public IEvalParser                                                                                                                      
{
public:
	FUN_CREATER_PARSER(CEvalParserBreak);
public:
	static	bool	InitParser(IEvalParser* pParser);
public:
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserBreak(IEvalParser* pParent );
	virtual ~CEvalParserBreak(void);
};
//switch ���
class CEvalParserSwitch
	:public IEvalParser                                                                                                                      
{
public:
	FUN_CREATER_PARSER(CEvalParserSwitch);
public:
	static	bool	InitParser(IEvalParser* pParser);
public:
	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
private:
	virtual bool	ParseCase(const size_t nSrc );
	bool			IsValidCaseSentence(IEvalNode* pExpCase,const ListEvalNode& vSetence);
	bool			TestCaseParsingOver(const size_t nSrc);//�жϵ�ǰ�ڵ��Ƿ����

	bool			StoreParsingCase();		//�洢�����е�case
	bool			RestoreParsingCase();	//�ָ������е�case		
public:
	CEvalParserSwitch(IEvalParser* pParent );
	virtual ~CEvalParserSwitch(void);
private:
	IEvalNode*		_pNodeExp;
	ListCaseSetence	_vCaseSentence;	//<case,statement>
	
	IEvalNode*		_pExpCase;	//�����е�case
	ListEvalNode	_vSetence;	//�����е����
};
//��������(��,��{}�Ű���)
class CEvalParserSentenceBrace
	:public IEvalParser
{
public:
	bool	ParseSentence(const size_t nSrc );
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );
public:
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	bool	Push(IEvalNode* pNode);
	bool	Pop();
public:
	CEvalParserSentenceBrace(IEvalParser* pParent);
	virtual ~CEvalParserSentenceBrace(void);
public:
	ListEvalNode	_vNodeParsing;		//����ʱ�ڵ�
};

//��������(��,��;�ŷָ�)
class CEvalParserSentenceSemicolon
	:public IEvalParser
{
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );
public:
	virtual bool OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserSentenceSemicolon(IEvalParser* pParent);
	virtual ~CEvalParserSentenceSemicolon(void);
};

//��������
class CEvalParserSentence
	:public IEvalParser
{
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	static bool KeyWordRule( char ch );
public:
	CEvalParserSentence(IEvalParser* pParent );
	virtual ~CEvalParserSentence(void);
};

//����������
//////////////////////////////////////////////////////////////////////////
class CEvalParserSegment
	:public IEvalParser
{
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );//��ʼ���� 
public:
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	bool	Push(IEvalNode* pNode);
	bool	Pop();
public:
	CEvalParserSegment(IEvalParser* pParent);
	virtual ~CEvalParserSegment(void);
public:
	ListEvalNode	_vNodeParsing;		//����ʱ�ڵ�
};

//Eval�ܻص��ӿ�
//////////////////////////////////////////////////////////////////////////
class CEvalParserCallBack
	:public IEvalParser
{
public:
	virtual	bool	Init();
public:
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEvalParserCallBack();
	virtual ~CEvalParserCallBack(void);
};

NS_TOOL_FRAME_END
