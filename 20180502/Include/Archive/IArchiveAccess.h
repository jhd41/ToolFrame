#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "IArchive.h"

//�浵������
NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IArchiveAccess
{
	//�ĵ�����
	typedef IArchive*	(*FnCreater)();
	typedef	std::map<uint,FnCreater> MapCreater;	//�汾��,��������

	//�ĵ�ת��
	typedef bool		(*FnConverter)(IArchive* pSrc,IArchive* pDes);//�ĵ��汾�ṹת����
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
	virtual bool		RegistConverter(uint nVerSrc,uint nVerDes,FnConverter fnConverter);//ע�������İ汾��
protected:
	virtual bool		OnVersionDifferent(IStreamBase& stream,IArchive* pArchiveSrc,IArchive* pArchiveDes);
	virtual FnConverter	FindConverterAbsMin(uint& uVerTarget,uint nVerSrc,uint nVerDes)const;//Ѱ����ӽ�Ŀ��汾��ת����
	virtual uint16		ReadVersion(IStreamBase& stream);					//���ļ��ж�ȡ�汾��(��Ч���� InvaildID)
	virtual bool		WriteVersion(IStreamBase& stream,const IArchive* pArchive)const;
	virtual IArchive*	CreateArchive(uint nVer);
	virtual	bool		DestoryArchive(IArchive* pArchive);
public:
	IArchiveAccess(void);
	IArchiveAccess(const std::string& sFile);
	virtual ~IArchiveAccess(void);
private:
	CFIELD_STRING(ArchiveFile);	//�浵�ļ�·��
private:
	MapCreater			_vCreater;			//<�汾��,��������>
	MapConverter		_vConverter;		//<��ʼ�汾��,<Ŀ��汾��,ת������> >
};

NS_TOOL_FRAME_END
