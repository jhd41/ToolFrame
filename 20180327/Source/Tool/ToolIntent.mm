#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <UIKit/UIImage.h>

#include "ToolIntent.h"


@interface Reader : NSObject<UINavigationControllerDelegate, UIImagePickerControllerDelegate> {
    UIImage * localImage;
}


@property HIntent * intent;

-(bool)SelImage:(HIntent*) hIntent;

+(Reader*)create;

@end


@implementation Reader

-(void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    [picker dismissModalViewControllerAnimated:YES];
    
//    UIImage * image =[info objectForKey:UIImagePickerControllerEditedImage];
    NSURL * url = [info objectForKey:UIImagePickerControllerMediaURL];
    
    
    [self performSelector:@selector(selectPic:) withObject:url afterDelay:0.1];
}


- (void)selectPic:(NSURL *)url

{

    NSLog(@"url%@", url);
//    NSLog(@"image%@",image);

//    UIImageView * imageView = [[UIImageView alloc] initWithImage:image];

//    imageView.frame = CGRectMake(0, 0, image.size.width, image.size.height);

    //    [self.view addSubview:imageView];

    _intent->CallBackSelImg([[url absoluteString] UTF8String]);
    
 //   [self performSelectorInBackground:@selector(detect:) withObject:nil];

}

-(void)imagePickerControllerDIdCancel:(UIImagePickerController*)picker

{
    
    [picker dismissModalViewControllerAnimated:YES];
    
}

-(bool)SelImage:(HIntent*) hIntent
{
	if (!hIntent)return false;
    
    Reader * reader = [Reader create];
    [reader setIntent:hIntent];
    
	UIImagePickerControllerSourceType sourceType=UIImagePickerControllerSourceTypeCamera;
    
    if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        
        sourceType=UIImagePickerControllerSourceTypePhotoLibrary;
        
    }
    
    UIImagePickerController * picker = [[UIImagePickerController alloc]init];

    picker.delegate = reader;
    
    picker.allowsEditing=YES;
    
    picker.sourceType=sourceType;
    
    [[[UIApplication sharedApplication] keyWindow].rootViewController presentModalViewController:picker animated:YES];
    
	return true;
}


+(Reader*)create
{
    return [[Reader alloc] init];
}

@end

