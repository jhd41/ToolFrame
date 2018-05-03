#define _CRT_SECURE_NO_WARNINGS 1

#include "ZipFile.h"
#include "ToolFrame.h"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

NS_TOOL_FRAME_BEGIN

ToolFrame::CZipFile::CZipFile()
{
	_pInfoCurrent= nullptr;
	_unzFile = nullptr;
}

CZipFile::CZipFile( const std::string& sFile,const std::string& sPassWord )
{
	_pInfoCurrent = nullptr;
	_unzFile = nullptr;

	Open(sFile, sPassWord);
}

CZipFile::~CZipFile(void)
{
	Close();
}

bool CZipFile::Open(const std::string& sFile, const std::string& sPassWord)
{
	Close();

	_sFileName = sFile;
	_sPassWord = sPassWord;

	_unzFile = unzOpen(sFile.c_str());
	if (!_unzFile)return false;

	MakeIndex();

	if (!_vFilePos.empty())
		_pInfoCurrent = &(_vFilePos.begin()->second);
	return true;
}

bool CZipFile::Reset()
{
	Open(_sFileName, _sPassWord);
	Close();
	return true;
}

bool CZipFile::OpenZipFile( const std::string& sFile )
{
	//查找索引
	XFileInfo* pInfo = ToolFrame::GetValuePtrByKey(_vFilePos, sFile);
	if (!pInfo)return false;

	_pInfoCurrent = pInfo;
	return UNZ_OK == unzGoToFilePos(_unzFile, &pInfo->xPos);
}

bool CZipFile::Close()
{
	if (!_unzFile)return true;

	unzClose(_unzFile);
	_unzFile = nullptr;

	ToolFrame::Clear(_vFilePos);
	return true;
}

bool CZipFile::ReadFirstFile()
{
	return UNZ_OK == unzGoToFirstFile(_unzFile);
}

bool CZipFile::ReadNextFile()
{
	return UNZ_OK == unzGoToNextFile(_unzFile);
}

const unz_file_info& CZipFile::GetCurFileInfo()const
{
	return _pInfoCurrent->xInfo;
}

const std::string& CZipFile::GetCurFileName() const
{
	return _pInfoCurrent->sName;
}

uint32 CZipFile::GetCurFileUncompressedSize() const
{
	return _pInfoCurrent->xInfo.uncompressed_size;
}

bool CZipFile::OpenCurFilePassword( const std::string& sPassword )
{
	return UNZ_OK ==unzOpenCurrentFilePassword(_unzFile,sPassword.empty() ? nullptr : sPassword.c_str());
}

bool CZipFile::CloseCurFile()
{
	return UNZ_OK ==unzCloseCurrentFile(_unzFile);
}

bool CZipFile::LoadData( void* pData, size_t uLen )
{
	if (!OpenCurFilePassword(_sPassWord))return true;
	
	if (!ReadCurFile(pData,uLen))
	{
		CloseCurFile();
		return false;
	}
	CloseCurFile();
	return true;
}

bool CZipFile::LoadData( const std::string& sFile,void* pData, size_t uLen )
{
	if (!OpenZipFile(sFile))return false;
	if (!LoadData(pData,uLen))return false;

	return true;
}

bool CZipFile::ReadCurFile( void* pData, size_t uLen )
{
	return unzReadCurrentFile(_unzFile,pData,(uint)uLen) >= 0;
}

bool ToolFrame::CZipFile::MakeIndex()
{
	ToolFrame::Clear(_vFilePos);

	if (!_unzFile)return false;

	//开始制作索引
	for (bool bSucceed = ReadFirstFile(); bSucceed; bSucceed = ReadNextFile()) {
		XFileInfo xInfo;

		//读取头信息
		char szZipName[MAX_PATH] = { 0 };
		if (UNZ_OK != unzGetCurrentFileInfo(_unzFile, &xInfo.xInfo, szZipName, sizeof(szZipName), nullptr, 0, nullptr, 0))return false;
		xInfo.sName = szZipName;

		//读取文件位置信息
		if (UNZ_OK != unzGetFilePos(_unzFile, &xInfo.xPos))return false;

		ToolFrame::Insert(_vFilePos, xInfo.sName, xInfo);
	}

	return true;
}

bool CZipFile::UnZipFile(const std::string& sDir)
{
	if (!_unzFile)return false;
	if (!ReadFirstFile())return false;

	if (!ToolFrame::MakeDir(sDir))return false;
	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(_unzFile, &global_info) != UNZ_OK)return false;

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];

	//CCLOG("start uncompressing");

	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(_unzFile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)return false;

		const std::string fullPath = sDir + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength-1] == '/')
		{
			// Entry is a direcotry, so create it.
			// If the directory exists, it will failed scilently.
			if (!ToolFrame::MakeDir(fullPath))return false;
		}
		else
		{
			//There are not directory entry in some case.
			//So we need to test whether the file directory exists when uncompressing file entry
			//, if does not exist then create directory
			const std::string fileNameStr(fileName);

			size_t startIndex=0;

			SSIZE_TYPE index=fileNameStr.find("/",startIndex);

			while(index != std::string::npos)
			{
				const std::string dir=sDir+fileNameStr.substr(0,index);

				FILE *out = fopen(dir.c_str(), "r");

				if(!out)
				{
					if (!ToolFrame::MakeDir(dir))return false;
				}
				else
				{
					fclose(out);
				}

				startIndex=index+1;

				index=fileNameStr.find("/",startIndex);

			}



			// Entry is a file, so extract it.

			// Open current file.
			if (unzOpenCurrentFile(_unzFile) != UNZ_OK)return false;

			// Create a file to store current file.
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (! out)
			{
				//CCLOG("can not open destination file %s", fullPath.c_str());
				unzCloseCurrentFile(_unzFile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(_unzFile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					//CCLOG("can not read zip file %s, error code is %d", fileName, error);
					unzCloseCurrentFile(_unzFile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while(error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(_unzFile);

		// Goto next entry listed in the zip file.
		if ((i+1) < global_info.number_entry)
		{
			if (unzGoToNextFile(_unzFile) != UNZ_OK)
				return false;
		}
	}
	return true;
}

NS_TOOL_FRAME_END
