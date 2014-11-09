/////////////////////////////////////////////////////////////////////////
//																	   //
//																	   //
// COPYRIGHT NOTICE                                                    //
// Copyright (c) 2014                                                  //
//                                                                     //
// @File Name:     SortBinaryTree.h                                    //
// @File Function: The header of sort binary tree	                   //
//																	   //
// @Version 1.0 													   //
// @Author  Duan Kai            									   //
// @Date    2014-06-18												   //
//																	   //
/////////////////////////////////////////////////////////////////////////
#ifndef _TIMER_H_
#define _TIMER_H_



#include <map>
#include "SortBinaryTree.h"

#include <WinSock2.h>
#pragma comment(lib,"ws2_32")
/*WINDOWS*/
#define SLEEP(millSecond)                   Sleep          (millSecond) 
#define CREATE_THREAD(nPid, pFunc, pParmts) CreateThread   (NULL, 0, pFunc, pParmts, 0, NULL)

#define INVILID_TIMER_ID       0
#define INVILID_TIMER_INSTANCE 0
#define VILID_TIMER_INSTANCE   1

#pragma pack(push, 4)
/************************************************************************/
/*
/* @STRUCT: TIMER_T
/*
/************************************************************************/
typedef struct TIMER_T
{
	int              uiTimerID;
	long             lMilliSecond;
	void	      (* lpProcessFunction)(void * pvData);
	void           * pvData;
} TIMER_T;

/************************************************************************/
/*
/* @CLASS: Timer
/*
/************************************************************************/
class Timer
{
public:
	Timer();
	int SetTimer(
		long     lMilliSecond,   //the millisecond of timer
		void  (*_lpProcessFunction)(void * pvData),
		void   * pvData
	);
	bool CancleTimer(int ulTimerID);
	bool GetInstanceStatus();
	~Timer();

private:
	static DWORD WINAPI ScanTimerQueue(LPVOID lp);
	static int   CmpFunc(TIMER_T * t1, TIMER_T * t2);

private:
	static SortBinaryTree<TIMER_T> * m_pstSBT;
	static int                       m_uiTimerID;
	bool                             m_bInit;
	HANDLE                           m_hScan;
	std::map<int, TIMER_T *>         m_map;    
};

#pragma pack(pop)
#endif
