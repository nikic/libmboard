/* $Id: mb_pooled_list.h 2925 2012-07-20 14:12:17Z lsc $ */
/*!
 * \file mb_pooled_list.h
 * \code
 *      Author: Lee-Shawn Chin 
 *      Date  : Feb 2008 
 *      Copyright (c) 2008 STFC Rutherford Appleton Laboratory
 * \endcode
 * 
 * \brief Header file for Pooled List
 * 
 */
#ifndef MB_POOLED_LIST_H_
#define MB_POOLED_LIST_H_

/*! \defgroup PLIST Utility: Pooled List 
 * 
 * A linked-list implementation which allocates memory in large chunks. 
 * Nodes are to be added/removed from the list using the given routines,
 * and can be traversed either as a linked-list, or by referenced by index.
 * 
 * This implementation is designed primarily for the FLAME framework, 
 * as such, only a subset of linked-list operations are implemented.
 * For now, access routines are limited to appending nodes to the list,
 * and several approaches to clearing the list:
 * 
 *  -# pl_recycle() : Empties the list, but does not deallocate any memory.
 *                   Memory will be reused when the next set of data is 
 *                   added to the list. 
 *  -# pl_reset()   : Empties the list, and deallocates most of the memory
 *                   except for the first block.
 *  -# pl_delete()  : Deletes the object, and deallocates all used memory.
 *                   List object will have to be recreated before being
 *                   reused.
 * 
 * Within each memory block, each user data is prepended with a header of
 * type pl_address_node. The header will store a 'next' pointer to the subsequent
 * data header, as well as an 'addr' pointer to the user data it is associated
 * with.
 * 
 * \note All pl_*() routines return an Integer return code of PL_SUCCESS or PL_ERR_*.
 * 
 * \todo Unit test for pl_randomise()
 * 
 * \warning Pooled lists are not inherently thread-safe. It is up the the user to 
 * include the necessary lockings during read/write access when simultaneous access
 * by multiple threads are possible.
 * 
 * Example usage:
 * \code
 *   // linked list node datatype
 *   struct mynode {
 *      int value;
 *      double trouble;
 *   };
 *  
 * 
 *   int i, rc;
 *   pooled_list *pl;
 *   pl_iterator *pl_itr;
 *   mynode *node_new; 
 *   mynode *obj;
 * 
 *   // Create a pooled list with 50 nodes per memory block
 *   pl_create(&pl, sizeof(mynode), 50);
 * 
 *   // populate list
 *   for (i = 0; i < 100; i++)
 *   {
 *       rc = pl_newnode(pl, &node_new);
 *       node_new->value = i;
 *       node_new->trouble = i * 0.23;
 *   }
 * 
 *   // traverse data as linked list
 *   
 *   for (pl_itr = PL_ITERATOR(pl); pl_itr; pl_itr = pl_itr->next)
 *   {
 *       obj = (mynode *)PL_NODEDATA(pl_itr);
 *       printf("Node value %d\n", obj->value);
 *   }
 * 
 *   // Get data by index;
 *   pl_getnode(pl, 10, (void **)&obj); // get first node
 *   if (obj != NULL) printf("Node 10 has value %d\n", obj->value);
 * 
 *   // Delete pooled list
 *   pl_delete(&pl);
 * \endcode
 * 
 * @{
 * */

#ifdef HAVE_CONFIG_H
#include "mb_config.h"
#endif

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*! \brief Return Code: Success */
#define PL_SUCCESS     0 
/*! \brief Return Code: Fatal Error */
#define PL_ERR_FATAL   1 
/*! \brief Return Code: Memory Allocation Error */
#define PL_ERR_MALLOC  2 
/*! \brief Return Code: Invalid Input */
#define PL_ERR_INVALID 3 /* Invalid input */

/* ----- Data Structures ----- */
/*! \brief internal list node for storing memory block addresses 
 * 
 * Used for storing address list (\c addr_list) in pooled_list as 
 * well as for indexing data within memblock
 */
struct pl_address_node {
    /*!\brief memory address */
    void *addr; 
    /*!\brief pointer to next node in list */
    struct pl_address_node *next;
};
/*!\brief shorthand for struct pl_address_node */
typedef struct pl_address_node pl_address_node;

/* \brief datatype used as handle for traversing linked list */
typedef pl_address_node pl_iterator;


/*! \brief Pooled List object */
typedef struct {
    
    /* blocksize = (elem_size + PL_ADDRNODE_SIZE )* elem_count */
    
    /*! \brief Size of each list node */
    unsigned int elem_size;   
    /*! \brief Number of nodes per memory block */
    unsigned int elem_count;  
    
    /* memory usage counters */
    
    /*! \brief free nodes within allocated memory */
    unsigned int count_free;
    /*! \brief total nodes allocated memory can accommodate */
    unsigned int count_total; 
    /*! \brief used nodes within allocated memory */
    unsigned int count_current;
    
    
    /* references to specific data blocks */
    
    /*! \brief pointer to head node */
    void * head;
    /*! \brief pointer to last node in list */
    void * tail;
    /*! \brief pointer to next available memory */
    void * next_free;
    
    
    /* list referencing allocated memory blocks */
    
    /*! \brief list storing allocated memory blocks  */
    pl_address_node *addr_list; 
    /*! \brief pointer to current active memory block */
    pl_address_node *active_memblock; 
    
} pooled_list;


/* ----- Macros ----- */
/*! \brief Address node size used for calculating total block size */
#define PL_ADDRNODE_SIZE sizeof(pl_address_node)

/*! \brief macro retrieve data block address from data header */
#define PL_NODEDATA(node) (((pl_address_node *)node)->addr)

/*! \brief macro retrieve first data header in pooled list */
#define PL_ITERATOR(obj) ((pl_address_node *)obj->head)


/* ----- Function Prototypes ----- */
/* .... see src/utils/pooled_list.c .... */
int pl_create(pooled_list **pl_ptr_loc, size_t elem_size, int pool_size);
int pl_delete(pooled_list **pl_ptr_loc);

int pl_newnode(pooled_list *pl, void **ptr_new);
int pl_recycle(pooled_list *pl);
int pl_reset(pooled_list *pl);

int pl_getnode_container(pooled_list *pl, int index,  pl_address_node **ptr);
int pl_getnode(pooled_list *pl, int index, void **ptr);
int pl_randomise(pooled_list *pl);

/*! @} */
#endif /*MB_POOLED_LIST_H_*/
