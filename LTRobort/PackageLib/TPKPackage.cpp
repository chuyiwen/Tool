#include "TPKPackage.h"
#include <algorithm>
#include <cassert>
#include <time.h>


#include "ICompress.h"

#include "..\Common\Util.h"

namespace Package
{
struct CPKTableLessFunction
{
	bool operator()(tagCPKTable const& lhr, tagCPKTable const& rhr )
	{
		return lhr.hash1 < rhr.hash1;
	}
};	

void CPKUpdate::SortTable()
{
	std::sort( m_vTable.begin(), m_vTable.begin() + m_Header.file_num, CPKTableLessFunction() );
}
uint32_t CPKUpdate::CalcHash(tstring const& strFile)
{
	tstring tmp = strFile;
	std::transform( tmp.begin(), tmp.end(), tmp.begin(), tolower );

    // '/'�ָ����滻Ϊ'\'�ָ���
    for ( tstring::iterator it = tmp.begin(); it != tmp.end(); ++it )
    {
        if ( *it == _T('/') )
            *it = _T('\\');
    }

    // �ϲ����ڵ�'\'�ָ���
    for ( tstring::iterator it = tmp.begin(); it != tmp.end(); )
    {
        if ( *it == _T('\\') && (it + 1) != tmp.end() && *(it + 1) == _T('\\') )
            it = tmp.erase( it );
        else
            ++it;
    }

	return Util::Crc32( tmp.c_str() );
}
tagCPKTable* CPKUpdate::GetTable(uint32_t hash)
{
    std::map<uint32_t,tagCPKTable*>::iterator it_find = m_hash2table.find( hash );
	if ( it_find != m_hash2table.end() )
		return it_find->second;

	return NULL;
}

tagCPKTable* CPKUpdate::NewTable(uint32_t hash, uint32_t len)
{
    if ( m_Header.file_num == m_Header.max_table_num )
    {
        SetError( EPEC_PackageFull );
    	return NULL;
    }

	tagCPKTable* tab_find = NULL;

	// ����Ѱ�ҿ��õ���Ƭ�ռ�
	uint32_t min_fragment_index = m_Header.max_table_num;
	uint32_t min_fragment_len   = uint32_t(-1);
	for ( uint32_t i = m_Header.file_num; i < m_Header.valid_table_num; ++i )
	{
		tagCPKTable* tab = &m_vTable[i];

		if ( tab->packed_size >= len )
		{
			tab->hash1 = hash;			
			
			// ��Ƭʣ��ռ����ָ��ֵ���һ���ʣ��ı�����õ�ʱ�� ����׷��ʣ��Ŀռ�
			uint32_t new_fragment_len = tab->packed_size - len;
			if ( new_fragment_len > TPK_MIN_TRACK_FRAGMENT &&
				 m_Header.valid_table_num < m_Header.max_table_num )
			{
				m_vTable[m_Header.valid_table_num].data_offset = tab->data_offset + len;
				m_vTable[m_Header.valid_table_num].packed_size = tab->packed_size - len;
				m_Header.valid_table_num += 1;
			}

			tab->packed_size = len;
			tab_find = tab;
			goto find_ok;
		}
		
		if ( tab->packed_size < min_fragment_len )
			min_fragment_index = i;
	}

	// ���б�����õĻ� ʹ��һ���µı���
	if ( m_Header.valid_table_num < m_Header.max_table_num )
	{
		m_vTable[m_Header.valid_table_num].hash1 = hash;
		m_file.seekg( 0, std::ios_base::end );		
		m_vTable[m_Header.valid_table_num].data_offset = (uint32_t)m_file.tellg();
		m_vTable[m_Header.valid_table_num].packed_size = len;
		m_Header.valid_table_num += 1;

		tab_find = &m_vTable[m_Header.valid_table_num-1];
		goto find_ok;
	}

	// û�б�������� ������С����Ƭ�ռ�
	if ( min_fragment_index < m_Header.max_table_num )	
	{
		m_vTable[min_fragment_index].hash1 = hash;
		m_file.seekg( 0, std::ios_base::end );		
		m_vTable[min_fragment_index].data_offset = (uint32_t)m_file.tellg();
		m_vTable[min_fragment_index].packed_size = len;

		tab_find = &m_vTable[min_fragment_index];
		goto find_ok;
	}

	// û�п��õı���ռ���
    SetError( EPEC_PackageFull );
    return NULL;

find_ok:
	// ���ҵ��ı����ƶ�����Ч�ļ�������
	std::swap( *tab_find, m_vTable[m_Header.file_num] );
	tab_find = &m_vTable[m_Header.file_num];
	m_Header.file_num += 1;

	// �±�����뵽HASH��������
	m_hash2table[hash] = tab_find;
    m_Header.package_size += tab_find->packed_size;

	return tab_find;
}
bool CPKUpdate::FreeTable(uint32_t hash)
{
	tagCPKTable* tab = GetTable( hash );
	if ( !tab )
    {
        SetError( EPEC_HashNotExist );
        return false;
    }

	// ��������ɾ��
	m_hash2table.erase( hash );
	
	// �������ƶ�����Ƭ����
	assert( m_Header.valid_table_num > 1 );
	std::swap( *tab,  m_vTable[m_Header.file_num-1] );

    // ���½����ı�������
    m_hash2table[tab->hash1] = tab;

	m_Header.file_num -= 1;
    m_Header.package_size -= m_vTable[m_Header.file_num].packed_size;

	return true;
}

bool CPKUpdate::RebuildHashMap()
{
	m_hash2table.clear();
	for ( uint32_t i = 0; i < m_Header.file_num; ++i )
	{
		tagCPKTable* tab = &m_vTable[i];
		
		if ( m_hash2table.find( tab->hash1 ) != m_hash2table.end() )
        {
            SetError( EPEC_HashConflict );
            return false;
        }

		m_hash2table[tab->hash1] = tab;		
	}

	return true;
}

CPKUpdate::CPKUpdate()
{	
	memset( &m_Header, 0, sizeof(tagCPKHeader) );
	m_bDirty = false;
}

CPKUpdate::~CPKUpdate()
{
	Close();
}

bool CPKUpdate::Create(tstring const& strPackage, uint32_t maxFileNum)
{
	std::fstream fs_new;
	fs_new.open( strPackage.c_str(), 
		std::ios_base::binary|std::ios_base::out|std::ios_base::trunc );
	if ( !fs_new.is_open() )
    {
        SetError( EPEC_IOCreateFileFailed );
        return false;
    }
	
	// ��д�ļ�ͷ��Ϣ	
	tagCPKHeader header_new;
	header_new.magic				= TPK_MAGIC;
	header_new.ver					= TPK_VERSION;	
	header_new.table_start_offset	= sizeof(tagCPKHeader);
	header_new.data_start_offset	= sizeof(tagCPKHeader) + maxFileNum * sizeof(tagCPKTable);	
	header_new.header_size   		= sizeof(tagCPKHeader);
	header_new.file_num				= 0;
	header_new.valid_table_num  	= 0;	
	header_new.max_table_num    	= maxFileNum;	
	header_new.package_size    		= 0;
    header_new.ctime                = _time64(NULL);

	std::vector<tagCPKTable> table_empty;	
	table_empty.resize( header_new.max_table_num );
	memset( &(table_empty[0]), 0, sizeof(tagCPKTable) * header_new.max_table_num );

	// д�ļ�ͷ
	fs_new.write( (char*)&header_new, sizeof(tagCPKHeader) );
	if ( fs_new.bad() )
    {
        SetError( EPEC_IOWriteFileFailed );
    	return false;
    }
	
	// д������
	fs_new.write( (char*)&(table_empty[0]), sizeof(tagCPKTable) * header_new.max_table_num );
	if ( fs_new.bad() )
	{
        SetError( EPEC_IOWriteFileFailed );
    	return false;
    }
	
	// �ر��ļ�
	fs_new.close();

    // ɾ��ͬ���ı����ļ�ͷ
    m_path = strPackage;
    DeleteBackupHeader();
	
	return Open( strPackage );
}

bool CPKUpdate::Open(tstring const& strPackage)
{
	Close();

    m_path = strPackage;

    // ����ļ�ͷ����
    CheckBackupHeader();

	// ֻ��ģʽ���ļ� �����ļ��Ƿ����
    m_file.open( strPackage.c_str(), std::ios_base::in | std::ios_base::binary );
	if ( !m_file.is_open() )
    {
        SetError( EPEC_IOOpenFileNotExist );
    	return false;
    }

	// ��дģʽ���ļ�
	m_file.close();
	m_file.open( strPackage.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::binary, _SH_DENYRW );
	if ( !m_file.is_open() )
    {
        SetError( EPEC_IOOpenFileFailed );
        return false;
    }

    // ��ȡ��У���ļ�ͷ�ͱ��� ����HASH������
    if ( !ReadHeaderAndTable(m_file, m_Header, m_vTable) ||
         !RebuildHashMap() )
    {
        Close();
        return false;
    }

	return true;
}

bool CPKUpdate::Close()
{
	Flush();

	if ( m_file.is_open() )
		m_file.close();

	memset( &m_Header, 0, sizeof(tagCPKHeader) );
	m_vTable.swap(std::vector<tagCPKTable>());
	m_bDirty = false;
    m_path = _T("");
	
	return true;
}


bool CPKUpdate::Flush()
{
	if ( !m_bDirty )
		return true;

	// ������������
	SortTable();

	// �ؽ�HASHӳ��
	if ( !RebuildHashMap() )
		return false;

    BackupHeader();

    // д���ļ�ͷ�ͱ���
    if ( !WriteHeaderAndTable(m_file, m_Header, m_vTable) )
        return false;

    DeleteBackupHeader();
	
	m_bDirty = false;
	return true;
}
bool CPKUpdate::AddFile(tstring const& strFile, void const* pData, size_t len)
{
    return _AddFile( CalcHash(strFile), pData, len );
}

bool CPKUpdate::AddFile(tstring const& strFile)
{
	std::fstream fs_read;
	fs_read.open( strFile.c_str(), std::ios_base::in|std::ios_base::binary );
	if ( !fs_read.is_open() )
    {
        SetError( EPEC_IOOpenFileFailed );
        return false;
    }

	fs_read.seekg( 0, std::ios_base::end );
	uint32_t len = (uint32_t)fs_read.tellg();
	fs_read.seekg( 0, std::ios_base::beg );
	
	std::vector<char> vBuffer;
	vBuffer.resize( len > 0 ? len : 1 );
	fs_read.read( &vBuffer[0], len );

	if ( fs_read.bad() )
    {
        SetError( EPEC_IOReadFileFailed );
        return false;
    }

	return AddFile( strFile, &vBuffer[0], len );
}

bool CPKUpdate::DelFile(tstring const& strFile)
{
    return _DelFile( CalcHash(strFile) );
}

FileSizeResult CPKUpdate::GetFileSize(tstring const& strFile)
{
    return _GetFileSize( CalcHash(strFile) );
}

bool CPKUpdate::GetFileData(tstring const& strFile, void* pData, size_t len)
{
    return _GetFileData( CalcHash(strFile), pData, len );
}

void CPKUpdate::CheckBackupHeader()
{
    tstring bak_path = GetBackupPath( m_path );

    {
        std::fstream bak_fs( bak_path.c_str(), std::ios_base::in|std::ios_base::binary );
        std::fstream ori_fs( m_path.c_str(), std::ios_base::in|std::ios_base::out|std::ios_base::binary );
        if ( !bak_fs || !ori_fs )
            return;

        tagCPKHeader bak_header;
        std::vector<tagCPKTable> bak_table;
        if ( !ReadHeaderAndTable(bak_fs, bak_header, bak_table) )
            return;

        tagCPKHeader ori_header;
        std::vector<tagCPKTable> ori_table;
        if ( !ReadHeaderAndTable(ori_fs, ori_header, ori_table) )
            return;

        // ��֤�����ļ�ͷ
        if ( ori_header.magic               == bak_header.magic             &&
             ori_header.ver                 == bak_header.ver               &&
             ori_header.max_table_num       == bak_header.max_table_num     &&
             ori_header.table_start_offset  == bak_header.table_start_offset&&
             ori_header.header_size         == bak_header.header_size       &&
             ori_header.data_start_offset   == bak_header.data_start_offset &&
             ori_header.ctime               == bak_header.ctime )
        {
            WriteHeaderAndTable( ori_fs, bak_header, bak_table );
        }
    }

    DeleteBackupHeader();
}

void CPKUpdate::BackupHeader()
{
    tstring bak_path = GetBackupPath( m_path );

    std::fstream bak_fs( bak_path.c_str(), std::ios_base::out|std::ios_base::binary );
    if ( !bak_fs )
        return;

    // �޸�д����ļ�ͷMAGICֵΪ��Ч��ֵ
    // д��ɹ�֮����д����ȷ��MAGICֵ
    uint32_t real_magic = m_Header.magic;
    m_Header.magic = 0;

    WriteHeaderAndTable( bak_fs, m_Header, m_vTable );

    m_Header.magic = real_magic;

    bak_fs.seekp( 0, std::ios_base::beg );
    bak_fs.write( (char*)&m_Header.magic, sizeof(m_Header.magic) );
}

void CPKUpdate::DeleteBackupHeader()
{
    tstring bak_path = GetBackupPath( m_path );

    _tremove( bak_path.c_str() );
}

tstring CPKUpdate::GetBackupPath(tstring const& strPath)
{
    tstring strTemp = strPath;
    tstring::size_type pos = strTemp.find_last_of( _T('.') );
    if ( pos != tstring::npos )
        strTemp = strTemp.substr( 0, pos );
    return strTemp + _T(".bidx");
}

tstring CPKUpdate::GetRebuildPath(tstring const& strPath)
{
    tstring strTemp = strPath;
    tstring::size_type pos = strTemp.find_last_of( _T('.') );
    if ( pos != tstring::npos )
        strTemp = strTemp.substr( 0, pos );
    return strTemp + _T(".rebd");
}

tstring CPKUpdate::GetRebuildBackupPath(tstring const& strPath)
{
    tstring strTemp = strPath;
    tstring::size_type pos = strTemp.find_last_of( _T('.') );
    if ( pos != tstring::npos )
        strTemp = strTemp.substr( 0, pos );
    return strTemp + _T(".rebbak");
}

bool CPKUpdate::ReadHeaderAndTable(std::fstream& fs, tagCPKHeader& header, std::vector<tagCPKTable>& table)
{
    // ��ȡ�ļ�ͷ
    fs.seekg( 0, std::ios_base::beg );
    if ( !fs.read( (char*)&header, sizeof(tagCPKHeader) ) )
    {
        SetError( EPEC_IOReadFileFailed );
        return false;
    }

    // У���ļ�ͷ
    if ( header.magic != TPK_MAGIC )
    {
        SetError( EPEC_OpenMagicInvalid );
        return false;
    }
    if ( header.ver != TPK_VERSION )
    {
        SetError( EPEC_OpenVersionInvalid );
        return false;
    }
    if ( header.max_table_num  > TPK_MAX_FILE            || 
        header.valid_table_num > header.max_table_num  ||
        header.file_num        > header.valid_table_num )
    {
        SetError( EPEC_OpenFileNumInvalid );
        return false;
    }

    // ��ȡ������
    table.resize( header.max_table_num );
    fs.seekg( header.table_start_offset, std::ios_base::beg );
    if ( !fs.read( (char*)&(table[0]), sizeof(tagCPKTable) * header.max_table_num ) )
    {
        SetError( EPEC_IOReadFileFailed );
        return false;
    }

    return true;
}

bool CPKUpdate::WriteHeaderAndTable(std::fstream& fs, tagCPKHeader const& header, std::vector<tagCPKTable> const& table)
{
	// д�ļ�ͷ
	fs.seekp( 0, std::ios_base::beg );
	fs.write( (char*)&header, sizeof(tagCPKHeader) );
	if ( fs.bad() )
    {
        SetError( EPEC_IOWriteFileFailed );
        return false;
    }
	
	// д������
    if ( table.size() < header.max_table_num )
    {
        SetError( EPEC_IOWriteFileFailed );
        return false;
    }
	fs.seekp( header.table_start_offset, std::ios_base::beg );
	fs.write( (char*)&(table[0]), sizeof(tagCPKTable) * header.max_table_num );
	if ( fs.bad() )
	{
        SetError( EPEC_IOWriteFileFailed );
        return false;
    }

    return true;
}

void CPKUpdate::SetError(EPackageErrorCode code, tstring const& msg/* = _T("")*/)
{
    m_errCode = code;
    m_errMsg  = msg;
}

EPackageErrorCode CPKUpdate::GetErrorCode()
{
    return m_errCode;
}

tstring const& CPKUpdate::GetErrorMsg()
{
    return m_errMsg;
}

bool CPKUpdate::Rebuild()
{
    if ( m_path.empty() )
        return false;

    tstring strOrigin  = m_path;
    tstring strBackup  = GetRebuildBackupPath( m_path );
    tstring strRebuild = GetRebuildPath( m_path );

    CPKUpdate new_pck;
    if ( !new_pck.Create(strRebuild, m_Header.max_table_num) )
        return false;

    std::vector<char> vBuffer;
    for ( std::map<uint32_t,tagCPKTable*>::iterator it = m_hash2table.begin(); 
        it != m_hash2table.end(); ++it )
    {
        uint32_t hash = it->first;

        FileSizeResult ret = _GetFileSize( hash );
        if ( !ret.first )
            return false;

        vBuffer.resize( ret.second > 0 ? ret.second : 1 );
        if ( !_GetFileData( hash, &vBuffer[0], ret.second ) )
            return false;

        if ( !new_pck._AddFile(hash, &vBuffer[0], ret.second) )
            return false;
    }

    if ( !new_pck.Close() )
        return false;
    if ( !this->Close() )
        return false;

    if ( _trename(strOrigin.c_str(), strBackup.c_str()) != 0 )
        return false;
    if ( _trename(strRebuild.c_str(), strOrigin.c_str()) != 0 )
    {
        _trename(strBackup.c_str(), strOrigin.c_str());
        return false;
    }
    _tremove(strBackup.c_str());

    return true;
}

float CPKUpdate::GetFragmentPercent()
{
    float percent = 0.0f;

    if ( m_file )
    {
        m_file.seekg( 0, std::ios_base::end );
        float total_size = (float)m_file.tellg();
        total_size -= m_Header.header_size;
        total_size -= m_Header.max_table_num * sizeof(tagCPKTable);

        if ( total_size != 0.0f )
        {
            percent = (total_size - m_Header.package_size)/total_size;

            if ( percent < 0.0f )
                percent = 0.0f;
            if ( percent >1.0f )
                percent = 1.0f;
        }
    }

    return percent;
}

bool CPKUpdate::_AddFile(uint32_t hash, void const* pData, size_t len)
{
	// HASH��ͻ
	tagCPKTable* tab = GetTable( hash );
	if ( tab )
    {
        SetError( EPEC_HashConflict );
    	return false;
    }

	// �㳤���ļ�����
	if ( len == 0 )
	{
		// �½�����
		tab = NewTable( hash, len );
		if ( !tab )
			return false;

		assert( tab->packed_size == len );
		tab->origin_size = (uint32_t)len;
		SET_NOCOMPRESSED( tab->flag );

		m_bDirty = true;
		return true;
	}

	// ѹ������
	Compress::CompressPtr cp = Compress::GetCompressInterface( Compress::ECT_ZLIB );
	uint32_t buf_size = cp->GetBufferSize( len );	

	std::vector<uint8_t> buf;
	buf.resize( buf_size > 0 ? buf_size : 1 );
	Compress::ProcessResult cp_ret = 
		cp->Compress( &buf[0], buf_size, (uint8_t*)pData, (uint32_t)len );
		
	// ѹ�������ɹ���ѹ�������ݱ�ԭ����С
	if ( cp_ret.first && cp_ret.second < len )
	{
		// �½�����
		tab = NewTable( hash, cp_ret.second );
		if ( !tab )
			return false;
		
		assert( tab->packed_size == cp_ret.second );
		tab->origin_size = (uint32_t)len;
		SET_COMPRESSED( tab->flag );
		
		// д��ѹ������ļ�����
		m_file.seekp( tab->data_offset, std::ios_base::beg );
		m_file.write( (char*)&buf[0], cp_ret.second );		
		if ( m_file.bad() )
        {
            SetError( EPEC_IOWriteFileFailed );
        	return false;
        }
	}	
	// ʹ��ԭ����
	else
	{
		// �½�����
		tab = NewTable( hash, len );
		if ( !tab )
			return false;

		assert( tab->packed_size == len );
		tab->origin_size = (uint32_t)len;
		SET_NOCOMPRESSED( tab->flag );

		// д��ԭʼ�ļ�����
		m_file.seekp( tab->data_offset, std::ios_base::beg );
		m_file.write( (char*)pData, len );
		if ( m_file.bad() )
	    {
            SetError( EPEC_IOWriteFileFailed );
        	return false;
        }
	}

	m_bDirty = true;
	return true;
}

bool CPKUpdate::_DelFile(uint32_t hash)
{
    if ( FreeTable( hash ) )
	{
		m_bDirty = true;
		return true;
	}

	return false;
}

FileSizeResult CPKUpdate::_GetFileSize(uint32_t hash)
{
	FileSizeResult ret;
	ret.first  = false;
	ret.second = 0;

	if ( !m_file.is_open() )
		return ret;

	tagCPKTable* tab = GetTable( hash );
	if ( !tab )
		return ret;		

	ret.second = tab->origin_size;
	ret.first  = true;
	
	return ret;
}

bool CPKUpdate::_GetFileData(uint32_t hash, void* pData, size_t len)
{
	if ( !m_file.is_open() )
		return false;

	tagCPKTable* tab = GetTable( hash );
	if ( !tab )
		return false;

	// ��������С
	if ( tab->origin_size > len )
    {
        SetError( EPEC_BuffTooSmall );
    	return false;
    }

	// ѹ������
	if ( IS_COMPRESSED( tab->flag ) )
	{
		// ��ȡѹ������
		std::vector<uint8_t> compress_data;
		compress_data.resize( tab->packed_size > 0 ? tab->packed_size : 1 );
		m_file.seekg( tab->data_offset, std::ios_base::beg );
		m_file.read( (char*)&compress_data[0], tab->packed_size );
		if ( !m_file.good() )
        {
            SetError( EPEC_IOReadFileFailed );
        	return false;
        }

		Compress::CompressPtr cp = Compress::GetCompressInterface(Compress::ECT_ZLIB);
		uint32_t buf_size = cp->GetBufferSize( tab->origin_size );

		std::vector<uint8_t> buf;
		buf.resize( buf_size > 0 ? buf_size : 1 );
		Compress::ProcessResult cp_ret = cp->Uncompress( &buf[0], buf_size, &compress_data[0], tab->packed_size );

		// ��ѹʧ��
		if ( !cp_ret.first || cp_ret.second != tab->origin_size )
        {
            SetError( EPEC_UncompressFailed );
        	return false;
        }

		// ����������
		if ( cp_ret.second > len )
        {
            SetError( EPEC_BuffTooSmall );
        	return false;
        }

		// ������ѹ������ݵ�������
		memcpy( pData, &buf[0], cp_ret.second );
	}
	// ��ѹ������
	else
	{
		// ֱ�Ӷ�ȡ�ļ����ݵ�������
		m_file.seekg( tab->data_offset, std::ios_base::beg );
		m_file.read( (char*)pData, tab->packed_size );
		if ( !m_file.good() )
        {
            SetError( EPEC_IOReadFileFailed );
        	return false;
        }
	}

	return true;
}

}; // namespace Package