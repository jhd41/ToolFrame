#pragma once

#include "MacroTopology.h"

NS_TOOL_FRAME_BEGIN

class CTopologyServerController
{
public:
	bool						Init();
	bool						Clear();
	bool						AddControl(const XServerControl& xControl);
	bool						AddControl(const VectorControl& vControl);
	bool						RemoveControlByClientID(uint uClientID);
	bool						IsControlEmpty()const;
	const MapControl&		GetControls()const;
	CMutexReadWrite&			GetMutexControl()const;
public:
	CTopologyServerController(void);
	virtual ~CTopologyServerController(void);
public:
	mutable CMutexReadWrite	_xMutexControl;
	MapControl				_vControl;		//¿ØÖÆÆ÷
};

NS_TOOL_FRAME_END
