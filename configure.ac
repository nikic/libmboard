# ===========================================================================
# Copyright (c) 2007-2013 STFC Rutherford Appleton Laboratory 
# Author: Lee-Shawn Chin 
# ===========================================================================
# 
# Process this file with autoconf to produce a configure script.

# Note: first 3 segments of version number must only contain digits!!
AC_INIT(libmboard, 0.3.1, shawn.chin@_NOSPAM_stfc.ac.uk)
AM_INIT_AUTOMAKE

#AM_MAINTAINER_MODE

AC_PREREQ(2.59)
AC_REVISION($Revision: 3117 $)
AC_COPYRIGHT([Copyright (c) 2007-2013 STFC Rutherford Appleton Laboratory])

AC_CONFIG_SRCDIR([src/serial/env_init.c])
AC_CONFIG_HEADER([include/mb_config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET
AC_DISABLE_SHARED

# initialise CFLAGS so AC_PROG_LIBTOOL does not add -g -O2
CFLAGS="" 
AC_PROG_LIBTOOL

# Checks for $CC -c -o. Needed to allow pre-target flags
AM_PROG_CC_C_O

# GCC CFLAGS for different warning levels.
GCC_CFLAGS_LVL1="-Wall -pedantic"
GCC_CFLAGS_LVL2="-Wextra -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith"
GCC_CFLAGS_LVL3="-Wreturn-type -Wswitch -Wshadow -Wcast-align -Wunused"
GCC_CFLAGS_LVL4="-Wwrite-strings -Wcast-qual "
GCC_CFLAGS_SHOWSTOPPER="-Werror" # OTT
# removed: -Wunreachable-code (too many false positives)

# Default CFLAGS
# Need extra checks to set this depending on compiler
case "$CC" in
	gcc*)
		CFLAGS="${CFLAGS} -fno-common -std=c99"
		CFLAGS="${CFLAGS} ${GCC_CFLAGS_LVL1}"
		CFLAGS="${CFLAGS} ${GCC_CFLAGS_LVL2}"
		CFLAGS="${CFLAGS} ${GCC_CFLAGS_LVL3}"
		#CFLAGS="${CFLAGS} ${GCC_CFLAGS_LVL4}"
		#CFLAGS="${CFLAGS} ${GCC_CFLAGS_SHOWSTOPPER}"
		;;
	pgcc*)
		CFLAGS="${CFLAGS} -c9x -Minform=warn"
		;;
	icc*)
		CFLAGS="${CFLAGS} -std=c99 -Wall"
		;;
	xlc*)
		CFLAGS="${CFLAGS} -qlanglvl=stdc99 -qinfo=all -qflag=w:u -qcheck=all"
		;;
	*)
		CFLAGS="${CFLAGS}"
		;;
esac

PRODUCTION_CFLAGS="-DNDEBUG -O3"
DEBUG_CFLAGS="-g -D_EXTRA_CHECKS"

AC_SUBST(PRODUCTION_CFLAGS)
AC_SUBST(DEBUG_CFLAGS)

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h stddef.h unistd.h float.h],[],
				 [AC_MSG_ERROR(That header file is required)])

# Check requirements for parallel implementation
MBOARD_CHECK_PARALLEL

# Check requirements for testing
MBOARD_CHECK_TESTING

# Check requirements for performing coverage analysis
MBOARD_CHECK_COVERAGE

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
#AC_FUNC_MALLOC
#AC_CHECK_FUNCS([memset],[],[AC_MSG_ERROR(memset() is required)])
#AC_CHECK_FUNCS([memcpy],[],[AC_MSG_ERROR(memcpy() is required)])
#AC_CHECK_FUNCS([sqrt],[],[AC_MSG_ERROR(sqrt() is required)])
#AC_CHECK_FUNCS([floor],[],[AC_MSG_ERROR(floor() is required)])

# Check support for variadic macros
LSC_C_C99_VARIADIC_MACROS
LSC_C_GNU_VARIADIC_MACROS

# check for __func__ support
AC_C_VAR_FUNC

