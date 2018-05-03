#include "ApiAndroid.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include <stdarg.h>
#include <android/log.h>

#include "ToolFrame.h"
#include "JniCaller.h"
#include "ApiStd.h"
#include "ApiJni.h"
#include "JniCaller.h"

#include "ZipFile.h"

//����ʹ��ϵͳʱ��
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>

#if __ANDROID_API__ <= 8
	#include <sys/timeb.h>
#endif

//����
#if __ANDROID_API__ <= 8

bool sysinfo(struct sysinfo* info){
	return true;
}

#endif

#include "android/asset_manager_jni.h"

USING_NS_TOOL_FRAME;

static AAssetManager* g_pAssetMgr = NULL;

void ApiAndroid::SetJavaVM(JavaVM* pJavaVM)
{
	ApiJni::SetJavaVM(pJavaVM);

	jobject assetManager = ApiJni::CallJniReturnJObject("com/CloudCity/Lib/ApiAndroid", "GetAssetManager");

	CJniEnvLock lock;
	g_pAssetMgr = AAssetManager_fromJava(lock.GetEnv(), assetManager);
}

UINT64 ApiAndroid::GetNowTimeMill(){
	//return ToolFrame::GetNowTime();
	
	//����
#if __ANDROID_API__ <= 8

	//ʹ��Linux��������
	struct timeb tp;
	ftime(&tp);
	return ((UINT64)(tp.time) * 1000) + tp.millitm;
#endif

	struct timeval tv;
	gettimeofday(&tv, NULL);

	return ((UINT64)(tv.tv_sec) * 1000) + tv.tv_usec / 1000;
}

void ApiAndroid::LogDebug(const std::string& sMsg){
     OutPut(sMsg,"Debug");
}

void ApiAndroid::OutPut(const std::string& sMsg,const std::string& sTag){
	ApiLogPrintDebug(sTag,sMsg);
}
std::string ApiAndroid::GetLanguageString()
{
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetLanguage");
}

std::string ApiAndroid:: GetProcessName(){
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetProcessName");
}

std::string ApiAndroid:: GetPackageName(){
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetPackageName");
}

std::string ApiAndroid:: GetDataDir(){
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetDataDir");
}

std::string ApiAndroid:: GetSourceDir(){
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetSourceDir");
}

std::string ApiAndroid::GetCacheDir()
{
	//getCacheDir()�������ڻ�ȡ/data/data//cacheĿ¼
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetCacheDir");
}

std::string ApiAndroid::GetFilesDir()
{
	//getFilesDir()�������ڻ�ȡ/data/data//filesĿ¼
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetFilesDir");
}

bool ApiAndroid::IsExtemalStorageReady()
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","IsExtemalStorageReady");
}

std::string ApiAndroid::GetExtemalStorageDir()
{
	//sdcardĿ¼
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetExtemalStorageDir");
}

bool ApiAndroid::IsAbsPath( const std::string& sPath ){
	return ToolFrame::IsBeginWith(sPath,"/");
}

void ApiAndroid::Sleep( int nTimeMill ){
	return ApiJni::CallJniReturnVoid("com/CloudCity/Lib/ApiAndroid","Sleep",nTimeMill);
}

uint64 ApiAndroid::GetThreadId(){
	return (uint64)pthread_self();
}

bool ApiAndroid::MakeDir( const std::string& sDir){
	if (sDir.empty())return false;
	return MakeDirWithJni(sDir);
}

bool ApiAndroid::IsFileExist( const std::string& sFileName)
{
	if (sFileName.empty())return false;

	//����Ǿ���·��ֱ�ӱ�׼�� ���� ��assets��ȥ��ȡ
	if (!IsAbsPath(sFileName)){
		AAsset* pAsset = AAssetManager_open(g_pAssetMgr, sFileName.c_str(), AASSET_MODE_UNKNOWN);
		if (!pAsset)return false;
		AAsset_close(pAsset);
		return true;
	}
	return ApiStd::IsFileExist(sFileName);
}

size_t ApiAndroid::GetFileLength( const std::string& sFileName )
{
	if (sFileName.empty())return false;

	//����Ǿ���·��ֱ�ӱ�׼�� ���� ��assets��ȥ��ȡ
	if (!IsAbsPath(sFileName))
	{
		AAsset* pAsset = AAssetManager_open(g_pAssetMgr, sFileName.c_str(), AASSET_MODE_UNKNOWN);
		if (!pAsset)return 0;

		size_t tLength = AAsset_getLength(pAsset);
		AAsset_close(pAsset);
		return tLength;
	}
	return ApiStd::GetFileLength(sFileName);
}

