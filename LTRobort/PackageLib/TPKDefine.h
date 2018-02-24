#pragma once

namespace Package
{
uint32_t const TPK_MAGIC			= 0xFF317029L;
uint32_t const TPK_VERSION			= 1;
uint32_t const TPK_MAX_FILE			= 0x0007FFFFL;
uint32_t const TPK_MIN_TRACK_FRAGMENT = 1024;

#pragma pack(push, pack_1)
#pragma pack(4)

// 文件表项结构
// ======================================================================
// ^                    ^                        ^                      ^
// |   有效表项			|        碎片表项		 |		 空白表项		|
// 0                 file_num              valid_table_num		max_table_num	

// CPK文件头结构
struct tagCPKHeader
{
	uint32_t	magic;				// 文件类型标志
	uint32_t	ver;				// 版本号
	uint32_t	file_num;			// 有效文件数
	uint32_t	valid_table_num;	// 已使用的索引表项数 包括索引包文件和索引碎片空间的
	uint32_t	max_table_num;		// 索引表项总数
	uint32_t	table_start_offset;	// 索引表项起始偏移
	uint32_t	header_size;	    // 文件头大小
	uint32_t	data_start_offset;	// 数据区起始偏移
	uint32_t	package_size;		// 当前包大小
    uint64_t    ctime;              // 创建时间
	uint32_t	reserved[5];
}; // 32*4

// CPK文件表结构
struct tagCPKTable
{
	uint32_t	hash1;				// hash1
	uint32_t	hash2;				// hash2		
	uint32_t	data_offset;		// 数据偏移
	uint32_t	packed_size;		// 包中存储数据大小
	uint32_t	origin_size;		// 原始文件大小
	uint32_t	flag;				// 标志	
	uint32_t	reserved[2];	
};

// uint32_t flag:
// 0000 0000-0000 0000-0000 0000-0000 0001 (0x0001) 压缩
#define IS_COMPRESSED(f)		((f) &   0x00000001)
#define SET_COMPRESSED(f)       ((f) |=  0x00000001)
#define SET_NOCOMPRESSED(f)     ((f) &= ~0x00000001)

#pragma pack(pop, pack_1)

}; // namespace Package