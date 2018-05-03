#pragma once
#include "Macro.h"
#include "EvalTypeInfo.h"

NS_TOOL_FRAME_BEGIN

class CEval;				//执行器
class CEvalOperationConfig;	//操作符配置表
class IEvalNode;			//节点基类
class CEvalOperator;		//操作符节点

typedef std::list<IEvalNode*>							ListEvalNode;
typedef std::map<int,CEvalOperationConfig*>				MapEvalOperationConfig;
typedef std::vector<CEvalOperationConfig*>				VectorEvalOperationConfig;
typedef std::map<int,VectorEvalOperationConfig>			MapEvalIntVectorOperationConfig;
typedef std::pair<IEvalNode*,IEvalNode*>				PairEvalNode;
typedef std::pair<IEvalNode*,ListEvalNode>				PairCaseSetence;
typedef	std::list<PairCaseSetence>						ListCaseSetence;

//结合方式
enum EAssociativity{
	ASSOCIATIVITY_INVAILD=INVALID_ID,
	ASSOCIATIVITY_LEFT,
	ASSOCIATIVITY_RIGHT,
	ASSOCIATIVITY_MAX,
};

//n-元操作符
enum EAryOperation{
	ARYOPERATION_INVAILD=INVALID_ID,
	ARYOPERATION_NO,
	ARYOPERATION_1,
	ARYOPERATION_2,
	ARYOPERATION_3,
	ARYOPERATION_MAX,
};

//操作类型
enum EOperation{
	OPERATION_INVAILD = INVALID_ID,

	//1
	OPERATION_SPACE,				//全局解析	类域解析 ::x X::x
	
	//2
	OPERATION_INCREMENT_SUFFIX,		//自增(后缀)n++
	OPERATION_DECREMENT_SUFFIX,		//自减(后缀)n--
	OPERATION_PARENTHESES,			//圆括号	()
	OPERATION_FUNCTION_CALL,		//函数调用	rand()
	OPERATION_TYPE_CONSTRUCTION,	//类型构造	int(ch)
	OPERATION_ARRAY_SUBSCRIPTING ,	//下标运算符a[i]

	//3
	OPERATION_INCREMENT_PERFIX,		//自增(前缀)++n
	OPERATION_DECREMENT_PERFIX,		//自减(前缀)--n
	OPERATION_POSITIVE,				//一元加号	+N
	OPERATION_NEGATIVE,				//一元减号	-N
	OPERATION_INVERTER,				//逻辑非运算符	!N

	//5
	OPERATION_MULTIPLY,				//乘法运算符M*N
	OPERATION_DIVIDE,				//除法运算符m/n
	OPERATION_MODULUS,				//求余运算符m%n

	//6
	OPERATION_ADD,					//加法运算符m+n
	OPERATION_SUBTRACT,				//减法运算符m-n

	//8
	OPERATION_LESS,					//小于比较符M<N
	OPERATION_LESS_EQUAL,			//小于等于比较符M<=N
	OPERATION_GREATER,				//大于比较符M<N
	OPERATION_GREATER_EQUAL,		//大于等于比较符M>=N

	//9
	OPERATION_EQUAL,				//等于比较符M==N
	OPERATION_NOT_EQUAL,			//不等于比较符M!=N

	//13
	OPERATION_AND,				//逻辑与运算符M&&N

	//14
	OPERATION_OR,				//逻辑或运算符M||N

	//15
	OPERATION_TERNARY_CONDITIONAL,//双目运算符 ? : 

	//16
	OPERATION_ASSIGNMENT,		//赋值运算符
	OPERATION_ADD_ASS,			//先加，再赋值		m+=n
	OPERATION_SUB_ASS,			//先减，再赋值		m-=n
	OPERATION_MUL_ASS,			//先乘，再赋值		m*=n
	OPERATION_DIV_ASS,			//先除，再赋值		m/=n
	OPERATION_MOD_ASS,			//先求余，再赋值	m%=n

	//18
	OPERATION_COMMA,			//逗号

	OPERATION_MAX,
};

