#pragma once
#include "Macro.h"
//�����ΪToolFrame�������ڣ�������Ϊ���ƹ���������ȫ���Ӷ����ڵ�����д����
//���Ѿ���ȫ����ϵĸ����࣬�ڴ˴��Բ�̫���ܵķ�ʽ���й��������������뵽���õ�����ȥ��
//���һ��,���Բ���Ҫ��ȫ���Ӽ�����ɡ�
//��ע:Android����ȫ����ΪWHOLE_STATIC_LINK,IOS��XOCDE���� all_load. Windows��ֻ��Ŀǰֻ��ʹ�ÿ�����������ſ��������������Ѿ�����õĿ� Ŀǰ�޷����롣
//��ʹ��DLL��ʽ �����һ�����ɲ���֮�١�DLL������ѭ�ڴ�DLL������ �����ڴ�DLL���ͷš���STL�ڲ������������ͷţ������ⲿ�����޷�ʹ�á���˷�������д����

NS_TOOL_FRAME_BEGIN

bool InitLogExecutor();	//����LogExecutor
bool InitEvalParser();	//����EvalParser
bool InitExceptionReport();//����ExceptionReport

bool InitToolFramePatch(){
	if (!InitLogExecutor())return false;
	if (!InitEvalParser())return false;
	if (!InitExceptionReport())return false;
	return true;
}

NS_TOOL_FRAME_END
