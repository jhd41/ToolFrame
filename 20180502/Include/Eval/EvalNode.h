#pragma once
#include "Macro.h"
#include "EvalTypeInfo.h"

NS_TOOL_FRAME_BEGIN

class CEval;				//ִ����
class CEvalOperationConfig;	//���������ñ�
class IEvalNode;			//�ڵ����
class CEvalOperator;		//�������ڵ�

typedef std::list<IEvalNode*>							ListEvalNode;
typedef std::map<int,CEvalOperationConfig*>				MapEvalOperationConfig;
typedef std::vector<CEvalOperationConfig*>				VectorEvalOperationConfig;
typedef std::map<int,VectorEvalOperationConfig>			MapEvalIntVectorOperationConfig;
typedef std::pair<IEvalNode*,IEvalNode*>				PairEvalNode;
typedef std::pair<IEvalNode*,ListEvalNode>				PairCaseSetence;
typedef	std::list<PairCaseSetence>						ListCaseSetence;

//��Ϸ�ʽ
enum EAssociativity{
	ASSOCIATIVITY_INVAILD=INVALID_ID,
	ASSOCIATIVITY_LEFT,
	ASSOCIATIVITY_RIGHT,
	ASSOCIATIVITY_MAX,
};

//n-Ԫ������
enum EAryOperation{
	ARYOPERATION_INVAILD=INVALID_ID,
	ARYOPERATION_NO,
	ARYOPERATION_1,
	ARYOPERATION_2,
	ARYOPERATION_3,
	ARYOPERATION_MAX,
};

//��������
enum EOperation{
	OPERATION_INVAILD = INVALID_ID,

	//1
	OPERATION_SPACE,				//ȫ�ֽ���	������� ::x X::x
	
	//2
	OPERATION_INCREMENT_SUFFIX,		//����(��׺)n++
	OPERATION_DECREMENT_SUFFIX,		//�Լ�(��׺)n--
	OPERATION_PARENTHESES,			//Բ����	()
	OPERATION_FUNCTION_CALL,		//��������	rand()
	OPERATION_TYPE_CONSTRUCTION,	//���͹���	int(ch)
	OPERATION_ARRAY_SUBSCRIPTING ,	//�±������a[i]

	//3
	OPERATION_INCREMENT_PERFIX,		//����(ǰ׺)++n
	OPERATION_DECREMENT_PERFIX,		//�Լ�(ǰ׺)--n
	OPERATION_POSITIVE,				//һԪ�Ӻ�	+N
	OPERATION_NEGATIVE,				//һԪ����	-N
	OPERATION_INVERTER,				//�߼��������	!N

	//5
	OPERATION_MULTIPLY,				//�˷������M*N
	OPERATION_DIVIDE,				//���������m/n
	OPERATION_MODULUS,				//���������m%n

	//6
	OPERATION_ADD,					//�ӷ������m+n
	OPERATION_SUBTRACT,				//���������m-n

	//8
	OPERATION_LESS,					//С�ڱȽϷ�M<N
	OPERATION_LESS_EQUAL,			//С�ڵ��ڱȽϷ�M<=N
	OPERATION_GREATER,				//���ڱȽϷ�M<N
	OPERATION_GREATER_EQUAL,		//���ڵ��ڱȽϷ�M>=N

	//9
	OPERATION_EQUAL,				//���ڱȽϷ�M==N
	OPERATION_NOT_EQUAL,			//�����ڱȽϷ�M!=N

	//13
	OPERATION_AND,				//�߼��������M&&N

	//14
	OPERATION_OR,				//�߼��������M||N

	//15
	OPERATION_TERNARY_CONDITIONAL,//˫Ŀ����� ? : 

	//16
	OPERATION_ASSIGNMENT,		//��ֵ�����
	OPERATION_ADD_ASS,			//�ȼӣ��ٸ�ֵ		m+=n
	OPERATION_SUB_ASS,			//�ȼ����ٸ�ֵ		m-=n
	OPERATION_MUL_ASS,			//�ȳˣ��ٸ�ֵ		m*=n
	OPERATION_DIV_ASS,			//�ȳ����ٸ�ֵ		m/=n
	OPERATION_MOD_ASS,			//�����࣬�ٸ�ֵ	m%=n

	//18
	OPERATION_COMMA,			//����

	OPERATION_MAX,
};

//���������ñ�
class CEvalOperationConfig{
	CFIELD_ENUM(EOperation,Operation);		//������
	CFIELD_INT(Precedence);					//���ȼ�
	CFIELD_ENUM(EAryOperation,AryOperation);//n-Ԫ������
	CFIELD_STRING(Description);				//����
	CFIELD_STRING(Example);					//ʾ��
	CFIELD_BOOL(OverLoading);				//������
};

class CEvalOperator;
//�ڵ�
class IEvalNode{
public:
	virtual	bool SetScope(CScopeInfo* pScope);
	virtual	CScopeInfo* GetScope()const;
	//�ӿڶ���
public:
	virtual IEvalNode*					Clone() const =0;		//��¡,������µĶ���
	virtual	double						GetReturnValue() const=0;
public:
	virtual const CEvalOperator* const	ToOperator()const;
	virtual	CEvalOperator*				ToOperator();
protected:
	virtual bool						IsTrue(IEvalNode* pNode)const;
protected:
	bool	Copy(const IEvalNode* pNode);//����
public:
	IEvalNode(CEval* pEval);
	virtual ~IEvalNode(void);
private:
	CFIELD_PTR(CEval*,Eval,p);
	CFIELD_BOOL(PrasingDone);					//�Ƿ�������
private:
	VectorString _vScopeName;
};

//������
class CEvalOperator
	:public IEvalNode
{
public:
	EOperation		GetOperation()const;	//��������
	EAssociativity	GetAssociativity()const;//��Ϸ�ʽ
	EAryOperation	GetAryOperation()const;//NԪ������
	const CEvalOperationConfig*	GetOperationConfig()const;
public:
	virtual IEvalNode*					Clone()const;
	virtual	double						GetReturnValue() const;

	 //ʵ�ֽӿ�
public:
	virtual	const CEvalOperator* const	ToOperator()const;
	virtual	CEvalOperator*				ToOperator();
protected:
	bool						Copy(const CEvalOperator* pNode);//����

	void						SetOperation(EOperation eOperation);
private:
	double						Assignment(IEvalNode* pNode , double fValue)const;//��ֵ
public:
	CEvalOperator(CEval* pEval,EOperation eOperation);
	virtual ~CEvalOperator();
private:
	//һԪ������
	CFIELD_PTR(IEvalNode*,NodeSingle,p);

	//��Ԫ������
	CFIELD_PTR(IEvalNode*,NodeLeft,p);
	CFIELD_PTR(IEvalNode*,NodeRight,p);
private:
	const CEvalOperationConfig* _pOperationConfig;
};

//����
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
	CFIELD_PTR(const CFunTypeInfo*,Function,ref);//���ú���
private:
	ListEvalNode _vNodeArgs;
};

//��������
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
	CFIELD_STRING(VarType);//��������
	CFIELD_REF(VectorVar,Vars,v);//����
};

//�սڵ�
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

//���ֽڵ�
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

//�����ڵ�
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

//���ڵ�
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
//If Else���
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
	IEvalNode* _pNodeExp;	//���ʽ��ʱ���
	IEvalNode* _pNodeTrue;	
	IEvalNode* _pNodeFalse;
};

//�����ڵ�
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

//for���
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

//do..while���
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

//while���
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
	CFIELD_BOOL(IsBegin);//�Ƿ��� ? �� falseΪ :��
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
