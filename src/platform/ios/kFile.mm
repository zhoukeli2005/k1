#import <Foundation/Foundation.h>
#include "kFile.h"
#include "log/kLog.h"

k_namespace_begin
io_namespace_begin

struct kFile_platform {
	NSData * data_;
	NSString * fullname_;
	
	kFile_platform() : data_(NULL), fullname_(NULL) {}
};

kFile::kFile(const std::string & filename)
{
	kFile_platform * platform = new kFile_platform;
	
	filename_ = filename;

	NSString * bundleResoucePath_objc = [[NSBundle mainBundle] resourcePath];
	fullname_ = [bundleResoucePath_objc UTF8String];
	fullname_.append("/");
	fullname_.append(filename_);

	platform->fullname_ = [NSString stringWithUTF8String: fullname_.c_str()];
	
	exist_ = [[NSFileManager defaultManager] fileExistsAtPath: platform->fullname_];
	if(!exist_) {
		log::info("File Not Exist:%s", filename_.c_str());
	}
	
	platform_ = platform;
}

kFile::~kFile()
{
	kFile_platform * platform = (kFile_platform *)platform_;
	/*
	if(platform->data_) {
		[platform->data_ release];
	}
	if(platform->fullname_) {
		[platform->fullname_ release];
	}*/
	
	delete platform;
}

static void iload(kFile_platform * platform)
{
	if(!platform->data_) {
		platform->data_ = [[NSFileManager defaultManager] contentsAtPath: platform->fullname_];
	}
}

std::string kFile::read(size_t count)
{
	iload((kFile_platform *)platform_);
	
	return read();
}

std::string kFile::read()
{
	kFile_platform * platform = (kFile_platform *)platform_;
	iload(platform);
	
	NSData * data_objc = platform->data_;
	const char * p = (const char *)[data_objc bytes];
	size_t length = [data_objc length];
	return std::string{p, length};
}

size_t kFile::size()
{
	kFile_platform * platform = (kFile_platform *)platform_;
	iload(platform);

	NSData * data_objc = platform->data_;
	return [data_objc length];
}

const char * kFile::data()
{
	kFile_platform * platform = (kFile_platform *)platform_;
	iload(platform);
	
	NSData * data_objc = platform->data_;
	
	return (const char *)[data_objc bytes];
}

io_namespace_end
k_namespace_end
