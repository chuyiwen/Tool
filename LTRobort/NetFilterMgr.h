#pragma once
namespace Tang {
namespace Net {

enum EFM_FILTER	// ����������
{
	FMF_Null,

	// ��������ѹ���㷨
	FMF_Changeless,
	FMF_MiniLzo,
	FMF_ZLib,
	FMF_ZLibDeflated,

	// ���ּ��ܽ���ɢ���㷨
	FMF_Des,
	FMF_Ras,
	FMF_Md5,
	FMF_Sha1,
	FMF_Sha512,

	FMF_End
};
 
struct tagFilterParam	// ��������������
{
	// ���²����ɵ��÷���д(in)
	EFM_FILTER	eFilter;			// ���к��ֹ���
	BOOL		bCompress;			// �����������
	LPVOID		lpMemIn;			// Դָ��(ָ�����뻺��)
	LPVOID		lpMemOut;			// Ŀ��ָ��(ָ���������)
	DWORD		dwInBufferSize;		// ���뻺���С
	DWORD		dwOutBufferSize;	// ��������С
	DWORD		dwInDataSize;		// �������ݴ�С
	DWORD		dwQueryPart;		// ��Ҫĳһ������

	// ���²����ɹ�������д(out)
	DWORD		dwOutDataSize;	
	BOOL		bSuccess;
};

class NetFilterMgr
{
public:

	BOOL InitFilter(EFM_FILTER eFilter);	// ��ʼ��������
	
	// �õ�����������Ҫ��Dest���帽��ֵ
	DWORD GetFilterExtraSpace(DWORD dwSrcSize, EFM_FILTER eFilter);
	// �����ֹ������㷨��Ҫ�Ķ�������ռ�
	BOOL CheckExtraSpace(DWORD dwInSize, DWORD dwOutSize, EFM_FILTER eFilter);

	VOID Filter(tagFilterParam* pParam);

	NetFilterMgr();
	~NetFilterMgr();

private:
	// ��������ѹ���㷨
	VOID FilterMiniLzo(tagFilterParam* pParam);
	VOID FilterZLib(tagFilterParam* pParam);
	VOID FilterZLibDeflated(tagFilterParam* pParam);

};

} // namespace Net {
} // namespace Tang {
