#include "ToolIntent.h"

USING_NS_TOOL_FRAME;

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#include "ApiJni.h"
#include "JniCaller.h"

extern "C"
{
	void Java_com_CloudCity_lib_ApiAndroid_NativePickImage(JNIEnv*  env, jobject thiz, jstring sUrl)
	{
		CJniString jniString(env,sUrl);
		MIntentHelper::Singleton().GetIntentHander()->CallBackSelImg(jniString.GetString());
	}
}

bool ToolFrame::SelImage( HIntent* hIntent )
{
	if (!hIntent)return false;

	MIntentHelper::Singleton().SetIntentHander(hIntent);

	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","PickImage");
}

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#include "ApiWin.h"
bool ToolFrame::SelImage( HIntent* hIntent )
{
	if (!hIntent)return false;

	MIntentHelper::Singleton().SetIntentHander(hIntent);
	VectorString vPath;
	if (ApiWin::DialogFileOpen(vPath))
	{
		MIntentHelper::Singleton().GetIntentHander()->CallBackSelImg(vPath[0]);
	}else
	{
		MIntentHelper::Singleton().GetIntentHander()->CallBackSelImg("");
	}

	return true;
}

#endif


