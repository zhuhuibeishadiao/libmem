/*
 *  ----------------------------------
 * |         libmem - by rdbo         |
 * |      Memory Hacking Library      |
 *  ----------------------------------
 */

#pragma once
#ifndef LIBMEM_H
#define LIBMEM_H

/* Operating System */
#define LM_OS_WIN   0
#define LM_OS_LINUX 1
#define LM_OS_BSD   2

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32)) \
	&& !defined(__CYGWIN__) && !defined(linux)
#define LM_OS LM_OS_WIN
#elif defined(linux) || defined(__linux__)
#define LM_OS LM_OS_LINUX
#elif defined(BSD) || defined(__FreeBSD__) \
	|| defined(__OpenBSD__) || defined(__NetBSD__)
#define LM_OS LM_OS_BSD
#endif

/* Architecture */
#define LM_ARCH_X86 0
#define LM_ARCH_ARM 1

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) \
	|| defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) \
	|| defined (i386) || defined(__i386) || defined(__i386__)
#define LM_ARCH LM_ARCH_X86
#elif defined(__arm__) || defined(_ARM) \
	|| defined(_M_ARM) || defined(__aarch64__)
#define LM_ARCH LM_ARCH_ARM
#endif

/* Bits */
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) \
	|| defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) \
	|| defined(__aarch64__) \
	|| defined(__LP64__) || defined(_LP64) \
	|| (defined(__WORDSIZE) && __WORDSIZE == 64)
#define LM_BITS 64
#else
#define LM_BITS 32
#endif

/* Compiler */
#define LM_COMPILER_MSVC 0
#define LM_COMPILER_CC   1

#ifdef _MSC_VER
#define LM_COMPILER LM_COMPILER_MSVC
#else
#define LM_COMPILER LM_COMPILER_CC
#endif

/* Charset */
#define LM_CHARSET_UC 0
#define LM_CHARSET_MB 1

#if defined(_UNICODE) && LM_OS == LM_OS_WIN
#define LM_CHARSET LM_CHARSET_UC
#else
#define LM_CHARSET LM_CHARSET_MB
#endif

/* Language */
#define LM_LANG_C   0
#define LM_LANG_CPP 1

#if defined(LIBMEM_HPP) || defined(__cplusplus)
#define LM_LANG LM_LANG_CPP
#else
#define LM_LANG LM_LANG_C
#endif

/* Helpers */
#define LM_MALLOC   malloc
#define LM_CALLOC   calloc
#define LM_FREE     free
#define LM_MEMCPY   memcpy
#if LM_CHARSET == LM_CHARSET_UC
#define LM_STR(str) L##str
#define LM_STRCMP   wcscmp
#define LM_STRNCMP  wcsncmp
#define LM_STRCPY   wcscpy
#define LM_STRNCPY  wcsncpy
#define LM_STRLEN   wcslen
#define LM_STRCHR   wcschr
#define LM_STRSTR   wcsstr
#define LM_SNPRINTF snwprintf
#define LM_STRTOP   wcstoul
#define LM_ATOI     wtoi
#else
#define LM_STR(str) str
#define LM_STRCMP   strcmp
#define LM_STRNCMP  strncmp
#define LM_STRCPY   strcpy
#define LM_STRNCPY  strncpy
#define LM_STRLEN   strlen
#define LM_STRCHR   strchr
#define LM_STRSTR   strstr
#define LM_SNPRINTF snprintf
#define LM_STRTOP   strtoul
#define LM_ATOI     atoi
#endif
#define LM_ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define LM_CHKMASK(c) \
	(c == LM_STR(LM_MASK_KNOWN) || c == LM_STR(LM_MASK_KNOWN2))
#define LM_RCHKMASK(c) \
	(c == LM_STR(LM_MASK_UNKNOWN) || c == LM_STR(LM_MASK_UNKNOWN2))
#define LM_CHKADDR(addr) ((lm_address_t)addr != (lm_address_t)LM_BAD)