//操作符配置表
class CEvalOperationConfig{
	CFIELD_ENUM(EOperation,Operation);		//操作符
	CFIELD_INT(Precedence);					//优先级
	CFIELD_ENUM(EAryOperation,AryOperation);//n-元操作符
	CFIELD_STRING(Description);				//描述
	CFIELD_STRING(Example);					//示例
	CFIELD_BOOL(OverLoading);				//重载性
};

class CEvalOperator;
//节点
class IEvalNode{
public:
	virtual	bool SetScope(CScopeInfo* pScope);
	virtual	CScopeInfo* GetScope()const;
	//接口定义
public:
	virtual IEvalNode*					Clone() const =0;		//克隆,会产生新的对象
	virtual	double						GetReturnValue() const=0;
public:
	virtual const CEvalOperator* const	ToOperator()const;
	virtual	CEvalOperator*				ToOperator();
protected:
	virtual bool						IsTrue(IEvalNode* pNode)const;
protected:
	bool	Copy(const IEvalNode* pNode);//拷贝
public:
	IEvalNode(CEval* pEval);
	virtual ~IEvalNode(void);
private:
	CFIELD_PTR(CEval*,Eval,p);
	CFIELD_BOOL(PrasingDone);					//是否解析完成
private:
	VectorString _vScopeName;
};

//操作符
class CEvalOperator
	:public IEvalNode
{
public:
	EOperation		GetOperation()const;	//操作类型
	EAssociativity	GetAssociativity()const;//结合方式
	EAryOperation	GetAryOperation()const;//N元操作符
	const CEvalOperationConfig*	GetOperationConfig()const;
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;

	 //实现接口
public:
	virtual	const CEvalOperator* const	ToOperator()const;
	virtual	CEvalOperator*				ToOperator();
protected:
	bool						Copy(const CEvalOperator* pNode);//拷贝

	void						SetOperation(EOperation eOperation);
private:
	double						Assignment(IEvalNode* pNode , double fValue)const;//赋值
public:
	CEvalOperator(CEval* pEval,EOperation eOperation);
	virtual ~CEvalOperator();
private:
	//一元操作符
	CFIELD_PTR(IEvalNode*,NodeSingle,p);

	//二元操作符
	CFIELD_PTR(IEvalNode*,NodeLeft,p);
	CFIELD_PTR(IEvalNode*,NodeRight,p);
private:
	const CEvalOperationConfig* _pOperationConfig;
};

//函数
class CEvalFunction
	:public CEvalOperator
{
public:
	void	SetArgs(ListEvalNode& vNodeArgs);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalFunction* pNode );
public:
	CEvalFunction(CEval* pEval);
	virtual ~CEvalFunction();
public:
	CFIELD_PTR(const CFunTypeInfo*,Function,ref);//设置函数
private:
	ListEvalNode _vNodeArgs;
};

//变量声明
class CEvalDeclareVariable
	:public IEvalNode
{
public:
	typedef std::pair<std::string,IEvalNode*>	PairVar;
	typedef std::vector<PairVar>				VectorVar;
public:
	bool	InsertVar(const std::string& sVarName,IEvalNode* pNode);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalDeclareVariable* pNode );
public:
	CEvalDeclareVariable(CEval* pEval);
	virtual ~CEvalDeclareVariable();
private:
	CFIELD_STRING(VarType);//变量类型
	CFIELD_REF(VectorVar,Vars,v);//变量
};

//空节点
class CEvalNone
	:public IEvalNode
{
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalNone* pNode );
public:
	CEvalNone(CEval* pEval);
	virtual ~CEvalNone();
};

//数字节点
class CEvalNumber
	:public IEvalNode
{
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalNumber* pNode );
public:
	CEvalNumber(CEval* pEval);
	virtual ~CEvalNumber();
public:
	CFIELD_DOUBLE(Value);
};

//变量节点
class CEvalVariable
	:public IEvalNode
{
public:
	bool								SetVarName(const std::string& sVarName);
	CRefTypeInfo*						GetVarRefType()const;
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalVariable* pNode );
public:
	CEvalVariable(CEval* pEval);
	virtual ~CEvalVariable();
public:
	std::string		_sVarName;
};

//语句节点
class CEvalSegment
	:public IEvalNode
{
public:
	bool SetNode(ListEvalNode& vNode);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalSegment* pNode );