bool ApiAndroid::LoadFile( const std::string& sFileName,void* pBuffer,size_t uLength)
{
	if (sFileName.empty())return false;
	if (!pBuffer)return false;
	if (uLength <=0)return false;

	//���ж�����������Ƿ���assets
	if (!IsAbsPath(sFileName)) {
		AAsset* pAsset = AAssetManager_open(g_pAssetMgr, sFileName.c_str(), AASSET_MODE_UNKNOWN);
		if (!pAsset)return false;

		int iRet = AAsset_read(pAsset, pBuffer, uLength);
		if (iRet <= 0) {
			AAsset_close(pAsset);
			return false;
		}
		AAsset_close(pAsset);
		return true;
	}
	return ApiStd::LoadFile(sFileName,pBuffer,uLength);
}

bool ApiAndroid::SaveFile( const std::string& sFileName,const void* pBuffer,size_t uLength)
{
	return ApiStd::SaveFile(sFileName,pBuffer,uLength);
}

bool ApiAndroid::RemoveFile( const std::string& sFileName)
{
	return ApiStd::RemoveFile(sFileName);
}

bool ApiAndroid::RenameFile( const std::string& sPathSrc,const std::string& sPathDes)
{
	return ApiStd::RenameFile(sPathSrc,sPathDes);
}

//�ж��Ƿ�ΪĿ¼
bool ApiAndroid::IsDir(const std::string& sDir)
{
	struct stat statbuf;
	if(lstat(sDir.c_str(), &statbuf) ==0)//lstat�����ļ�����Ϣ���ļ���Ϣ�����stat�ṹ��
	{
		return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR�꣬�ж��ļ������Ƿ�ΪĿ¼
	}
	return false;
}

//�ж��Ƿ�Ϊ�����ļ�
bool ApiAndroid::IsFile(const std::string& sPath)
{
	struct stat statbuf;
	if(lstat(sPath.c_str(), &statbuf) ==0)
		return S_ISREG(statbuf.st_mode) != 0;//�ж��ļ��Ƿ�Ϊ�����ļ�
	return false;
}

bool ApiAndroid::RemoveDir( const std::string& sPath )
{
	return ApiRemoveDir(sPath);
}

bool ApiAndroid::CopyDir( const std::string& sSrcDir,const std::string& sDesDir )
{
	//����������ļ�����
	if(IsFile(sSrcDir)){
		if (ApiStd::CopyFile(sSrcDir,sDesDir))return true;

		//�������ļ�ʧ�ܳ��Դ����ļ����ٴθ���
		if (!MakeDir(ToolFrame::PickDir(sDesDir)))return false;
		return ApiStd::CopyFile(sSrcDir,sDesDir);
	}

	//����������ļ����򴴽��ļ��в�������Ŀ¼
	if (!MakeDir(sDesDir))return false;

	DIR *dir  = opendir(sSrcDir.c_str());
	if( nullptr == dir)
		return false;

	dirent *dir_info = nullptr;
	while((dir_info = readdir(dir)) != nullptr)
	{
		if(IsSpecialDir(dir_info->d_name))
			continue;

		if (!CopyDir(sSrcDir +"/" + dir_info->d_name,sDesDir +"/" + dir_info->d_name))return false;
	}

	return true;
}

bool ApiAndroid::IsSpecialDir(const char *path)
{
	return strcmp(path, ".") == 0 || strcmp(path, "..") == 0;
}

UINT64 ApiAndroid::GetProcessMemoryUsed()
{
	struct sysinfo s_info;
	sysinfo(& s_info);
	return s_info.mem_unit;
}

UINT64 ApiAndroid::GetProcessMemoryFree()
{
	struct sysinfo s_info;
	sysinfo(& s_info);
	return s_info.freeram;
}

bool ApiAndroid::MakeDirWithJni( const std::string& sDir )
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","MakeDir",sDir);
}

int64 ApiAndroid::GetThreadIdWithJni()
{
	return ApiJni::CallJniReturnInt("com/CloudCity/Lib/ApiAndroid","GetThreadId");
}

bool ApiAndroid::ApiRemoveDir( const std::string& sPath )
{
	if(IsFile(sPath))
	{
		remove(sPath.c_str());
		return true;
	}
	if(IsDir(sPath))
	{
		DIR *dir  = opendir(sPath.c_str());
		if( nullptr == dir)
			return false;

		dirent *dir_info = nullptr;
		while((dir_info = readdir(dir)) != nullptr)
		{
			if(ToolFrame::IsSpecialDir(dir_info->d_name))
				continue;

			std::string sFilePath = sPath +"/" + dir_info->d_name;
			ApiRemoveDir(sFilePath);
			rmdir(sFilePath.c_str());
		}
		rmdir(sPath.c_str());
		return true;
	}

	return false;
}

