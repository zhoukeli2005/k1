//
//  AppDelegate.m
//  kGame
//
//  Created by qiaokeli on 15/6/6.
//  Copyright (c) 2015年 qiaokeli. All rights reserved.
//

#import "AppDelegate.h"
#import "kGLKViewController.h"
#import <GLKit/GLKit.h>

@interface AppDelegate () {
}
- (void)initGLView;
@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
	// Override point for customization after application launch.
	self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	[self.window makeKeyAndVisible];

	[self initGLView];
	
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
	// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)initGLView {
	EAGLContext * eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
	[EAGLContext setCurrentContext: eglContext];

	GLKView * view = [[GLKView alloc] initWithFrame: self.window.bounds context: eglContext];
	[self.window addSubview: view];

	view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
	view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
	view.drawableStencilFormat = GLKViewDrawableStencilFormat8;

	// enable multi-sample
	view.drawableMultisample = GLKViewDrawableMultisample4X;
	
	view.multipleTouchEnabled = YES;

	kGLKViewController * viewController = [[kGLKViewController alloc] init];
	view.delegate = viewController;
	viewController.view = view;

	NSLog(@"view is:%p, %p", view, viewController.view);

	self.window.rootViewController = viewController;

	viewController.preferredFramesPerSecond = 60;

	NSLog(@"AppDelegate:initGLView");
	
	[viewController start];
}
@end
