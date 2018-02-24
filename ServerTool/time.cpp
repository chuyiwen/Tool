#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include <windows.h>
#include "time.h"
#include <stdio.h>

//-------------------------------------------------------------------------------------
// �õ���ǰʱ��
//-------------------------------------------------------------------------------------
tagDWORDTime GetCurrentDWORDTime()
{
	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
	tagDWORDTime time;
	time.day = CurTime.wDay;
	time.hour = CurTime.wHour;
	time.min = CurTime.wMinute;
	time.month = CurTime.wMonth;
	time.sec = CurTime.wSecond;
	time.year = (CurTime.wYear) % 100;

	return time;
}

//-------------------------------------------------------------------------------------
// �ж�ĳ���Ƿ�Ϊ����
//-------------------------------------------------------------------------------------
BOOL IsLeapYear(WORD iYear)
{
	return !(iYear % 4) && (iYear % 100) || !(iYear % 400);
}   

//-------------------------------------------------------------------------------------
// �����������ڵ�ʱ��������
//-------------------------------------------------------------------------------------
DWORD CalcTimeDiff(tagDWORDTime destTime, tagDWORDTime srcTime)
{
	if( *(DWORD*)(&destTime) == *(DWORD*)(&srcTime) )
		return 0;

	tagDWORDTime* pDestTime = (tagDWORDTime*)(&destTime);
	tagDWORDTime* pSrcTime = (tagDWORDTime*)(&srcTime);

	// ��dwSrcTime�����һ��һ��0ʱ0��0��Ϊ��׼,�������˶�����ʱ��
	DWORD dwSrcRun =  0;	// src���ŵ�ʱ��
	DWORD dwDestRun =  0;   // dest���ŵ�ʱ��

	{
		// ����src������ʱ��(��)
		for(INT i = 1; i < (INT)pSrcTime->month; i++)
		{
			// ���ŵ��·�
			if( i == 2 )
			{
				// ����,���ǿ����ǲ�������
				if( TRUE == IsLeapYear((WORD)(pSrcTime->year) + 2000) )
				{
					dwSrcRun += 29 * 24 * 60 * 60;
				}
				else
				{
					dwSrcRun += 28 * 24 * 60 * 60;
				}

				continue;
			}

			if( i <= 7 )
			{
				if( i%2 == 0 )
					dwSrcRun += 30 * 24 * 60 * 60;
				else
					dwSrcRun += 31 * 24 * 60 * 60;
			}
			else
			{
				if( i%2 == 1 )
					dwSrcRun += 30 * 24 * 60 * 60;
				else
					dwSrcRun += 31 * 24 * 60 * 60;
			}
		}

		// ������,Сʱ���֣��������ʱ��
		dwSrcRun += (pSrcTime->day-1) * 24 * 60 * 60 + \
			pSrcTime->hour * 60 * 60 + \
			pSrcTime->min * 60 + \
			pSrcTime->sec;

	}

	{
		// ����dest���ŵ�ʱ��
		for(INT i = pSrcTime->year; i < (INT)pDestTime->year; i++)
		{
			// ���ŵ�������
			if( TRUE == IsLeapYear(i + 2000) )
			{
				dwDestRun += 366 * 24 * 60 * 60;
			}
			else
			{
				dwDestRun += 365 * 24 * 60 * 60;
			}
		}

		//dest�Ը���һ��һ��0ʱ0��0��Ϊ��׼�����ŵ�ʱ��
		for(INT i=1; i<(INT)pDestTime->month; i++)
		{
			//���ŵ��·�
			if( i == 2 )
			{
				//����,���ǿ����ǲ�������
				if( TRUE == IsLeapYear((WORD)pDestTime->year + 2000) )
				{
					dwDestRun += 29 * 24 * 60 * 60;
				}
				else
				{
					dwDestRun += 28 * 24 * 60 * 60;
				}

				continue;
			}
			if( i <= 7 )
			{
				if( i%2 == 0 )
					dwDestRun += 30 * 24 * 60 * 60;
				else
					dwDestRun += 31 * 24 * 60 * 60;
			}
			else
			{
				if( i%2 == 1 )
					dwDestRun += 30 * 24 * 60 * 60;
				else
					dwDestRun += 31 * 24 * 60 * 60;
			}
		}

		//������,Сʱ���֣��������ʱ��
		dwDestRun += (pDestTime->day-1) * 24 * 60 * 60 + \
			pDestTime->hour * 60 * 60 + \
			pDestTime->min * 60 + \
			pDestTime->sec;
	}


	// SI_ASSERT( dwDestRun >= dwSrcRun );
	if( dwDestRun < dwSrcRun )
		return 0;

	return (dwDestRun - dwSrcRun);
}


