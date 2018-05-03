#include "IntentHelper.h"


MIntentHelper::MIntentHelper(void)
{
	_hIntent = nullptr;
}

MIntentHelper::~MIntentHelper(void)
{
}

bool MIntentHelper::SetIntentHander( HIntent* hIntent )
{
	_hIntent = hIntent;
	return true;
}

HIntent* MIntentHelper::GetIntentHander()
{
	return _hIntent;
}