/* Flags */
#if LM_OS == LM_OS_WIN
#define LM_PROT_R   (PAGE_READONLY)
#define LM_PROT_W   (PAGE_WRITECOPY)
#define LM_PROT_X   (PAGE_EXECUTE)
#define LM_PROT_RW  (PAGE_READWRITE)
#define LM_PROT_XR  (PAGE_EXECUTE_READ)
#define LM_PROT_XRW (PAGE_EXECUTE_READWRITE)
#define LM_PROCESS_ACCESS (PROCESS_ALL_ACCESS)
#elif LM_OS == LM_OS_LINUX || LM_OS == LM_OS_BSD
#define LM_PROT_R   (PROT_READ)
#define LM_PROT_W   (PROT_WRITE)
#define LM_PROT_X   (PROT_EXEC)
#define LM_PROT_RW  (PROT_READ | PROT_WRITE)
#define LM_PROT_XR  (PROT_EXEC | PROT_READ)
#define LM_PROT_XRW (PROT_EXEC | PROT_READ | PROT_WRITE)
#endif

/* Imports/Exports */
#if defined(LM_EXPORT)
#if LM_COMPILER == LM_COMPILER_MSVC
#define LM_API __declspec(dllexport)
#elif LM_COMPILER == LM_COMPILER_CC
#define LM_API __attribute__((visibility("default")))
#endif
#elif defined(LM_IMPORT)
#if LM_COMPILER == LM_COMPILER_MSVC
#define LM_API __declspec(dllimport)
#elif LM_COMPILER == LM_COMPILER_CC
#define LM_API extern
#endif
#else
#define LM_API
#endif

/* Old V3 API */
#if defined(LM_OLD)
#define MEM_OS_WIN        LM_OS_WIN
#define MEM_OS_LINUX      LM_OS_LINUX
#define MEM_OS_BSD        LM_OS_BSD
#define MEM_OS            LM_OS

#define MEM_ARCH_X86      LM_ARCH_X86
#define MEM_ARCH_ARM      LM_ARCH_ARM
#define MEM_ARCH          LM_ARCH
#define MEM_BITS          LM_BITS

#define MEM_CHARSET_UC    LM_CHARSET_UC
#define MEM_CHARSET_MB    LM_CHARSET_MB
#define MEM_CHARSET       LM_CHARSET

#define MEM_COMPILER_MSVC LM_COMPILER_MSVC
#define MEM_COMPILER_CC   LM_COMPILER_CC
#define MEM_COMPILER      LM_COMPILER

#define MEM_LANG_C        LM_LANG_C
#define MEM_LANG_CPP      LM_LANG_CPP
#define MEM_LANG          LM_LANG

#define MEM_NULL          LM_NULL
#define MEM_NULLPTR       LM_NULLPTR
#define MEM_TRUE          LM_TRUE
#define MEM_FALSE         LM_FALSE
#define MEM_BAD           LM_BAD
#define MEM_MAX           LM_MAX
#define MEM_PATH_MAX      LM_PATH_MAX
#define MEM_MASK_KNOWN    LM_MASK_KNOWN
#define MEM_MASK_KNOWN2   LM_MASK_KNOWN2
#define MEM_MASK_UNKNOWN  LM_MASK_UNKNOWN
#define MEM_MASK_UNKNOWN2 LM_MASK_UNKNOWN2
#define MEM_PROT_R        LM_PROT_R
#define MEM_PROT_W        LM_PROT_W
#define MEM_PROT_RW       LM_PROT_RW
#define MEM_PROT_XR       LM_PROT_XR
#define MEM_PROT_XRW      LM_PROT_XRW

#define MEM_STR           LM_STR

#define mem_char_t    lm_char_t
#define mem_uchar_t   lm_uchar_t
#define mem_int_t     lm_int_t
#define mem_uint_t    lm_uint_t
#define mem_short_t   lm_short_t
#define mem_ushort_t  lm_ushort_t
#define mem_long_t    lm_long_t
#define mem_ulong_t   lm_ulong_t
#define mem_wchar_t   lm_wchar_t
#define mem_void_t    lm_void_t
#define mem_bool_t    lm_bool_t

#define mem_int8_t    lm_int8_t
#define mem_int16_t   lm_int16_t
#define mem_int32_t   lm_int32_t
#define mem_int64_t   lm_int64_t
#define mem_uint8_t   lm_uint8_t
#define mem_uint16_t  lm_uint16_t
#define mem_uint32_t  lm_uint32_t
#define mem_uint64_t  lm_uint64_t

#define mem_byte_t    lm_byte_t
#define mem_word_t    lm_word_t
#define mem_dword_t   lm_dword_t
#define mem_qword_t   lm_qword_t

