#include "ApiStd.h"
#include "ToolStd.h"

void ApiStd::Trace( const std::string& msg )
{
#if MACRO_TARGET_VER == MACRO_VER_DEBUG
	std::cout<<msg<<std::endl;
#endif // MACRO_VER_DEBUG
}

void ApiStd::OutPut( const std::string& msg )
{
	std::cout<<msg<<std::endl;
}

void ApiStd::OutPutCerr( const std::string& msg )
{
	std::cerr << msg << std::endl;
}

time_t ApiStd::GetNowTime()
{
	return time(nullptr);
}

size_t ApiStd::GetFileLength( const std::string& sFileName )
{
	if (sFileName.empty())return 0;

	std::ifstream fStream; 

	//打开文件
	if (!ToolFrame::OpenFile(fStream,sFileName))return 0;

	return ToolFrame::GetFileLength(fStream);
}

bool ApiStd::LoadFile( const std::string& sFileName,void* pBuffer,size_t uLength )
{
	if (sFileName.empty())return false;
	if (!pBuffer)return false;
	if (uLength <=0)return false;
	
	std::ifstream fStream; 

	//打开文件
	if (!ToolFrame::OpenFile(fStream,sFileName,std::ios::in|std::ios::binary))return false;

	//检测文件长度
	UINT uFileLen = ToolFrame::GetFileLength(fStream);
	if(uFileLen == 0)return false;

	//申请空间读取
	if (uLength < uFileLen)return false;

	//读取
	fStream.read((char*)pBuffer, uFileLen);  
	fStream.close();

	return true;
}

bool ApiStd::SaveFile( const std::string& sFileName,const void* pBuffer,size_t uLength)
{
	if (sFileName.empty())return false;
	if (!pBuffer)return false;
	if (uLength <=0)return false;

	//得到BUFF内存
	std::ofstream fStream;

	//打开文件
	if (!ToolFrame::OpenFile(fStream,sFileName,std::ios::out|std::ios::binary))return false;

	//写入
	fStream.write((const char*)pBuffer,uLength);
	fStream.close();
	return true;
}

bool ApiStd::IsFileExist( const std::string& sFileName )
{
	if (sFileName.empty())return false;

	std::ifstream fStream;

	//打开文件
	fStream.open(sFileName.c_str());
	return !!fStream;
}
bool ApiStd::CopyFile( const std::string& sPathSrc,const std::string& sPathDes )
{
	if (sPathSrc.empty())return false;
	if (sPathDes.empty())return false;

	std::ifstream fInput;
	if (!ToolFrame::OpenFile(fInput,sPathSrc,std::ios::binary))return false;//打开源文件

	std::ofstream fOutPut;
	if (!ToolFrame::OpenFile(fOutPut,sPathDes,std::ios::binary))return false;//创建目标文件 

	return ToolFrame::CopyFile(fOutPut,fInput);
}

bool ApiStd::RemoveFile( const std::string& sFileName )
{
	if (sFileName.empty())return false;
	return 0 == ::remove(sFileName.c_str());
}

bool ApiStd::RenameFile( const std::string& sPathSrc,const std::string& sPathDes )
{
	if (sPathSrc.empty())return false;
	if (sPathDes.empty())return false;
	return 0 == ::rename(sPathSrc.c_str(),sPathDes.c_str());
}

bool ApiStd::MakePathVector( VectorString& vDes,const std::string& sPath )
{
	if (sPath.empty())return false;

	ToolFrame::SplitString(vDes,sPath,"/");
	if (vDes.empty())return false;

	if (ToolFrame::GetBack(vDes).empty())
		ToolFrame::EraseBack(vDes);

	return true;
}

std::string ApiStd::AbsPathToRelativePath( const std::string& sPath,const std::string& sCmpPath )
{
	if (sPath.empty())return ToolFrame::EmptyString();

	VectorString vCmpPath;
	if (!MakePathVector(vCmpPath,StardPath(sCmpPath)))return ToolFrame::EmptyString();

	return AbsPathToRelativePath(sPath,vCmpPath);
}

