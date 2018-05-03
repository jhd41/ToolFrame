#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MFC

#include <afxdlgs.h>

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
// Ù–‘“≥(Œﬁ±ﬂøÚ)
class CPropertySheetNoBorder
	:public CPropertySheet
{
public:
	virtual void PreSubclassWindow();
	virtual BOOL OnInitDialog();
public:
	CPropertySheetNoBorder(){}
	virtual ~CPropertySheetNoBorder(){}
};

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC