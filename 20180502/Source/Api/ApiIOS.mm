#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CTCarrier.h>
#import <CTTelephonyNetworkInfo.h>
#import <AudioToolbox/AudioToolbox.h>
#import "Reachability.h"

#include "ApiIOS.h"
#include "ToolStd.h"

std::string ApiIOS::GetRescoreceDir()
{
    NSString *fullpath = [[NSBundle mainBundle]resourcePath];
    std::string sDir = [fullpath UTF8String];
    return MAKE_STRING(sDir +"/");
}

std::string ApiIOS::GetMainBundleDir()
{
    NSString *fullpath = [[NSBundle mainBundle]bundlePath];

    std::string sDir = [fullpath UTF8String];
    return MAKE_STRING(sDir +"/");
}

std::string ApiIOS::GetExeutableDir()
{
    NSString *fullpath = [[NSBundle mainBundle]executablePath];
    
    std::string sDir = [fullpath UTF8String];
    return MAKE_STRING(sDir +"/");
}

std::string ApiIOS::GetCacheDir()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    
    NSString* fullpath = [paths objectAtIndex:0];
    std::string sDir = [fullpath UTF8String];
    return MAKE_STRING(sDir +"/");
}

bool ApiIOS::IsAbsPath( const std::string& sPath )
{
    NSString *nsPath  = [NSString stringWithUTF8String: sPath.c_str()];
	
	return [nsPath isAbsolutePath];
}

std::string ApiIOS::GetLocalCacheDir()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory,NSLocalDomainMask, YES);
	NSString *sDirectory = [paths objectAtIndex:0];
    
    std::string sDir = [sDirectory UTF8String];
    return MAKE_STRING(sDir +"/");
}

std::string ApiIOS::GetDocumentDir()
{
	// save to document folder
	 
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES);
	NSString *sDirectory = [paths objectAtIndex:0];
    
    std::string sDir = [sDirectory UTF8String];
    return MAKE_STRING(sDir +"/");
}

std::string ApiIOS::GetDownloadsDir()
{ 
	// save to document folder
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDownloadsDirectory,NSUserDomainMask,YES);
	NSString *sDirectory = [paths objectAtIndex:0];
    
    std::string sDir = [sDirectory UTF8String];
    return MAKE_STRING(sDir +"/");
}

std::string ApiIOS::GetProcessNameWithOutExt()
{
    NSString *fullpath = [[NSBundle mainBundle]executablePath];
    
	return	ToolFrame::PickFileName([fullpath UTF8String]);
}

uint64 ApiIOS::GetThreadId()
{
	//将当前线程的指针当做ID号返回
   return  (uint64)[NSThread currentThread];
}

bool ApiIOS::MakeDir( const std::string& sDir )
{
    NSString* nsDir  = [NSString stringWithUTF8String: sDir.c_str()];
    
    NSFileManager * fileManager = [NSFileManager defaultManager];
    
    if ([fileManager fileExistsAtPath:nsDir]!=YES) {
        return YES == [fileManager createDirectoryAtPath:nsDir withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return true;
}

std::string ApiIOS::GetLanguageString()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];

	return [languageCode UTF8String ];
}

std::string ApiIOS::GetDeviceName(){
    return [[[UIDevice currentDevice] name] UTF8String ];
}

std::string ApiIOS::GetSystemName(){// "iPhone OS"
    return [[[UIDevice currentDevice] systemName] UTF8String ];
}

std::string ApiIOS::GetSystemVersion(){// "5.1.1"
    return [[[UIDevice currentDevice] systemVersion] UTF8String ];
}

std::string ApiIOS::GetModel(){ // "iPhone" on both devices
    return [[[UIDevice currentDevice] model] UTF8String ];
}

bool ApiIOS::PlayVideo(const std::string& sUrl){
	//playMovie(sUrl.c_str()); //在ApiIos.cpp中
	return true;
}

bool ApiIOS::OpenUrl( const std::string& sUrl )
{
    NSString *nsPath  = [NSString stringWithUTF8String: sUrl.c_str()];
    NSURL * url = [NSURL URLWithString: nsPath];
    [[UIApplication sharedApplication] openURL:url];
	return true;
}

std::string ApiIOS::GetNetWorkType()
{
    NetworkStatus internetStatus = [[Reachability reachabilityForInternetConnection] currentReachabilityStatus];
    //Reachability *reachability   = [Reachability reachabilityWithHostName:@"www.apple.com"];
    //NetworkStatus internetStatus = [reachability currentReachabilityStatus];
    switch (internetStatus) {
        case ReachableViaWiFi:
            return "WIFI";
            break;
        case ReachableViaWWAN:
            //"蜂窝数据";
        {
            CTTelephonyNetworkInfo *info = [[CTTelephonyNetworkInfo alloc] init];
            if(!info)return "";
            NSString *currentStatus = info.currentRadioAccessTechnology;
            if(!currentStatus)return "";
            if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyGPRS"]) {
                return "GPRS";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyEdge"]) {
                return "2.75G EDGE";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyWCDMA"]){
                return "3G";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyHSDPA"]){
                return "3.5G HSDPA";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyHSUPA"]){
                return "3.5G HSUPA";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyCDMA1x"]){
                return "2G";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyCDMAEVDORev0"]){
                return "3G";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyCDMAEVDORevA"]){
                return "3G";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyCDMAEVDORevB"]){
                return "3G";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyeHRPD"]){
                return "HRPD";
            }else if ([currentStatus isEqualToString:@"CTRadioAccessTechnologyLTE"]){
                return "4G";
            }
        }
            break;
        case NotReachable:
            return "";
            
        default:
            break;
    }
    return "";
