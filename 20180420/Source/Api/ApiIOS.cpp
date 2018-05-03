#include "ApiIOS.h"

#if MACRO_TARGET_OS == MACRO_OS_IOS

#include "ToolStd.h"
#include "ApiStd.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>
#include <unistd.h>
#include <mach/mach.h> 

UINT64 ApiIOS::GetNowTimeMill()
{
	struct timeb tp;
	ftime(&tp);
	return ((UINT64)(tp.time)*1000) + tp.millitm;
}

bool ApiIOS::SaveFile( const std::string& sFileName,const void* pBuffer,size_t uLength)
{
	return ApiStd::SaveFile(sFileName,pBuffer,uLength);
}

bool ApiIOS::LoadFile( const std::string& sFileName,void* pBuffer,size_t uLength)
{
	return ApiStd::LoadFile(sFileName,pBuffer,uLength);
}

std::string  ApiIOS::GetWorkDir(){
	return getcwd(nullptr, 0);
}

bool ApiIOS::SetWorkDir( const std::string& sDir )
{
	return 0 == chdir(sDir.c_str());
}

size_t ApiIOS::GetFileLength( const std::string& sFileName)
{
	return ApiStd::GetFileLength(sFileName);
}

bool ApiIOS::IsFileExist( const std::string& sFileName)
{
	return ApiStd::IsFileExist(sFileName);
}

bool ApiIOS::RemoveFile( const std::string& sFileName)
{
	return ApiStd::RemoveFile(sFileName); 
}

bool ApiIOS::RenameFile( const std::string& sPathSrc,const std::string& sPathDes)
{
	return ApiStd::RenameFile(sPathSrc,sPathDes);
}

//�ж��Ƿ�ΪĿ¼
bool ApiIOS::IsDir(const std::string& sDir)
{
 	struct stat statbuf;
 	if(lstat(sDir.c_str(), &statbuf) ==0)//lstat�����ļ�����Ϣ���ļ���Ϣ�����stat�ṹ��
 	{
 		return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR�꣬�ж��ļ������Ƿ�ΪĿ¼
 	}
 	return false;
}

//�ж��Ƿ�Ϊ�����ļ�
bool ApiIOS::IsFile(const std::string& sPath)
{
	struct stat statbuf;
	if(lstat(sPath.c_str(), &statbuf) ==0)
		return S_ISREG(statbuf.st_mode) != 0;//�ж��ļ��Ƿ�Ϊ�����ļ�
	return false;
}

bool ApiIOS::RemoveDir( const std::string& sPath)
{
	return ApiRemoveDir(sPath);
}

bool ApiIOS::ApiRemoveDir( const std::string& sPath )
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


bool ApiIOS::CopyDir( const std::string& sSrcDir,const std::string& sDesDir )
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
		if(ToolFrame::IsSpecialDir(dir_info->d_name))
			continue;

		if (!CopyDir(sSrcDir +"/" + dir_info->d_name,sDesDir +"/" + dir_info->d_name))return false;
	}

	return true;
}

BOOL ApiIOS::ApiMemoryInfo(vm_statistics_data_t *vmStats) { 
	mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT; 
	kern_return_t kernReturn = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)vmStats, &infoCount); 

	return kernReturn == KERN_SUCCESS; 
} 

UINT64 ApiIOS::GetProcessMemoryUsed()
{
	vm_statistics_data_t vmStats;
	if (!ApiMemoryInfo(&vmStats))return 0;
	
	return (vmStats.active_count + vmStats.wire_count) * vm_page_size;
}

UINT64 ApiIOS::GetProcessMemoryFree()
{
	vm_statistics_data_t vmStats;
	if (!ApiMemoryInfo(&vmStats))return 0;

	return (vmStats.free_count + vmStats.inactive_count) * vm_page_size;
}

std::string ApiIOS::GetDirByType( int eDirType )
{
	switch(eDirType)
	{
	case DIR_TYPE_WORKING:
		return GetMainBundleDir();
		break;
	case DIR_TYPE_WRITEABLE:
		return GetDocumentDir();
		break;
	case DIR_TYPE_CACHE:
		return GetCacheDir();
		break;
	case DIR_TYPE_EXT_WORKING:
		return MAKE_STRING(GetLocalCacheDir()<< GetProcessNameWithOutExt()<<"/");
		break;
	case DIR_TYPE_EXT_WRITEABLE:
		return MAKE_STRING(GetLocalCacheDir() << GetProcessNameWithOutExt() << "/");
		break;
	case DIR_TYPE_EXT_CACHE:
		return MAKE_STRING(GetLocalCacheDir() << GetProcessNameWithOutExt() << "/Cache/");
		break;
	case DIR_TYPE_EXT_ROOT:
		return GetLocalCacheDir();
		break;
	}

	return "";
}

