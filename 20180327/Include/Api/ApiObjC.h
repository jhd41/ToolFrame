#pragma once
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include <string>

class ApiObjC
{
public:
	static UIImage * Snapshot(UIView * view);
	static bool SaveImageToFile(UIImage * image, const std::string & fName);
	static bool ScreenShot(UIView * view, const std::string & fName);
public:
	ApiObjC(void);
	virtual ~ApiObjC(void);
};

