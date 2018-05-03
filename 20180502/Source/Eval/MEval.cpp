#include "MEval.h"
#include "MLoger.h"
#include "Eval.h"
#include <typeinfo>

NS_TOOL_FRAME_BEGIN

MEval::MEval(void)
{
// 	ASSERT_LOG_ERROR(_xSingleScope.DeclareVarTypeInfo(TYPE_ARG(double) ,true));
// 	ASSERT_LOG_ERROR(_xSingleScope.DeclareVarTypeInfo(TYPE_ARG(long),true));
// 
// 	ASSERT_LOG_ERROR(_xSingleScope.RegistFunTypeInfo("+",Add_double));
// 	ASSERT_LOG_ERROR(_xSingleScope.RegistFunTypeInfo("+",Add_long));

	//参考链接:http://en.cppreference.com/w/cpp/language/operator_precedence

	//注册优先级的方向
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(1,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(2,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(3,ASSOCIATIVITY_RIGHT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(4,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(5,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(6,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(7,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(8,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(9,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(10,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(11,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(12,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(13,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(14,ASSOCIATIVITY_LEFT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(15,ASSOCIATIVITY_RIGHT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(16,ASSOCIATIVITY_RIGHT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(17,ASSOCIATIVITY_RIGHT));
	ASSERT_LOG_ERROR(RegistPrecedenceAssociativity(18,ASSOCIATIVITY_LEFT));

	//注册操作符配置
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_INCREMENT_SUFFIX,2,ARYOPERATION_1,"自增(后缀)","n++",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DECREMENT_SUFFIX,2,ARYOPERATION_1,"自减(后缀)","n--",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_PARENTHESES,	2,ARYOPERATION_NO,"圆括号",		"()",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_FUNCTION_CALL,	2,ARYOPERATION_NO,"函数调用",	"()",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_INCREMENT_PERFIX,3,ARYOPERATION_1,"自增(前缀)","++n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DECREMENT_PERFIX,3,ARYOPERATION_1,"自减(前缀)","--n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_POSITIVE,		3,ARYOPERATION_1,"一元加号",	"+n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_NEGATIVE,		3,ARYOPERATION_1,"一元减号",	"-n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_INVERTER,		3,ARYOPERATION_1,"逻辑非运算符","!n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MULTIPLY,		5,ARYOPERATION_2,"乘法运算符",	"m*n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DIVIDE,		5,ARYOPERATION_2,"除法运算符",	"m/n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MODULUS,		5,ARYOPERATION_2,"求余运算符",	"m%n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_ADD,			6,ARYOPERATION_2,"加法运算符",	"m+n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_SUBTRACT,		6,ARYOPERATION_2,"减法运算符",	"m-n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_LESS,			8,ARYOPERATION_2,"小于",		"m<n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_LESS_EQUAL,	8,ARYOPERATION_2,"小于等于",	"m<=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_GREATER,		8,ARYOPERATION_2,"大于",		"m>n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_GREATER_EQUAL,	8,ARYOPERATION_2,"大于等于",	"m>=n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_EQUAL,			9,ARYOPERATION_2,"等于",		"m==n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_NOT_EQUAL,		9,ARYOPERATION_2,"不等于",		"m!=n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_AND,			13,ARYOPERATION_2,"逻辑与",		"m&&n",	true));
	
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_OR,			14,ARYOPERATION_2,"逻辑或",		"m||n",	true));
	
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_TERNARY_CONDITIONAL,15,ARYOPERATION_3,"双目运算",	"m ? a:b",true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_ASSIGNMENT,	16,ARYOPERATION_2,"赋值运算符",		"m=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_ADD_ASS,		16,ARYOPERATION_2,"先加，再赋值",	"m+=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_SUB_ASS,		16,ARYOPERATION_2,"先减，再赋值",	"m-=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MUL_ASS,		16,ARYOPERATION_2,"先乘，再赋值",	"m*=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DIV_ASS,		16,ARYOPERATION_2,"先除，再赋值",	"m/=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MOD_ASS,		16,ARYOPERATION_2,"先求余，再赋值",	"m%=n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_COMMA,			18,ARYOPERATION_2,"逗号",		"m,n",	true));

	//ASSERT_LOG_ERROR(Regist(1,"::","全局解析",				"::x",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			false,"::",nullptr));
	//ASSERT_LOG_ERROR(Regist(1,"::","类域解析",				"X::x",		ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			false,"::",nullptr));

	//ASSERT_LOG_ERROR(Regist(2,"++","自增",					"n++",		ASSOCIATIVITY_LEFT,	ARYOPERATION_1,			true,"++",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"--","自减",					"n--",		ASSOCIATIVITY_LEFT,	ARYOPERATION_1,			true,"--",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"()","圆括号",				"",			ASSOCIATIVITY_LEFT,	ARYOPERATION_INVAILD,	true,"()",FunParseParentheses));
	//ASSERT_LOG_ERROR(Regist(2,"()","函数调用",				"rand()",	ASSOCIATIVITY_LEFT,	ARYOPERATION_INVAILD,	true,"()",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"()","类型构造",				"int(ch)",	ASSOCIATIVITY_LEFT,	ARYOPERATION_INVAILD,	true,"()",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"[]","下标运算符",			"a[i]",		ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			true,"[]",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,".",	"直接成员选择运算符",	"s.len",	ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			false,".",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"->",	"间接成员选择运算符",	"p->len",	ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			true,"->",nullptr));

	//ASSERT_LOG_ERROR(Regist(3,"++","自增",					"++n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"++",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"--","自减",					"--n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"--",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"+","一元加号",				"+n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"+",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"-","一元减号",				"-n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"-",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"!","逻辑非运算符",			"!p",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"!",FunParseInverter));
	//ASSERT_LOG_ERROR(Regist(3,"~","按位取反运算符",			"~s",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"~",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"(类型)","类型转换运算符",	"(int)ch",	ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"()",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"*","反引用运算符",			"*p",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"*",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"&","求地址运算符",			"&x",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"&",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"sizeof","长度运算符",		"sizeof(a)",ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			false,"sizeof",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"new","空间分配",				"new int(9)",ASSOCIATIVITY_RIGHT,ARYOPERATION_1,		false,"new",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"delete","空间释放",			"delete p",	ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			false,"delete",nullptr));

	//4	.*   ->*	 Pointer to member	 Left-to-right

	//	ASSERT_LOG_ERROR(Regist(5,"*","乘法运算符",	"m*n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"*",FunParseMultiply));
	//ASSERT_LOG_ERROR(Regist(5,"/","除法运算符",	"m/n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"/",FunParseDivide));
	//ASSERT_LOG_ERROR(Regist(5,"%","求余运算符",	"m%n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"%",FunParseMod));

	//ASSERT_LOG_ERROR(Regist(6,"+","加法运算符",	"m+n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"+",FunParseAdd));
	//ASSERT_LOG_ERROR(Regist(6,"-","减法运算符",	"m-n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"-",FunParseSubtract));

	//ASSERT_LOG_ERROR(Regist(7,"<<","左移运算符","m<<n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"<<",nullptr));
	//ASSERT_LOG_ERROR(Regist(7,">>","右移运算符","m>>n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,">>",nullptr));

	//ASSERT_LOG_ERROR(Regist(8,"<","小于",		"x<y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"<",FunParseLess));
	//ASSERT_LOG_ERROR(Regist(8,"<=","小于等于",	"x<=y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"<=",FunParseLessAndEqual));
	//ASSERT_LOG_ERROR(Regist(8,">","大于",		"x>y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,">",FunParseGreater));
	//ASSERT_LOG_ERROR(Regist(8,">=","大于等于",	"x>=y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,">=",FunParseGreaterAndEqual));

	//ASSERT_LOG_ERROR(Regist(9,"==","等于运算符","x==y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"==",FunParseEqual));
	//ASSERT_LOG_ERROR(Regist(9,"!=","不等于运算符","x!=y",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"!=",FunParseNotEqual));

	//ASSERT_LOG_ERROR(Regist(10,"&","按位与运算符","s&t",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"&",nullptr));

	//ASSERT_LOG_ERROR(Regist(11,"^","按位异或运算符","s^t",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"^",nullptr));

	//ASSERT_LOG_ERROR(Regist(12,"|","按位或运算符","s|t",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"|",nullptr));

	//ASSERT_LOG_ERROR(Regist(13,"&&","逻辑与运算符","u&&v",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"&&",FunParseAnd));

	//ASSERT_LOG_ERROR(Regist(14,"||","逻辑或运算符","u||v",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"||",FunParseOr));

	//ASSERT_LOG_ERROR(Regist(15,"?:","条件运算符","u? x : y",			ASSOCIATIVITY_RIGHT,ARYOPERATION_3,			false,"?",nullptr));

	//ASSERT_LOG_ERROR(Regist(16,"=","赋值运算符","n=22",					ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"+=","先加，再赋值","n+=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"+=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"-=","先减，再赋值","n-=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"-=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"*=","先乘，再赋值","n*=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"*=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"/=","先除，再赋值","n/=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"/=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"%=","先求余，再赋值","n%=22",			ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"%=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,">>=","先左移位，再赋值","n>>=22",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,">>=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"<<=","先右移位，再赋值","n<<=22",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"<<=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"&=","先按位与，再赋值","n&=22",			ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"&=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"^=","先按位异或，再赋值","n^=22",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"^=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"|=","先按位或，再赋值","n|=22",			ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"|=",nullptr));

	//ASSERT_LOG_ERROR(Regist(17,"throw","抛异常","throw exception",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"throw",nullptr));

	//ASSERT_LOG_ERROR(Regist(18,",","逗号运算符","++m,--n",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,",",nullptr));

}

MEval::~MEval(void)
{
}

bool MEval::RegistPrecedenceAssociativity( int nPriority,EAssociativity eAssociativity )
{
	return ToolFrame::Insert(_vPrecedenceAssociativity,nPriority,(int)eAssociativity);
}

const MapIntInt& MEval::GetPriorityAssociativity() const
{
	return _vPrecedenceAssociativity;
}

// bool MEval::CreateParser( CEval* pEval )
// {
// 	ASSERT_LOG_ERROR(pEval);
// 
// 	//()
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserParentheses(pEval)));
// 
// 	//基本操作符 + - (正负) + - (加减) * / % < <= > >= == != && !=	
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserSimpleBaseOperator(pEval)));
// 
// 	//数字
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserNumber(pEval)));
// 
// 	//变量
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserVariable(pEval)));
// 
// 	//函数
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserFunction(pEval)));
// 
// 	return true;
// }

