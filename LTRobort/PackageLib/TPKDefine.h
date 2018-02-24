#pragma once

namespace Package
{
uint32_t const TPK_MAGIC			= 0xFF317029L;
uint32_t const TPK_VERSION			= 1;
uint32_t const TPK_MAX_FILE			= 0x0007FFFFL;
uint32_t const TPK_MIN_TRACK_FRAGMENT = 1024;

#pragma pack(push, pack_1)
#pragma pack(4)

// �ļ�����ṹ
// ======================================================================
// ^                    ^                        ^                      ^
// |   ��Ч����			|        ��Ƭ����		 |		 �հױ���		|
// 0                 file_num              valid_table_num		max_table_num	

// CPK�ļ�ͷ�ṹ
struct tagCPKHeader
{
	uint32_t	magic;				// �ļ����ͱ�־
	uint32_t	ver;				// �汾��
	uint32_t	file_num;			// ��Ч�ļ���
	uint32_t	valid_table_num;	// ��ʹ�õ����������� �����������ļ���������Ƭ�ռ��
	uint32_t	max_table_num;		// ������������
	uint32_t	table_start_offset;	// ����������ʼƫ��
	uint32_t	header_size;	    // �ļ�ͷ��С
	uint32_t	data_start_offset;	// ��������ʼƫ��
	uint32_t	package_size;		// ��ǰ����С
    uint64_t    ctime;              // ����ʱ��
	uint32_t	reserved[5];
}; // 32*4

// CPK�ļ���ṹ
struct tagCPKTable
{
	uint32_t	hash1;				// hash1
	uint32_t	hash2;				// hash2		
	uint32_t	data_offset;		// ����ƫ��
	uint32_t	packed_size;		// ���д洢���ݴ�С
	uint32_t	origin_size;		// ԭʼ�ļ���С
	uint32_t	flag;				// ��־	
	uint32_t	reserved[2];	
};

// uint32_t flag:
// 0000 0000-0000 0000-0000 0000-0000 0001 (0x0001) ѹ��
#define IS_COMPRESSED(f)		((f) &   0x00000001)
#define SET_COMPRESSED(f)       ((f) |=  0x00000001)
#define SET_NOCOMPRESSED(f)     ((f) &= ~0x00000001)

#pragma pack(pop, pack_1)

}; // namespace Package