#define mem_intptr_t  lm_intptr_t
#define mem_uintptr_t lm_uintptr_t
#define mem_voidptr_t lm_voidptr_t

#define mem_address_t lm_address_t
#define mem_size_t    lm_size_t
#define mem_tchar_t   lm_tchar_t

#define mem_bstring_t lm_bstring_t
#define mem_cstring_t lm_cstring_t
#define mem_wstring_t lm_wstring_t
#define mem_tstring_t lm_tstring_t
#define mem_string_t  lm_string_t

#define mem_pid_t     lm_pid_t
#define mem_tid_t     lm_tid_t
#define mem_prot_t    lm_prot_t
#define mem_flags_t   lm_flags_t
#define mem_detour_t  lm_detour_t
#define mem_argloc_t  lm_datloc_t
#define mem_datio_t   lm_datio_t

#define mem_process_t lm_process_t
#define mem_module_t  lm_module_t
#define mem_page_t    lm_page_t
#define mem_callarg_t lm_callarg_t

#define mem_ex_enum_processes   LM_EnumProcesses
#define mem_in_get_pid          LM_GetProcessId
#define mem_ex_get_pid          LM_GetProcessIdEx
#define mem_in_get_parent       LM_GetParentId
#define mem_ex_get_parent       LM_GetParentIdEx
#define mem_in_open_process     LM_OpenProcess
#define mem_ex_open_process     LM_OpenProcessEx
#define mem_in_close_process    LM_CloseProcess
#define mem_ex_close_process    LM_CloseProcess
#define mem_in_get_process_path LM_GetProcessPath
#define mem_ex_get_process_path LM_GetProcessPathEx
#define mem_in_get_process_name LM_GetProcessName
#define mem_ex_get_process_name LM_GetProcessNameEx
#define mem_ex_get_system_bits  LM_GetSystemBits
#define mem_in_get_bits         LM_GetProcessBits
#define mem_ex_get_bits         LM_GetProcessBitsEx

#define mem_in_enum_modules     LM_EnumModules
#define mem_ex_enum_modules     LM_EnumModulesEx
#define mem_in_get_module       LM_GetModule
#define mem_ex_get_module       LM_GetModuleEx
#define mem_in_get_module_path  LM_GetModulePath
#define mem_ex_get_module_path  LM_GetModulePathEx
#define mem_in_get_module_name  LM_GetModuleName
#define mem_ex_get_module_name  LM_GetModuleNameEx
#define mem_in_load_module      LM_LoadModule
#define mem_ex_load_module      LM_LoadModuleEx
#define mem_in_unload_module    LM_UnloadModule
#define mem_ex_unload_module    LM_UnloadModuleEx
#define mem_in_get_symbol       LM_GetSymbol
#define mem_ex_get_symbol       LM_GetSymbolEx

#define mem_in_enum_pages       LM_EnumPages
#define mem_ex_enum_pages       LM_EnumPagesEx
#define mem_in_get_page         LM_GetPage
#define mem_ex_get_page         LM_GetPageEx

#define mem_in_read             LM_ReadMemory
#define mem_ex_read             LM_ReadMemoryEx
#define mem_in_write            LM_WriteMemory
#define mem_ex_write            LM_WriteMemoryEx
#define mem_in_set              LM_SetMemory
#define mem_ex_set              LM_SetMemoryEx
#define mem_in_protect          LM_ProtMemory
#define mem_ex_protect          LM_ProtMemoryEx
#define mem_in_allocate         LM_AllocMemory
#define mem_ex_allocate         LM_AllocMemoryEx
#define mem_in_deallocate       LM_FreeMemory
#define mem_ex_deallocate       LM_FreeMemoryEx
#define mem_in_scan             LM_DataScan
#define mem_ex_scan             LM_DataScanEx
#define mem_in_pattern_scan     LM_PatternScan
#define mem_ex_pattern_scan     LM_PatternScanEx
#define mem_in_signature_scan   LM_SigScan
#define mem_ex_signature_scan   LM_SigScanEx

