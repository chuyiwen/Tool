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
 *	@file		f_data_set.h
 *	@author		zhaopeng
 *	@date		2011/02/24
 *	@version	
 *	@brief		
 */
#pragma once
namespace Tang {

class f_data_set
{
private:
	std::map<DWORD, tstring>	m_data_map;

	bool						b_support_save;
	std::map<DWORD, tstring>	m_name_map;
	std::list<tstring>			m_name_list;

	static IFS*					ms_default_fs;
public:
	// ���Ԫ��
	bool			add(tstring& val_, tstring& name_);

	bool			add(TCHAR const* val_, TCHAR const* name_);
	bool			add(DWORD val_, TCHAR const* name_);
	bool			add(float val_, TCHAR const* name_);

	// ��ȡԪ��
	TCHAR const*	get_string(TCHAR const* name_);
	DWORD			get_dword(TCHAR const* name_);
	float			get_float(TCHAR const* name_);
	int				get_int(TCHAR const* name_);

	TCHAR const*	get_string(TCHAR const* name_, TCHAR const* field_);
	DWORD			get_dword(TCHAR const* name_, TCHAR const* field_);
	float			get_float(TCHAR const* name_, TCHAR const* field_);
	int				get_int(TCHAR const* name_, TCHAR const* field_);

	TCHAR const*	get_string(TCHAR const* name_, TCHAR const* field_, TCHAR const* def_val_);
	DWORD			get_dword(TCHAR const* name_, TCHAR const* field_, DWORD def_val_);
	float			get_float(TCHAR const* name_, TCHAR const* field_, float def_val_);
	int				get_int(TCHAR const* name_, TCHAR const* field_, int def_val_);

	TCHAR const*	get_string(TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, TCHAR const* def_val_);
	DWORD			get_dword(TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, DWORD def_val_);
	float			get_float(TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, float def_val_);
	int				get_int(TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, int def_val_);

	// ����Ԫ�أ����û�о���Ӳ�����false
	bool			set(TCHAR const* val_, TCHAR const* name_);
	bool			set(DWORD val_, TCHAR const* name_);
	bool			set(float val_, TCHAR const* name_);

	// ɾ��Ԫ��
	bool			remove(TCHAR const* name_);
	bool			remove(TCHAR const* name_, TCHAR const* field_);
	void			clear() { m_data_map.clear(); m_name_map.clear(); }

	// ������������
	DWORD			get_var_num() { return m_data_map.size(); }	// �õ�Ԫ����Ŀ
	std::list<tstring>&	get_var_name();	// �õ��������м���

	bool			load(TCHAR const* filename_, char const* keyname_ = "name", std::list<tstring>* fieldlist_ = NULL, IFS* fs_ = NULL);	// ��ȡ�ļ�
	bool			save(TCHAR const* filename_);	// �����ļ�

	// �����Ƿ�֧�ִ���
	void			set_save_support(bool support_save_) { b_support_save = support_save_;	}

	// Ĭ�ϲ�֧�ִ���
	f_data_set():b_support_save(false){}

	static IFS*		get_default_fs()         { return ms_default_fs; }
	static void		set_default_fs(IFS* vfs) { ms_default_fs = vfs;  }
};

} // namespace Tang {
