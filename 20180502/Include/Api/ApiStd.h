#pragma once
#include "Macro.h"

class ApiStd{
public:
	//�����ļ�
	static bool			IsFileExist(const std::string& sFileName);
	static size_t		GetFileLength(const std::string& sFileName);
	static bool			SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	static bool			LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength);
	static bool			CopyFile(const std::string&	sPathSrc,const std::string& sPathDes);
	static bool			RemoveFile(const std::string& sFileName);
	static bool			RenameFile(const std::string& sPathSrc,const std::string& sPathDes);	

	//·��
	static std::string	StardPath(const std::string& sPath);//��׼��·��(��·���е�\\���滻Ϊ/)Linux��ֻ�ܶ�ȡ"/"������"\"
	static std::string	AbsPathToRelativePath( const std::string& sPath,const std::string& sCmpPath);//�������·��
	static bool			AbsPathToRelativePath(VectorString& vDes,const VectorString& vAbsPath,const std::string& sCmpPath);
	static std::string	TrimPath(const std::string& sPath);//����·��

	//����
	static void			Trace(const std::string& msg);
	static void			OutPut( const std::string& msg );
	static void			OutPutCerr( const std::string& msg );

	//ʱ��
	static time_t		GetNowTime();	//��ȡ��ǰʱ��
private:
	static std::string	AbsPathToRelativePath( const std::string& sAbsPath,const VectorString& vCmpPath);
	static bool			MakePathVector( VectorString& vDes,const std::string& sPath );
};