#define mem_in_syscall          LM_SystemCall
#define mem_ex_syscall          LM_SystemCallEx
#define mem_in_fncall           LM_FunctionCall
#define mem_ex_fncall           LM_FunctionCallEx
#define mem_in_detour           LM_DetourCode
#define mem_ex_detour           LM_DetourCodeEx
#define mem_in_make_trampoline  LM_MakeTrampoline
#define mem_ex_make_trampoline  LM_MakeTrampolineEx
#define mem_in_del_trampoline   LM_DestroyTrampoline
#define mem_ex_del_trampoline   LM_DestroyTrampolineEx
#endif

/* Others */
#define LM_NULL    (0)
#define LM_NULLPTR ((lm_void_t *)LM_NULL)
#define LM_BAD     (-1)
#define LM_OK      (!(LM_BAD))
#define LM_FALSE   (0)
#define LM_TRUE    (!(LM_FALSE))
#define LM_MAX     (-1UL)
#define LM_MASK_KNOWN    'x'
#define LM_MASK_KNOWN2   'X'
#define LM_MASK_UNKNOWN  '?'
#define LM_MASK_UNKNOWN2 '*'
#if LM_OS == LM_OS_WIN
#define LM_PATH_MAX MAX_PATH
#elif LM_OS == LM_OS_LINUX
#define LM_PATH_MAX PATH_MAX
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define LM_PROCFS "/proc"
#elif LM_OS == LM_OS_BSD
#define LM_PATH_MAX PATH_MAX
#define LM_PROCFS "/proc"
#endif

/* Compatibility */
#if defined(LM_OS) && defined(LM_ARCH) && defined(LM_BITS) \
	&& defined(LM_COMPILER) && defined(LM_CHARSET) && defined(LM_LANG)
#define LM_COMPATIBLE 1
#else
#define LM_COMPATIBLE 0
#endif

#if LM_COMPATIBLE
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#if LM_OS == LM_OS_WIN
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#elif LM_OS == LM_OS_LINUX
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <sys/io.h>
#include <sys/uio.h>
#include <dlfcn.h>
#include <link.h>
#include <fcntl.h>
#include <elf.h>
#elif LM_OS == LM_OS_BSD
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/user.h>
#include <sys/sysctl.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <machine/reg.h>
#include <dlfcn.h>
#include <link.h>
#include <fcntl.h>
#include <kvm.h>
#include <libprocstat.h>
#include <paths.h>
#include <elf.h>
#endif /* LM_OS */

