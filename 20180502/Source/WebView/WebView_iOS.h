//
//  WebView_iOS.h
//  CCXWebview
//
//  Created by Vincent on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface WebView_iOS : NSObject <UIWebViewDelegate>
{
    UIActivityIndicatorView* m_indicatorView;
    UIWebView* m_webview;
    UIButton* m_backButton;
}

- (void)showWebView_x:(float)x y:(float)y width:(float) widht height:(float)height;

- (void)updateURL:(const char*)url;
- (void)updateLocalURL:(const char*)url;
- (void)removeWebView;
- (NSString*)getURL;
- (NSString*)getURLTitle;

- (UIWebView *) getView;

@end
