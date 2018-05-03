#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"

//存档应该分为三部分
//存档存写器 当前版本存档结构 存档升级工具

//创建函数
#define CREATE_ARCHIVE(className) public:static ToolFrame::IArchive* Create(){return new className();}
//快速建档类
#define ARCHIVE_SERIALIZE(className,ver,serialize) \
	public:	\
		CREATE_ARCHIVE(className);	\
		className(void){SetVersion(ver);}\
		virtual ~className(void){}\
		virtual bool	Serialize(ToolFrame::IStreamBase& stream){stream & serialize;return !stream.IsError();}

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IArchive
{
public:
	virtual	uint	GetVersion()const;
	virtual bool	Serialize(IStreamBase& stream)=0;
public:
	virtual bool	SetVersion(uint uVer);
public:
	IArchive(void);
	virtual ~IArchive(void);
protected:
	uint16	_uVer;
};

NS_TOOL_FRAME_END