//-----------------------------------------------------------------------------
// ʱ���ϵ���ָ������
//-----------------------------------------------------------------------------
tagDWORDTime IncreaseTime(tagDWORDTime srcTime, INT nIncrementSecond)
{
	tagDWORDTime* pSrcTime = (tagDWORDTime*)(&srcTime);

	// ��dwSrcTime�����һ��һ��0ʱ0��0��Ϊ��׼,�������˶�����ʱ��
	DWORD dwSrcRun =  0;		// src���ŵ�ʱ��

	{
		// ����src������ʱ��(��)
		for(INT i = 1; i < (INT)pSrcTime->month; i++)
		{
			// ���ŵ��·�
			if( i == 2 )
			{
				// ����,���ǿ����ǲ�������
				if( TRUE == IsLeapYear((WORD)pSrcTime->year + 2000) )
				{
					dwSrcRun += 29 * 24 * 60 * 60;
				}
				else
				{ 
					dwSrcRun += 28 * 24 * 60 * 60;
				}

				continue;
			}

			if( i <= 7 )
			{
				if( i%2 == 0 )
					dwSrcRun += 30 * 24 * 60 * 60;
				else
					dwSrcRun += 31 * 24 * 60 * 60;
			}
			else
			{
				if( i%2 == 1 )
					dwSrcRun += 30 * 24 * 60 * 60;
				else
					dwSrcRun += 31 * 24 * 60 * 60;
			}
		}

		// ������,Сʱ���֣��������ʱ��
		dwSrcRun += (pSrcTime->day-1) * 24 * 60 * 60 + \
			pSrcTime->hour * 60 * 60 + \
			pSrcTime->min * 60 + \
			pSrcTime->sec;

	}


	// ���ϵ�����ʱ��
	DWORD dwRunTime = dwSrcRun + nIncrementSecond;

	// ��ʱ������
	INT nDays = dwRunTime / (24*60*60);           // ������
	INT nSecs  = dwRunTime % (24*60*60);          // ����ʣ�������

	// ��ʼ�����ʱ��
	tagDWORDTime destTime;
	tagDWORDTime* pDestTime = (tagDWORDTime*)(&destTime);

	// �ȼ�����
	pDestTime->year = pSrcTime->year;
	for( ;; )
	{
		INT nDaysPerYear = 0;
		if( TRUE == IsLeapYear((WORD)pDestTime->year + 2000) )
			nDaysPerYear = 366;
		else
			nDaysPerYear = 365;

		if( nDays < nDaysPerYear )
			break;

		pDestTime->year++;
		nDays -= nDaysPerYear;
	}

	// �ټ�������
	pDestTime->month = 1;
	pDestTime->day = 1;
	for( ;; )
	{
		INT nDaysPerMonth = 0;

		// ���������Ҫ������
		if( pDestTime->month == 2 )
		{
			// ����,���ǿ����ǲ�������
			if( TRUE == IsLeapYear((WORD)pDestTime->year + 2000) )
			{
				nDaysPerMonth = 29;
			}
			else
			{
				nDaysPerMonth = 28;
			}
		}
		else if( pDestTime->month <= 7 )
		{
			if( pDestTime->month % 2 == 0 )
				nDaysPerMonth = 30 ;
			else
				nDaysPerMonth = 31;
		}
		else
		{
			if( pDestTime->month % 2 == 1 )
				nDaysPerMonth = 30;
			else
				nDaysPerMonth = 31;
		}

		if( nDays < nDaysPerMonth )
		{
			// ������������
			pDestTime->day += nDays;
			break;
		}

		pDestTime->month++;
		nDays -= nDaysPerMonth;
	}

	// ����Сʱ����
	pDestTime->hour = nSecs / (60*60);
	pDestTime->min = (nSecs / 60) % 60;
	pDestTime->sec = nSecs % 60;

	return destTime;
}

