/* $Id: unmap.c 2925 2012-07-20 14:12:17Z lsc $ */
/*!
 * \file unmap.c
 * \code
 *      Author: Lee-Shawn Chin 
 *      Date  : Feb 2008 
 *      Copyright (c) 2008 STFC Rutherford Appleton Laboratory
 * \endcode
 * 
 * \brief wrapper routines for mapping Handles to object pointers
 * 
 */
#include "mb_utils.h"

/*! 
 * \brief wrapper routine for mapping MessageBoard handle to object reference 
 * \param[in] mb MessageBoard handle
 * \return pointer to MessageBoard object (\c NULL if handle invalid)
 * 
 * Performs the necessary assertions (if compiled in debug mode) and obtains
 * the associated board reference from the appropriate ObjectMap.
 */
void * MBI_getMBoardRef_withasserts(MBt_Board mb) {
    
    /* make sure mboard object map valid */
    assert(MBI_OM_mboard != NULL);
    assert((int)MBI_OM_mboard->type == OM_TYPE_MBOARD);
    
    /* return object mapped to mb handle */
    return MBI_objmap_getobj(MBI_OM_mboard, (OM_key_t)mb);
}


/*! 
 * \brief wrapper routine for mapping Iterator handle to object reference 
 * \param[in] iter Iterator handle
 * \return pointer to Iterator object (\c NULL if handle invalid)
 * 
 * Performs the necessary assertions (if compiled in debug mode) and obtains
 * the associated Iterator reference from the appropriate ObjectMap.
 */
void * MBI_getIteratorRef_withasserts(MBt_Iterator iter) {
    
    /* make sure mboard object map valid */
    assert(MBI_OM_iterator != NULL);
    assert((int)MBI_OM_iterator->type == OM_TYPE_ITERATOR);
    
    /* return object mapped to mb handle */
    return MBI_objmap_getobj(MBI_OM_iterator, (OM_key_t)iter);
}


/*! 
 * \brief wrapper routine for mapping Filter handle to object reference 
 * \param[in] ft Filter handle
 * \return pointer to filter function wrapper (\c NULL if handle invalid)
 * 
 * Performs the necessary assertions (if compiled in debug mode) and obtains
 * the associated Filter function reference from the appropriate ObjectMap.
 */
void * MBI_getFilterRef_withasserts(MBt_Filter ft) {
    
    /* make sure function object map valid */
    assert(MBI_OM_filter != NULL);
    assert((int)MBI_OM_filter->type == OM_TYPE_FILTER);
    
    /* return object mapped to handle */
    return MBI_objmap_getobj(MBI_OM_filter, (OM_key_t)ft);
}

/*! 
 * \brief wrapper routine for mapping Index Map handle to object reference 
 * \param[in] ih Index Map handle
 * \return pointer to Index Map object (\c NULL if handle invalid)
 * 
 * Performs the necessary assertions (if compiled in debug mode) and obtains
 * the associated Map object reference from the appropriate ObjectMap.
 */
void * MBI_getIndexMapRef_withasserts(MBt_IndexMap ih) {
    
    /* make sure indexmap object map valid */
    assert(MBI_OM_indexmap != NULL);
    assert((int)MBI_OM_indexmap->type == OM_TYPE_INDEXMAP);
    
    /* return object mapped to handle */
    return MBI_objmap_getobj(MBI_OM_indexmap, (OM_key_t)ih);
}

/*!
 * \brief wrapper routine for mapping SearchTree handle to object reference
 * \param[in] sh SearchTree handle
 * \return pointer to SearchTree object (\c NULL if handle invalid)
 *
 * Performs the necessary assertions (if compiled in debug mode) and obtains
 * the associated Map object reference from the appropriate ObjectMap.
 */
void * MBI_getSearchTreeRef_withasserts(MBt_SearchTree sh) {

    /* make sure searchtree object map valid */
    assert(MBI_OM_searchtree != NULL);
    assert((int)MBI_OM_searchtree->type == OM_TYPE_SEARCHTREE);

    /* return object mapped to handle */
    return MBI_objmap_getobj(MBI_OM_searchtree, (OM_key_t)sh);
}

