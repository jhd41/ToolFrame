//
//  WebView_iOS.m
//  CCXWebview
//
//  Created by Vincent on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "WebView_iOS.h"

//IOS代码基于Cocos2dx编写以后要修改 SongJ
//#ifdef MACRO_LIB_COCOS2D

//#import "CCEAGLView-ios.h"
//#import "cocos2d.h"

#define IS_RETINA ([[UIScreen mainScreen] respondsToSelector:@selector(displayLinkWithTarget:selector:)] && ([UIScreen mainScreen].scale == 2.0))

@implementation WebView_iOS

- (void)showWebView_x:(float)x y:(float)y width:(float) width height:(float)height
{
	if (IS_RETINA) {
		x = x / 2;
		y = y / 2;
		width = width / 2;
		height = height / 2;
	}
    
	x += 0.5f;
	y += 0.5f;
	width += 0.5f;
	height += 0.5f;

    UIWebView* tempWebView = [[UIWebView alloc] initWithFrame:CGRectZero];
    
    // 获取 iOS 默认的 UserAgent，可以很巧妙地创建一个空的UIWebView来获取：
    NSString *userAgent = [tempWebView stringByEvaluatingJavaScriptFromString:@"navigator.userAgent"];
    
    //[[NSUserDefaults standardUserDefaults] unregisterDefaultForKey:@"UserAgent"];
    //修改UserAgent;
    NSString *UserAgent=@"ali213app";
    
    NSString *customUserAgent = [userAgent stringByAppendingFormat:@" %@", UserAgent];
    NSDictionary *dictionary = [[NSDictionary alloc] initWithObjectsAndKeys:customUserAgent,@"UserAgent", nil];
    [[NSUserDefaults standardUserDefaults] registerDefaults:dictionary];
    
   // [[NSUserDefaults standardUserDefaults] synchronize];
    
    [tempWebView release];
    
    
	if(m_webview){
		[m_webview setFrame:CGRectMake(x, y, width , height)];
		return;
	}
    
    m_webview = [[UIWebView alloc] initWithFrame:CGRectMake(x, y, width , height)];
    [m_webview setDelegate:self];
    /*
    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
    if (glview)
    {
        CCEAGLView *eaglview = (__bridge CCEAGLView*) glview->getEAGLView();
        
        if (eaglview)
        {
            // your code
            [eaglview addSubview:m_webview];
            /*
             m_backButton = [UIButton buttonWithType:UIButtonTypeCustom];
             UIImage *img = [UIImage imageNamed:@"CloseNormal.png"];
             m_backButton.frame = CGRectMake(widht-3-img.size.width, 3, img.size.width, img.size.height);
             //                btn.backgroundColor = [UIColor clearColor];
             //                [btn setTitle:@"点击" forState:UIControlStateNormal];
             [m_backButton setImage:img forState:UIControlStateNormal];
             [m_backButton setImage:[UIImage imageNamed:@"CloseSelected.png"] forState:UIControlStateSelected];
             [m_backButton addTarget:self action:@selector(removeWebView) forControlEvents:UIControlEventTouchUpInside
             ];
             
             [eaglview addSubview:m_backButton];
             */
            
       //     m_indicatorView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
       //     m_indicatorView.center = CGPointMake(width / 2, height / 2);
    /*
            m_indicatorView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
            m_indicatorView.center = CGPointMake(width / 2, height / 2);
            m_indicatorView.backgroundColor = UIColor.grayColor;
            m_indicatorView.alpha = 0.5;
            m_indicatorView.layer.cornerRadius = 6;
            m_indicatorView.layer.masksToBounds = YES;
            
            [m_indicatorView setHidesWhenStopped:YES];
            [eaglview addSubview:m_indicatorView];
        }
    }
*/
    
    //        [[CCEAGLView sharedEGLView] addSubview:m_webview];
    //   [m_webview release];
    
    m_webview.backgroundColor = [UIColor whiteColor];
    m_webview.opaque = NO;
    m_webview.scrollView.bounces = NO;
    
    for (UIView *aView in [m_webview subviews])
    {
        if ([aView isKindOfClass:[UIScrollView class]])
        {
            UIScrollView* scView = (UIScrollView *)aView;
            
            //                [(UIScrollView *)aView setShowsVerticalScrollIndicator:NO]; //右侧的滚动条 （水平的类似）
            [scView setShowsHorizontalScrollIndicator:NO];
                            scView.bounces = NO;
            
            for (UIView *shadowView in aView.subviews)
            {
                if ([shadowView isKindOfClass:[UIImageView class]])
                {
                    shadowView.hidden = YES;  //上下滚动出边界时的黑色的图片 也就是拖拽后的上下阴影
                }
            }
        }
    }
    
    
    //		[m_webview setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
}

- (void)updateURL:(const char*)url
{
    NSString *request = [NSString stringWithUTF8String:url];
    [m_webview loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:request]
                                            cachePolicy:NSURLRequestReloadIgnoringLocalCacheData
                                        timeoutInterval:60]];
}

- (void)updateLocalURL:(const char*)url
{
	 NSString *request = [NSString stringWithUTF8String:url];
	[m_webview loadRequest:[NSURLRequest requestWithURL:[NSURL fileURLWithPath:request]]];
}

- (void)removeWebView
{
	[m_webview setDelegate:nullptr];
    [m_indicatorView stopAnimating];
    [m_webview stopLoading];

    [m_indicatorView removeFromSuperview];
    [m_backButton removeFromSuperview];
    [m_webview removeFromSuperview];
    m_webview = nullptr;
}

- (NSString*)getURL
{
    return m_webview.request.URL.absoluteString;
}

- (NSString*)getURLTitle
{
    return [m_webview stringByEvaluatingJavaScriptFromString:@"document.title"];
}

#pragma mark - WebView
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return true;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    [m_indicatorView startAnimating];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    [m_indicatorView stopAnimating];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [m_indicatorView stopAnimating];
}

- (UIWebView *) getView
{
    return m_webview;
}

@end

//#endif //MACRO_LIB_COCOS2D
