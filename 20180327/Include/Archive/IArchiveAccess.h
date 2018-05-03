#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "IArchive.h"

//存档访问器
NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IArchiveAccess
{
	//文档创建
	typedef IArchive*	(*FnCreater)();
	typedef	std::map<uint,FnCreater> MapCreater;	//版本号,创建函数

	//文档转换
	typedef bool		(*FnConverter)(IArchive* pSrc,IArchive* pDes);//文档版本结构转换器
	typedef std::pair<uint,FnConverter>			PairConverter;
	typedef std::multimap<uint,PairConverter>	MapConverter;
	typedef	std::pair<MapConverter::const_iterator,MapConverter::const_iterator>	PairMapConverter;
	typedef std::vector<PairConverter>			VectorConverter;
public:
	virtual bool		Save(const IArchive* pArchive)const;
	virtual bool		Load(IArchive* pArchive);
public:
	virtual bool		Save(const std::string& sFile,const IArchive* pArchive)const;
	virtual bool		Load(const std::string& sFile,IArchive* pArchive);
public:
	virtual bool		Save(IStreamBase& fStream,const IArchive* pArchive)const;
	virtual bool		Load(IStreamBase& fStream,IArchive* pArchive);
public:								
	virtual bool		RegistCreater(uint uVer,FnCreater fnCreate);
	virtual bool		RegistConverter(uint nVerSrc,uint nVerDes,FnConverter fnConverter);//注册升级的版本号
protected:
	virtual bool		OnVersionDifferent(IStreamBase& stream,IArchive* pArchiveSrc,IArchive* pArchiveDes);
	virtual FnConverter	FindConverterAbsMin(uint& uVerTarget,uint nVerSrc,uint nVerDes)const;//寻找最接近目标版本的转换器
	virtual uint16		ReadVersion(IStreamBase& stream);					//从文件中读取版本号(无效返回 InvaildID)
	virtual bool		WriteVersion(IStreamBase& stream,const IArchive* pArchive)const;
	virtual IArchive*	CreateArchive(uint nVer);
	virtual	bool		DestoryArchive(IArchive* pArchive);
public:
	IArchiveAccess(void);
	IArchiveAccess(const std::string& sFile);
	virtual ~IArchiveAccess(void);
private:
	CFIELD_STRING(ArchiveFile);	//存档文件路径
private:
	MapCreater			_vCreater;			//<版本号,创建函数>
	MapConverter		_vConverter;		//<起始版本号,<目标版本号,转换函数> >
};

NS_TOOL_FRAME_END