//    //测试WIFI环境
//    NetworkStatus wifiStatus = [[Reachability reachabilityForLocalWiFi] currentReachabilityStatus];
//    if (wifiStatus == ReachableViaWiFi) {
//        return "wifi";
//    }
//
//    //测试网络连接
//    NetworkStatus internetStatus = [[Reachability reachabilityForInternetConnection] currentReachabilityStatus];
////    if(internetStatus == ReachableVia3G)
////        return "3g";
////    if(internetStatus == ReachableVia2G)
////        return "2g";
//    if(internetStatus == ReachableViaWWAN)
//        return "wwan";
//    return "";
}

int ApiIOS::GetResolutionWidth()
{
	CGRect rect = [[UIScreen mainScreen] bounds];
	CGSize size = rect.size;
	return size.width;
}

int ApiIOS::GetResolutionHeight()
{
	CGRect rect = [[UIScreen mainScreen] bounds];
	CGSize size = rect.size;
	return size.height;
}

std::string ApiIOS::GetOperatorName()
{
	CTTelephonyNetworkInfo *netInfo = [[CTTelephonyNetworkInfo alloc]init];
    if (nullptr  == netInfo) return "";
	CTCarrier*carrier = [netInfo subscriberCellularProvider];
    if (nullptr  == carrier) return "";
    if (nullptr  == carrier.mobileCountryCode) return "";
    if (nullptr  == carrier.mobileNetworkCode) return "";
    
	NSString* sName = [[NSString alloc] initWithFormat:@"%@%@", carrier.mobileCountryCode, carrier.mobileNetworkCode];
	[netInfo release];
	return [sName UTF8String];
}

bool IOS_ScreenShot(UIView *subView,NSString *path){
	//支持retina高分的关键
	if(UIGraphicsBeginImageContextWithOptions != NULL)
	{
		UIGraphicsBeginImageContextWithOptions(subView.frame.size, NO, 0.0);
	} else {
		UIGraphicsBeginImageContext(subView.frame.size);
	}            

	//获取图像
	[subView.layer renderInContext:UIGraphicsGetCurrentContext()];
	UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();

	//保存图像
	return [UIImagePNGRepresentation(image) writeToFile:path atomically:YES];
}

UIView* IOS_FindView(NSString* nsUIName){
	UIView *view = [[[[[UIApplication sharedApplication] windows] objectAtIndex:1] subviews] lastObject];//获得某个window的某个subView
    for (UIView *subView in [view subviews]) {//遍历这个view的subViews
        if ([subView isKindOfClass:NSClassFromString(nsUIName)]) {//找到自己需要的subView
			return subView;
		}
	}
	return nullptr;
}

bool ApiIOS::ScreenShot( const std::string& sFileName )
{
	NSString *nsPath  = [NSString stringWithUTF8String: sFileName.c_str()];
	return true;
}

bool ApiIOS::IsPad()
{
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
}


NSMutableDictionary* getKeychainQuery(NSString* service)
{
    return [NSMutableDictionary dictionaryWithObjectsAndKeys:
            (id)kSecClassGenericPassword, (id)kSecClass,
            service, (id)kSecAttrService,
            service, (id)kSecAttrAccount,
            (id)kSecAttrAccessibleAfterFirstUnlock, (id)kSecAttrAccessible,
            nil];
}

bool ApiIOS::StoreChain(const std::string& sKey,const std::string& sValue)
{
	if(sKey.empty())return false;

	NSString *key  = [NSString stringWithUTF8String: sKey.c_str()];
	NSString *value  = [NSString stringWithUTF8String: sValue.c_str()];

    NSMutableDictionary * keychainQuery = getKeychainQuery(key);
    
    // 删除之前的数据
    SecItemDelete((CFDictionaryRef)keychainQuery);
    // 存入新的数据
    [keychainQuery setObject:[NSKeyedArchiver archivedDataWithRootObject:value] forKey:(id)kSecValueData];
    SecItemAdd((CFDictionaryRef)keychainQuery, NULL);
    
    return true;
}

std::string ApiIOS::ReadChain(const std::string& sKey)
{
	if(sKey.empty())return "";

	NSString *key  = [NSString stringWithUTF8String: sKey.c_str()];

    NSString * strValue = @"";
    
    NSMutableDictionary * keychainQuery = getKeychainQuery(key);
    
    [keychainQuery setObject:(id)kCFBooleanTrue forKey:(id)kSecReturnData];
    [keychainQuery setObject:(id)kSecMatchLimitOne forKey:(id)kSecMatchLimit];
    
    // 查找值
    CFDataRef keyData = NULL;
    if (SecItemCopyMatching((CFDictionaryRef)keychainQuery, (CFTypeRef*)&keyData) == noErr)
    {
        @try
        {
            strValue = [NSKeyedUnarchiver unarchiveObjectWithData:(__bridge NSData*)keyData];
        }
        @catch(NSException* e)
        {
            NSLog(@"Unarchive of %@ failed: %@", key, e);
        }
    }
    
	return [strValue UTF8String];
}

bool ApiIOS::DeleteChain(const std::string& sKey)
{
	if(sKey.empty())return false;

	NSString *key  = [NSString stringWithUTF8String: sKey.c_str()];

    NSMutableDictionary * keychainQuery = getKeychainQuery(key);

    return errSecSuccess == SecItemDelete((CFDictionaryRef)keychainQuery);
}

bool ApiIOS::Vibrator(int nMillTime)
{
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
	return true;
}
