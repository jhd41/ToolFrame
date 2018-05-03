#pragma once
#include "Macro.h"

class ApiStd{
public:
	//加载文件
	static bool			IsFileExist(const std::string& sFileName);
	static size_t		GetFileLength(const std::string& sFileName);
	static bool			SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	static bool			LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength);
	static bool			CopyFile(const std::string&	sPathSrc,const std::string& sPathDes);
	static bool			RemoveFile(const std::string& sFileName);
	static bool			RenameFile(const std::string& sPathSrc,const std::string& sPathDes);	

	//路径
	static std::string	StardPath(const std::string& sPath);//标准化路径(将路径中的\\都替换为/)Linux下只能读取"/"而不是"\"
	static std::string	AbsPathToRelativePath( const std::string& sPath,const std::string& sCmpPath);//计算相对路径
	static bool			AbsPathToRelativePath(VectorString& vDes,const VectorString& vAbsPath,const std::string& sCmpPath);
	static std::string	TrimPath(const std::string& sPath);//整理路径

	//调试
	static void			Trace(const std::string& msg);
	static void			OutPut( const std::string& msg );
	static void			OutPutCerr( const std::string& msg );

	//时间
	static time_t		GetNowTime();	//获取当前时间
private:
	static std::string	AbsPathToRelativePath( const std::string& sAbsPath,const VectorString& vCmpPath);
	static bool			MakePathVector( VectorString& vDes,const std::string& sPath );
};
