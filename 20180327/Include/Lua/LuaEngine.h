#pragma once
#include "Macro.h"
#include "ELuna.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CLuaEngine
{
public:
	bool IsLuaFunction(const std::string& sFunc);
	bool DoString(const std::string& sString);

	template<typename T>
	inline void WriteVariable(const std::string& sVarName,const T& tValue);
	template<typename T>
	inline T ReadVariable(const std::string& sVarName);

	template<typename T>
	inline bool RegisterFunction(const char* szName,T fn);
	template<typename T,typename K>
	inline bool RegisterFunction(const char* szName,T fn,K Obj);
	
	template<typename T>
	inline void RegisterClass(const char* name);
	template<typename T, typename F>
	inline void RegisterClass(const char* name, F func);

	template<typename T, typename RL>
	inline bool RegisterMethod(const char* name, RL (T::*func)());

	template<typename RL>
	inline RL CallFuction(const std::string& sName);
	template<typename RL,typename P1>
	inline RL CallFuction(const std::string& sName,const P1& p1);
	template<typename RL,typename P1,typename P2>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2);
	template<typename RL,typename P1,typename P2,typename P3>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3);
	template<typename RL,typename P1,typename P2,typename P3,typename P4>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4);
	template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5);
	template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6);
	template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6,const P7& p7);
	template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6,const P7& p7,const P8& p8);
	template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8,typename P9>
	inline RL CallFuction(const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6,const P7& p7,const P8& p8,const P9& p9);
private:
	bool pushMethod(ELuna::GenericMethod* method);
	bool pushFunction(ELuna::GenericFunction* function);

	void release();
public:
	CLuaEngine(void);
	virtual ~CLuaEngine(void);
private:
	lua_State*				_luaState;
	ELuna::Function_Vector	m_CPPFunctions;
	ELuna::Method_Vector	m_CPPMethods;
};

NS_TOOL_FRAME_END

//命名空间 ELuna 添加
namespace ELuna{
	template<>	inline std::string	read2cpp(lua_State *L, int index) { return lua_tostring(L, index);};
	template<> inline void push2lua(lua_State *L, const std::string& ret) { lua_pushstring(L, ret.c_str());};
	template<> inline void push2lua(lua_State *L, std::string ret) { lua_pushstring(L, ret.c_str());};

	template<typename T>
	inline T ReadValue(lua_State* L,const std::string& sVarName){
		lua_getglobal(L,sVarName.c_str());
		T t = read2cpp<T>(L,-1);
		lua_pop(L,1);
		return t;
	}

	template<typename T>
	inline void WriteValue(lua_State* L,const std::string& sVarName,const T& tSrc){
		push2lua(L,tSrc);
		lua_setglobal(L,sVarName.c_str());
	}

	inline void doString( lua_State *L, const char *szString )
	{
		lua_pushcclosure(L, error_log, 0);
		int stackTop = lua_gettop(L);

		if(luaL_loadstring(L, szString) == 0) {
			if(lua_pcall(L, 0, 0, stackTop)) {
				lua_pop(L, 1);
			}
		} else {
			printf("dostring error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}

		lua_pop(L, 1);
	}

#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_0
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_1 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_0, typename P1
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_2 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_1, typename P2
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_3 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_2, typename P3
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_4 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_3, typename P4
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_5 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_4, typename P5
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_6 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_5, typename P6
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_7 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_6, typename P7
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_8 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_7, typename P8
#define ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_9 ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_8, typename P9

#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_0 
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_1 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_0, P1
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_2 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_1, P2
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_3 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_2, P3
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_4 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_3, P4
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_5 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_4, P5
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_6 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_5, P6
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_7 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_6, P7
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_8 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_7, P8
#define ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_9 ELUNA_MEMBER_FUNCTIONCLASSX_SP_PARAM_LIST_8, P9

#define ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(N)\
	template<ELUNA_FUNCTIONCLASSX_PARAM_LIST_##N,typename T >\
	struct FunctionMemberClass##N : GenericFunction\
	{\
	typedef RL (T::*TFUNC)(ELUNA_PARAM_LIST_##N);\
	TFUNC m_func;\
	T* m_tObj;\
	const char* m_name;\
	FunctionMemberClass##N( const char* name, TFUNC func,T* tObj): m_func(func), m_name(name), m_tObj(tObj) {};\
	~FunctionMemberClass##N() {};\
	inline virtual int call(lua_State *L) {\
	push2lua(L, (m_tObj->*m_func)(ELUNA_READ_FUNCTION_PARAM_LIST_##N));\
	return 1;\
	};\
	};

#define  ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(N) \
	template<typename RL,typename T ELUNA_FUNCTIONCLASSX_VOID_RL_MEMBER_PARAM_LIST_##N> \
	struct FunctionMemberVoidClass##N  :GenericFunction{\
	typedef void (T::*TFUNC)(ELUNA_PARAM_LIST_##N);\
	const char* m_name;\
	TFUNC m_func;\
	T* m_tObj;\
	FunctionMemberVoidClass##N( const char* name, TFUNC func,T* tObj): m_func(func), m_name(name), m_tObj(tObj) {};\
	~FunctionMemberVoidClass##N() {};\
	inline virtual int call(lua_State *L) {\
	(m_tObj->*m_func)(ELUNA_READ_FUNCTION_PARAM_LIST_##N);\
	return 0;\
	};\
	};

	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(0)
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(1);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(2);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(3);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(4);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(5);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(6);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(7);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(8);
	ELUNA_MAKE_VOID_RL_MEMBER_FUNCTIONCLASSX(9);

	ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(0)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(1)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(2)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(3)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(4)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(5)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(6)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(7)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(8)
		ELUNA_MAKE_MEMBER_FUNCTIONCLASSX(9)

	//SongJ
	inline GenericFunction* registerFunction(lua_State* L, const char* name,GenericFunction* pFunc){
		
		lua_pushlightuserdata(L, pFunc);
		lua_pushcclosure(L, proxyFunctionCall, 1);
		lua_setglobal(L, name);

		return pFunc;
	}

	template<typename RL,typename T>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass0<RL,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass1<RL,P1,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass2<RL,P1,P2,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass3<RL,P1,P2,P3,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3, typename P4>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3,P4),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass4<RL,P1,P2,P3,P4,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3,P4,P5),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass5<RL,P1,P2,P3,P4,P5,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3,P4,P5,P6),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass6<RL,P1,P2,P3,P4,P5,P6,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3,P4,P5,P6,P7),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass7<RL,P1,P2,P3,P4,P5,P6,P7,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3,P4,P5,P6,P7,P8),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass8<RL,P1,P2,P3,P4,P5,P6,P7,P8,T>(name, func,pObj));
	}
	template<typename RL,typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, RL (T::*func)(P1,P2,P3,P4,P5,P6,P7,P8,P9),T* pObj) {
		return registerFunction(L,name,new FunctionMemberClass9<RL,P1,P2,P3,P4,P5,P6,P7,P8,P9,T>(name, func,pObj));
	}

	template<typename T>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass0<void,T>(name, func,pObj));
	}
	template<typename T, typename P1>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass1<void,P1,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass2<void,P1,P2,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass3<void,P1,P2,P3,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3, typename P4>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3,P4),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass4<void,P1,P2,P3,P4,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3,P4,P5),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass5<void,P1,P2,P3,P4,P5,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3,P4,P5,P6),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass6<void,P1,P2,P3,P4,P5,P6,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3,P4,P5,P6,P7),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass7<void,P1,P2,P3,P4,P5,P6,P7,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3,P4,P5,P6,P7,P8),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass8<void,P1,P2,P3,P4,P5,P6,P7,P8,T>(name, func,pObj));
	}
	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	inline  GenericFunction*  registerFunction(lua_State* L, const char* name, void (T::*func)(P1,P2,P3,P4,P5,P6,P7,P8,P9),T* pObj) {
		return registerFunction(L,name,new FunctionMemberVoidClass9<void,P1,P2,P3,P4,P5,P6,P7,P8,P9,T>(name, func,pObj));
	}
};

