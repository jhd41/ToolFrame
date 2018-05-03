#pragma once
//#include "LuaEngine.h"
#include "ToolFrame.h"
#include "MLoger.h"
//#include "ELuna.h"
#include "LuaEngine.h"

//  extern "C"{
//  #include "lua.h"
//  #include "lualib.h"
//  #include "lauxlib.h" 
//  };
// 
// int CallLua(lua_State* L,int x,int y){
// 	lua_getglobal(L,"f");
// 	lua_pushinteger(L,x);
// 	lua_pushinteger(L,y);
// 	lua_call(L,2,1);
// 	int re = lua_tointeger(L,-1);
// 	lua_pop(L,1);
// 	return re;
// }
// 
// int LuaCallC(lua_State* L){
// 	int nArgs = lua_gettop(L);
// 	int nSum = 0;
// 	for (int nIndex = 1;nIndex<=nArgs;++nIndex)
// 	{
// 		nSum += lua_tointeger(L,nIndex);
// 	}
// 	lua_pushnumber(L,nSum);
// 	return 1;
// }

int Duce(int x,int y){
	return x - y;
}

void PrintTest(){

}

double TestDouble(double fArg1,double fArg2){
	return fArg1 + fArg2;
}

void TestArg(int fArg1,double fArg2, std::string s,const char* sz){
	ASSERT_LOG_ERROR(5 == fArg1 && 6 ==fArg2 &&  s == "K" &&  std::string("T") == sz);
}

bool LuaAssertResult(bool bAssert){
	ASSERT_LOG_ERROR(bAssert);
	return true;
}
class CTestB{
public:
	void Print(){
		ToolFrame::OutPut("CTestB");
	}
};
class CTestLua{
public:
	CTestLua(){
		_nIndex = 3;
	}
public:
	int Add(int x,int y){
		return x + y + _nIndex;
	}
	int GetValue(){
		return 5;
	}
	int _nIndex;

	void PrintTest(){
		ToolFrame::OutPut("Hello Lua");
	}

	void PrintString( const std::string& sString){
		ToolFrame::OutPut(sString);
	}

	CTestB* GetTestB(){
		static CTestB a;
		return &a;
	}
};

bool TestLua(CLuaEngine& lua,CTestLua& test){
	//写入 读取变量
	lua.WriteVariable("c",9);
	int c = lua.ReadVariable<int>("c");
	lua.WriteVariable("bBool",true);
	bool bBool = lua.ReadVariable<bool>("bBool");

	//静态函数调用
	lua.RegisterFunction("Duce",&Duce);
	lua.DoString("a = Duce(5,4)");
	int a = lua.ReadVariable<int>("a");

	//面向对象创建调用成员函数
	lua.RegisterClass<CTestLua>("CTestLua",ELuna::constructor<CTestLua>);
	lua.RegisterMethod<CTestLua>("GetValue",&CTestLua::GetValue);
	lua.RegisterMethod<CTestLua>("PrintTest",&CTestLua::PrintTest);
	lua.DoString(" cpp = CTestLua() \n  b= cpp:GetValue()");
	int b = lua.ReadVariable<int>("b");

	//现有C++对象绑定到lua
	lua.WriteVariable("test",&test);
	lua.DoString("test:GetValue()");

	//调用lua函数
	lua.DoString("function LuaAdd(x,y) return x + y end");
	int nSum = lua.CallFuction<int>("LuaAdd",5,6);

	lua.DoString("function PrintLua(s) print(s) end");
	const std::string& s = "I'm come form C++";
	lua.CallFuction<void>("PrintLua",s);

	//成员函数映射到全局函数
	lua.RegisterFunction("GetValue",	&CTestLua::GetValue,&test);
	lua.RegisterFunction("Add",			&CTestLua::Add,&test);
	lua.RegisterFunction("PrintTest",	&CTestLua::PrintTest,&test);
	//lua.RegisterFunction("PrintString",	&CTestLua::PrintString,&test);

	lua.DoString("GetValue()");
	lua.DoString("Add(1,34)");
	lua.DoString("PrintTest()");
	//lua.DoString("PrintString(\"aaaa\")");

	//注册自定义类型类型
	lua.RegisterClass<CTestB>("CTestB");
	lua.RegisterMethod<CTestB>("Print",&CTestB::Print);
	lua.RegisterMethod<CTestLua>("GetTestB",&CTestLua::GetTestB);
	lua.RegisterFunction("GetTestBObj()",&CTestLua::GetTestB,&test);
	lua.DoString("testb = test:GetTestB() \n testb:Print()");

	return true;
}

bool TestLuaDouble(){
	CTestLua test;
	CLuaEngine lua1;

	//此花括号目的让lua2释放掉。再调用1中注册的函数
	{
		CLuaEngine lua2;
		if (!TestLua(lua1,test))return false;
		if (!TestLua(lua2,test))return false;

		lua1.DoString("testb = test:GetTestB() \n testb:Print()");
	}

	lua1.DoString("testb = test:GetTestB() \n testb:Print()");

	return true;
}

bool TestLua(){
	CTestLua test;
 	CLuaEngine lua;

	return TestLua(lua,test);
}
