#include "stdafx.h"
#include "NetFilterMgr.h"

// ʹ����������
//#include "..\vfs\cpkdefine.h"
#include "minilzo\minilzo.h"
//#include "zlib\zlib.h"

namespace Tang {
namespace Net {

//minilzo��Ҫ������Ѷ���
#define HEAP_ALLOC(var,size) \
	long __LZO_MMODEL var [((size)+(sizeof(long)-1))/sizeof(long)]
static HEAP_ALLOC(pLzoWorkMem, LZO1X_1_MEM_COMPRESS);


//-----------------------------------------------------------------------------
// construction / destruction
//-----------------------------------------------------------------------------
NetFilterMgr::NetFilterMgr()
{
	InitFilter(FMF_MiniLzo);	// minilzo��Ҫ��ʼ��
}

NetFilterMgr::~NetFilterMgr()
{}



//-----------------------------------------------------------------------------
// ��ʼ��������
//-----------------------------------------------------------------------------
BOOL NetFilterMgr::InitFilter(EFM_FILTER eFilter)
{
	INT nResult = 0;
	switch(eFilter)
	{
	case FMF_MiniLzo:
		nResult = lzo_init();
		if( LZO_E_OK!=nResult )
			return FALSE;
		
		break;
	}

	return TRUE;
}


//-----------------------------------------------------------------------------
// �õ����ֹ������㷨��Ҫ�Ķ�������ռ䣬����ָWork Space
// ��Щ�����㷨���������
//-----------------------------------------------------------------------------
DWORD NetFilterMgr::GetFilterExtraSpace(DWORD dwInSize, EFM_FILTER eFilter)
{
	DWORD dwAddition = 0;
	switch(eFilter)
	{
	case FMF_MiniLzo:
		dwAddition = (dwInSize/64) + 16 + 3;
		break;

	case FMF_ZLib:
	case FMF_ZLibDeflated:
		// 0.1% larger than sourcelen plus 12 bytes
		dwAddition = (dwInSize/1000) + 12;
		break;
	}

	return dwAddition;
}



//-----------------------------------------------------------------------------
// �����ֹ������㷨��Ҫ�Ķ�������ռ䣬����ָWork Space
//-----------------------------------------------------------------------------
BOOL NetFilterMgr::CheckExtraSpace(DWORD dwInSize, DWORD dwOutSize,
								 EFM_FILTER eFilter)
{
	DWORD dwAddition = GetFilterExtraSpace(dwInSize, eFilter);

	if( dwOutSize < dwInSize + dwAddition )
		return FALSE;
	else
		return TRUE;
}



//-----------------------------------------------------------------------------
// ��ʼ���˹���
//-----------------------------------------------------------------------------
VOID NetFilterMgr::Filter(tagFilterParam *pParam)
{
	SI_ASSERT(pParam);
	switch(pParam->eFilter)
	{
	//case FMF_Changeless:
	//	memcpy(pParam->lpMemOut, pParam->lpMemIn, pParam->dwInDataSize);
	//	pParam->dwOutDataSize = pParam->dwInDataSize;
	//	pParam->bSuccess = TRUE;
	//	break;

	case FMF_MiniLzo:
		FilterMiniLzo(pParam);
		break;

	//case FMF_ZLib:
	//	FilterZLib(pParam);
	//	break;

	//case FMF_ZLibDeflated:	// zip ѹ���ļ��Ľ�ѹ����
	//	FilterZLibDeflated(pParam);
	//	break;

	default:
		SI_ASSERT(0);
		break;
	}

}

//-----------------------------------------------------------------------------
// ��������ѹ���㷨 minilzo
//-----------------------------------------------------------------------------
VOID NetFilterMgr::FilterMiniLzo(tagFilterParam* pParam)
{
	INT nResult = 0;
	if( pParam->bCompress )	// minilzo compress
	{
		nResult = lzo1x_1_compress((lzo_byte*)pParam->lpMemIn,
			pParam->dwInDataSize,
			(lzo_byte*)pParam->lpMemOut,
			(lzo_uint*)&(pParam->dwOutDataSize),
			pLzoWorkMem);
		if (nResult == LZO_E_OK)
			pParam->bSuccess = TRUE;
		else
		{
			pParam->bSuccess = FALSE;
			CONSOLE_TRACE(_T("MiniLzo compression failed: %d\n"), nResult);
		}
	}
	else	// minilzo decompress
	{
		nResult = lzo1x_decompress((lzo_byte*)pParam->lpMemIn,
			pParam->dwInDataSize,
			(lzo_byte*)pParam->lpMemOut,
			(lzo_uint*)&(pParam->dwOutDataSize),
			NULL);
		if( nResult == LZO_E_OK )
			pParam->bSuccess = TRUE;
		else
			pParam->bSuccess = FALSE;
	}
}


//-----------------------------------------------------------------------------
// ��������ѹ���㷨 zlib
//-----------------------------------------------------------------------------
VOID NetFilterMgr::FilterZLib(tagFilterParam* pParam)
{
	//INT nResult = 0;
	//if( pParam->bCompress ) // zlib compress
	//{
	//	nResult = ::compress((PBYTE)pParam->lpMemOut, &(pParam->dwOutDataSize),
	//		(PBYTE)pParam->lpMemIn, pParam->dwInDataSize);
	//	
	//	if( nResult == Z_OK )
	//		pParam->bSuccess = TRUE;
	//	else
	//	{
	//		pParam->bSuccess = FALSE;
	//		CONSOLE_TRACE(_T("zlib compression failed."));
	//	}
	//}
	//else	// zlib decompress
	//{	
	//	nResult = ::uncompress((PBYTE)pParam->lpMemOut, &(pParam->dwOutDataSize),
	//		(PBYTE)pParam->lpMemIn, pParam->dwInDataSize);
	//	
	//	if( nResult == Z_OK )
	//		pParam->bSuccess = TRUE;
	//	else
	//	{	
	//		pParam->bSuccess = FALSE;
	//		CONSOLE_TRACE(_T("zlib uncompression failed."));
	//	}
	//}
}


//-----------------------------------------------------------------------------
// ��������ѹ���㷨 zlib deflated
//-----------------------------------------------------------------------------
VOID NetFilterMgr::FilterZLibDeflated(tagFilterParam* pParam)
{
	//SI_ASSERT( !pParam->bCompress ); // ֻ��ѹ
	//
	//INT nErr;
	//z_stream d_stream; // decompression stream
	//
	//memset(&d_stream,0,sizeof(d_stream));
	//d_stream.zalloc = (alloc_func)0;
	//d_stream.zfree	= (free_func)0;
	//d_stream.opaque = (voidpf)0;
	//
	//d_stream.next_in  = (Bytef*)pParam->lpMemIn;
	//d_stream.avail_in = pParam->dwInBufferSize;
	//
	//nErr = inflateInit2(&d_stream,-MAX_WBITS);
	//if( nErr != Z_OK )
	//{
	//	pParam->bSuccess = FALSE;
	//	CONSOLE_TRACE(_T("ZIP decompression (inflateInit2) failed."));
	//	return; 
	//}
	//
	//for ( ;; )
	//{
	//	d_stream.next_out  = (Bytef*)pParam->lpMemOut;
	//	d_stream.avail_out = pParam->dwOutBufferSize;
	//	
	//	nErr = inflate(&d_stream,Z_FINISH);
	//	if( nErr == Z_STREAM_END )
	//		break;
	//	
	//	if( nErr != Z_OK )
	//	{
	//		switch( nErr )
	//		{
	//		case Z_MEM_ERROR:	
	//			CONSOLE_TRACE(_T("ZIP decompression failed (memory error)."));
	//			break;
	//		case Z_BUF_ERROR:	
	//			CONSOLE_TRACE(_T("ZIP decompression failed (buffer error)."));
	//			break;
	//		case Z_DATA_ERROR:	
	//			CONSOLE_TRACE(_T("ZIP decompression failed (data error)."));
	//			break;
	//		default:
	//			CONSOLE_TRACE(_T("ZIP decompression failed (unknown error)."));
	//		}
	//		pParam->bSuccess = FALSE;
	//		return;
	//	}
	//}
	//
	//nErr = inflateEnd( &d_stream );
	//if( nErr != Z_OK )
	//{
	//	CONSOLE_TRACE(_T("ZIP decompression (inflateEnd) failed."));
	//	pParam->bSuccess = FALSE;
	//	return;
	//}
	//
	//pParam->dwOutDataSize = d_stream.total_out;
	//pParam->bSuccess = TRUE;
}

} // namespace Net {
} // namespace Tang {
