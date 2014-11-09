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
// @Date    2014-05-20												   //
//																	   //
/////////////////////////////////////////////////////////////////////////

#ifndef _SORT_BINARY_TREE_H_
#define _SORT_BINARY_TREE_H_

#include <stdio.h>
#include <malloc.h>

/************************************************************************/
/*
/* @STRUCT: Tree node
/*
/************************************************************************/
template <typename AnyType>
struct TREE_NODE_T
{
	AnyType              * pcData;
	TREE_NODE_T<AnyType> * pstParent;
	TREE_NODE_T<AnyType> * pstLeftChild;
	TREE_NODE_T<AnyType> * pstRightChild;
};

/************************************************************************/
/*
/* @CLASS: Sort binary tree
/*
/************************************************************************/
template <typename AnyType>
class SortBinaryTree
{
public:

/************************************************************************/
/*
/* @Function:   Constructor of SortBinaryTree class
/* @Parameters: 
/*  1. name: cmpFunc, type:pointer function. 
/*  This parameter provides the compare method between AnyType d1 and d2,
/*  and additionally, cmpFunc must return >0, <0 and =0.
/*  Like this:
/*  int cmpFunc(int * d1, int * d2)
/*  {
/*	    if (*d1 > *d2)
/*		    return 1;
/*	    if (*d1 == *d2)
/*		    return 0;
/*	    if (*d1 < *d2)
/*		    return -1;
/*   }
/*
/* @Return:     None.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	SortBinaryTree(int(* cmpFunc)(AnyType * d1, AnyType * d2))
	{
		m_pstRoot         = NULL;
		m_pstSmallestNode = NULL;
		m_cmpFunc         = cmpFunc;
	};

/************************************************************************/
/*
/* @Function:   Get root node of SortBinaryTree
/* @Parameters: None.
/* @Return:     TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	TREE_NODE_T<AnyType> * GetRootNode()
	{
		return m_pstRoot;
	}

/************************************************************************/
/*
/* @Function:   Insert new node into SortBinaryTree
/* @Parameters: 
/*  1. name: pcData, type: AnyType *. It indicates the data you want to 
/*     store in the sort binary tree.
/* @Return:     bool.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	bool InsertTreeNode(AnyType * pcData)
	{
		TREE_NODE_T<AnyType> * pstNode = (TREE_NODE_T<AnyType> *)malloc(sizeof(TREE_NODE_T<AnyType>));
		if (!pstNode)
		{
			return false;
		}

		pstNode->pcData        = pcData;
		pstNode->pstLeftChild  = NULL;
		pstNode->pstRightChild = NULL;
		pstNode->pstParent     = NULL;

		InsertTreeNode(pstNode, m_pstRoot);

		return true;
	};

/************************************************************************/
/*
/* @Function:   Delete smallset node of SortBinaryTree
/* @Parameters: None.
/* @Return:     AnyType *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	AnyType * DeleteSmallestNode()
	{
		GetSmallestNode(m_pstRoot);

		if (NULL == m_pstSmallestNode)
		{
			return NULL;
		}
		AnyType * pcData = m_pstSmallestNode->pcData;
		
		if (m_pstSmallestNode == m_pstRoot)
		{
			m_pstRoot = m_pstRoot->pstRightChild;
		}
		SetPointerThisNull(m_pstSmallestNode);

		free(m_pstSmallestNode);
		m_pstSmallestNode = NULL;
		
		return pcData;
	};

/************************************************************************/
/*
/* @Function:   Get smallest node of SortBinaryTree
/* @Parameters: None.
/* @Return:     AnyType *.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	AnyType * GetSmallestNode()
	{
		GetSmallestNode(m_pstRoot);

		if (NULL == m_pstSmallestNode)
		{
			return NULL;
		}

		return m_pstSmallestNode->pcData;
	};

/************************************************************************/
/*
/* @Function: Search the given data if exist in SortBinaryTree or not
/* @Parameters: 
/*  1. name: pvData, type:void *. This point indicates address of the data
/*     you want to search.
/*  2. name: pstRoot,type:TREE_NODE_T<AnyType> *. This is usually root of 
/*     the SortBinaryTree.
/* @Return: AnyType *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/	
	AnyType * SearchTree(void * pvData, TREE_NODE_T<AnyType> * pstRoot)
	{
		if (NULL == pstRoot || NULL == pvData)
		{
			return NULL;
		}

		TREE_NODE_T<AnyType> * pstTreeNode = SearchNode(pvData, pstRoot);
		if (!pstTreeNode)
		{
			return NULL;
		}

		return pstTreeNode->pcData;
	};
/************************************************************************/
/*
/* @Function:   Delete one node
/* @Parameters: 
/*  1.name:pvData,type: void *,This is the node you want to delete
/* @Return:     bool.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	bool DeleteTreeNode(void * pvData)
	{
		if (NULL == pvData)
		{
			return false;
		}

		TREE_NODE_T<AnyType> * pstTreeNode = SearchNode(pvData, GetRootNode());
		if (!pstTreeNode)
		{
			return false;
		}

		if (pstTreeNode->pstLeftChild != NULL && pstTreeNode->pstRightChild != NULL)
		{
			TREE_NODE_T<AnyType> * pstForeNode = GetForeNodeMiddleOrder(pstTreeNode);
			if (!pstForeNode)
			{
				return false;
			}

			memcpy(pstTreeNode->pcData, pstForeNode->pcData, sizeof(AnyType));

			SetPointerThisNull(pstForeNode);
			free(pstForeNode);
			pstForeNode = NULL;

			return true;
		}


		if (pstTreeNode->pstLeftChild == NULL && pstTreeNode->pstRightChild != NULL)
		{
			if (m_pstRoot == pstTreeNode)
			{
				m_pstRoot = pstTreeNode->pstRightChild;
				pstTreeNode->pstRightChild->pstParent = NULL;
			}
			else
			{
				if (pstTreeNode == pstTreeNode->pstParent->pstLeftChild)
				{
					pstTreeNode->pstParent->pstLeftChild = pstTreeNode->pstRightChild;
				}
				if (pstTreeNode == pstTreeNode->pstParent->pstRightChild)
				{
					pstTreeNode->pstParent->pstRightChild = pstTreeNode->pstRightChild;
				}
			}
		}
		if (pstTreeNode->pstRightChild == NULL && pstTreeNode->pstLeftChild != NULL)
		{
			if (m_pstRoot == pstTreeNode)
			{
				m_pstRoot = pstTreeNode->pstLeftChild;
				pstTreeNode->pstLeftChild->pstParent = NULL;
			}
			else
			{
				if (pstTreeNode == pstTreeNode->pstParent->pstLeftChild)
				{
					pstTreeNode->pstParent->pstLeftChild = pstTreeNode->pstLeftChild;
				}
				if (pstTreeNode == pstTreeNode->pstParent->pstRightChild)
				{
					pstTreeNode->pstParent->pstRightChild = pstTreeNode->pstLeftChild;
				}
			}

		}

		SetPointerThisNull(pstTreeNode);
		free(pstTreeNode);
		pstTreeNode = NULL;
		return true;

	};

/************************************************************************/
/*
/* @Function:   Deconstructor of SortBinaryTree
/* @Parameters: None.
/* @Return:     TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	~SortBinaryTree()
	{
		GetNodeByLast(m_pstRoot);
	};

private:
/************************************************************************/
/*
/* @Function:   Private function is called by InsertTreeNode
/* @Parameters: 
/*  1.name:pstNode, type:TREE_NODE_T<AnyType> *. New node you want to insert.
/*  2.name:pstTempRoot, type:TREE_NODE_T<AnyType> *.Root node of this tree. 
/* @Return: TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	bool InsertTreeNode(TREE_NODE_T<AnyType> * pstNode, TREE_NODE_T<AnyType> * pstTempRoot)
	{
		if (!pstNode)
		{
			return false;
		}

		if (NULL != pstTempRoot)
		{
			if (m_cmpFunc(pstNode->pcData ,pstTempRoot->pcData) > 0)
			{
				if (NULL != pstTempRoot->pstRightChild)
				{
					return InsertTreeNode(pstNode, pstTempRoot->pstRightChild);
				}
				else
				{
					pstTempRoot->pstRightChild = pstNode;
					pstNode->pstParent = pstTempRoot;
				}
			}
			if (m_cmpFunc(pstNode->pcData ,pstTempRoot->pcData) < 0)
			{
				if (NULL != pstTempRoot->pstLeftChild)
				{
					return InsertTreeNode(pstNode, pstTempRoot->pstLeftChild);
				}
				else
				{
					pstTempRoot->pstLeftChild = pstNode;
					pstNode->pstParent = pstTempRoot;
				}
			}
			if (m_cmpFunc(pstNode->pcData ,pstTempRoot->pcData) == 0)
			{
				return false;
			}
		}
		else
		{
			m_pstRoot = pstNode;
		}
		return true;
	};

/************************************************************************/
/*
/* @Function: Get all nodes of SortBinaryTree by last order. It used in
/*            Deconstructor function.
/* @Parameters: None.
/* @Return:     TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	void GetNodeByLast(TREE_NODE_T<AnyType> * pstRoot)
	{
		if(NULL == pstRoot)
		{
			return;
		}
		
		if(NULL != pstRoot->pstLeftChild)
		{
			GetNodeByLast(pstRoot->pstLeftChild);
		}
		if(NULL != pstRoot->pstRightChild)
		{
			GetNodeByLast(pstRoot->pstRightChild);
		}

		SetPointerThisNull(pstRoot);

		free(pstRoot);
		pstRoot = NULL;
	};

/************************************************************************/
/*
/* @Function:   Get the smallset node of SortBinaryTree by middle order
/* @Parameters: 
/*  1.name:pstRoot,type: TREE_NODE_T<AnyType> *,
/* @Return:     TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	TREE_NODE_T<AnyType> *  GetSmallestNode(TREE_NODE_T<AnyType> * pstRoot)
	{
		if(NULL == pstRoot)
		{
			return NULL;
		}
		
		if(NULL != pstRoot->pstLeftChild)
		{
			return GetSmallestNode(pstRoot->pstLeftChild);
		}

		m_pstSmallestNode = pstRoot;

		return m_pstSmallestNode;
	};

/************************************************************************/
/*
/* @Function:   Get the fore node of this given node by middle order
/* @Parameters: 
/*  1.name:pstTreeNode,type: TREE_NODE_T<AnyType> *,
/* @Return:     TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	TREE_NODE_T<AnyType> * GetForeNodeMiddleOrder(TREE_NODE_T<AnyType> * pstTreeNode)
	{
		if (!pstTreeNode)
		{
			return NULL;
		}

		TREE_NODE_T<AnyType> * pstForeNode = NULL;

		if (pstTreeNode->pstLeftChild != NULL)
		{
			pstForeNode = pstTreeNode->pstLeftChild;
		}
		else
		{
			pstForeNode = pstForeNode->pstParent;
			return pstForeNode;
		}
		while(pstForeNode->pstRightChild != NULL)
		{
			pstForeNode = pstForeNode->pstRightChild;
		}

		return pstForeNode;
	};

/************************************************************************/
/*
/* @Function:   When delete one node, set releate pointer NULL
/* @Parameters: 
/*  1.name:pstTreeNode,type: TREE_NODE_T<AnyType> *,
/* @Return:     bool.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	bool SetPointerThisNull(TREE_NODE_T<AnyType> * pstTreeNode)
	{
		if (!pstTreeNode)
		{
			return false;
		}

		if (pstTreeNode->pstParent != NULL)
		{
			if (pstTreeNode == pstTreeNode->pstParent->pstLeftChild)
			{
				pstTreeNode->pstParent->pstLeftChild = NULL;
			}
			if (pstTreeNode == pstTreeNode->pstParent->pstRightChild)
			{
				pstTreeNode->pstParent->pstRightChild = NULL;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

/************************************************************************/
/*
/* @Function: Get all nodes of SortBinaryTree by last order. It used in
/*            Deconstructor function.
/* @Parameters: None.
/* @Return:     TREE_NODE_T<AnyType> *.
/*-----------------------------------------------------------------------
/* @Author:      Duan Kai
/* @Create Date: 2014-05-20
/* @Modify Date:
/*
/************************************************************************/
	TREE_NODE_T<AnyType> * SearchNode(void * pvData, TREE_NODE_T<AnyType> * pstRoot)
	{
		if (NULL == pstRoot || NULL == pvData)
		{
			return NULL;
		}

		if (m_cmpFunc(pstRoot->pcData ,(AnyType *)pvData) == 0)
		{
			return pstRoot;
		}
		else if (m_cmpFunc((AnyType *)pvData, pstRoot->pcData) < 0)
		{
			return SearchNode(pvData, pstRoot->pstLeftChild);
		}
		else if (m_cmpFunc((AnyType *)pvData, pstRoot->pcData) > 0)
		{
			return SearchNode(pvData, pstRoot->pstRightChild);
		}
		else
		{
			return NULL;
		}
	};

private:
	TREE_NODE_T<AnyType> * m_pstRoot;
	TREE_NODE_T<AnyType> * m_pstSmallestNode;
	int                 (* m_cmpFunc)(AnyType * d1, AnyType * d2);//if d1>d2, return value > 0;d1==d2, return 0; d1<d2,return <0;
};

#endif
