#include "render/kTexture.h"
#include "io/kFile.h"
#include "log/kLog.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

k_namespace_begin
render_namespace_begin

void kTexture::_load_file()
{
	boost::shared_ptr<io::kFile> file = boost::make_shared<io::kFile>(filename_);
	if(!file->exist()) {
		return;
	}
	
	if(filename_.rfind(".jpg") != std::string::npos) {
		info_.format = E_TEXTURE_FORMAT::E_JPG;
	} else if (filename_.rfind(".png") != std::string::npos) {
		info_.format = E_TEXTURE_FORMAT::E_PNG;
	} else {
		log::warn("Not support Texture Format:%s", filename_.c_str());
		return;
	}
	
	std::string data = file->read();
	CGImageRef CGImage;
	NSData * data_ns;
	
	data_ns = [NSData dataWithBytes:data.c_str() length:data.size()];
	CGImage = [[UIImage imageWithData:data_ns] CGImage];
	
	info_.width = CGImageGetWidth(CGImage);
	info_.height = CGImageGetHeight(CGImage);
	
	CGImageAlphaInfo alpha_info = CGImageGetAlphaInfo(CGImage);
	info_.has_alpha = (alpha_info == kCGImageAlphaFirst) ||
						(alpha_info == kCGImageAlphaLast) ||
						(alpha_info == kCGImageAlphaPremultipliedFirst) ||
						(alpha_info == kCGImageAlphaPremultipliedLast);
	
	float system_version = [[[UIDevice currentDevice] systemVersion] floatValue];
	if(system_version < 5.0f) {
		info_.has_alpha |= alpha_info == kCGImageAlphaNoneSkipLast;
	}
	
	CGColorSpaceRef color_space = CGImageGetColorSpace(CGImage);
	if(!color_space) {
		log::warn("Get color_space Failed:%s", filename_.c_str());
		return;
	}
	
	if(info_.has_alpha) {
		alpha_info = kCGImageAlphaPremultipliedLast;
		info_.pre_multiply_alpha = true;
	} else {
		alpha_info = kCGImageAlphaNoneSkipLast;
		info_.pre_multiply_alpha = false;
	}
	
	// change to RGBA8888
	info_.has_alpha = true;
	info_.bit_per_component = 8;
	
	unsigned char * image_data = new unsigned char[info_.width * info_.height * 4];
	color_space = CGColorSpaceCreateDeviceRGB();
	CGContextRef context = CGBitmapContextCreate(image_data,
												 info_.width,
												 info_.height,
												 info_.bit_per_component,
												 4 * info_.width,
												 color_space,
												 alpha_info | kCGBitmapByteOrder32Big);
	CGContextClearRect(context, CGRectMake(0, 0, info_.width, info_.height));
	CGContextDrawImage(context, CGRectMake(0, 0, info_.width, info_.height), CGImage);
	CGContextRelease(context);
	CFRelease(color_space);
	
	_init_with_data(image_data);
	
	delete [] image_data;
}

render_namespace_end
k_namespace_end