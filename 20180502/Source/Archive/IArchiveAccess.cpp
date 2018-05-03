#include "IArchiveAccess.h"

#include "ToolFrame.h"
#include "StreamFile.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IArchiveAccess::IArchiveAccess(void)
{
}

IArchiveAccess::IArchiveAccess( const std::string& sFile )
{
	SetArchiveFile(sFile);
}

IArchiveAccess::~IArchiveAccess(void)
{
}

bool IArchiveAccess::Save(const IArchive* pArchive)const
{
	if (GetArchiveFile().empty())return false;
	return Save(GetArchiveFile(),pArchive);
}

bool IArchiveAccess::Load(IArchive* pArchive)
{
	if (GetArchiveFile().empty())return false;
	return Load(GetArchiveFile(),pArchive);
}

bool IArchiveAccess::Save( const std::string& sFile ,const IArchive* pArchive )const
{
	if (sFile.empty())return false;
	if (!pArchive)return false;

	CStreamFile fStream(sFile,CStreamFile::OP_OUT, DIR_TYPE_WRITEABLE);
	return Save(fStream,pArchive);
}

bool IArchiveAccess::Save( IStreamBase& fStream,const IArchive* pArchive ) const
{
	if (!pArchive)return false;

	fStream.SetDirection(IStreamBase::STREAM_INPUT);

	if (!WriteVersion(fStream,pArchive))return false;

	if(!ToolFrame::ConstCast(pArchive)->Serialize(fStream))return false;
	return !fStream.IsError();
}

bool IArchiveAccess::Load( IStreamBase& fStream,IArchive* pArchive )
{
	if (!pArchive)return false;

	fStream.SetDirection(IStreamBase::STREAM_OUTPUT);

	uint16 uVer = ReadVersion(fStream);
	if (INVALID_ID == uVer)return false;

	//如果版本不一致进行尝试转换，否则直接序列化
	if (uVer != pArchive->GetVersion())
	{
		IArchive* pArchiveFile = CreateArchive(uVer);
		if (!pArchiveFile)return false;
		if (!pArchiveFile->Serialize(fStream))
		{
			DestoryArchive(pArchiveFile);
			return false;
		}

		if (!OnVersionDifferent(fStream,pArchiveFile,pArchive))
		{
			DestoryArchive(pArchiveFile);
			return false;
		}

		DestoryArchive(pArchiveFile);
	}else
	{
		if (!pArchive->Serialize(fStream))
			return false;
	}

	return true;
}

bool IArchiveAccess::Load( const std::string& sFile ,IArchive* pArchive)
{
	if (sFile.empty())return false;
	if (!pArchive)return false;

	CStreamFile fStream;
	if (!fStream.Open(sFile,CStreamFile::OP_IN,DIR_TYPE_WRITEABLE))return false;
	return Load(fStream,pArchive);
}

IArchive* IArchiveAccess::CreateArchive( uint nVer )
{
	FnCreater fnCreater = ToolFrame::GetPtrValueByKey(_vCreater,nVer);
	if (!fnCreater)return nullptr;
	IArchive* pArchive =  fnCreater();
	ASSERT_LOG_ERROR(pArchive);
	pArchive->SetVersion(nVer);
	return pArchive;
}

uint16 IArchiveAccess::ReadVersion( IStreamBase& stream )
{
	uint16 nVer = INVALID_ID;
	stream & nVer;

	return stream.IsError() ? INVALID_ID : nVer;
}

bool IArchiveAccess::WriteVersion( IStreamBase& stream,const IArchive* pArchive )const
{
	uint16 uVer = pArchive->GetVersion();
	stream & uVer;
	return !stream.IsError();
}

bool IArchiveAccess::DestoryArchive( IArchive* pArchive)
{
	delete pArchive;
	return true;
}

bool IArchiveAccess::OnVersionDifferent( IStreamBase& stream,IArchive* pArchiveSrc,IArchive* pArchiveDes )
{
	ASSERT_LOG_DEBUG_ERR(pArchiveSrc && pArchiveDes);
	ASSERT_LOG_DEBUG_ERR(pArchiveSrc->GetVersion() != pArchiveDes->GetVersion());

	//找到升级方案
	VectorConverter vConverter;
	uint uVerTarget = pArchiveSrc->GetVersion();
	while (uVerTarget != pArchiveDes->GetVersion())
	{
		FnConverter fn = FindConverterAbsMin(uVerTarget,uVerTarget,pArchiveDes->GetVersion());
		if (!fn)return false;

		vConverter.push_back(PairConverter(uVerTarget,fn));
	}

	ASSERT_LOG_DEBUG_ERR(!vConverter.empty());
	
	//执行升级方案
	IArchive* pArchiveLast = pArchiveSrc;
	VectorConverter::const_iterator itr;
	foreach(itr,vConverter){
		const PairConverter& pair = *itr;
		IArchive* pArchiveTarget = pair.first == pArchiveDes->GetVersion() ? pArchiveDes : CreateArchive(pair.first);
		if (!pArchiveTarget)
		{
			if (pArchiveLast != pArchiveSrc)
				DestoryArchive(pArchiveLast);

			return false;
		}

		FnConverter fnConverter = pair.second;
		ASSERT_LOG_DEBUG_ERR(fnConverter);
		
		//转换
		if (!fnConverter(pArchiveLast,pArchiveTarget))
		{
			if (pArchiveLast != pArchiveSrc)
				DestoryArchive(pArchiveLast);

			if (pArchiveTarget != pArchiveDes)
				DestoryArchive(pArchiveTarget);

			return false;
		}

		if (pArchiveLast != pArchiveSrc)
			DestoryArchive(pArchiveLast);
		pArchiveLast = pArchiveTarget;
	}

	return true;
}

IArchiveAccess::FnConverter IArchiveAccess::FindConverterAbsMin(uint& uVerTarget,uint nVerSrc,uint nVerDes ) const
{
	PairMapConverter itrRange = _vConverter.equal_range(nVerSrc);
	if (ToolFrame::IsEnd(itrRange))return nullptr;
	
	FnConverter fn = nullptr;
	uint uAbsMin =ToolFrame::GetLimitMax<uint>();

	MapConverter::const_iterator itr;
	foreachPair(itr,itrRange){
		const PairConverter& pair = itr->second;
		uint uAbs = ToolFrame::AbsDifference(nVerDes,pair.first);
		if (uAbs < uAbsMin)
		{
			uAbsMin = uAbs;
			fn = pair.second;
			uVerTarget = pair.first;
		}
	}

	ASSERT_LOG_DEBUG_ERR(fn);
	return fn;
}

bool IArchiveAccess::RegistConverter( uint nVerSrc,uint nVerDes,FnConverter fnConverter )
{
	return ToolFrame::Insert(_vConverter,nVerSrc,PairConverter(nVerDes,fnConverter));
}

bool IArchiveAccess::RegistCreater( uint uVer,FnCreater fnCreate )
{
	return ToolFrame::Insert(_vCreater,uVer,fnCreate);
}

NS_TOOL_FRAME_END
