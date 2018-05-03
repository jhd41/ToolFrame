#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"

NS_TOOL_FRAME_BEGIN

typedef StreamBufferPtr			SqlField;	//字段
typedef std::vector<SqlField>	SqlRecord;	//记录(一条记录)
typedef std::vector<SqlRecord>	SqlResult;	//结果集(记录的集合)
typedef	std::vector<SqlResult>	SqlResults;	//所有

NS_TOOL_FRAME_END