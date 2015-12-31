//
//  kdriver.cpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#include "kdriver.h"
#include "kapp.h"

namespace klib {

	static kapp app;
	
	void kdriver_init(int screen_width, int screen_height)
	{
		app.init();
	}
	
	void kdriver_update(double delta_time)
	{
		
	}
	
	void kdriver_draw()
	{
		
	}

	
	void ktouch_began_init()
	{
	}
	
	void ktouch_began(void * touch_id, int x, int y)
	{
	}
	
	void ktouch_began_fini()
	{
		
	}
	
	void ktouch_ended_init()
	{
		
	}
	
	void ktouch_ended(void * touch_id, int x, int y)
	{
		
	}
	
	void ktouch_ended_fini()
	{
		
	}
	
	void ktouch_moved_init()
	{
		
	}
	
	void ktouch_moved(void * touch_id, int x, int y)
	{
		
	}
	
	void ktouch_moved_fini()
	{
		
	}
	
	void ktouch_cancelled_init()
	{
		
	}
	
	void ktouch_cancelled(void * touch_id, int x, int y)
	{
		
	}
	
	void ktouch_cancelled_fini()
	{
		
	}
}