NS_TOOL_FRAME_BEGIN

//LuaEngine模板实现
template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8,typename P9>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6,const P7& p7,const P8& p8,const P9& p9 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}

template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6,const P7& p7,const P8& p8 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3,p4,p5,p6,p7,p8);
}

template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6,const P7& p7 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3,p4,p5,p6,p7);
}

template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5,const P6& p6 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3,p4,p5,p6);
}

template<typename RL,typename P1,typename P2,typename P3,typename P4,typename P5>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4,const P5& p5 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3,p4,p5);
}

template<typename RL,typename P1,typename P2,typename P3,typename P4>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3,const P4& p4 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3,p4);
}

template<typename RL,typename P1,typename P2,typename P3>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2,const P3& p3 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2,p3);
}

template<typename RL,typename P1,typename P2>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1,const P2& p2 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1,p2);
}

template<typename RL,typename P1>
inline RL CLuaEngine::CallFuction( const std::string& sName,const P1& p1 )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func(p1);
}

template<typename RL>
inline RL CLuaEngine::CallFuction( const std::string& sName )
{
	ELuna::LuaFunction<RL> func(_luaState,sName.c_str());
	return func();
}

template<typename T, typename RL>
inline bool CLuaEngine::RegisterMethod( const char* name, RL (T::*func)() )
{
	ELuna::GenericMethod* pMethod = ELuna::registerMethod(_luaState,name,func);
	if (!pMethod)return false;
	
	return pushMethod(pMethod);
}

template<typename T, typename F>
inline void CLuaEngine::RegisterClass(const char* name, F func) {
	ELuna::registerClass<T,F>(_luaState,name,func);
}

template<typename T>
inline void CLuaEngine::RegisterClass( const char* name )
{
	ELuna::ClassName<T>::setName(name);
	ELuna::registerMetatable<T>(_luaState,name);
}

template<typename T,typename K>
inline bool CLuaEngine::RegisterFunction( const char* szName,T fn,K Obj )
{
	ELuna::GenericFunction* pFun = ELuna::registerFunction(_luaState,szName,fn,Obj);
	if (!pFun)return false;
	return pushFunction(pFun);
}

template<typename T>
inline bool CLuaEngine::RegisterFunction( const char* szName,T fn )
{
	ELuna::GenericFunction* pFun = ELuna::registerFunction(_luaState,szName,fn);
	if (!pFun)return false;
	return pushFunction(pFun);
}

template<typename T>
inline T CLuaEngine::ReadVariable( const std::string& sVarName )
{
	return ELuna::ReadValue<T>(_luaState,sVarName);
}

template<typename T>
inline void CLuaEngine::WriteVariable( const std::string& sVarName,const T& tValue )
{
	ELuna::WriteValue(_luaState,sVarName,tValue);
}

NS_TOOL_FRAME_END
