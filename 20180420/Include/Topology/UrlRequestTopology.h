#pragma once
#include "IUrlRequest.h"
#include "MacroTopology.h"

NS_TOOL_FRAME_BEGIN
class CUrlRequestTopology;
typedef CSharePtr<CUrlRequestTopology>	CUrlRequestTopologyPtr;
class CUrlRequestTopology
	:public IUrlRequest
{
public:
	CFIELD_REF(XTopologyID, TopologyID, x);
	CFIELD_UINT(ServerID);
	CFIELD_UINT(ClientID);
public:
	CUrlRequestTopology();
	virtual ~CUrlRequestTopology();
};

NS_TOOL_FRAME_END
