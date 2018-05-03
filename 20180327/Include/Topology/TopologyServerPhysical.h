#pragma once

#include "MacroTopology.h"

NS_TOOL_FRAME_BEGIN

class CTopologyServerPhysical
{
public:
	bool						Init();
	bool						Clear();
public:
	bool						AddServer(const XServerPhysical& xServer);
	bool						AddServer(const VectorPhysical& vPhysical);
	bool						RemovePhysicalByPhysicalID(uint uPhysicalID);
	const XServerPhysical*		FindPhysicalByPhysicalID(uint uPhysicalID)const;
	const XServerPhysical*		FindPhysicalByClientID(uint uClientID)const;
	
	bool						UpdatePhysicalState(uint uPhysicalID,const XPhysicalUpdate& xUpdate);

	
	bool						IsPhysicalEmpty()const;
	const MapPhysical&			GetPhysical()const;
	CMutexReadWrite&			GetMutexPhysical()const;
public:
	CTopologyServerPhysical(void);
	virtual ~CTopologyServerPhysical(void);
public:
	mutable CMutexReadWrite	_xMutexPhysical;
	MapPhysical			_vPhysical;		//物理服务器
};

NS_TOOL_FRAME_END
