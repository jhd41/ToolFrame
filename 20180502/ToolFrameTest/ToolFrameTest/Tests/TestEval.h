#pragma once
#include "Eval.h"
double Function(double fArg){
	return fArg + 1.0;
};

class TestFunction{
public:
	double Function(double fArg){
		return fArg + 2.0;
	};
public:
	TestFunction(){
		int a=0;
	}
	virtual ~TestFunction(){
		int a=0;
	}
};

double FunctionVoid(){
	return 1.0;
}

double FunctionArg2(double fArg1,double fArg2){
	return fArg1 + fArg2;
}

double Assert(double fArg1){
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(fArg1,1.0f));
	return fArg1;
}

TestFunction evalTestObj;
bool InitEval(CEval& eval){
	ASSERT_LOG_ERROR(eval.GetDefaultScope().DeclareVar("double","nIndex",3));
	ASSERT_LOG_ERROR(eval.GetDefaultScope().DeclareFun("Function",		Function));						// fArg + 1.0;
	ASSERT_LOG_ERROR(eval.GetDefaultScope().DeclareFun("FunctionTest",	&TestFunction::Function,&evalTestObj));	// fArg + 2.0;
	ASSERT_LOG_ERROR(eval.GetDefaultScope().DeclareFun("FunctionVoid",	FunctionVoid));					// 1.0;
	ASSERT_LOG_ERROR(eval.GetDefaultScope().DeclareFun("FunctionArg2",	FunctionArg2));					// fArg1 + fArg2;
	ASSERT_LOG_ERROR(eval.GetDefaultScope().DeclareFun("Assert",		Assert));							// 打印结果。必须为真
	return true;
}

bool TestEvalExpression(const std::string& sExp,double fValue){
	CEval eval;
	ASSERT_LOG_ERROR(InitEval(eval));
	UINT64 uTimeBegin = ToolFrame::GetNowTimeMill();
	if (!eval.Expression(sExp))return false;

	UINT64 uTimePrase=ToolFrame::GetNowTimeMill();
	if (eval.GetReturnValue() != fValue)return false;

	UINT64 uTimeExecute = ToolFrame::GetNowTimeMill();

	LOG_SYSTEM("解析表达式:耗时毫秒"<<"("<<uTimePrase - uTimeBegin <<","<<uTimeExecute-uTimePrase<<")" <<" 表达式:"<<sExp);
	return true;
}
bool TestEvalScript(const std::string& sScript){
	CEval eval;
	ASSERT_LOG_ERROR(InitEval(eval));

	UINT64 uTimeBegin = ToolFrame::GetNowTimeMill();
	if (!eval.Script(sScript))return false;

	UINT64 uTimePrase=ToolFrame::GetNowTimeMill();
	ASSERT_LOG_ERROR(eval.Execute());

	UINT64 uTimeExecute = ToolFrame::GetNowTimeMill();

	LOG_SYSTEM("解析脚本:耗时毫秒"<<"("<<uTimePrase - uTimeBegin <<","<<uTimeExecute-uTimePrase<<")" <<" 脚本:"<<sScript);
	return true;
}
#define TEST_EVAL(exp) ASSERT_LOG_ERROR(TestEvalExpression(#exp,exp))

bool TestEvalExpression(){
	TEST_EVAL(- 1);
	TEST_EVAL( - - - - - - - 1);
	TEST_EVAL(6+7);
	TEST_EVAL(-4 + - - 7);
	TEST_EVAL((6+(7-1))+(- - - - - - - - - -1)*8 + + + + + + + 6.1 * 4 / 0.6+3-1.3 + (-4 + - - 7) % 3);

	ASSERT_LOG_ERROR(TestEvalExpression("nIndex",3));
	ASSERT_LOG_ERROR(TestEvalExpression("Function(nIndex) + 5",9));
	ASSERT_LOG_ERROR(TestEvalExpression("FunctionVoid() + Function(nIndex)",5));
	ASSERT_LOG_ERROR(TestEvalExpression("FunctionArg2(nIndex,3)",6));
	ASSERT_LOG_ERROR(TestEvalExpression("FunctionArg2(nIndex,nIndex + 4)",10));
	ASSERT_LOG_ERROR(TestEvalExpression("FunctionArg2(FunctionVoid(),FunctionArg2(Function(nIndex),1))",6));

	ASSERT_LOG_ERROR(TestEvalExpression("FunctionArg2(nIndex,3 *4 + 2%(4 - -1) +	FunctionTest(nIndex) - 1) - 5 + (nIndex + Function	(	nIndex)) % 2 + FunctionTest (1) + FunctionVoid() ",21.0f));
	ASSERT_LOG_ERROR(TestEvalExpression("3 > 2 ? 4:5",4));
	return true;
}