bool ApiStd::AbsPathToRelativePath( VectorString& vDes,const VectorString& vPath,const std::string& sCmpPath )
{
	if (vPath.empty())return false;

	if (ToolFrame::IsSelf(vDes,vPath))return false;

	VectorString vCmpPath;
	if (!MakePathVector(vCmpPath,StardPath(sCmpPath)))return false;

	VectorString::const_iterator itr;
	foreach(itr,vPath){
		ToolFrame::PushBack(vDes,AbsPathToRelativePath(StardPath(*itr),vCmpPath));
		if ( ToolFrame::EmptyString() == ToolFrame::GetBack(vDes))
			return false;

	}

	return true;
}

std::string ApiStd::AbsPathToRelativePath( const std::string& sAbsPath,const VectorString& vCmpPath )
{
	if (sAbsPath.empty())return ToolFrame::EmptyString();

	VectorString vAbsPath;
	if (!MakePathVector(vAbsPath,sAbsPath))return ToolFrame::EmptyString();
	if (vAbsPath.empty() || vCmpPath.empty())return ToolFrame::EmptyString();

	// aa/bb/c
	// aa/c/d/c

	//思路:找到路径不一样的地方，之后添加 被比较路径剩余部分 个 ../ 然后将绝对路径中剩下不同地方一起写入即可

	//找到不一样的地方
	size_t uDiff = -1;
	size_t uMax = ToolFrame::Min(vAbsPath.size(),vCmpPath.size());
	for (size_t uIndex = 0;uIndex<uMax;++uIndex)
	{
		if (vAbsPath[uIndex] != vCmpPath[uIndex])break;

		uDiff = uIndex;
	}
	if (uDiff <= 0)return ToolFrame::EmptyString();

	std::stringstream sStream;

	//被比较路径剩余部分
	for(size_t uIndex = uDiff + 1;uIndex<vCmpPath.size();++uIndex){
		sStream<<"../";
	}

	//如果是当前目录
	if (uDiff + 1 >= vCmpPath.size())
		sStream<<"./";

	//添加绝对路径不同部分
	for(size_t uIndex = uDiff + 1;uIndex<vAbsPath.size();++uIndex){
		sStream<<vAbsPath[uIndex];
		if (uIndex != vAbsPath.size() - 1)
			sStream<<"/";
	}
	return sStream.str();
}

std::string ApiStd::StardPath( const std::string& sPath )
{
	if (sPath.empty())return ToolFrame::EmptyString();

	std::string s = sPath;
	ToolFrame::Replace(s,"\\","/");//Linux下只能读取"/"而不是"\"
	return s;
}

std::string ApiStd::TrimPath( const std::string& sPath )
{
	if (sPath.empty())return ToolFrame::EmptyString();

	std::stringstream sStream;//返回值

	//如果sPath是绝对路径开头先添加进去
	if (ToolFrame::IsBeginWith(sPath,"/"))
	{
		sStream<<"/";
	}

	//然后拼接调整文件夹
	{
		VectorString vDes;

		std::string s = sPath;
		ToolFrame::Replace(s,"\\","/");

		VectorString vString;
		ToolFrame::SplitString(vString,s,"/");

		VectorString::const_iterator itr;
		foreach(itr,vString){
			const std::string& sDirName = *itr;
			if (sDirName == "")
			{
				continue;
			}
			if (sDirName == ".")
			{
				continue;
			}
			if (sDirName == "..")
			{
				if (vDes.empty() || vDes.back() == "..")
				{
					vDes.push_back("..");
				}else
				{
					vDes.pop_back();
				}
				continue;
			}

			vDes.push_back(sDirName);
		}

		if (!vString.empty() && vString.back() == "")
		{
			vDes.push_back("");
		}

		//参考自 ToolFrame::ToString
		{
			bool bAttch= false;
			VectorString::const_iterator itr;
			foreach(itr,vDes){
				if (bAttch)sStream << "/";
				bAttch = true;

				sStream << *itr;
			}
		}
	}

	return sStream.str();
}
