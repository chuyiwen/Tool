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
 *	@file		f_md5.h
 *	@author		zhaopeng
 *	@date		2011/03/14
 *	@version	
 *	@brief		
 */
#pragma once
namespace Tang
{
class f_md5
{
public:
	void	md5_for_buffer(unsigned char *buffer_, unsigned int buffer_len_, unsigned char digest_[16]);
	void	md5_for_string(char *str_, unsigned char digest_[16]);
	void	md5_to_string(std::string& str_, unsigned char digest_[16]);
private:
	void	init();
	void	update(unsigned char *input_, unsigned int input_len_);
	void	final(unsigned char digest_[16]);
	void	transform (unsigned int state_[4], unsigned char block_[64]);
	
	void	encode(unsigned char *output_, unsigned int *input_, unsigned int len_);	
	void	decode(unsigned int *output_, unsigned char *input_,unsigned int len_);

	typedef struct 
	{
		unsigned int  state[4];		/* state (ABCD) */
		unsigned int  count[2];		/* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];		/* input buffer */
	} s_ctx;
	s_ctx	m_context;
};
};