//-----------------------------------------------------------------------------
// ʱ���ϵݼ�ָ������
//-----------------------------------------------------------------------------
tagDWORDTime DecreaseTime(tagDWORDTime srcTime, INT nDecrementSecond)
{
	tagDWORDTime* pSrcTime = (tagDWORDTime*)(&srcTime);

	// ��dwSrcTime�����һ��һ��0ʱ0��0��Ϊ��׼,�������˶�����ʱ��
	DWORD dwSrcRun =  0;		// src���ŵ�ʱ��
	{
		// ����src������ʱ��(��)
		for(INT i = 1; i < (INT)pSrcTime->month; i++)
		{
			// ���ŵ��·�
			if( i == 2 )
			{
				// ����,���ǿ����ǲ�������
				if( TRUE == IsLeapYear((WORD)pSrcTime->year + 2000) )
				{
					dwSrcRun += 29 * 24 * 60 * 60;
				}
				else
				{ 
					dwSrcRun += 28 * 24 * 60 * 60;
				}

				continue;
			}

			if( i <= 7 )
			{
				if( i%2 == 0 )
					dwSrcRun += 30 * 24 * 60 * 60;
				else
					dwSrcRun += 31 * 24 * 60 * 60;
			}
			else
			{
				if( i%2 == 1 )
					dwSrcRun += 30 * 24 * 60 * 60;
				else
					dwSrcRun += 31 * 24 * 60 * 60;
			}
		}

		// ������,Сʱ���֣��������ʱ��
		dwSrcRun += (pSrcTime->day-1) * 24 * 60 * 60 + \
			pSrcTime->hour * 60 * 60 + \
			pSrcTime->min * 60 + \
			pSrcTime->sec;

	}

	DWORD dwSrcLeft =  0;		// src��ǰ��ʣ��ʱ�� 
	INT nDaysPerYear = 0;
	if( TRUE == IsLeapYear((WORD)pSrcTime->year + 2000) )
		nDaysPerYear = 366;
	else
		nDaysPerYear = 365;

	dwSrcLeft = nDaysPerYear * 24 * 60 * 60 - dwSrcRun;

	// ���ϵݼ���ʱ��
	DWORD dwDesTime = dwSrcLeft + nDecrementSecond;

	// ��ʱ������
	INT nDays = dwDesTime / (24*60*60);           // ������
	INT nSecs  = dwDesTime % (24*60*60);          // ����ʣ�������

	// ��ʼ�����ʱ��
	tagDWORDTime destTime;
	tagDWORDTime* pDestTime = (tagDWORDTime*)(&destTime);

	// �ȼ�����
	pDestTime->year = pSrcTime->year;
	for( ;; )
	{
		INT nDaysPerYear = 0;
		if( TRUE == IsLeapYear((WORD)pDestTime->year + 2000) )
			nDaysPerYear = 366;
		else
			nDaysPerYear = 365;

		if( nDays < nDaysPerYear )
			break;

		pDestTime->year--;
		nDays -= nDaysPerYear;
	}

	// ת����Des�����ŵ�ʱ��
	nDays = nDaysPerYear - nDays - 1;
	nSecs = 24 * 60 * 60 - nSecs;

	// �ټ�������
	pDestTime->month = 1;
	pDestTime->day = 1;
	for( ;; )
	{
		INT nDaysPerMonth = 0;

		// ���������Ҫ������
		if( pDestTime->month == 2 )
		{
			// ����,���ǿ����ǲ�������
			if( TRUE == IsLeapYear((WORD)pDestTime->year + 2000) )
			{
				nDaysPerMonth = 29;
			}
			else
			{
				nDaysPerMonth = 28;
			}
		}
		else if( pDestTime->month <= 7 )
		{
			if( pDestTime->month % 2 == 0 )
				nDaysPerMonth = 30 ;
			else
				nDaysPerMonth = 31;
		}
		else
		{
			if( pDestTime->month % 2 == 1 )
				nDaysPerMonth = 30;
			else
				nDaysPerMonth = 31;
		}

		if( nDays < nDaysPerMonth )
		{
			// ������������
			pDestTime->day += nDays;
			break;
		}

		pDestTime->month++;
		nDays -= nDaysPerMonth;
	}

	// ����Сʱ����
	pDestTime->hour = nSecs / (60*60);
	pDestTime->min = (nSecs / 60) % 60;
	pDestTime->sec = nSecs % 60;

	return destTime;
}