bool MEval::RegistOperationConfig( EOperation eOperation,int nPrecedence,EAryOperation eAryOperation,const std::string& sDescription,const std::string& sExample,bool bOverLoading )
{
	CEvalOperationConfig* pOperationConfig = new CEvalOperationConfig();
	ASSERT_LOG_ERROR(pOperationConfig);

	pOperationConfig->SetOperation(eOperation);
	pOperationConfig->SetPrecedence(nPrecedence);
	pOperationConfig->SetAryOperation(eAryOperation);
	pOperationConfig->SetDescription(sDescription);
	pOperationConfig->SetExample(sExample);
	pOperationConfig->SetOverLoading(bOverLoading);

	return ToolFrame::Insert(_vOperationConfig,(int)eOperation,pOperationConfig);
}
const MapEvalOperationConfig& MEval::GetOperationConfig() const
{
	return _vOperationConfig;
}

int MEval::GetPrecedenceMin() 
{
	return 1;
}

int MEval::GetPrecedenceMax() 
{
	return 18;
}

double MEval::Add_double( double fSrc1,double fSrc2 )
{
	return fSrc1 + fSrc2;
}

long MEval::Add_long( long nSrc1,long nSrc2 )
{
	return nSrc1 + nSrc2;
}

NS_TOOL_FRAME_END