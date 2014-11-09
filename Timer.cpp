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
#include "Timer.h"

/************************************************************************/
/*
/* @Description: Initialize static variable of Timer
/*
/************************************************************************/
SortBinaryTree<TIMER_T> * Timer::m_pstSBT = new SortBinaryTree<TIMER_T>(Timer::CmpFunc);

int Timer::m_uiTimerID = 0;

/************************************************************************/
/*
/* @Function:   Constructor of Timer
/* @Parameters: None.
/* @Return:     None.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
Timer::Timer()
{
	m_hScan = CREATE_THREAD(&nPid, ScanTimerQueue, NULL);
	if (m_hScan == NULL || m_pstSBT == NULL)
	{
		GetLastError();
		m_bInit = INVILID_TIMER_INSTANCE;
	}
	else
	{
		m_bInit = VILID_TIMER_INSTANCE;
	}
}

/************************************************************************/
/*
/* @Function:   The compare function of Timer
/* @Parameters: 
/*  1.name:t1, type:TIMER_T.
/*  2.name:t2, type:TIMER_T
/* @Return:     int.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
int Timer::CmpFunc(TIMER_T * t1, TIMER_T * t2)
{
	if (t1->lMilliSecond > t2->lMilliSecond)
	{
		return 1;
	}
	else if (t1->lMilliSecond < t2->lMilliSecond)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/************************************************************************/
/*
/* @Function:   SetTimer
/* @Parameters: 
/*  1.name:lMilliSecond, type:long. The milliSecond of the Timer
/*  2.name:_lpProcessFunction, type:void  (*_lpProcessFunction)(void * pvData).
/*    This function will be called when timer is triggered.
/*  3.name:pvData, type: void *. The parameter of timer function.
/* @Return: int. When a new timer is created success, return its id, 
/*               otherwis, return INVILID_TIMER_ID;
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
int Timer::SetTimer(
		long     lMilliSecond,   //the millisecond of timer
		void  (*_lpProcessFunction)(void * pvData),
		void   * pvData
		)
{
	TIMER_T * stTimerInstc = (TIMER_T *)malloc(sizeof(TIMER_T));

	if (!stTimerInstc)
	{
		return INVILID_TIMER_ID;
	}

	stTimerInstc->lpProcessFunction = _lpProcessFunction;
	 /*The GetTickCount() function will be zero when your system run more than 49.7 days.*/
	stTimerInstc->lMilliSecond = GetTickCount() + lMilliSecond;
	stTimerInstc->uiTimerID = ++m_uiTimerID;
	stTimerInstc->pvData = pvData;

	if (m_pstSBT->InsertTreeNode(stTimerInstc))
	{
		m_map.insert(std::pair<int,TIMER_T *>(m_uiTimerID, stTimerInstc));
		return m_uiTimerID;
	}
	else
	{
		free(stTimerInstc);
		stTimerInstc = NULL;
		return INVILID_TIMER_ID;
	}
}

/************************************************************************/
/*
/* @Function:   Cancle a timer through timer id.
/* @Parameters: 
/*  1.name:ulTimerID, type:int.
/* @Return:     bool.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
bool Timer::CancleTimer(int ulTimerID)
{
	std::map<int, TIMER_T *>::iterator itor_map;
	itor_map = m_map.find(ulTimerID);

	if (itor_map == m_map.end())
	{
		return false;
	}

	if (m_pstSBT->DeleteTreeNode((void *)itor_map->second))
	{
		free(itor_map->second);
		itor_map->second = NULL;

		m_map.erase(itor_map);
		return true;
	}
	else
	{
		return false;	
	}
	
}

/************************************************************************/
/*
/* @Function:   Scan Timer Queue, this will search the sort binary tree.
/* @Parameters: 
/*  1.name:lp, type:LPVOID.
/* @Return:     DWORD WINAPI.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
DWORD WINAPI Timer::ScanTimerQueue(LPVOID lp)
{
	LONG ulCurrTime;
	while(1){

		ulCurrTime = GetTickCount();
		if (NULL != m_pstSBT->GetSmallestNode() && 
			m_pstSBT->GetSmallestNode()->lMilliSecond <= ulCurrTime)
		{

			TIMER_T * pstTimer = m_pstSBT->DeleteSmallestNode();

			if (NULL != pstTimer)
			{
				pstTimer->lpProcessFunction(pstTimer->pvData);
				
				free(pstTimer);
				pstTimer = NULL;
			}

		}		
		SLEEP(100);
	}
	return 0;
}

/************************************************************************/
/*
/* @Function:   Get the instance status of Class Timer
/* @Parameters: None.
/* @Return:     bool.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
bool Timer::GetInstanceStatus()
{
	return m_bInit;
}

/************************************************************************/
/*
/* @Function:   Deconstructor function of Timer
/* @Parameters: None.
/* @Return:     None.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-06-18
/* @Modify Date:
/*
/************************************************************************/
Timer::~Timer()
{
	delete m_pstSBT;
	m_map.clear();
	CloseHandle(m_hScan);
}
