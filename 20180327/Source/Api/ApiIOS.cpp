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

//判断是否为目录
bool ApiIOS::IsDir(const std::string& sDir)
{
 	struct stat statbuf;
 	if(lstat(sDir.c_str(), &statbuf) ==0)//lstat返回文件的信息，文件信息存放在stat结构中
 	{
 		return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR宏，判断文件类型是否为目录
 	}
 	return false;
}

//判断是否为常规文件
bool ApiIOS::IsFile(const std::string& sPath)
{
	struct stat statbuf;
	if(lstat(sPath.c_str(), &statbuf) ==0)
		return S_ISREG(statbuf.st_mode) != 0;//判断文件是否为常规文件
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
	//如果传入是文件则复制
	if(IsFile(sSrcDir)){
		if (ApiStd::CopyFile(sSrcDir,sDesDir))return true;

		//若复制文件失败尝试创建文件夹再次复制
		if (!MakeDir(ToolFrame::PickDir(sDesDir)))return false;
		return ApiStd::CopyFile(sSrcDir,sDesDir);
	}
		
	//如果传入是文件夹则创建文件夹并复制子目录
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

//参考自 http://www.cnblogs.com/bandy/archive/2012/08/15/2639742.html
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

// 调用memoryInfo()就能拿到内存信息了，它的类型是vm_statistics_data_t。这个结构体有很多字段，在logMemoryInfo()中展示了如何获取它们。注意这些字段大都是页面数，要乘以vm_page_size才能拿到字节数。
// 顺便再简要介绍下：free是空闲内存；active是已使用，但可被分页的（在iOS中，只有在磁盘上静态存在的才能被分页，例如文件的内存映射，而动态分配的内存是不能被分页的）；inactive是不活跃的，也就是程序退出后却没释放的内存，以便加快再次启动，而当内存不足时，就会被回收，因此也可看作空闲内存；wire就是已使用，且不可被分页的。此外，这篇文档也有作介绍。
// 
// 最后你会发现，即使把这些全加起来，也比设备内存少很多，那么剩下的只好当成已被占用的神秘内存了。不过在模拟器上，这4个加起来基本上就是Mac的物理内存量了，相差不到2MB。
// 而总物理内存可以用NSRealMemoryAvailable()来获取，这个函数不需要提供参数，文档里也有记载，我就不写演示代码了。

// /**
//  @method 播放电影
//  */
// -(void)playMovie:(NSString *)fileName{
//     //视频文件路径
//     NSString *path = [[NSBundle mainBundle] pathForResource:fileName ofType:@"mp4"];
//     //视频URL
//     NSURL *url = [NSURL fileURLWithPath:path];
//     //视频播放对象
//     MPMoviePlayerController *movie = [[MPMoviePlayerController alloc] initWithContentURL:url];
//     movie.controlStyle = MPMovieControlStyleFullscreen;
//     [movie.view setFrame:self.view.bounds];
//     movie.initialPlaybackTime = -1;
//     [self.view addSubview:movie.view];
//     // 注册一个播放结束的通知
//     [[NSNotificationCenter defaultCenter] addObserver:self
//                                              selector:@selector(myMovieFinishedCallback:)
//                                                  name:MPMoviePlayerPlaybackDidFinishNotification
//                                                object:movie];
//     [movie play];
// }
// 
// #pragma mark -------------------视频播放结束委托--------------------
// 
// /*
//  @method 当视频播放完毕释放对象　
//  */
// -(void)myMovieFinishedCallback:(NSNotification*)notify
// {
//     //视频播放对象
//     MPMoviePlayerController* theMovie = [notify object];
//     //销毁播放通知
//     [[NSNotificationCenter defaultCenter] removeObserver:self
//                                                     name:MPMoviePlayerPlaybackDidFinishNotification
//                                                   object:theMovie];
//     [theMovie.view removeFromSuperview];
//     // 释放视频对象
//     [theMovie release];
// }


#endif
