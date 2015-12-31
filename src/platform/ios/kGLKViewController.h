//
//  kGLKViewController.h
//  kGame
//
//  Created by qiaokeli on 15/6/6.
//  Copyright (c) 2015年 qiaokeli. All rights reserved.
//

#import <GLKit/GLKit.h>

#import "AppDelegate.h"

@interface kGLKViewController : GLKViewController

- (void)start;

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect;
- (void)update;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

@end
