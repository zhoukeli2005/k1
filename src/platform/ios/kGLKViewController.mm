//
//  kGLKViewController.m
//  kGame
//
//  Created by qiaokeli on 15/6/6.
//  Copyright (c) 2015年 qiaokeli. All rights reserved.
//

#import "kGLKViewController.h"
#import "platform/kdriver.h"

@implementation kGLKViewController

- (void)start
{
	CGRect sz = [[UIScreen mainScreen] bounds];
	CGFloat scale = [[UIScreen mainScreen] scale];
	klib::kdriver_init(sz.size.width * scale, sz.size.height * scale);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	klib::kdriver_draw();
}

- (void)update
{
	[self.view setNeedsDisplay];
	
	NSTimeInterval deltaTime = [self timeSinceFirstResume];
	
	klib::kdriver_update(deltaTime);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
//	NSLog(@"touchesBegan:%@", event.description);
	klib::ktouch_began_init();
	for(UITouch * touch in event.allTouches) {
		CGPoint pnt = [touch locationInView:nil];
		klib::ktouch_began((__bridge void *)(touch), pnt.x, pnt.y);
	}
	klib::ktouch_began_fini();
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
//	NSLog(@"touchesCancelled:%@", event);
	klib::ktouch_cancelled_init();
	for(UITouch * touch in event.allTouches) {
		CGPoint pnt = [touch locationInView:nil];
		klib::ktouch_cancelled((__bridge void *)(touch), pnt.x, pnt.y);
	}
	klib::ktouch_cancelled_fini();
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
//	NSLog(@"touchesEnded:%@", event);
	klib::ktouch_ended_init();
	for(UITouch * touch in event.allTouches) {
		CGPoint pnt = [touch locationInView:nil];
		klib::ktouch_ended((__bridge void *)(touch), pnt.x, pnt.y);
	}
	klib::ktouch_ended_fini();
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
//	NSLog(@"touchesMoved:%@", event);
	klib::ktouch_moved_init();
	for(UITouch * touch in event.allTouches) {
		CGPoint pnt = [touch locationInView:nil];
		klib::ktouch_moved((__bridge void *)(touch), pnt.x, pnt.y);
	}
	klib::ktouch_moved_fini();
}
@end
