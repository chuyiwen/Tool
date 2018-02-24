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
 *	@file		Singleton.h
 *	@author		zhaopeng
 *	@date		2010/12/01
 *	@version	
 *	@brief		����ģ�����
 */
#pragma once

namespace Tang {
/** �ϲ��ֹ����Ƶ���ʵ����������
*/
template<typename T>
struct NullInstancePolicy
{
    static T* GetInstance() { return NULL; }    
};

/** ʹ���Զ���̬�������󵥼�ʵ�� 
    �ڵ�һ�ε���ʵ������ʱ����ʵ��
*/
template<typename T>
struct StaticInstancePolicy
{
    static T* GetInstance() { static T s_ins; return &s_ins; }
};

/** ��������
*/
template<typename T, template<typename> class InstancePolicy = StaticInstancePolicy>
class Singleton
{
public:
    Singleton()
    {
        SI_ASSERT( !ms_pSingleton );
        ms_pSingleton = static_cast<T*>(this);
    }

    ~Singleton()
    {
        SI_ASSERT( ms_pSingleton );
        ms_pSingleton = NULL;
    }
    
    static T& GetSingleton()    {  TryGetInstance(); return *ms_pSingleton; }
    static T* GetSingletonPtr() {  TryGetInstance(); return  ms_pSingleton; }
private:
    static void TryGetInstance() { if ( !ms_pSingleton ) ms_pSingleton = InstancePolicy<T>::GetInstance(); }
    static T* ms_pSingleton;
};

template<typename T, template<typename> class InstancePolicy> 
T* Singleton<T,InstancePolicy>::ms_pSingleton;

}; //namespace Tang