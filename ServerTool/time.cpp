#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include <windows.h>
#include "time.h"
#include <stdio.h>

//-------------------------------------------------------------------------------------
// 得到当前时间
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
// 判断某年是否为闰年
//-------------------------------------------------------------------------------------
BOOL IsLeapYear(WORD iYear)
{
	return !(iYear % 4) && (iYear % 100) || !(iYear % 400);
}   

//-------------------------------------------------------------------------------------
// 计算两个日期的时间差，返回秒
//-------------------------------------------------------------------------------------
DWORD CalcTimeDiff(tagDWORDTime destTime, tagDWORDTime srcTime)
{
	if( *(DWORD*)(&destTime) == *(DWORD*)(&srcTime) )
		return 0;

	tagDWORDTime* pDestTime = (tagDWORDTime*)(&destTime);
	tagDWORDTime* pSrcTime = (tagDWORDTime*)(&srcTime);

	// 以dwSrcTime的年份一月一日0时0分0秒为基准,看看过了多少秒时间
	DWORD dwSrcRun =  0;	// src流逝的时间
	DWORD dwDestRun =  0;   // dest流逝的时间

	{
		// 计算src的流逝时间(秒)
		for(INT i = 1; i < (INT)pSrcTime->month; i++)
		{
			// 流逝的月份
			if( i == 2 )
			{
				// 二月,我们看看是不是闰年
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

		// 加上日,小时，分，秒等零碎时间
		dwSrcRun += (pSrcTime->day-1) * 24 * 60 * 60 + \
			pSrcTime->hour * 60 * 60 + \
			pSrcTime->min * 60 + \
			pSrcTime->sec;

	}

	{
		// 计算dest流逝的时间
		for(INT i = pSrcTime->year; i < (INT)pDestTime->year; i++)
		{
			// 流逝的整年数
			if( TRUE == IsLeapYear(i + 2000) )
			{
				dwDestRun += 366 * 24 * 60 * 60;
			}
			else
			{
				dwDestRun += 365 * 24 * 60 * 60;
			}
		}

		//dest以该年一月一日0时0分0秒为基准所流逝的时间
		for(INT i=1; i<(INT)pDestTime->month; i++)
		{
			//流逝的月份
			if( i == 2 )
			{
				//二月,我们看看是不是闰年
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

		//加上日,小时，分，秒等零碎时间
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
// 时间上递增指定秒数
//-----------------------------------------------------------------------------
tagDWORDTime IncreaseTime(tagDWORDTime srcTime, INT nIncrementSecond)
{
	tagDWORDTime* pSrcTime = (tagDWORDTime*)(&srcTime);

	// 以dwSrcTime的年份一月一日0时0分0秒为基准,看看过了多少秒时间
	DWORD dwSrcRun =  0;		// src流逝的时间

	{
		// 计算src的流逝时间(秒)
		for(INT i = 1; i < (INT)pSrcTime->month; i++)
		{
			// 流逝的月份
			if( i == 2 )
			{
				// 二月,我们看看是不是闰年
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

		// 加上日,小时，分，秒等零碎时间
		dwSrcRun += (pSrcTime->day-1) * 24 * 60 * 60 + \
			pSrcTime->hour * 60 * 60 + \
			pSrcTime->min * 60 + \
			pSrcTime->sec;

	}


	// 加上递增的时间
	DWORD dwRunTime = dwSrcRun + nIncrementSecond;

	// 将时间折算
	INT nDays = dwRunTime / (24*60*60);           // 整天数
	INT nSecs  = dwRunTime % (24*60*60);          // 零碎剩余的妙数

	// 初始化结果时间
	tagDWORDTime destTime;
	tagDWORDTime* pDestTime = (tagDWORDTime*)(&destTime);

	// 先计算年
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

	// 再计算月日
	pDestTime->month = 1;
	pDestTime->day = 1;
	for( ;; )
	{
		INT nDaysPerMonth = 0;

		// 计算该月需要的天数
		if( pDestTime->month == 2 )
		{
			// 二月,我们看看是不是闰年
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
			// 该月天数不够
			pDestTime->day += nDays;
			break;
		}

		pDestTime->month++;
		nDays -= nDaysPerMonth;
	}

	// 计算小时分秒
	pDestTime->hour = nSecs / (60*60);
	pDestTime->min = (nSecs / 60) % 60;
	pDestTime->sec = nSecs % 60;

	return destTime;
}

//-----------------------------------------------------------------------------
// 时间上递减指定秒数
//-----------------------------------------------------------------------------
tagDWORDTime DecreaseTime(tagDWORDTime srcTime, INT nDecrementSecond)
{
	tagDWORDTime* pSrcTime = (tagDWORDTime*)(&srcTime);

	// 以dwSrcTime的年份一月一日0时0分0秒为基准,看看过了多少秒时间
	DWORD dwSrcRun =  0;		// src流逝的时间
	{
		// 计算src的流逝时间(秒)
		for(INT i = 1; i < (INT)pSrcTime->month; i++)
		{
			// 流逝的月份
			if( i == 2 )
			{
				// 二月,我们看看是不是闰年
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

		// 加上日,小时，分，秒等零碎时间
		dwSrcRun += (pSrcTime->day-1) * 24 * 60 * 60 + \
			pSrcTime->hour * 60 * 60 + \
			pSrcTime->min * 60 + \
			pSrcTime->sec;

	}

	DWORD dwSrcLeft =  0;		// src当前所剩的时间 
	INT nDaysPerYear = 0;
	if( TRUE == IsLeapYear((WORD)pSrcTime->year + 2000) )
		nDaysPerYear = 366;
	else
		nDaysPerYear = 365;

	dwSrcLeft = nDaysPerYear * 24 * 60 * 60 - dwSrcRun;

	// 加上递减的时间
	DWORD dwDesTime = dwSrcLeft + nDecrementSecond;

	// 将时间折算
	INT nDays = dwDesTime / (24*60*60);           // 整天数
	INT nSecs  = dwDesTime % (24*60*60);          // 零碎剩余的妙数

	// 初始化结果时间
	tagDWORDTime destTime;
	tagDWORDTime* pDestTime = (tagDWORDTime*)(&destTime);

	// 先计算年
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

	// 转换成Des年流逝的时间
	nDays = nDaysPerYear - nDays - 1;
	nSecs = 24 * 60 * 60 - nSecs;

	// 再计算月日
	pDestTime->month = 1;
	pDestTime->day = 1;
	for( ;; )
	{
		INT nDaysPerMonth = 0;

		// 计算该月需要的天数
		if( pDestTime->month == 2 )
		{
			// 二月,我们看看是不是闰年
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
			// 该月天数不够
			pDestTime->day += nDays;
			break;
		}

		pDestTime->month++;
		nDays -= nDaysPerMonth;
	}

	// 计算小时分秒
	pDestTime->hour = nSecs / (60*60);
	pDestTime->min = (nSecs / 60) % 60;
	pDestTime->sec = nSecs % 60;

	return destTime;
}

//---------------------------------------------------------------------------
// 判断某年某月某日是星期几，0为星期日
//---------------------------------------------------------------------------
DWORD WhichWeekday(tagDWORDTime dw_time)
{
	// 首先求出是哪一年
	INT nYear = (INT)dw_time.year + 2000;

	// 然后看当前是这一年的第几天
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

	// 年和日都已经知道，就可以计算了
	// 泰勒公式：x-1+[(x-1)/4]-[(x-1)/100]+[(x-1)/400]+c
	return ( (nYear-1) + (nYear-1)/4 - (nYear-1)/100 + (nYear-1)/400 + nDay ) % 7;
}

//-------------------------------------------------------------------------------------
// 转化成: 年-月-日 如：2008-09-12
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
// 将 年-月-日 格式的数据转换为tagDWORDTime
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
	//	{//年
	//		memcpy(p, szTime, 4);
	//		p[4] = '\0';
	//		dw_time.year = atoi(p) % 100;
	//		pCur += 2;		//比别的情况多出2个字节
	//	}
	//	else if( dwValue == 2)
	//	{//月
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.month = atoi(p);
	//	}
	//	else if( dwValue == 3)
	//	{//日
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.day = atoi(p);
	//	}
	//	else if( dwValue == 4)
	//	{//小时
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.hour = atoi(p);
	//	}
	//	else if( dwValue == 5)
	//	{//分
	//		memcpy(p, pCur, 2);
	//		p[2] = '\0';
	//		dw_time.min = atoi(p);
	//	}
	//	else if( dwValue == 6)
	//	{//秒
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
