#include "StreamFile.h"

#include "ToolStd.h"
#include "ToolPlat.h"
#include "MLoger.h"

#include "StreamBufferMalloc.h"

NS_TOOL_FRAME_BEGIN

CStreamFile::CStreamFile(void)
{
	_eDirType = INVALID_ID;
	_eOp = OP_INVAID;
}

CStreamFile::CStreamFile(const std::string& sPath, EOperator eOp, int eDirType /*= DIR_TYPE_INVALID*/)
{
	if (!Open(sPath, eOp,eDirType))
		SetError();
}

CStreamFile::~CStreamFile(void)
{
	Close();
}

bool CStreamFile::Open(const std::string& sPath, EOperator eOp, int eDirType /*= DIR_TYPE_INVALID*/)
{
	if (sPath.empty())return false;
	_eOp = eOp;
	_sPath = sPath;
	_eDirType = eDirType;

	switch (_eOp)
	{
		case OP_IN:
			{
				if (!ToolFrame::IsFileExist(sPath, eDirType))return false;
				size_t uLength = ToolFrame::GetFileLength(sPath, eDirType);
				if (uLength > 0)//我们认为打开一个空文件是成功的。
				{
					StreamBufferPtr ptr(new CStreamBufferMalloc(uLength));
					if (!ToolFrame::LoadFile(sPath, ptr->GetWriteBuffer(), ptr->GetMaxSize(), eDirType))return false;
					ptr->SetSize(ptr->GetMaxSize());
					ptr->SetWriteCursor(ptr->GetMaxSize());
					_vBuffer.push_back(ptr);

					SetSize(uLength);
					SetWriteCursor(uLength);
				}
				SetDirection(STREAM_OUTPUT);
				return true;
			}
			break;
		case OP_OUT:
			{
				SetDirection(STREAM_INPUT);
				return true;
			}
			break;
	}

	return false;
}

bool CStreamFile::Close()
{
	if (OP_OUT == _eOp)
	{
		if (GetSize() > 0 && !IsError())
		{
			CStreamBufferMalloc buffer(GetSize());

			size_t uLength = 0;
			ListStreamBufferPtr::const_iterator itr;
			foreach(itr,_vBuffer){
				StreamBufferPtr ptr = *itr;
				ASSERT_LOG_ERROR(ptr);

				if (!buffer.Write(ptr->GetBuffer(),ptr->GetLength()))
					return false;
				uLength += ptr->GetLength();
			}

			ASSERT_LOG_ERROR(_uSize == uLength);
			if (!ToolFrame::SaveFile(_sPath,buffer.GetBuffer(),buffer.GetLength(),_eDirType))return false;

			_uSize=0;
			_vBuffer.clear();
		}
	}

	return true;
}


NS_TOOL_FRAME_END
