#pragma once
#include "Macro.h"
#include "ToolFrame.h"
#include "tinyxml.h"

bool TestXml(){
	TiXmlDocument xDoc;
	const std::string sFileName =ToolFrame::LoadFile("Test.xml");
	ASSERT_LOG_ERROR(ToolFrame::Parse(xDoc,sFileName));
	
	std::string sID,sValue;
	ASSERT_LOG_ERROR(ToolFrame::GetAttribute(&xDoc,"Role/Frame[Money='200' ID Value]",sID,sValue));
	ASSERT_LOG_ERROR(sID == "2" && sValue== "300");

	MapStringString vMap;

	VectorElement vFrame;
	ASSERT_LOG_ERROR(ToolFrame::GetElement(vFrame,&xDoc,"Role/Frame"));
	ASSERT_LOG_ERROR(vFrame.size() == 3);

	for (size_t uIndex =0;uIndex<vFrame.size();++uIndex)
	{
		std::string sID,sValue;
		if (ToolFrame::GetAttribute(vFrame[uIndex], "[Money='100' ID Value]", sID, sValue))
		{
			ASSERT_LOG_ERROR(ToolFrame::Insert(vMap, sID, sValue));
		}
	}
	ASSERT_LOG_ERROR(vMap.size() == 2);
	return true;
}