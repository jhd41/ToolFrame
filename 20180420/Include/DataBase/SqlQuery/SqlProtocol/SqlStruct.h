#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"

NS_TOOL_FRAME_BEGIN

typedef StreamBufferPtr			SqlField;	//�ֶ�
typedef std::vector<SqlField>	SqlRecord;	//��¼(һ����¼)
typedef std::vector<SqlRecord>	SqlResult;	//�����(��¼�ļ���)
typedef	std::vector<SqlResult>	SqlResults;	//����

NS_TOOL_FRAME_END