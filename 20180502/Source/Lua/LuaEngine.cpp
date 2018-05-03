#include "LuaEngine.h"
#include "MLoger.h"

//对ELuna的补充
NS_TOOL_FRAME_BEGIN
int LuaErrLogDefault(lua_State *L){//默认
	printf("error : %s\n", lua_tostring(L, -1));

	ELuna::traceStack(L, 0);
	return 0;
}

void LuaTraceStack(lua_State* L, int n) {
	lua_Debug ar;
	if(lua_getstack(L, n, &ar)) {
		lua_getinfo(L, "Sln", &ar);

		if(ar.name) {
			LOG_LUA_ERR("\tstack["<<n<<"] -> line "<<ar.currentline<<" : "<<ar.name<<"()["<<ar.short_src<<" : line "<<ar.linedefined<<"]");
			//printf("\tstack[%d] -> line %d : %s()[%s : line %d]\n", n, ar.currentline, ar.name, ar.short_src, ar.linedefined);
		} else {
			LOG_LUA_ERR("\tstack["<<n<<"] -> line "<<ar.currentline<<" : unknown["<<ar.short_src<<" : line "<<ar.linedefined<<"]");
			//printf("\tstack[%d] -> line %d : unknown[%s : line %d]\n", n, ar.currentline, ar.short_src, ar.linedefined);
		}

		LuaTraceStack(L, n+1);
	}
}

int LuaErrLog(lua_State *L){
	LOG_LUA_ERR(lua_tostring(L, -1));
	//printf("error : %s\n", lua_tostring(L, -1));
	LuaTraceStack(L, 0);
	return 0;
}


NS_TOOL_FRAME_END

ELuna::FnLuaErrLog ELuna::g_fnErrLog = ToolFrame::LuaErrLog;

// ELuna::Function_Vector ELuna::CPPGarbage::m_CPPFunctions;
// ELuna::Method_Vector   ELuna::CPPGarbage::m_CPPMethods;


//引擎类 实现
NS_TOOL_FRAME_BEGIN

CLuaEngine::CLuaEngine( void )
{
	_luaState = ELuna::openLua();
}

CLuaEngine::~CLuaEngine( void )
{
	ELuna::closeLua(_luaState);
	release();
}

bool CLuaEngine::DoString( const std::string& sString )
{
	bool bSucceed = false;

	lua_pushcclosure(_luaState, ELuna::error_log, 0);
	int stackTop = lua_gettop(_luaState);

	if(luaL_loadstring(_luaState, sString.c_str()) == 0) {
		if(lua_pcall(_luaState, 0, 0, stackTop)) {
			lua_pop(_luaState, 1);

			bSucceed = true;
		}
	} else {
		LOG_LUA_ERR("dostring error: "<<lua_tostring(_luaState, -1));
		lua_pop(_luaState, 1);
	}

	lua_pop(_luaState, 1);

	return bSucceed;
}

bool CLuaEngine::pushMethod( ELuna::GenericMethod* method )
{
	m_CPPMethods.push_back(method);
	return true;
}

bool CLuaEngine::pushFunction( ELuna::GenericFunction* function )
{
	m_CPPFunctions.push_back(function);
	return true;
}

void CLuaEngine::release()
{
	for (ELuna::Function_Vector::iterator itr = m_CPPFunctions.begin(); itr != m_CPPFunctions.end(); ++itr) {
		//printf("releaseFunctions %p\n", *itr);
		delete *itr;
	}

	m_CPPFunctions.clear();//SongJ

	for (ELuna::Method_Vector::iterator itr = m_CPPMethods.begin(); itr != m_CPPMethods.end(); ++itr) {
		//printf("releaseMethods %p\n", *itr);
		delete *itr;
	}

	m_CPPMethods.clear();//SongJ
}

bool CLuaEngine::IsLuaFunction( const std::string& sFunc )
{
	lua_getglobal(_luaState, sFunc.c_str());
	return lua_isfunction(_luaState, -1);
}

NS_TOOL_FRAME_END