std::string ApiAndroid::GetDirByType( int eDirType )
{
	switch(eDirType)
	{
	case DIR_TYPE_WORKING:
		return "";//����Ҫ���ء���Ϊ��Դ�ļ�����apk��ѹ������ļ���/data/app/���� Ŀ¼�¡�
		break;
	case DIR_TYPE_WRITEABLE:
		{
			std::stringstream sStream;
			sStream<<"/data/data/"<<GetPackageName()<<"/";
			return sStream.str();
		}
		break;
	case DIR_TYPE_CACHE:
		return GetCacheDir();
		break;
	case DIR_TYPE_EXT_WORKING:
		{
			std::stringstream sStream;
			sStream << GetExtemalStorageDir() << GetPackageName() << "/";
			return sStream.str();
		}
		break;
	case DIR_TYPE_EXT_WRITEABLE:
		{
			std::stringstream sStream;
			sStream << GetExtemalStorageDir() << GetPackageName() << "/";
			return sStream.str();
		}
		break;
	case DIR_TYPE_EXT_CACHE:
		{
			std::stringstream sStream;
			sStream << GetExtemalStorageDir() << GetPackageName() << "/Cache/";
			return sStream.str();
		}
		break;
	case DIR_TYPE_EXT_ROOT:
		return GetExtemalStorageDir();
		break;
	}

	return "";
}

std::string ApiAndroid::GetPlatformVer()
{
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetPlatformVer");
}

std::string ApiAndroid::GetModel()
{
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetModel");
}

bool ApiAndroid::IsPad()
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid", "IsTab");
}

bool ApiAndroid::Vibrator(int nMillTime)
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid", "Vibrator", nMillTime);
}

bool ApiAndroid::PlayVideo(const std::string& sUrl, const std::string& sType)
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid", "PlayVideo", sUrl, sType);
}

bool ApiAndroid::PlayVideo(const std::string& sUrl)
{
	//SongJ ��Ƶ����δ�ж�
	return PlayVideo(sUrl, "video/mp4");
}

bool ApiAndroid::OpenUrl(const std::string& sUrl)
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","OpenUrl",sUrl);
}

std::string ApiAndroid::GetNetWorkType()
{
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetNetWorkType");
}

std::string ApiAndroid::GetMacAddress()
{
	//���صõ�14:ff:aa:aa:70
	//������Ҫ��ͳһ��ʽΪ 14-ED-FD- �ĸ�ʽ
	std::string sMac = ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetMacAddress");
	ToolFrame::Replace(sMac,":","-");
	std::string sMacFormatted = ToolFrame::ToUpperCase(sMac);
	return sMacFormatted;
}

int ApiAndroid::GetResolutionWidth()
{
	return ApiJni::CallJniReturnInt("com/CloudCity/Lib/ApiAndroid","GetResolutionWidth");
}

int ApiAndroid::GetResolutionHeight()
{
	return ApiJni::CallJniReturnInt("com/CloudCity/Lib/ApiAndroid","GetResolutionHeight");
}

std::string ApiAndroid::GetOperatorName()
{
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","GetOperatorName");
}

void ApiAndroid::ApiLogPrintVerbose(const std::string& sTag, const std::string& sMsg)
{
	__android_log_print(ANDROID_LOG_VERBOSE, sTag.c_str(), sMsg.c_str(), "");
}

void ApiAndroid::ApiLogPrintDebug(const std::string& sTag, const std::string& sMsg)
{
	__android_log_print(ANDROID_LOG_DEBUG, sTag.c_str(), sMsg.c_str(), "");
}

void ApiAndroid::ApiLogPrintInfo(const std::string& sTag, const std::string& sMsg)
{
	__android_log_print(ANDROID_LOG_INFO, sTag.c_str(), sMsg.c_str(), "");
}

void ApiAndroid::ApiLogPrintWarn(const std::string& sTag, const std::string& sMsg)
{
	__android_log_print(ANDROID_LOG_WARN, sTag.c_str(), sMsg.c_str(), "");
}

void ApiAndroid::ApiLogPrintError(const std::string& sTag, const std::string& sMsg)
{
	__android_log_print(ANDROID_LOG_ERROR, sTag.c_str(), sMsg.c_str(), "");
}

uint ApiAndroid::GetThreadAmount()
{
	return ApiJni::CallJniReturnInt("com/CloudCity/Lib/ApiAndroid","GetThreadAmount");
}

int ApiAndroid::GetProcessId()
{
	return getpid();
}

#endif