public:
	CEvalSegment(CEval* pEval);
	virtual ~CEvalSegment();
public:
	ListEvalNode _vNode;
};
//If Else语句
class CEvalIfElse
	:public IEvalNode
{
public:
	void SetNode(IEvalNode* pNodeExp,IEvalNode* pNodeTrue,IEvalNode* pNodeFalse);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalIfElse* pNode );
public:
	CEvalIfElse(CEval* pEval);
	virtual ~CEvalIfElse();
public:
	IEvalNode* _pNodeExp;	//表达式临时存放
	IEvalNode* _pNodeTrue;	
	IEvalNode* _pNodeFalse;
};

//多语句节点
class CEvalBrace
	:public IEvalNode
{
public:
	bool SetNode(ListEvalNode& vNode,const std::string& sScopeName);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalBrace* pNode );
public:
	CEvalBrace(CEval* pEval);
	virtual ~CEvalBrace();
public:
	ListEvalNode	_vNode;
	std::string		_sScopeName;
};

//for语句
class CEvalFor
	:public IEvalNode
{
public:
	bool SetNode(const std::string& sNewScopeName,IEvalNode* pNodeExp1,IEvalNode* pNodeExp2,IEvalNode* pNodeExp3,IEvalNode* pNodeLoop);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalFor* pNode );
	bool								IsExpTrue(IEvalNode* pNode)const;
public:
	CEvalFor(CEval* pEval);
	virtual ~CEvalFor();
private:
	IEvalNode* _pNodeExp1;
	IEvalNode* _pNodeExp2;
	IEvalNode* _pNodeExp3;
	IEvalNode* _pNodeLoop;
	std::string _sNewScopeName;
};

//do..while语句
class CEvalDoWhile
	:public IEvalNode
{
public:
	bool SetNode(const std::string& sNewScopeName,IEvalNode* pNodeExp,IEvalNode* pNodeLoop);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalDoWhile* pNode );
public:
	CEvalDoWhile(CEval* pEval);
	virtual ~CEvalDoWhile();
private:
	IEvalNode*	_pNodeExp;
	IEvalNode*	_pNodeLoop;
	std::string _sNewScopeName;
};

//while语句
class CEvalWhile
	:public IEvalNode
{
public:
	bool SetNode(const std::string& sNewScopeName, IEvalNode* pNodeExp,IEvalNode* pNodeLoop);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalWhile* pNode );
public:
	CEvalWhile(CEval* pEval);
	virtual ~CEvalWhile();
private:
	IEvalNode*	_pNodeExp;
	IEvalNode*	_pNodeLoop;
	std::string _sNewScopeName;
};

//? :
class CEvalTernary
	:public CEvalOperator
{
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalTernary* pNode );
public:
	CEvalTernary(CEval* pEval);
	virtual ~CEvalTernary();
public:
	CFIELD_BOOL(IsBegin);//是否是 ? 号 false为 :号
	CFIELD_PTR(IEvalNode*,NodeExp,p);
	CFIELD_PTR(IEvalNode*,NodeTrue,p);
	CFIELD_PTR(IEvalNode*,NodeFalse,p);
};

//break
class CEvalbreak
	:public IEvalNode
{
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalbreak* pNode );
public:
	CEvalbreak(CEval* pEval);
	virtual ~CEvalbreak();
};

//switch
class CEvalSwitch
	:public IEvalNode
{
public:
	bool SetNode(IEvalNode* pExp,const ListCaseSetence& vCaseSentence,ListEvalNode& vDefault);
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;
private:
	bool								Copy( const CEvalSwitch* pNode );
	bool								Clone(ListCaseSetence& vDes,const ListCaseSetence& vSrc);
	bool								Destory(ListCaseSetence& vCase);
	bool								RunSentence(const ListEvalNode& vSentence)const;
public:
	static bool							FindCase(ListCaseSetence::const_iterator& itr,const double& fCase);
public:
	CEvalSwitch(CEval* pEval);
	virtual ~CEvalSwitch();
private:
	IEvalNode*		_pNodeExp;
	ListCaseSetence	_vCaseSentence;	//<case,statement>
	ListEvalNode	_vSetenceDefault;		
};

NS_TOOL_FRAME_END
