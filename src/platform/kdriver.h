//
//  kplatform.h
//  klib
//
//  Created by qiaokeli on 15/12/30.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#ifndef k_driver_h_
#define k_driver_h_

#include "kobject.h"

namespace klib {
	
	void kdriver_init(int screen_width, int screen_height);
	
	void kdriver_update(double delta_time);
	
	void kdriver_draw();
	
	// for touches
	void ktouch_began_init();
	void ktouch_began(void * touch_id, int x, int y);
	void ktouch_began_fini();
	
	void ktouch_ended_init();
	void ktouch_ended(void * touch_id, int x, int y);
	void ktouch_ended_fini();
	
	void ktouch_moved_init();
	void ktouch_moved(void * touch_id, int x, int y);
	void ktouch_moved_fini();
	
	void ktouch_cancelled_init();
	void ktouch_cancelled(void * touch_id, int x, int y);
	void ktouch_cancelled_fini();
	
} // namespace klib


#endif /* kplatform_h */