# Allow users to enable instrumentation of memory usage
MEMLOG_CFLAGS="-D_LOG_MEMORY_USAGE"
AC_ARG_ENABLE([memlog], 
              [AC_HELP_STRING([--enable-memlog],
                              [Enable instrumentation of memory usage])],
              [want_memlog=yes],
              [want_memlog=no]
             )
if test "x${want_memlog}" = xyes;
then
	WANT_MEMLOG=1
	
	AC_CHECK_HEADERS([argp.h],[],
				 [AC_MSG_ERROR([
** argp.h is needed by mboard-parse-memlogdb.c (included with --enable-memlog)
   If you are using a non-glibc system, please install argp-standalone
   before proceeding.			 
				 ])])
				 
	PRODUCTION_CFLAGS="${MEMLOG_CFLAGS} ${PRODUCTION_CFLAGS}"
	DEBUG_CFLAGS="${MEMLOG_CFLAGS} ${DEBUG_CFLAGS}"
	AM_CONDITIONAL([COMPILE_SQLITE], [true])
    AM_CONDITIONAL([COMPILE_MEMLOG], [true])
else
	WANT_MEMLOG=0
	AM_CONDITIONAL([COMPILE_SQLITE], [false])
	AM_CONDITIONAL([COMPILE_MEMLOG], [false])
fi
AC_SUBST(WANT_MEMLOG)
AC_SUBST(MEMLOG_CFLAGS)

# Enable developer debug code
DEVELOPER_CFLAGS="-D_UNSAFE_CHECKS"
AC_ARG_ENABLE([unsafe-checks], 
              [AC_HELP_STRING([--enable-unsafe-checks],
                              [Enable run-time checks that are more thorough but may fail if MPI is not thread-compliant])],
              [want_unsafe_checks=yes],
              [want_unsafe_checks=no]
             )
if test "x${want_unsafe_checks}" = xyes;
then
	DEBUG_CFLAGS="${DEBUG_CFLAGS} ${DEVELOPER_CFLAGS}"
fi

# Allow users to enable verbose printing of warning/debug messages
VERBOSE_CFLAGS="-D_EXTRA_INFO"
AC_ARG_ENABLE([verbose], 
              [AC_HELP_STRING([--enable-verbose],
                              [Print warning and info messages (in debug version)])],
              [want_verbose=yes],
              [want_verbose=no]
             )
if test "x${want_verbose}" = xyes;
then
	DEBUG_CFLAGS="${DEBUG_CFLAGS} ${VERBOSE_CFLAGS}"
fi

# Allow users to enable verbose printing of warning/debug messages
WARNING_CFLAGS="-D_PRINT_WARNINGS"
AC_ARG_ENABLE([warnings], 
              [AC_HELP_STRING([--enable-warnings],
                              [Print warning messages (in debug version)])],
              [want_warnings=yes],
              [want_warnings=no]
             )
if test "x${want_warnings}" = xyes || test "x${want_verbose}" = xyes;
then
	DEBUG_CFLAGS="${DEBUG_CFLAGS} ${WARNING_CFLAGS}"
fi

# provide some extra info to *.in files
MB_CONFIG_ARGS=$ac_configure_args
AC_SUBST(MB_CONFIG_ARGS)
AC_DEFINE_UNQUOTED(INFO_CONFIG_ARGS, "${MB_CONFIG_ARGS}", [Options used to configure package])

MB_CONFIG_DATE=`date`
AC_SUBST(MB_CONFIG_DATE)
AC_DEFINE_UNQUOTED(INFO_CONFIG_DATE, "${MB_CONFIG_DATE}", [Date package was configure])

MB_SRC_DIR=`pwd`
AC_SUBST(MB_SRC_DIR)

AC_DEFINE_DIR([MB_INSTALL_BINDIR], [bindir], [Install dir for binaries])
AC_DEFINE_DIR([MB_INSTALL_LIBDIR], [libdir], [Install dir for libraries])
AC_DEFINE_DIR([MB_INSTALL_INCLUDEDIR], [includedir], [Install dir for include files])

