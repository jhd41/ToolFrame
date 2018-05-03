#pragma once
#include "Macro.h"
//本类成为ToolFrame补丁存在，仅仅是为了绕过编译器完全链接而存在的特殊写法。
//将已经完全解耦合的各个类，在此处以不太紧密的方式进行关联起来。并导入到有用的类中去。
//如此一来,可以不需要完全链接即可完成。
//备注:Android下完全链接为WHOLE_STATIC_LINK,IOS下XOCDE加入 all_load. Windows下只有目前只有使用库依赖项输入才可以做到，对于已经编译好的库 目前无法导入。
//而使用DLL方式 则更是一个不可采用之举。DLL必须遵循在此DLL中申请 必须在此DLL中释放。而STL内部经常在申请释放，导致外部几乎无法使用。因此放弃这种写法。

NS_TOOL_FRAME_BEGIN

bool InitLogExecutor();	//导入LogExecutor
bool InitEvalParser();	//导入EvalParser
bool InitExceptionReport();//导入ExceptionReport

bool InitToolFramePatch(){
	if (!InitLogExecutor())return false;
	if (!InitEvalParser())return false;
	if (!InitExceptionReport())return false;
	return true;
}

NS_TOOL_FRAME_END
