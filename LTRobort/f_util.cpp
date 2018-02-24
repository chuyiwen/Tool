/*******************************************************************************

	Copyright 2010 by Shengshi Interactive Game Co., Ltd.
	All rights reserved.
	
	This software is the confidential and proprietary information of
	Shengshi Interactive Game Co., Ltd. ('Confidential Information'). You shall
	not disclose such Confidential Information and shall use it only in
	accordance with the terms of the license agreement you entered into with
	Shengshi Interactive  Co., Ltd.

*******************************************************************************/
/**
 *	@file		f_util.cpp
 *	@author		zhaopeng
 *	@date		2011/03/14
 *	@version	
 *	@brief		
 */
#include "stdafx.h"
#include "f_util.h"

namespace Tang {
#define CHAR_POOL_SIZE	1024*64
#define MASKBITS 0x3F
#define MASKBYTE 0x80
#define MASK2BYTES 0xC0
#define MASK3BYTES 0xE0
namespace {
char    CHAR_POOL[CHAR_POOL_SIZE];
wchar_t WCHAR_POOL[CHAR_POOL_SIZE];

const unsigned long CRC32_TAB[256]={
0x00000000,0x04c11db7,0x09823b6e,0x0d4326d9,0x130476dc,0x17c56b6b,0x1a864db2,0x1e475005,
0x2608edb8,0x22c9f00f,0x2f8ad6d6,0x2b4bcb61,0x350c9b64,0x31cd86d3,0x3c8ea00a,0x384fbdbd,
0x4c11db70,0x48d0c6c7,0x4593e01e,0x4152fda9,0x5f15adac,0x5bd4b01b,0x569796c2,0x52568b75,
0x6a1936c8,0x6ed82b7f,0x639b0da6,0x675a1011,0x791d4014,0x7ddc5da3,0x709f7b7a,0x745e66cd,
0x9823b6e0,0x9ce2ab57,0x91a18d8e,0x95609039,0x8b27c03c,0x8fe6dd8b,0x82a5fb52,0x8664e6e5,
0xbe2b5b58,0xbaea46ef,0xb7a96036,0xb3687d81,0xad2f2d84,0xa9ee3033,0xa4ad16ea,0xa06c0b5d,
0xd4326d90,0xd0f37027,0xddb056fe,0xd9714b49,0xc7361b4c,0xc3f706fb,0xceb42022,0xca753d95,
0xf23a8028,0xf6fb9d9f,0xfbb8bb46,0xff79a6f1,0xe13ef6f4,0xe5ffeb43,0xe8bccd9a,0xec7dd02d,
0x34867077,0x30476dc0,0x3d044b19,0x39c556ae,0x278206ab,0x23431b1c,0x2e003dc5,0x2ac12072,
0x128e9dcf,0x164f8078,0x1b0ca6a1,0x1fcdbb16,0x018aeb13,0x054bf6a4,0x0808d07d,0x0cc9cdca,
0x7897ab07,0x7c56b6b0,0x71159069,0x75d48dde,0x6b93dddb,0x6f52c06c,0x6211e6b5,0x66d0fb02,
0x5e9f46bf,0x5a5e5b08,0x571d7dd1,0x53dc6066,0x4d9b3063,0x495a2dd4,0x44190b0d,0x40d816ba,
0xaca5c697,0xa864db20,0xa527fdf9,0xa1e6e04e,0xbfa1b04b,0xbb60adfc,0xb6238b25,0xb2e29692,
0x8aad2b2f,0x8e6c3698,0x832f1041,0x87ee0df6,0x99a95df3,0x9d684044,0x902b669d,0x94ea7b2a,
0xe0b41de7,0xe4750050,0xe9362689,0xedf73b3e,0xf3b06b3b,0xf771768c,0xfa325055,0xfef34de2,
0xc6bcf05f,0xc27dede8,0xcf3ecb31,0xcbffd686,0xd5b88683,0xd1799b34,0xdc3abded,0xd8fba05a,
0x690ce0ee,0x6dcdfd59,0x608edb80,0x644fc637,0x7a089632,0x7ec98b85,0x738aad5c,0x774bb0eb,
0x4f040d56,0x4bc510e1,0x46863638,0x42472b8f,0x5c007b8a,0x58c1663d,0x558240e4,0x51435d53,
0x251d3b9e,0x21dc2629,0x2c9f00f0,0x285e1d47,0x36194d42,0x32d850f5,0x3f9b762c,0x3b5a6b9b,
0x0315d626,0x07d4cb91,0x0a97ed48,0x0e56f0ff,0x1011a0fa,0x14d0bd4d,0x19939b94,0x1d528623,
0xf12f560e,0xf5ee4bb9,0xf8ad6d60,0xfc6c70d7,0xe22b20d2,0xe6ea3d65,0xeba91bbc,0xef68060b,
0xd727bbb6,0xd3e6a601,0xdea580d8,0xda649d6f,0xc423cd6a,0xc0e2d0dd,0xcda1f604,0xc960ebb3,
0xbd3e8d7e,0xb9ff90c9,0xb4bcb610,0xb07daba7,0xae3afba2,0xaafbe615,0xa7b8c0cc,0xa379dd7b,
0x9b3660c6,0x9ff77d71,0x92b45ba8,0x9675461f,0x8832161a,0x8cf30bad,0x81b02d74,0x857130c3,
0x5d8a9099,0x594b8d2e,0x5408abf7,0x50c9b640,0x4e8ee645,0x4a4ffbf2,0x470cdd2b,0x43cdc09c,
0x7b827d21,0x7f436096,0x7200464f,0x76c15bf8,0x68860bfd,0x6c47164a,0x61043093,0x65c52d24,
0x119b4be9,0x155a565e,0x18197087,0x1cd86d30,0x029f3d35,0x065e2082,0x0b1d065b,0x0fdc1bec,
0x3793a651,0x3352bbe6,0x3e119d3f,0x3ad08088,0x2497d08d,0x2056cd3a,0x2d15ebe3,0x29d4f654,
0xc5a92679,0xc1683bce,0xcc2b1d17,0xc8ea00a0,0xd6ad50a5,0xd26c4d12,0xdf2f6bcb,0xdbee767c,
0xe3a1cbc1,0xe760d676,0xea23f0af,0xeee2ed18,0xf0a5bd1d,0xf464a0aa,0xf9278673,0xfde69bc4,
0x89b8fd09,0x8d79e0be,0x803ac667,0x84fbdbd0,0x9abc8bd5,0x9e7d9662,0x933eb0bb,0x97ffad0c,
0xafb010b1,0xab710d06,0xa6322bdf,0xa2f33668,0xbcb4666d,0xb8757bda,0xb5365d03,0xb1f740b4
};
};

f_util::f_util():dw_id_seed(1),n_rand_seed(0),n_rand_call_num(0)
{
	InitializeCriticalSection(&_lock);
}

f_util::~f_util()
{
	DeleteCriticalSection(&_lock);
}

DWORD f_util::get_idlesse_id()
{
	if( dw_id_seed >= 0x7fffffff )	
		dw_id_seed = 1;
	return dw_id_seed++;
}


VOID f_util::tool_randomize(DWORD dw_seed_)
{
	n_rand_seed = (INT)dw_seed_;
	n_rand_call_num = 0;
}

INT f_util::tool_rand()
{
	EnterCriticalSection(&_lock);
	n_rand_call_num++;


	INT n_result = (((n_rand_seed = n_rand_seed * 1103515245 + 12345) >> 1 ) & LONG_MAX);

	LeaveCriticalSection(&_lock);
	return n_result;
}


//-----------------------------------------------------------------------------
//! 根据概率计算成功率
//-----------------------------------------------------------------------------
BOOL f_util::probability(INT n_radices_)
{
	INT n_temp = 0, n_max = 0;
	if( n_radices_<=0 )
		return FALSE;

	n_max = (INT)(((FLOAT)CARDINAL_NUMBER) / 100.0f * (FLOAT)n_radices_);
	n_temp = (this->tool_rand() % CARDINAL_NUMBER);
	if (n_temp < n_max)
		return TRUE;
	else
		return FALSE;
}


//-----------------------------------------------------------------------------
//! 给定数值及上下浮动范围，算出浮动数
//-----------------------------------------------------------------------------
FLOAT f_util::fluctuate(FLOAT f_num_, FLOAT f_increase_, FLOAT f_decrease_)
{
	FLOAT f_max = f_num_ * ( 100.0f + f_increase_ ) / 100.0f;
	FLOAT f_min = f_num_ * ( 100.0f - f_decrease_ ) / 100.0f;
	FLOAT f_result = f_min;
	if( (INT)(f_max-f_min) == 0 )
		f_result = f_min;
	else
		f_result = f_min + (FLOAT)(tool_rand() % ((INT)(f_max - f_min)));

	return f_result;
}

//-----------------------------------------------------------------------------
// ! 给定最大，最小值，算出某个中间值
//-----------------------------------------------------------------------------
INT f_util::rand_in_range(INT n_min_, INT n_max_)
{
	if( n_min_ < 0 || n_max_ < 0 ) return 0;

	if( n_max_ <= n_min_ ) return n_min_;

	return n_min_ + tool_rand() % (n_max_ - n_min_ + 1);
}


unsigned long f_util::get_crc(char const* str_)
{	
	unsigned char* data_ = (unsigned char*)str_;
	if( 0 == data_[0] ) 
		return (unsigned long)INVALID;

	unsigned long ret_ = *data_++ << 24;
	if( *data_ )
	{
		ret_ |= *data_++ << 16;
		if( *data_ )
		{
			ret_ |= *data_++ << 8;
			if( *data_ ) ret_ |= *data_++;
		}
	}
	ret_ = ~ ret_;
	while( *data_ )
	{
		ret_ = (ret_ << 8 | *data_) ^ CRC32_TAB[ret_ >> 24];
		data_++;
	}
	return ~ret_;
}

unsigned long f_util::get_crc(wchar_t const* str_)
{
	unsigned char* data = (unsigned char*)str_;
	if( !(*data || *(data+1)) ) 
		return (unsigned long)INVALID;

	unsigned long ret = *data++ << 24;
	ret |= *data++ << 16;
	if( *data || *(data+1) )
	{
		ret |= *data++ << 8;
		ret |= *data++;
	}
	ret = ~ ret;
	int nCount = 0;
	while( (nCount&1) ? true : (*data || *(data+1)) )
	{
		ret = (ret << 8 | *data) ^ CRC32_TAB[ret >> 24];
		++data;
		++nCount;
	}

	return ~ret;
}

unsigned long f_util::get_crc(unsigned char* data_, int len_)
{
	if( len_ <= 0 )
		return (unsigned long)INVALID;

	unsigned int ret = *data_++ << 24;
	if( --len_ > 0 )
	{
		ret |= *data_++ << 16;
		if( --len_ > 0 )
		{
			ret |= *data_++ << 8;
			if( --len_ > 0 ) ret |= *data_++;
		}
	}
	ret = ~ ret;
	while( --len_ > 0 )
	{
		ret = (ret << 8 | *data_) ^ CRC32_TAB[ret >> 24];
		data_++;
	}

	return ~ret;
}

char const* f_util::unicode_to_utf8(wchar_t const* src_, char* out_)
{
	if( !out_ )
		out_ = CHAR_POOL;
	char* dest = out_;

	while( *src_ )
	{
		if(*src_ < 0x80)	// 0xxxxxxx
		{
			*dest++ = (unsigned char)*src_;
		}
		else if( *src_ < 0x800 )	// 110xxxxx 10xxxxxx
		{
			*dest++ = ((unsigned char)(MASK2BYTES | *src_ >> 6));
			*dest++ = ((unsigned char)(MASKBYTE | *src_ & MASKBITS));
		}
		else	// 1110xxxx 10xxxxxx 10xxxxxx
		{
			*dest++ = ((unsigned char)(MASK3BYTES | *src_ >> 12));
			*dest++ = ((unsigned char)(MASKBYTE | *src_ >> 6 & MASKBITS));
			*dest++ = ((unsigned char)(MASKBYTE | *src_ & MASKBITS));
		}
		++src_;
	}

	*dest = 0; // 加上0结束符
	return out_;
}

wchar_t const*	f_util::utf8_to_unicode(char const* src_, wchar_t* out_)
{
	if( !out_ )
		out_ = WCHAR_POOL;

	wchar_t* dest = out_;

	while( *src_ )
	{
		if( !(*src_ & MASKBYTE) )	// 0xxxxxxx
		{
			*dest++ = *src_++;
		}
		else if( (*src_ & MASK3BYTES) == MASK3BYTES )	// 1110xxxx 10xxxxxx 10xxxxxx
		{
			*dest++ = ((*src_ & 0x0F) << 12) | ((*(src_+1) & MASKBITS) << 6) | (*(src_+2) & MASKBITS);
			++src_;
			++src_;
			++src_;
		}
		else if( (*src_ & MASK2BYTES) == MASK2BYTES )	// 110xxxxx 10xxxxxx
		{
			*dest++ = ((*src_ & 0x1F) << 6) | (*(src_+1) & MASKBITS);
			++src_;
			++src_;
		}
	}

	*dest = 0; // 加上0结束符
	return out_;
}

char const* f_util::unicode_to_ansi(wchar_t const* src_)
{
	CHAR_POOL[0] = 0;
	WideCharToMultiByte(CP_ACP, 0, src_, -1, CHAR_POOL, CHAR_POOL_SIZE, NULL, NULL);
	return CHAR_POOL;
}

wchar_t const* f_util::ansi_to_unicode(char const* src_)
{
	WCHAR_POOL[0] = 0;
	MultiByteToWideChar(CP_ACP, 0, src_, -1, WCHAR_POOL, CHAR_POOL_SIZE);
	return WCHAR_POOL;
}

void f_util::trim_string(tstring& str_)
{
	// 必须检查:如果字符串中只有空格,不能进行此操作
	if( str_.find_first_not_of(_T(" ")) != -1 )
	{
		str_.assign(str_, str_.find_first_not_of(_T(" ")),
			str_.find_last_not_of(_T(" "))-str_.find_first_not_of(_T(" "))+1);
	}
	else
	{
		str_.clear();
	}
}

void f_util::token_string(std::vector<tstring>& token_result_, TCHAR const* str_, TCHAR separator_/*=_T(' ')*/)
{
	assert(str_);
	tstring token;
	token_result_.clear();

	bool in_quot = false;	// 是否进入引号部分
	for(TCHAR const* p = str_; *p; p++)
	{
		if( *p == separator_ )
		{
			if( !token.empty() )
			{
				if( in_quot )
					token.append(separator_, 1);	// 保留引号里的分隔符
				else
				{
					token_result_.push_back(token);
					token.clear();
				}
			}
		}
		else if( *p == _T('"') )
		{
			in_quot = !in_quot;
		}
		else
		{
			token.append(p, 1);
		}
	}

	if(!token.empty())	// 加上剩余的字符
		token_result_.push_back(token);
}

bool f_util::check_reg(HKEY key_, TCHAR const* sub_key_)
{
	HKEY hKey;
	long ret0 = RegOpenKeyEx(key_, sub_key_, 0, KEY_READ, &hKey);
	if ( ret0 == ERROR_SUCCESS )
	{
		RegCloseKey(hKey);
		return true;
	}

	RegCloseKey(hKey);
	return false;
}

bool f_util::write_reg(TCHAR const* key_root_, TCHAR const* key_name_, TCHAR const* sz_)
{
	if( key_root_ == NULL || key_name_ == NULL ) 
		return false;

	HKEY key;
	unsigned long dwDisposition = REG_CREATED_NEW_KEY;

	long ret0 = 0;
	TCHAR buf[256]={0};
	if ( !check_reg(HKEY_LOCAL_MACHINE, key_root_) )
	{
		ret0 = RegCreateKeyEx(HKEY_LOCAL_MACHINE, key_root_, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisposition);
		if ( ret0 != ERROR_SUCCESS )
			return false;

		RegCloseKey(key);
	}

	// -- 写入
	RegOpenKeyEx( HKEY_LOCAL_MACHINE, key_root_, 0, KEY_WRITE, &key );
	ret0 = RegSetValueEx(key, key_name_, NULL, REG_SZ, (const BYTE*)sz_, lstrlen(sz_)*sizeof(sz_[0])+sizeof(sz_[0]));
	if ( ret0 != ERROR_SUCCESS )
		return false;

	RegCloseKey(key);
	return true;
}

bool f_util::read_reg(TCHAR const* key_root_, TCHAR const* key_name_, unsigned long& key_value_)
{
	HKEY key;
	long ret0 = RegOpenKeyEx( HKEY_LOCAL_MACHINE, key_root_, 0, KEY_QUERY_VALUE, &key );
	if( ret0 != ERROR_SUCCESS )
		return false;

	unsigned long buf_len=32;
	RegQueryValueEx( key, key_name_, NULL, NULL, (LPBYTE)&key_value_, &buf_len);
	RegCloseKey(key);

	return true;
}

bool f_util::read_reg(TCHAR const* key_root_, TCHAR const* key_name_, TCHAR* out_str_)
{
	SI_ASSERT( out_str_ != NULL );
	HKEY key_;
	long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_root_, 0, KEY_READ, &key_);
	if ( ret0 != ERROR_SUCCESS )
	{
		out_str_[0] = 0;
		return false;
	}
	unsigned long len = MAX_PATH, type = REG_SZ;
	// if char* (LPBYTE)char*
	// if char [] (LPBYTE)&char
	RegQueryValueEx(key_, key_name_, NULL, &type, (LPBYTE)out_str_, &len);

	RegCloseKey(key_);
	return true;
}

} // namespace Tang {