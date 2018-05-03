#include "ApiObjC.h"

ApiObjC::ApiObjC(void)
{
}

ApiObjC::~ApiObjC(void)
{
}

UIImage * ApiObjC::Snapshot(UIView * view)
{
		UIGraphicsBeginImageContext(view.bounds.size);

		CGContextRef context = UIGraphicsGetCurrentContext();

		[view.layer renderInContext:context];
		UIImage *image = UIGraphicsGetImageFromCurrentImageContext();

		UIGraphicsEndImageContext();

		return image;
}

bool ApiObjC::SaveImageToFile(UIImage * image, const std::string & fName)
{
		if (!image) return  false;

		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES);

		NSString *filePath = [[paths objectAtIndex:0] stringByAppendingPathComponent:[NSString stringWithUTF8String: fName.c_str()]];

		BOOL result = [UIImagePNGRepresentation(image) writeToFile: filePath    atomically:YES];

		return result;
}

bool ApiObjC::ScreenShot(UIView * view, const std::string & fName){
	return SaveImageToFile(Snapshot(view),fName);
}