# Suppress repeated spaces in params (merely for aesthetic reasons)
LSC_NOREPEAT_SPACES([CFLAGS])
LSC_NOREPEAT_SPACES([LDFLAGSS])
LSC_NOREPEAT_SPACES([LIBS])
LSC_NOREPEAT_SPACES([PRODUCTION_CFLAGS])
LSC_NOREPEAT_SPACES([DEBUG_CFLAGS])
LSC_NOREPEAT_SPACES([MB_PARALLEL_CFLAGS])
LSC_NOREPEAT_SPACES([MB_PARALLEL_LDFLAGS])
LSC_NOREPEAT_SPACES([MB_PARALLEL_LIBS])
LSC_NOREPEAT_SPACES([THREADS_CFLAGS])
LSC_NOREPEAT_SPACES([THREADS_LDFLAGS])
LSC_NOREPEAT_SPACES([THREADS_LIBS])
LSC_NOREPEAT_SPACES([MPICFLAGS])
LSC_NOREPEAT_SPACES([MPILDFLAGS])
LSC_NOREPEAT_SPACES([MPILIBS])
LSC_NOREPEAT_SPACES([MEMLOG_CFLAGS])

# files to create
AC_CONFIG_FILES([Makefile])

AC_OUTPUT([
README
Doxyfile_user
Doxyfile_developer_serial
Doxyfile_developer_parallel
src/utils/Makefile
src/serial/Makefile
src/parallel/Makefile
src/progs/Makefile
src/progs/mboard-config
src/progs/mboard-check-minversion
src/progs/compile_coverage.sh
tests/Makefile
tests/testsuite_commqueue/Makefile
tests/testsuite_commutils/Makefile
tests/testsuite_commroutines_old/Makefile
tests/testsuite_commroutines_handshake/Makefile
tests/testsuite_mb_parallel/Makefile
tests/testsuite_mb_serial/Makefile
tests/testsuite_objmap/Makefile
tests/testsuite_tag_table/Makefile
tests/testsuite_pooled_list/Makefile
tests/testsuite_syncqueue/Makefile
tests/testsuite_avltree/Makefile
tests/testsuite_kdtree/Makefile
tests/testsuite_string_map/Makefile
])dnl

# Some external header files (such as pthread.h for pthreads-win32) may look
# for config.h if -DHAVE_CONFIG_H is defined. 
# Alias include/mb_config.h to include/config.h so compilation is not affected
# (note, only mb_config.h is installed during "make install")
(cd include && ln -sf mb_config.h config.h ) 2>/dev/null

echo ""
echo "------------------- Configuration successful --------------------------"
echo ""
echo "Compile parallel libs : $want_parallel"
if test x${want_parallel} = xyes; then
echo " - CC used by MPI Compiler Wrapper ($mpi_cc_wrapper) = $mpi_cc"
echo " - MPI CFLAGS       = $MPICFLAGS"
echo " - MPI LDFLAGS      = $MPILDFLAGS"
echo " - MPI LIBS         = $MPILIBS"
echo ""
echo " - PTHREADS CFLAGS  = $THREADS_CFLAGS"
echo " - PTHREADS LDFLAGS = $THREADS_LDFLAGS"
echo " - PTHREADS LIBS    = $THREADS_LIBS"
fi
echo ""
echo "Prepare unit tests    : $want_tests"
if test x${want_tests} = xyes; then
echo " - CUNIT CFLAGS     = $CUNITCFLAGS"
echo " - CUNIT LDFLAGS    = $CUNITLDFLAGS"
echo " - CUNIT LIBS       = $CUNITLIBS"
fi
echo ""
echo "Default compiler : $CC"
echo "Default CFLAGS   : $CFLAGS"
echo "Default LDFLAGS  : $LDFLAGS"
echo "Default LIBS     : $LIBS"
echo ""
echo "Additional CFLAGS (production) : $PRODUCTION_CFLAGS"
echo "Additional CFLAGS (debug)      : $DEBUG_CFLAGS"
echo ""
echo "-----------------------------------------------------------------------"
echo ""
echo "If you wish to use a different compiler and/or CFLAGS, you can "
echo "override CC and CFLAGS during the invocation of 'make'. For example:"
echo '# make CC="xlc_r" CFLAGS="-qlanglvl=stdc99 -qinfo=all -qflag=w:u -qcheck=all "'
echo ""