#if LM_LANG == LM_LANG_CPP
extern "C" {
#endif

/* Types/Enums */
typedef char           lm_char_t;
typedef unsigned char  lm_uchar_t;
typedef int            lm_int_t;
typedef unsigned int   lm_uint_t;
typedef short          lm_short_t;
typedef unsigned short lm_ushort_t;
typedef long           lm_long_t;
typedef unsigned long  lm_ulong_t;
typedef wchar_t        lm_wchar_t;
typedef void           lm_void_t;
typedef lm_int_t       lm_bool_t;

typedef char           lm_int8_t;
typedef short          lm_int16_t;
typedef int            lm_int32_t;
typedef long           lm_int64_t;

typedef unsigned char  lm_uint8_t;
typedef unsigned short lm_uint16_t;
typedef unsigned int   lm_uint32_t;
typedef unsigned long  lm_uint64_t;

typedef lm_uint8_t     lm_byte_t;
typedef lm_uint16_t    lm_word_t;
typedef lm_uint32_t    lm_dword_t;
typedef lm_uint64_t    lm_qword_t;

typedef lm_long_t      lm_intptr_t;
typedef lm_ulong_t     lm_uintptr_t;
typedef lm_void_t     *lm_voidptr_t;

typedef lm_voidptr_t   lm_address_t;
typedef lm_ulong_t     lm_size_t;

#if LM_CHARSET == LM_CHARSET_UC
typedef lm_wchar_t     lm_tchar_t;
#else
typedef lm_char_t      lm_tchar_t;
#endif

typedef lm_byte_t     *lm_bstring_t;
typedef lm_char_t     *lm_cstring_t;
typedef lm_wchar_t    *lm_wstring_t;
typedef lm_tchar_t    *lm_tstring_t;
typedef lm_tstring_t   lm_string_t;

#if LM_OS == LM_OS_WIN
typedef DWORD          lm_pid_t;
typedef DWORD          lm_prot_t;
typedef DWORD          lm_flags_t;
typedef DWORD          lm_tid_t;
#elif LM_OS == LM_OS_LINUX || LM_OS == LM_OS_BSD
typedef pid_t          lm_pid_t;
typedef lm_pid_t       lm_tid_t;
typedef int            lm_prot_t;
typedef int            lm_flags_t;
#endif

typedef struct {
	lm_pid_t pid;
#	if LM_OS == LM_OS_WIN
	HANDLE   handle;
#	endif
} lm_process_t;

typedef struct {
	lm_address_t base;
	lm_address_t end;
	lm_size_t    size;
} lm_module_t;

typedef struct {
	lm_address_t base;
	lm_address_t end;
	lm_size_t    size;
	lm_prot_t    prot;
	lm_flags_t   flags;
} lm_page_t;

enum {
#	if LM_ARCH == LM_ARCH_X86
	LM_DETOUR_JMP32,
	LM_DETOUR_JMP64,
	LM_DETOUR_CALL32,
	LM_DETOUR_CALL64,
	LM_DETOUR_RET32,
	LM_DETOUR_RET64,
#	endif
	LM_DETOUR_INVAL
};

typedef lm_int_t lm_detour_t;

/* LM_GetModule(Ex) Flags */
enum {
	LM_MOD_BY_STR = 0,
	LM_MOD_BY_ADDR
};

enum {
	LM_DATLOC_INVAL = 0,
#	if LM_ARCH == LM_ARCH_X86
	LM_DATLOC_RAX,
	LM_DATLOC_RBX,
	LM_DATLOC_RCX,
	LM_DATLOC_RDX,
	LM_DATLOC_RSI,
	LM_DATLOC_RDI,
	LM_DATLOC_RSP,
	LM_DATLOC_RBP,
	LM_DATLOC_R8,
	LM_DATLOC_R9,
	LM_DATLOC_R10,
	LM_DATLOC_R11,
	LM_DATLOC_R12,
	LM_DATLOC_R13,
	LM_DATLOC_R14,
	LM_DATLOC_R15,
#	define LM_DATLOC_EAX LM_DATLOC_RAX
#	define LM_DATLOC_EBX LM_DATLOC_RBX
#	define LM_DATLOC_ECX LM_DATLOC_RCX
#	define LM_DATLOC_EDX LM_DATLOC_RDX
#	define LM_DATLOC_ESI LM_DATLOC_RSI
#	define LM_DATLOC_EDI LM_DATLOC_RDI
#	define LM_DATLOC_ESP LM_DATLOC_RSP
#	define LM_DATLOC_EBP LM_DATLOC_RBP
#	elif LM_ARCH == LM_ARCH_ARM
#	endif
	LM_DATLOC_STACK
};

typedef lm_int_t lm_datloc_t;

typedef struct {
	lm_datloc_t datloc;
	lm_size_t   size;
	lm_byte_t  *data;
} lm_datio_t;

/* libmem */
LM_API lm_bool_t
LM_EnumProcesses(lm_bool_t(*callback)(lm_pid_t   pid,
				      lm_void_t *arg),
		 lm_void_t *arg);

LM_API lm_pid_t
LM_GetProcessId(lm_void_t);

LM_API lm_pid_t
LM_GetProcessIdEx(lm_tstring_t procstr);

LM_API lm_pid_t
LM_GetParentId(lm_void_t);

LM_API lm_pid_t
LM_GetParentIdEx(lm_pid_t pid);

LM_API lm_bool_t
LM_OpenProcess(lm_process_t *procbuf);

LM_API lm_bool_t
LM_OpenProcessEx(lm_pid_t      pid,
		 lm_process_t *procbuf);

LM_API lm_void_t
LM_CloseProcess(lm_process_t *procbuf);

LM_API lm_size_t
LM_GetProcessPath(lm_tchar_t *pathbuf,
		  lm_size_t   maxlen);

LM_API lm_size_t
LM_GetProcessPathEx(lm_process_t proc,
		    lm_tchar_t  *pathbuf,
		    lm_size_t    maxlen);

LM_API lm_size_t
LM_GetProcessName(lm_tchar_t *namebuf,
		  lm_size_t   maxlen);

LM_API lm_size_t
LM_GetProcessNameEx(lm_process_t proc,
		    lm_tchar_t  *namebuf,
		    lm_size_t    maxlen);

LM_API lm_size_t
LM_GetSystemBits(lm_void_t);

LM_API lm_size_t
LM_GetProcessBits(lm_void_t);

LM_API lm_size_t
LM_GetProcessBitsEx(lm_process_t proc);

/****************************************/

LM_API lm_bool_t
LM_EnumThreads(lm_bool_t(*callback)(lm_tid_t   tid,
				    lm_void_t *arg),
	       lm_void_t *arg);

LM_API lm_bool_t
LM_EnumThreadsEx(lm_process_t proc,
		 lm_bool_t  (*callback)(lm_tid_t   tid,
					lm_void_t *arg),
		 lm_void_t   *arg);

LM_API lm_tid_t
LM_GetThreadId(lm_void_t);

LM_API lm_tid_t
LM_GetThreadIdEx(lm_process_t proc);

/****************************************/

LM_API lm_bool_t
LM_EnumModules(lm_bool_t(*callback)(lm_module_t  mod,
				    lm_tstring_t path,
				    lm_void_t   *arg),
	       lm_void_t *arg);

LM_API lm_bool_t
LM_EnumModulesEx(lm_process_t proc,
		 lm_bool_t  (*callback)(lm_module_t  mod,
					lm_tstring_t path,
					lm_void_t   *arg),
		 lm_void_t   *arg);

LM_API lm_bool_t
LM_GetModule(lm_void_t   *modarg,
	     lm_module_t *modbuf,
	     lm_int_t     flags);

LM_API lm_bool_t
LM_GetModuleEx(lm_process_t proc,
	       lm_void_t   *modarg,
	       lm_module_t *modbuf,
	       lm_int_t     flags);

LM_API lm_size_t
LM_GetModulePath(lm_module_t mod,
		 lm_tchar_t *pathbuf,
		 lm_size_t   maxlen);

LM_API lm_size_t
LM_GetModulePathEx(lm_process_t proc,
		   lm_module_t  mod,
		   lm_tchar_t  *pathbuf,
		   lm_size_t    maxlen);

LM_API lm_size_t
LM_GetModuleName(lm_module_t mod,
		 lm_tchar_t *namebuf,
		 lm_size_t   maxlen);

LM_API lm_size_t
LM_GetModuleNameEx(lm_process_t proc,
		   lm_module_t  mod,
		   lm_tchar_t  *namebuf,
		   lm_size_t    maxlen);

LM_API lm_bool_t
LM_LoadModule(lm_tstring_t path,
	      lm_module_t *modbuf);

LM_API lm_bool_t
LM_LoadModuleEx(lm_process_t proc,
		lm_tstring_t path,
		lm_module_t *modbuf);

LM_API lm_bool_t
LM_UnloadModule(lm_module_t mod);

LM_API lm_bool_t
LM_UnloadModuleEx(lm_process_t proc,
		  lm_module_t  mod);

LM_API lm_address_t
LM_GetSymbol(lm_module_t  mod,
	     lm_cstring_t symstr);

LM_API lm_address_t
LM_GetSymbolEx(lm_process_t proc,
	       lm_module_t  mod,
	       lm_cstring_t symstr);

/****************************************/

LM_API lm_bool_t
LM_EnumPages(lm_bool_t(*callback)(lm_page_t  page,
				  lm_void_t *arg),
	     lm_void_t *arg);

LM_API lm_bool_t
LM_EnumPagesEx(lm_process_t proc,
	       lm_bool_t  (*callback)(lm_page_t  page,
				      lm_void_t *arg),
	       lm_void_t   *arg);

LM_API lm_bool_t
LM_GetPage(lm_address_t addr,
	   lm_page_t   *page);

LM_API lm_bool_t
LM_GetPageEx(lm_process_t proc,
	     lm_address_t addr,
	     lm_page_t   *page);

/****************************************/

LM_API lm_size_t
LM_ReadMemory(lm_address_t src,
	      lm_byte_t   *dst,
	      lm_size_t    size);

LM_API lm_size_t
LM_ReadMemoryEx(lm_process_t proc,
		lm_address_t src,
		lm_byte_t   *dst,
		lm_size_t    size);

LM_API lm_size_t
LM_WriteMemory(lm_address_t dst,
	       lm_bstring_t src,
	       lm_size_t    size);

LM_API lm_size_t
LM_WriteMemoryEx(lm_process_t proc,
		 lm_address_t dst,
		 lm_bstring_t src,
		 lm_size_t    size);

LM_API lm_size_t
LM_SetMemory(lm_byte_t *dst,
	     lm_byte_t  byte,
	     lm_size_t  size);

LM_API lm_size_t
LM_SetMemoryEx(lm_process_t proc,
	       lm_address_t dst,
	       lm_byte_t    byte,
	       lm_size_t    size);

LM_API lm_bool_t
LM_ProtMemory(lm_address_t addr,
	      lm_size_t    size,
	      lm_prot_t    prot,
	      lm_prot_t   *oldprot);

LM_API lm_bool_t
LM_ProtMemoryEx(lm_process_t proc,
		lm_address_t addr,
		lm_size_t    size,
		lm_prot_t    prot,
		lm_prot_t   *oldprot);

LM_API lm_address_t
LM_AllocMemory(lm_size_t size,
	       lm_prot_t prot);

LM_API lm_address_t
LM_AllocMemoryEx(lm_process_t proc,
		 lm_size_t    size,
		 lm_prot_t    prot);

LM_API lm_bool_t
LM_FreeMemory(lm_address_t alloc,
	      lm_size_t    size);

LM_API lm_bool_t
LM_FreeMemoryEx(lm_process_t proc,
		lm_address_t alloc,
		lm_size_t    size);

LM_API lm_address_t
LM_DataScan(lm_bstring_t data,
	    lm_size_t    size,
	    lm_address_t start,
	    lm_address_t stop);

LM_API lm_address_t
LM_DataScanEx(lm_process_t proc,
	      lm_bstring_t data,
	      lm_size_t    size,
	      lm_address_t start,
	      lm_address_t stop);

LM_API lm_address_t
LM_PatternScan(lm_bstring_t pattern,
	       lm_tstring_t mask,
	       lm_address_t start,
	       lm_address_t stop);

LM_API lm_address_t
LM_PatternScanEx(lm_process_t proc,
		 lm_bstring_t pattern,
		 lm_tstring_t mask,
		 lm_address_t start,
		 lm_address_t stop);

LM_API lm_address_t
LM_SigScan(lm_tstring_t sig,
	   lm_address_t start,
	   lm_address_t stop);

LM_API lm_address_t
LM_SigScanEx(lm_process_t proc,
	     lm_tstring_t sig,
	     lm_address_t start,
	     lm_address_t stop);

/****************************************/

LM_API lm_uintptr_t
LM_SystemCall(lm_int_t     nsyscall,
	      lm_uintptr_t arg0,
	      lm_uintptr_t arg1,
	      lm_uintptr_t arg2,
	      lm_uintptr_t arg3,
	      lm_uintptr_t arg4,
	      lm_uintptr_t arg5);

LM_API lm_uintptr_t
LM_SystemCallEx(lm_process_t proc,
		lm_int_t     nsyscall,
		lm_uintptr_t arg0,
		lm_uintptr_t arg1,
		lm_uintptr_t arg2,
		lm_uintptr_t arg3,
		lm_uintptr_t arg4,
		lm_uintptr_t arg5);

LM_API lm_uintptr_t
LM_FunctionCall(lm_address_t fnaddr,
		lm_size_t    nargs,
		...);

LM_API lm_bool_t
LM_FunctionCallEx(lm_process_t proc,
		  lm_uintptr_t stack_align,
		  lm_address_t fnaddr,
		  lm_size_t    nargs,
		  lm_size_t    nrets,
		  ...);

LM_API lm_bool_t
LM_DetourCode(lm_address_t src,
	      lm_address_t dst,
	      lm_detour_t  detour);

LM_API lm_bool_t
LM_DetourCodeEx(lm_process_t proc,
		lm_address_t src,
		lm_address_t dst,
		lm_detour_t  detour);

LM_API lm_address_t
LM_MakeTrampoline(lm_address_t src,
		  lm_size_t    size);

LM_API lm_address_t
LM_MakeTrampolineEx(lm_process_t proc,
		    lm_address_t src,
		    lm_size_t    size);

LM_API lm_void_t
LM_DestroyTrampoline(lm_address_t tramp);

LM_API lm_void_t
LM_DestroyTrampolineEx(lm_process_t proc,
		       lm_address_t tramp);

#if LM_LANG == LM_LANG_CPP
}
#endif

#endif /* LM_COMPATIBLE */
#endif /* LIBMEM_H */
