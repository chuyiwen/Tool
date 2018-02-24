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
 *	@file		f_util.h
 *	@author		zhaopeng
 *	@date		2011/03/14
 *	@version	
 *	@brief		
 */
#pragma once

#define CARDINAL_NUMBER	8192	//！ 随机数基数

namespace Tang {
class f_util : public Tang::Singleton<f_util>
{
public:
	DWORD	get_idlesse_id();
	//! 随机数相关
	VOID	tool_randomize(DWORD dw_seed_);
	DWORD	get_rand_seed() { return n_rand_seed; }
	INT		tool_rand();

	//! 根据概率计算成功率
	BOOL	probability(INT n_radices_);
	//! 给定数值及上下浮动范围，算出浮动数
	FLOAT	fluctuate(FLOAT f_num_, FLOAT f_increase_, FLOAT f_decrease_);

	//! 给定最大，最小值，算出某个中间值
	INT		rand_in_range(INT n_min_, INT n_max_);

	// CRC
	static unsigned long	get_crc(char const* str_);	// 字符串
	static unsigned long	get_crc(wchar_t const* str_);	// 字符串
	static unsigned long	get_crc(unsigned char* data_, int len_); // 字节块

	// utf8 <==> unicode
	static char const*		unicode_to_utf8(wchar_t const* src_, char* out_=NULL);
	static wchar_t const*	utf8_to_unicode(char const* src_, wchar_t* out_=NULL);
	static char const*		unicode_to_ansi(wchar_t const* src_);
	static wchar_t const*	ansi_to_unicode(char const* src_);
	
	static void	trim_string(tstring& str_);
	static void	token_string(std::vector<tstring>& token_result_, TCHAR const* str_, TCHAR separator_=_T(' '));

	// 检测注册表键值
	static bool check_reg(HKEY key_, TCHAR const* sub_key_);
	// 写入注册表键值
	static bool write_reg(TCHAR const* key_root_, TCHAR const* key_name_, TCHAR const* sz_);
	// 读取注册表键值
	static bool read_reg(TCHAR const* key_root_, TCHAR const* key_name_, unsigned long& key_value_);
	static bool read_reg(TCHAR const* key_root_, TCHAR const* key_name_, TCHAR* out_str_);
	
	f_util();
	~f_util();

private:
	CRITICAL_SECTION	_lock;
	DWORD	dw_id_seed;		
	INT		n_rand_seed;
	INT		n_rand_call_num;
};

} // namespace Tang {
