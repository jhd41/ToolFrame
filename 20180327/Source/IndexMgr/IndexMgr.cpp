#include "IndexMgr.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CIndexMgr::CIndexMgr(void)
{
}

CIndexMgr::~CIndexMgr(void)
{
}

bool CIndexMgr::Init()
{
	TiXmlDocument xDoc;
	if (!ToolFrame::Parse(xDoc,ToolFrame::LoadFile(GetIndexFile())))return false;

	VectorElement vElement;
	if (!ToolFrame::GetElement(vElement,&xDoc,"Index/ID"))return false;

	VectorElement::const_iterator itr;
	foreach(itr,vElement){
		int nID=INVALID_ID;std::string sFile;

		if (!ToolFrame::GetAttribute(*itr,"[ID File]",nID,sFile))return false;

		if (INVALID_ID == nID)return false;
		if (sFile.empty())return false;

		if (!ToolFrame::Insert(_vIndex,nID,sFile))return false;
	}

	return true;
}

const std::string& CIndexMgr::GetFile( int nID ) const
{
	return ToolFrame::GetValueByKey(_vIndex,nID,ToolFrame::EmptyString());
}

const MapIntString& CIndexMgr::GetIndex() const
{
	return _vIndex;
}

size_t CIndexMgr::GetIndexSize() const
{
	return _vIndex.size();
}

NS_TOOL_FRAME_END