//---------------------------------------------------------------------------
// �ж�ĳ��ĳ��ĳ�������ڼ���0Ϊ������
//---------------------------------------------------------------------------
DWORD WhichWeekday(tagDWORDTime dw_time)
{
	// �����������һ��
	INT nYear = (INT)dw_time.year + 2000;

	// Ȼ�󿴵�ǰ����һ��ĵڼ���
	INT nDay = 0;
	for( INT i = 1; i < (INT)dw_time.month; i++ )
	{
		if( i == 2 )
		{
			if( TRUE == IsLeapYear(nYear) )
			{
				nDay += 29;
			}
			else
			{
				nDay += 28;
			}
		}

		else if( i <= 7 )
		{
			if( i%2 == 0 )	nDay += 30;
			else			nDay += 31;
		}
		else
		{
			if( i%2 == 0 )	nDay += 31;
			else			nDay += 30;
		}
	}
	nDay += dw_time.day;

	// ����ն��Ѿ�֪�����Ϳ��Լ�����
	// ̩�չ�ʽ��x-1+[(x-1)/4]-[(x-1)/100]+[(x-1)/400]+c
	return ( (nYear-1) + (nYear-1)/4 - (nYear-1)/100 + (nYear-1)/400 + nDay ) % 7;
}

//-------------------------------------------------------------------------------------
// ת����: ��-��-�� �磺2008-09-12
//-------------------------------------------------------------------------------------
BOOL DwordTime2DataTime(OUT CHAR szTime[], INT nSzArray, const tagDWORDTime &dw_time)
{
	if(nSzArray <= X_DATATIME_LEN)
	{
		return FALSE;
	}

	//sprintf(szTime, "%d%d%d-%d%d-%d%d %d%d:%d%d:%d%d", 20, dw_time.year/10, dw_time.year%10,
	//	dw_time.month/10, dw_time.month%10, dw_time.day/10, dw_time.day%10, dw_time.hour/10, 
	//	dw_time.hour%10, dw_time.min/10, dw_time.min%10, dw_time.sec/10, dw_time.sec%10);

	sprintf(szTime, "20%02d-%02d-%02d %02d:%02d:%02d", 
		dw_time.year, dw_time.month, dw_time.day, dw_time.hour, dw_time.min, dw_time.sec);

	return TRUE;
}

//-------------------------------------------------------------------------------------
// �� ��-��-�� ��ʽ������ת��ΪtagDWORDTime
//-------------------------------------------------------------------------------------
BOOL DataTime2DwordTime(OUT tagDWORDTime &dw_time, const CHAR szTime[], INT nSzArray)
{
	dw_time.Clear();

	if(nSzArray != X_DATATIME_LEN)
	{
		return FALSE;
	}

	/************************************
	*  2008-09-12 13:21:00
	*  0123456789ABCDEFGHI19
	*************************************/
	
	CHAR p[X_DATATIME_LEN + 1];
	memcpy(p, szTime, X_DATATIME_LEN);
	p[4] = p[7] = p[10] = p[13] = p[16] = p[19] = '\0';

	dw_time.year		= atoi(p + 2);
	dw_time.month	= atoi(p + 5);
	dw_time.day		= atoi(p + 8);
	dw_time.hour		= atoi(p + 11);
	dw_time.min		= atoi(p + 14);
	dw_time.sec		= atoi(p + 17);

	return TRUE;

	//CHAR p[5];
	//CHAR *pCur = szTime;
	//DWORD dwValue = 0;
	//
	//for( INT i = 0; i < 6; i++ )
	//{
	//	dwValue++;
	//	if( dwValue == 1 )
	//	{//��
	//		memcpy(p, szTime, 4);
	//		p[4] = '\0';
	//		dw_time.year = atoi(p) % 100;
	//		pCur += 2;		//�ȱ��������2���ֽ�
	//	}
	//	else if( dwValue == 2)
	//	{//��
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.month = atoi(p);
	//	}
	//	else if( dwValue == 3)
	//	{//��
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.day = atoi(p);
	//	}
	//	else if( dwValue == 4)
	//	{//Сʱ
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.hour = atoi(p);
	//	}
	//	else if( dwValue == 5)
	//	{//��
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.min = atoi(p);
	//	}
	//	else if( dwValue == 6)
	//	{//��
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.sec = atoi(p);
	//	}
	//	else
	//	{
	//		SI_ASSERT(FALSE);
	//	}
	//	pCur += 3;
	//}
}