bool TestEvalScript(){
	//定义变量
	ASSERT_LOG_ERROR(TestEvalScript("double nFlat=0;"));
	//同时定义多个变量并赋初始值
	ASSERT_LOG_ERROR(TestEvalScript("double nFlat=0,nVar1 = 1+3;"));
	//使用脚本定义 和 程序定义的的变量
	ASSERT_LOG_ERROR(TestEvalScript("double nVar1=4,nVar2=nIndex%2;FunctionArg2(nVar1,nVar2);"));
	//赋值运算
	ASSERT_LOG_ERROR(TestEvalScript("nIndex +=1;"));
	//新定义变量和程序定义变量进行 高度复杂运算
	ASSERT_LOG_ERROR(TestEvalScript("double nVar1=4,nVar2=nIndex%2;FunctionArg2(nVar1,nVar2) + FunctionArg2(nIndex,3 *4 + 2%(4 - -1) +	FunctionTest(nIndex) - 1) - 5 + (nIndex + Function	(	nIndex)) % 2 + FunctionTest (1) + FunctionVoid() ; "));
	//if..else..的测试
	ASSERT_LOG_ERROR(TestEvalScript("if(1);if(3 == nIndex)nIndex -= 1;else nIndex +=1;Assert(2 == nIndex);"));
	//多个if语句的叠加，else的匹配 以及 不写else语句块
	ASSERT_LOG_ERROR(TestEvalScript("if(1)if(3 == nIndex)nIndex -= 1;else nIndex +=1;if(nIndex == 2){ nIndex+=1;nIndex+=2;}Assert(5 == nIndex);"));
	//多个作用域下的同样名称变量反复定义
	ASSERT_LOG_ERROR(TestEvalScript("{double nTest=1;}{double nTest = 1;}"));
	//for语句
	ASSERT_LOG_ERROR(TestEvalScript("double nSum;for(double nCounter=0;nCounter<3;nCounter += 1)nSum+=1;Assert(3 == nSum);"));
	//for语句的叠加使用
	ASSERT_LOG_ERROR(TestEvalScript("double nSum;for(double nCounter=0;nCounter<3;nCounter += 1)for(double n=0;n<3;n += 1)nSum+=1;Assert(9 == nSum);"));
	//for语句 循环体中定义变量
	ASSERT_LOG_ERROR(TestEvalScript("for(double nCounter=0;nCounter<2;nCounter += 1)double nSum;"));
	//do..while
	ASSERT_LOG_ERROR(TestEvalScript("double uSum=0;do{ uSum +=1;}while(uSum < 3);Assert(3 == uSum);"));
	//while ... do
	ASSERT_LOG_ERROR(TestEvalScript("double uSum=0;while(uSum<3)uSum+=1;Assert(3 == uSum);"));
	//while ... do 在while条件中定义变量,循环体部分进行使用
 	//ASSERT_LOG_ERROR(TestEvalScript("while(double uSum=0){uSum=2;}"));
	//while语句的叠加
	ASSERT_LOG_ERROR(TestEvalScript("double uSum=0;double i=0,j=0;while(i<1)while(j<2){uSum+= i + j; i += 1;j+=1;}Assert(2 == uSum);"));
	//do..while语句循环体中声明变量
	ASSERT_LOG_ERROR(TestEvalScript("do double nIndex=0; while(false);"));
	//while 循环体中声明变量
	ASSERT_LOG_ERROR(TestEvalScript("while(false)double nIndex;"));
	//自增运算符
	ASSERT_LOG_ERROR(TestEvalScript("nIndex++;Assert(4 == nIndex);"));
	//多自增运算符
	ASSERT_LOG_ERROR(TestEvalScript("nIndex++;++nIndex;nIndex--;--nIndex;Assert(3 == nIndex);"));
	//后缀自增运算符
	ASSERT_LOG_ERROR(TestEvalScript("double nSum = 1;nSum += nIndex++;Assert(4 == nSum);"));
	//前缀自增运算符
	ASSERT_LOG_ERROR(TestEvalScript("double nSum = 1;nSum += ++nIndex;Assert(5 == nSum);"));
	//父子作用域定义同样名称的变量
	ASSERT_LOG_ERROR(TestEvalScript("double nTest=1;{double nTest = 2;Assert(2 == nTest);}Assert(1 == nTest);"));
	//非0值的 各种 逻辑运算
	ASSERT_LOG_ERROR(TestEvalScript("Assert(1 && 2);"));
	ASSERT_LOG_ERROR(TestEvalScript("Assert(0 || 2);"));
	ASSERT_LOG_ERROR(TestEvalScript("Assert(!(2 < 2));"));
	ASSERT_LOG_ERROR(TestEvalScript("Assert(!(2 > 2));"));
	ASSERT_LOG_ERROR(TestEvalScript("Assert(!(2 > 2));"));
	ASSERT_LOG_ERROR(TestEvalScript("Assert(2 <= 2);"));
	ASSERT_LOG_ERROR(TestEvalScript("Assert(2 >= 2);"));
	//? : 
	ASSERT_LOG_ERROR(TestEvalScript("double uSum = FunctionArg2(1,3) > 3 ? 6:7;Assert( 6 == uSum);"));
	//switch 语句 不写default
	ASSERT_LOG_ERROR(TestEvalScript("double uNum=0; switch(1){case 1:uNum=1;case 2:uNum=2;}Assert(2 == uNum);"));
	//switch 语句 某个case 中 多个语句
	ASSERT_LOG_ERROR(TestEvalScript("double uNum=0; switch(1){case 1:uNum=1;case 2:uNum=2;uNum=3;}Assert(3 == uNum);"));
	//switch 语句 写default
	ASSERT_LOG_ERROR(TestEvalScript("double uNum=0; switch(3){case 1:uNum=1;case 2:uNum=2;default:uNum=3;}Assert(3 == uNum);"));
	//switch 语句 case 语句不写 语句体
	ASSERT_LOG_ERROR(TestEvalScript("double uNum=0; switch(1){case 1:case 2:uNum=3;}Assert(3 == uNum);"));
	//ASSERT_LOG_ERROR(TestEvalScript("for(;;)break;"));

	//ASSERT_LOG_ERROR(TestEvalScript("for(;;)double nSum;"));
	//ASSERT_LOG_ERROR(TestEvalScript("{double nSum;double nSum;}"));
	return true;
}
