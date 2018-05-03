#pragma once
#include "Macro.h"
#include "EvalNode.h"
#include "MCreator.h"
#include "MVector.h"

NS_TOOL_FRAME_BEGIN

class CEval;
class IEvalParser;

class CEvalParserExpression;	//表达式解析
class CEvalParserSentence;		//语句解析

//定义创建器类型
typedef IEvalParser* IEvalParserPtr;
typedef IEvalParserPtr (*FnCreateFunParser)(IEvalParser* parent);
typedef bool (*FnInitParser)(IEvalParser* pParser);

typedef MVector<FnInitParser,CEvalParserExpression>		MInitExpression;
typedef MVector<FnInitParser,CEvalParserSentence>		MInitSentence;

//定义创建函数
#define	FUN_CREATER_PARSER(className)					FUN_CREATE_ARG1(className,IEvalParserPtr,IEvalParserPtr)

//注册 初始化函数
#define REGIST_PARSER_EXPRESSION_INIT(className)		MVECTOR_REGIST_VALUE(className::InitParser,MInitExpression,	MInitExpression##className)
#define REGIST_PARSER_SENTENCE_INIT(className)			MVECTOR_REGIST_VALUE(className::InitParser,MInitSentence,	MInitSentence##className)

//解析器基类
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
	typedef std::multimap<std::string,IEvalActiveNode*>	MapActiveNode;		//激活关键字 以及 激活节点
	typedef std::map<size_t,MapActiveNode>				MapActiveParsers;	//关键字长度 以及 属性表
public:
	virtual	bool	Init();
	virtual bool	Parse(const size_t nSrc );//开始解析

	virtual bool	OnActive(const std::string& sActive,const size_t nSrc,IEvalParser* pCallBack);
	virtual bool	OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	bool			RegistParser	(const std::string& sActive,IEvalParser* pParser);			//注册解析器
	bool			RegistParser	(const std::string& sActive,FnCreateFunParser fnCreator);	//注册解析器

	bool			UnRegistParser	();
protected:
	CScopeInfo*		EnterNewScope(const std::string& sNewScopeName);
	bool			LeaveNewScope(CScopeInfo* pScope);
public:
	bool			ParseActive(const size_t nSrc );
	bool			ActiveParser(MapActiveNode& vActive,size_t nDes);

	bool			ParseActive(const std::string& sActive,const size_t nSrc);//精确的去触发
public:
	IEvalParser();
	IEvalParser(IEvalParser* pParent);
	virtual ~IEvalParser(void);
public:
	CFIELD_PTR(IEvalParser*,Parent,p);	//父解析器
	CFIELD_PTR(CEval*,Eval,p);
	CFIELD_PTR(CScopeInfo*,ScopeInfo,p);//当前解析的作用域
	MapActiveParsers	_vActive;		//触发表
};

//表达式解析器
//////////////////////////////////////////////////////////////////////////
//数字解析器
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
//True False解析器
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

//简单对应运算符(+ - * / % && ||...)
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

//圆括号解析器
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

//? : 解析器
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

//变量解析器
class CEvalParserVariable
	:public IEvalParser
{
	typedef std::map<std::string,CScopeInfo*>	MapVarScope;//变量名,所在作用域
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

//函数解析器(分)
class  CEvalParserFunctionSub
	:public IEvalParser
{
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );//开始解析
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
	std::string _sFuncName;		//函数名称
	CScopeInfo*	_pScopeInfo;	//作用域
};
//函数解析器(总)
class CEvalParserFunction
	:public IEvalParser
{
	typedef std::map<std::string,CScopeInfo*>	MapFuncScope;//函数名,所在作用域
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

//变量声明解析器(分:处理类型和后面表达式的单元)
class  CEvalParserDeclareVariableSub
	:public IEvalParser
{
	typedef std::pair<std::string,CEvalParserExpression*> PairExpression;
	typedef std::vector<PairExpression> VectorPairVar;
	typedef VectorPairVar::iterator ItrPairVar;
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );//开始解析
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

//变量声明解析器(总:变量解析的触发条件)
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

//表达式解析器
class CEvalParserExpression
	:public IEvalParser
{
public:
	virtual IEvalNode*				TryGetResult()const;
public:
	const ListEvalNode&				GetParsingNode()const;							//获取已经解析成功的节点链表
	ListEvalNode&					GetParsingNode();	
	bool							AddParsingNode(IEvalNode* pNode);				//添加到已经解析成功的节点链表
	bool							PopParsingNode();								//删除末尾的解析成功的节点
public:
	virtual	bool					Init();
	virtual bool					Parse(const size_t nSrc );//开始解析
	virtual bool					OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
private:
	bool							Link(ListEvalNode& vNode)const;	//连接
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
	ListEvalNode	_vNodeParsing;		//计算时节点
};

//语句解析器
//////////////////////////////////////////////////////////////////////////
//If语句解析器
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
	IEvalNode* _pNodeExp;	//表达式临时存放
	IEvalNode* _pNodeTrue;	
	IEvalNode* _pNodeFalse;
};

//for语句解析器
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

//do..while 语句
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

//while(); 语句
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

//break; 语句
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
//switch 语句
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
	bool			TestCaseParsingOver(const size_t nSrc);//判断当前节点是否结束

	bool			StoreParsingCase();		//存储解析中的case
	bool			RestoreParsingCase();	//恢复解析中的case		
public:
	CEvalParserSwitch(IEvalParser* pParent );
	virtual ~CEvalParserSwitch(void);
private:
	IEvalNode*		_pNodeExp;
	ListCaseSetence	_vCaseSentence;	//<case,statement>
	
	IEvalNode*		_pExpCase;	//解析中的case
	ListEvalNode	_vSetence;	//解析中的语句
};
//语句解析器(分,以{}号包括)
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
	ListEvalNode	_vNodeParsing;		//计算时节点
};

//语句解析器(分,以;号分割)
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

//语句解析器
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

//代码块解析器
//////////////////////////////////////////////////////////////////////////
class CEvalParserSegment
	:public IEvalParser
{
public:
	virtual	bool Init();
	virtual bool Parse(const size_t nSrc );//开始解析 
public:
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	bool	Push(IEvalNode* pNode);
	bool	Pop();
public:
	CEvalParserSegment(IEvalParser* pParent);
	virtual ~CEvalParserSegment(void);
public:
	ListEvalNode	_vNodeParsing;		//计算时节点
};

//Eval总回调接口
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
