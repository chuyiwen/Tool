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
 *	@file		f_data_set.cpp
 *	@author		zhaopeng
 *	@date		2011/02/24
 *	@version	
 *	@brief		
 */
#include "stdafx.h"
#include "f_data_set.h"
#include "XML/tinyxml.h"

namespace Tang {
IFS* f_data_set::ms_default_fs = NULL;
//-----------------------------------------------------------------------------
// 删除指定元素
//-----------------------------------------------------------------------------
bool f_data_set::remove(TCHAR const* name_)
{
	std::map<DWORD, tstring>::iterator it;
	DWORD id = Tang::f_util::get_crc(name_);

	it = m_data_map.find(id);
	if( it == m_data_map.end() )
		return false;	// 找不到

	m_data_map.erase(it);

	if( b_support_save )
	{
		it = m_name_map.find(id);
		m_name_map.erase(it);
	}

	return true;
}


//-----------------------------------------------------------------------------
// 删除指定元素
//-----------------------------------------------------------------------------
bool f_data_set::remove(TCHAR const* name_, TCHAR const* field_)
{
	tstring str = name_;
	str.append(_T(" "));
	str.append(field_);
	return remove(str.c_str());
}


//-----------------------------------------------------------------------------
// 获取所有元素的名称标示
//-----------------------------------------------------------------------------
std::list<tstring>& f_data_set::get_var_name()
{
	m_name_list.clear();
	std::map<DWORD, tstring>::iterator it;

	for( it=m_name_map.begin(); it!=m_name_map.end(); ++it )
		m_name_list.push_back(it->second);

	return m_name_list;
}


//-----------------------------------------------------------------------------
// 读取文件
//-----------------------------------------------------------------------------
bool f_data_set::load(TCHAR const* filename_, char const* keyname_/* = "name"*/,
						std::list<tstring>* fieldlist_/* = NULL*/, IFS* fs_ /*= NULL*/)
{
	DWORD dwTime = timeGetTime();
	tstring filename = filename_;
	if( filename.find(_T(".xml")) != tstring::npos )
	{
		XmlDocument doc;
		if ( fs_ == NULL )
			fs_ = get_default_fs();
		if( !doc.LoadFile(fs_, filename_) )
			return false;

		XmlHandle docHandle( &doc );
		/*XmlHandle eleHandle = docHandle.FirstChildElement("root").FirstChildElement();*/
		XmlHandle eleHandle = docHandle.FirstChildElement().FirstChildElement();

		Tang::XmlElement* pElement = eleHandle.Element();
		if( !pElement )	// 是否符合存盘格式
			return false;

		TCHAR field_[512];
		TCHAR szValue[512];
		TCHAR name_[512];
		TCHAR szFullName[512];
		while( pElement )	// 读入所有element
		{
			// 读出element的键，也就是field
			LPCSTR szKeyName = pElement->Attribute(keyname_);
			if( !IS_VALID_PTR(szKeyName) )
			{
				pElement = pElement->NextSiblingElement();
				continue;
			}

			Tang::f_util::utf8_to_unicode(szKeyName, field_);
			XmlAttribute* pAttrib = pElement->FirstAttribute();
			if( fieldlist_ && pAttrib )	// 如果Field需要导出
				fieldlist_->push_back(field_);

			while( pAttrib ) // 遍历此field中的所有属性
			{
				if( pAttrib->ValueStr().empty() )	// 如果此属性没有值则跳过
				{
					pAttrib = pAttrib->Next();
					continue;
				}

				Tang::f_util::utf8_to_unicode(pAttrib->Value(), szValue);
				Tang::f_util::utf8_to_unicode(pAttrib->Name(), name_);
				_tcscpy(szFullName, name_);
				_tcscat(szFullName, _T(" "));
				_tcscat(szFullName, field_);

				this->add(szValue, szFullName);

				// 如果是value则再添加一个直接以name为键的变量
				if(    name_[0] == _T('v') 
					&& name_[1] == _T('a') 
					&& name_[2] == _T('l') 
					&& name_[3] == _T('u') 
					&& name_[4] == _T('e') 
					&& name_[5] == 0 )
					this->add(szValue, field_);

				pAttrib = pAttrib->Next();
			}

			pElement = pElement->NextSiblingElement();
		}
	}
	//else if (filename.find(_T(".inc")) != tstring::npos )
	//{
	//	CreateObj("TempINI", "IniObj");
	//	if( false == TObjRef<INIObj>("TempINI")->load(szVFS, filename_, 1) )
	//	{
	//		KillObj("TempINI");
	//		return false;
	//	}
	//	TObjRef<INIObj>("TempINI")->PutToContainer(this);
	//	KillObj("TempINI");
	//}
	//else if (filename.find(_T(".ins")) != tstring::npos )
	//{
	//	CreateObj("TempINI", "IniObj");
	//	if( false == TObjRef<INIObj>("TempINI")->load(szVFS, filename_, 0) )
	//	{
	//		KillObj("TempINI");
	//		return false;
	//	}
	//	TObjRef<INIObj>("TempINI")->PutToContainer(this);
	//	KillObj("TempINI");
	//}
	//else 
	//{
	//	CreateObj("TempINI", "IniObj");
	//	if( false == TObjRef<INIObj>("TempINI")->load(szVFS, filename_) )
	//	{
	//		KillObj("TempINI");
	//		return false;
	//	}
	//	TObjRef<INIObj>("TempINI")->PutToContainer(this);
	//	KillObj("TempINI");
	//}

	CONSOLE_TRACE(_T("load xml time=%d:%s\r\n"), timeGetTime()-dwTime, filename_);
	return true;
}



//-----------------------------------------------------------------------------
// 保存文件
//-----------------------------------------------------------------------------
bool f_data_set::save(TCHAR const* filename_)
{
	if( !b_support_save )
		return false;

	tstring filename = filename_;
	if( filename.find(_T(".xml")) != tstring::npos )
	{
		XmlDocument doc;
		XmlDeclaration declaration("1.0", "UTF-8", "");
		doc.InsertEndChild(declaration);
		
		Tang::XmlElement eleRoot("root");
		std::map<DWORD, tstring>::iterator it;
		std::map<DWORD, tstring>::iterator itName;
		for( it=m_data_map.begin(); it!=m_data_map.end(); ++it )
		{
			itName = m_name_map.find(it->first);
			std::string strName = Tang::f_util::unicode_to_utf8(itName->second.c_str());
			std::string strValue = Tang::f_util::unicode_to_utf8(it->second.c_str());
			
			if( strName.find(" ") == std::string::npos )
				continue;

			std::string strField;
			strField.assign(strName, strName.find(" ")+1, strName.size()-strName.find(" ")+1);
			strName.assign(strName, 0, strName.find(" "));

			// 找到对应的ele
			bool bFound = false;
			Tang::XmlElement* pElement = eleRoot.FirstChildElement();
			while( pElement )
			{
				if( 0 == strcmp(pElement->Attribute("name"), strField.c_str()) )
				{
					pElement->SetAttribute(strName, strValue);
					bFound = true;
					break;
				}

				pElement = pElement->NextSiblingElement();
			}
			
			if( !bFound )
			{
				Tang::XmlElement ele("item");
				ele.SetAttribute("name", strField);
				ele.SetAttribute(strName, strValue);
				eleRoot.InsertEndChild(ele);
			}
		}

		doc.InsertEndChild(eleRoot);
		doc.SaveFile(filename_);

	}
	else
	{
		return false; // INIObj不支持写
	}

	return true;
}


//-----------------------------------------------------------------------------
// set
//-----------------------------------------------------------------------------
bool f_data_set::set( TCHAR const* val_, TCHAR const* name_ )
{
	bool ret = this->remove(name_);
	this->add(val_, name_);
	return ret;
}


//-----------------------------------------------------------------------------
// set
//-----------------------------------------------------------------------------
bool f_data_set::set( DWORD val_, TCHAR const* name_ )
{
	bool ret = this->remove(name_);
	this->add(val_, name_);
	return ret;
}


//-----------------------------------------------------------------------------
// set
//-----------------------------------------------------------------------------
bool f_data_set::set( float val_, TCHAR const* name_ )
{
	bool ret = this->remove(name_);
	this->add(val_, name_);
	return ret;
}

bool f_data_set::add( tstring& val_, tstring& name_ )
{
	DWORD id = Tang::f_util::get_crc(name_.c_str());
	if( m_data_map.insert(std::pair<DWORD, tstring>(id, val_)).second == NULL )	
		CONSOLE_TRACE(_T("Couldn't add <%s> twice to var_container"), name_.c_str());	

	if( b_support_save )
		m_name_map.insert(std::pair<DWORD, tstring>(id, name_));
	return true;
}

bool f_data_set::add( TCHAR const* val_, TCHAR const* name_ )
{
	DWORD id = Tang::f_util::get_crc(name_);
	tstring str = val_;

	if( NULL == m_data_map.insert(std::pair<DWORD, tstring>(id, str)).second )	
		CONSOLE_TRACE(_T("Couldn't add <%s> twice to var_container"), name_);

	if( b_support_save )
	{
		tstring strName = name_;
		m_name_map.insert(std::pair<DWORD, tstring>(id, name_));
	}

	return true;
}

bool f_data_set::add( DWORD val_, TCHAR const* name_ )
{
	TCHAR mess[512];
	_itot(val_, mess, 10);
	return this->add(mess, name_);
}

bool f_data_set::add( float val_, TCHAR const* name_ )
{
	CHAR mess[512];
	_gcvt(val_, 6, mess);
	return this->add(Tang::f_util::utf8_to_unicode(mess), name_);
}

TCHAR const* f_data_set::get_string( TCHAR const* name_ )
{
	std::map<DWORD, tstring>::iterator it;
	DWORD id = Tang::f_util::get_crc(name_);

	it = m_data_map.find(id);
	if( it == m_data_map.end() )
	{
		CONSOLE_TRACE(_T("Couldn't find <%s> in var_container"), name_);
		return NULL;
	}

	TCHAR const* pReturn = it->second.c_str();
	return pReturn;
}

TCHAR const* f_data_set::get_string( TCHAR const* name_, TCHAR const* field_ )
{
	tstring str = name_;
	str.append(_T(" "));
	str.append(field_);
	return get_string(str.c_str());
}

TCHAR const* f_data_set::get_string( TCHAR const* name_, TCHAR const* field_, TCHAR const* def_val_ )
{
	std::map<DWORD, tstring>::iterator it;
	TCHAR mess[512];

	_tcscpy(mess, name_);
	if( IS_VALID_PTR(field_) )
	{
		_tcscat(mess, _T(" "));
		_tcscat(mess, field_);
	}

	DWORD id = Tang::f_util::get_crc(mess);
	it = m_data_map.find(id);
	if( it == m_data_map.end() )
		return def_val_;

	return it->second.c_str();
}

TCHAR const* f_data_set::get_string( TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, TCHAR const* def_val_ )
{
	std::map<DWORD, tstring>::iterator it;
	tstring title = name_;
	title += name_postfix;
	if( IS_VALID_PTR(field_) )
	{
		title.append(_T(" "));
		title.append(field_);
	}

	DWORD id = Tang::f_util::get_crc(title.c_str());
	it = m_data_map.find(id);
	if( it == m_data_map.end() )
		return def_val_;

	return it->second.c_str();
}
DWORD f_data_set::get_dword( TCHAR const* name_ )
{
	TCHAR const* string_result = this->get_string(name_);
	return _tcstol(string_result, NULL, 10);
}

DWORD f_data_set::get_dword( TCHAR const* name_, TCHAR const* field_ )
{
	tstring str = name_;
	str.append(_T(" "));
	str.append(field_);
	return get_dword(str.c_str());
}

DWORD f_data_set::get_dword( TCHAR const* name_, TCHAR const* field_, DWORD def_val_ )
{
	TCHAR const* string_result = this->get_string(name_, field_, NULL);
	if( NULL == string_result )
		return def_val_;

	return _tcstol(string_result, NULL, 10);
}

DWORD f_data_set::get_dword( TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, DWORD def_val_ )
{
	TCHAR const* string_result = this->get_string(name_, name_postfix, field_, NULL);
	if( NULL == string_result )
		return def_val_;

	return _tcstol(string_result, NULL, 10);
}
float f_data_set::get_float( TCHAR const* name_ )
{
	TCHAR const* szValue = this->get_string(name_);
	return (float)_tstof(szValue);
}

float f_data_set::get_float( TCHAR const* name_, TCHAR const* field_ )
{
	tstring str = name_;
	str.append(_T(" "));
	str.append(field_);
	return get_float(str.c_str());
}

float f_data_set::get_float( TCHAR const* name_, TCHAR const* field_, float def_val_ )
{
	TCHAR const* string_result = this->get_string(name_, field_, NULL);
	if( NULL == string_result )
		return def_val_;

	return (float)_tstof(string_result);
}

float f_data_set::get_float( TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, float def_val_ )
{
	TCHAR const* string_result = this->get_string(name_, name_postfix, field_, NULL);
	if( NULL == string_result )
		return def_val_;

	return (float)_tstof(string_result);
}
int f_data_set::get_int( TCHAR const* name_ )
{
	TCHAR const* szValue = this->get_string(name_);
	return (int)_tcstol(szValue, NULL, 10);
}

int f_data_set::get_int( TCHAR const* name_, TCHAR const* field_ )
{
	tstring str = name_;
	str.append(_T(" "));
	str.append(field_);
	return get_int(str.c_str());
}

int f_data_set::get_int( TCHAR const* name_, TCHAR const* field_, int def_val_ )
{
	TCHAR const* string_result = this->get_string(name_, field_, NULL);
	if( NULL == string_result )
		return def_val_;

	return (int)_tcstol(string_result, NULL, 10);
}

int f_data_set::get_int( TCHAR const* name_, TCHAR const* name_postfix, TCHAR const* field_, int def_val_ )
{
	TCHAR const* string_result = this->get_string(name_, name_postfix, field_, NULL);
	if( NULL == string_result )
		return def_val_;

	return (int)_tcstol(string_result, NULL, 10);
}
} // namespace Tang {