std::string ApiIOS::GetPlatformVer()
{
	std::stringstream sStream;
	sStream<<GetSystemName()<<" "<<GetSystemVersion();
	return sStream.str();
}

int ApiIOS::GetProcessId()
{
	return getpid();
}

//�ο��� http://www.cnblogs.com/bandy/archive/2012/08/15/2639742.html
// void logMemoryInfo() { 
// 	vm_statistics_data_t vmStats; 
// 
// 	if (memoryInfo(&vmStats)) { 
// 		NSLog(@"free: %u\nactive: %u\ninactive: %u\nwire: %u\nzero fill: %u\nreactivations: %u\npageins: %u\npageouts: %u\nfaults: %u\ncow_faults: %u\nlookups: %u\nhits: %u", 
// 			vmStats.free_count * vm_page_size, 
// 			vmStats.active_count * vm_page_size, 
// 			vmStats.inactive_count * vm_page_size, 
// 			vmStats.wire_count * vm_page_size, 
// 			vmStats.zero_fill_count * vm_page_size, 
// 			vmStats.reactivations * vm_page_size, 
// 			vmStats.pageins * vm_page_size, 
// 			vmStats.pageouts * vm_page_size, 
// 			vmStats.faults, 
// 			vmStats.cow_faults, 
// 			vmStats.lookups, 
// 			vmStats.hits 
// 			); 
// 	} 
// } 

// ����memoryInfo()�����õ��ڴ���Ϣ�ˣ�����������vm_statistics_data_t������ṹ���кܶ��ֶΣ���logMemoryInfo()��չʾ����λ�ȡ���ǡ�ע����Щ�ֶδ���ҳ������Ҫ����vm_page_size�����õ��ֽ�����
// ˳���ټ�Ҫ�����£�free�ǿ����ڴ棻active����ʹ�ã����ɱ���ҳ�ģ���iOS�У�ֻ���ڴ����Ͼ�̬���ڵĲ��ܱ���ҳ�������ļ����ڴ�ӳ�䣬����̬������ڴ��ǲ��ܱ���ҳ�ģ���inactive�ǲ���Ծ�ģ�Ҳ���ǳ����˳���ȴû�ͷŵ��ڴ棬�Ա�ӿ��ٴ������������ڴ治��ʱ���ͻᱻ���գ����Ҳ�ɿ��������ڴ棻wire������ʹ�ã��Ҳ��ɱ���ҳ�ġ����⣬��ƪ�ĵ�Ҳ�������ܡ�
// 
// �����ᷢ�֣���ʹ����Щȫ��������Ҳ���豸�ڴ��ٺܶ࣬��ôʣ�µ�ֻ�õ����ѱ�ռ�õ������ڴ��ˡ�������ģ�����ϣ���4�������������Ͼ���Mac�������ڴ����ˣ�����2MB��
// ���������ڴ������NSRealMemoryAvailable()����ȡ�������������Ҫ�ṩ�������ĵ���Ҳ�м��أ��ҾͲ�д��ʾ�����ˡ�

// /**
//  @method ���ŵ�Ӱ
//  */
// -(void)playMovie:(NSString *)fileName{
//     //��Ƶ�ļ�·��
//     NSString *path = [[NSBundle mainBundle] pathForResource:fileName ofType:@"mp4"];
//     //��ƵURL
//     NSURL *url = [NSURL fileURLWithPath:path];
//     //��Ƶ���Ŷ���
//     MPMoviePlayerController *movie = [[MPMoviePlayerController alloc] initWithContentURL:url];
//     movie.controlStyle = MPMovieControlStyleFullscreen;
//     [movie.view setFrame:self.view.bounds];
//     movie.initialPlaybackTime = -1;
//     [self.view addSubview:movie.view];
//     // ע��һ�����Ž�����֪ͨ
//     [[NSNotificationCenter defaultCenter] addObserver:self
//                                              selector:@selector(myMovieFinishedCallback:)
//                                                  name:MPMoviePlayerPlaybackDidFinishNotification
//                                                object:movie];
//     [movie play];
// }
// 
// #pragma mark -------------------��Ƶ���Ž���ί��--------------------
// 
// /*
//  @method ����Ƶ��������ͷŶ���
//  */
// -(void)myMovieFinishedCallback:(NSNotification*)notify
// {
//     //��Ƶ���Ŷ���
//     MPMoviePlayerController* theMovie = [notify object];
//     //���ٲ���֪ͨ
//     [[NSNotificationCenter defaultCenter] removeObserver:self
//                                                     name:MPMoviePlayerPlaybackDidFinishNotification
//                                                   object:theMovie];
//     [theMovie.view removeFromSuperview];
//     // �ͷ���Ƶ����
//     [theMovie release];
// }


#endif
