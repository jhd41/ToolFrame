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

	//�ο�����:http://en.cppreference.com/w/cpp/language/operator_precedence

	//ע�����ȼ��ķ���
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

	//ע�����������
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_INCREMENT_SUFFIX,2,ARYOPERATION_1,"����(��׺)","n++",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DECREMENT_SUFFIX,2,ARYOPERATION_1,"�Լ�(��׺)","n--",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_PARENTHESES,	2,ARYOPERATION_NO,"Բ����",		"()",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_FUNCTION_CALL,	2,ARYOPERATION_NO,"��������",	"()",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_INCREMENT_PERFIX,3,ARYOPERATION_1,"����(ǰ׺)","++n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DECREMENT_PERFIX,3,ARYOPERATION_1,"�Լ�(ǰ׺)","--n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_POSITIVE,		3,ARYOPERATION_1,"һԪ�Ӻ�",	"+n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_NEGATIVE,		3,ARYOPERATION_1,"һԪ����",	"-n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_INVERTER,		3,ARYOPERATION_1,"�߼��������","!n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MULTIPLY,		5,ARYOPERATION_2,"�˷������",	"m*n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DIVIDE,		5,ARYOPERATION_2,"���������",	"m/n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MODULUS,		5,ARYOPERATION_2,"���������",	"m%n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_ADD,			6,ARYOPERATION_2,"�ӷ������",	"m+n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_SUBTRACT,		6,ARYOPERATION_2,"���������",	"m-n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_LESS,			8,ARYOPERATION_2,"С��",		"m<n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_LESS_EQUAL,	8,ARYOPERATION_2,"С�ڵ���",	"m<=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_GREATER,		8,ARYOPERATION_2,"����",		"m>n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_GREATER_EQUAL,	8,ARYOPERATION_2,"���ڵ���",	"m>=n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_EQUAL,			9,ARYOPERATION_2,"����",		"m==n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_NOT_EQUAL,		9,ARYOPERATION_2,"������",		"m!=n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_AND,			13,ARYOPERATION_2,"�߼���",		"m&&n",	true));
	
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_OR,			14,ARYOPERATION_2,"�߼���",		"m||n",	true));
	
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_TERNARY_CONDITIONAL,15,ARYOPERATION_3,"˫Ŀ����",	"m ? a:b",true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_ASSIGNMENT,	16,ARYOPERATION_2,"��ֵ�����",		"m=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_ADD_ASS,		16,ARYOPERATION_2,"�ȼӣ��ٸ�ֵ",	"m+=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_SUB_ASS,		16,ARYOPERATION_2,"�ȼ����ٸ�ֵ",	"m-=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MUL_ASS,		16,ARYOPERATION_2,"�ȳˣ��ٸ�ֵ",	"m*=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_DIV_ASS,		16,ARYOPERATION_2,"�ȳ����ٸ�ֵ",	"m/=n",	true));
	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_MOD_ASS,		16,ARYOPERATION_2,"�����࣬�ٸ�ֵ",	"m%=n",	true));

	ASSERT_LOG_ERROR(RegistOperationConfig(OPERATION_COMMA,			18,ARYOPERATION_2,"����",		"m,n",	true));

	//ASSERT_LOG_ERROR(Regist(1,"::","ȫ�ֽ���",				"::x",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			false,"::",nullptr));
	//ASSERT_LOG_ERROR(Regist(1,"::","�������",				"X::x",		ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			false,"::",nullptr));

	//ASSERT_LOG_ERROR(Regist(2,"++","����",					"n++",		ASSOCIATIVITY_LEFT,	ARYOPERATION_1,			true,"++",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"--","�Լ�",					"n--",		ASSOCIATIVITY_LEFT,	ARYOPERATION_1,			true,"--",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"()","Բ����",				"",			ASSOCIATIVITY_LEFT,	ARYOPERATION_INVAILD,	true,"()",FunParseParentheses));
	//ASSERT_LOG_ERROR(Regist(2,"()","��������",				"rand()",	ASSOCIATIVITY_LEFT,	ARYOPERATION_INVAILD,	true,"()",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"()","���͹���",				"int(ch)",	ASSOCIATIVITY_LEFT,	ARYOPERATION_INVAILD,	true,"()",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"[]","�±������",			"a[i]",		ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			true,"[]",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,".",	"ֱ�ӳ�Աѡ�������",	"s.len",	ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			false,".",nullptr));
	//ASSERT_LOG_ERROR(Regist(2,"->",	"��ӳ�Աѡ�������",	"p->len",	ASSOCIATIVITY_LEFT,	ARYOPERATION_2,			true,"->",nullptr));

	//ASSERT_LOG_ERROR(Regist(3,"++","����",					"++n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"++",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"--","�Լ�",					"--n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"--",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"+","һԪ�Ӻ�",				"+n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"+",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"-","һԪ����",				"-n",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"-",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"!","�߼��������",			"!p",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"!",FunParseInverter));
	//ASSERT_LOG_ERROR(Regist(3,"~","��λȡ�������",			"~s",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"~",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"(����)","����ת�������",	"(int)ch",	ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"()",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"*","�����������",			"*p",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"*",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"&","���ַ�����",			"&x",		ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			true,"&",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"sizeof","���������",		"sizeof(a)",ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			false,"sizeof",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"new","�ռ����",				"new int(9)",ASSOCIATIVITY_RIGHT,ARYOPERATION_1,		false,"new",nullptr));
	//ASSERT_LOG_ERROR(Regist(3,"delete","�ռ��ͷ�",			"delete p",	ASSOCIATIVITY_RIGHT,ARYOPERATION_1,			false,"delete",nullptr));

	//4	.*   ->*	 Pointer to member	 Left-to-right

	//	ASSERT_LOG_ERROR(Regist(5,"*","�˷������",	"m*n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"*",FunParseMultiply));
	//ASSERT_LOG_ERROR(Regist(5,"/","���������",	"m/n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"/",FunParseDivide));
	//ASSERT_LOG_ERROR(Regist(5,"%","���������",	"m%n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"%",FunParseMod));

	//ASSERT_LOG_ERROR(Regist(6,"+","�ӷ������",	"m+n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"+",FunParseAdd));
	//ASSERT_LOG_ERROR(Regist(6,"-","���������",	"m-n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"-",FunParseSubtract));

	//ASSERT_LOG_ERROR(Regist(7,"<<","���������","m<<n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"<<",nullptr));
	//ASSERT_LOG_ERROR(Regist(7,">>","���������","m>>n",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,">>",nullptr));

	//ASSERT_LOG_ERROR(Regist(8,"<","С��",		"x<y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"<",FunParseLess));
	//ASSERT_LOG_ERROR(Regist(8,"<=","С�ڵ���",	"x<=y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"<=",FunParseLessAndEqual));
	//ASSERT_LOG_ERROR(Regist(8,">","����",		"x>y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,">",FunParseGreater));
	//ASSERT_LOG_ERROR(Regist(8,">=","���ڵ���",	"x>=y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,">=",FunParseGreaterAndEqual));

	//ASSERT_LOG_ERROR(Regist(9,"==","���������","x==y",					ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"==",FunParseEqual));
	//ASSERT_LOG_ERROR(Regist(9,"!=","�����������","x!=y",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"!=",FunParseNotEqual));

	//ASSERT_LOG_ERROR(Regist(10,"&","��λ�������","s&t",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"&",nullptr));

	//ASSERT_LOG_ERROR(Regist(11,"^","��λ��������","s^t",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"^",nullptr));

	//ASSERT_LOG_ERROR(Regist(12,"|","��λ�������","s|t",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"|",nullptr));

	//ASSERT_LOG_ERROR(Regist(13,"&&","�߼��������","u&&v",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"&&",FunParseAnd));

	//ASSERT_LOG_ERROR(Regist(14,"||","�߼��������","u||v",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,"||",FunParseOr));

	//ASSERT_LOG_ERROR(Regist(15,"?:","���������","u? x : y",			ASSOCIATIVITY_RIGHT,ARYOPERATION_3,			false,"?",nullptr));

	//ASSERT_LOG_ERROR(Regist(16,"=","��ֵ�����","n=22",					ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"+=","�ȼӣ��ٸ�ֵ","n+=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"+=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"-=","�ȼ����ٸ�ֵ","n-=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"-=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"*=","�ȳˣ��ٸ�ֵ","n*=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"*=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"/=","�ȳ����ٸ�ֵ","n/=22",				ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"/=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"%=","�����࣬�ٸ�ֵ","n%=22",			ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"%=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,">>=","������λ���ٸ�ֵ","n>>=22",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,">>=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"<<=","������λ���ٸ�ֵ","n<<=22",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"<<=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"&=","�Ȱ�λ�룬�ٸ�ֵ","n&=22",			ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"&=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"^=","�Ȱ�λ����ٸ�ֵ","n^=22",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"^=",nullptr));
	//ASSERT_LOG_ERROR(Regist(16,"|=","�Ȱ�λ���ٸ�ֵ","n|=22",			ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"|=",nullptr));

	//ASSERT_LOG_ERROR(Regist(17,"throw","���쳣","throw exception",		ASSOCIATIVITY_RIGHT,ARYOPERATION_2,			true,"throw",nullptr));

	//ASSERT_LOG_ERROR(Regist(18,",","���������","++m,--n",				ASSOCIATIVITY_LEFT,ARYOPERATION_2,			true,",",nullptr));

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
// 	//���������� + - (����) + - (�Ӽ�) * / % < <= > >= == != && !=	
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserSimpleBaseOperator(pEval)));
// 
// 	//����
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserNumber(pEval)));
// 
// 	//����
// 	ASSERT_LOG_ERROR(pEval->AddParser(new CEvalParserVariable(pEval)));
// 
// 	//����
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