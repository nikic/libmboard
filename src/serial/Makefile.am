# $Id: Makefile.am 2925 2012-07-20 14:12:17Z lsc $
# 
# Copyright (c) 2008 STFC Rutherford Appleton Laboratory 
# Author: Lee-Shawn Chin 
# Date  : June 2008

INCLUDEDIR = $(top_srcdir)/include

noinst_LTLIBRARIES  = lib_mb_s.la lib_mb_sd.la

common_sources   = 	addmessage.c \
				    clear.c \
				    create.c \
				    delete.c \
				    env_finalise.c \
				    env_finalised.c \
				    env_init.c \
				    env_initialised.c \
				    filter_assign.c \
				    filter_delete.c \
				    filter_create.c \
				    function_assign.c \
				    function_free.c \
				    function_register.c \
				    iterator_create.c \
				    iterator_createfiltered.c \
				    iterator_createsorted.c \
				    iterator_createfilteredsorted.c \
				    iterator_delete.c \
				    iterator_getmessage.c \
				    iterator_randomise.c \
				    iterator_rewind.c \
				    indexmap_create.c \
				    indexmap_delete.c \
				    indexmap_sync.c \
				    indexmap_memberof.c \
				    indexmap_addentry.c \
				    searchtree_create.c \
				    searchtree_search.c \
				    searchtree_delete.c \
				    setaccessmode.c \
				    setsyncpattern.c \
				    serial_utils.c \
				    synccomplete.c \
				    syncstart.c \
				    synctest.c \
                    $(INCLUDEDIR)/mb_objmap.h \
                    $(INCLUDEDIR)/mb_pooled_list.h \
                    $(INCLUDEDIR)/mb_avltree.h \
                    $(INCLUDEDIR)/mboard.h \
                    $(INCLUDEDIR)/mb_utils.h \
                    $(INCLUDEDIR)/mb_common.h \
                    $(INCLUDEDIR)/mb_settings.h \
                    $(INCLUDEDIR)/mb_serial.h
                    
common_cflags    = -I$(INCLUDEDIR)

lib_mb_s_la_SOURCES   = $(common_sources)     
lib_mb_s_la_CFLAGS    = $(common_cflags) @PRODUCTION_CFLAGS@

lib_mb_sd_la_SOURCES  = $(common_sources)     
lib_mb_sd_la_CFLAGS   = $(common_cflags) @DEBUG_CFLAGS@
