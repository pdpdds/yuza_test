//
// excpt.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// The declarations of the compiler-dependent intrinsics, support functions, and
// keywords which implement the structured exception handling extensions.
//
#pragma once
#define _INC_EXCPT

#include <minwindef.h>





// Exception disposition return values
typedef enum _EXCEPTION_DISPOSITION
{
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;



// SEH handler
#if defined(_M_IX86) && !defined(_CHPE_X86_ARM64_EH_)

    struct _EXCEPTION_RECORD;
    struct _CONTEXT;

    EXCEPTION_DISPOSITION __cdecl _except_handler(
        _In_ struct _EXCEPTION_RECORD* _ExceptionRecord,
        _In_ void*                     _EstablisherFrame,
         struct _CONTEXT*       _ContextRecord,
         void*                  _DispatcherContext
        );

#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64 || defined _CHPE_X86_ARM64_EH_
    #ifndef _M_CEE_PURE

        struct _EXCEPTION_RECORD;
        struct _CONTEXT;
        struct _DISPATCHER_CONTEXT;

        _VCRTIMP EXCEPTION_DISPOSITION __cdecl __C_specific_handler(
            _In_    struct _EXCEPTION_RECORD*   ExceptionRecord,
            _In_    void*                       EstablisherFrame,
            _Inout_ struct _CONTEXT*            ContextRecord,
            _Inout_ struct _DISPATCHER_CONTEXT* DispatcherContext
            );

    #endif
#endif



// SEH intrinsics
#define GetExceptionCode        _exception_code
#define exception_code          _exception_code
#define GetExceptionInformation (struct _EXCEPTION_POINTERS*)_exception_info
#define exception_info          (struct _EXCEPTION_POINTERS*)_exception_info
#define AbnormalTermination     _abnormal_termination
#define abnormal_termination    _abnormal_termination

unsigned long __cdecl _exception_code(void);
void *        __cdecl _exception_info(void);
int           __cdecl _abnormal_termination(void);



// Defined values for the exception filter expression
#define EXCEPTION_EXECUTE_HANDLER      1
#define EXCEPTION_CONTINUE_SEARCH      0
#define EXCEPTION_CONTINUE_EXECUTION (-1)

#define THROW_ATTRS(t)			((t).attributes)
#define TI_IsPure			0x00000008		// object thrown from a pure module
#define THROW_ISPURE(t)			(THROW_ATTRS(t) & TI_IsPure)

#define MAXIMUM_SUPPORTED_EXTENSION     512
#define SIZE_OF_80387_REGISTERS      80

typedef struct _FLOATING_SAVE_AREA {
	DWORD   ControlWord;
	DWORD   StatusWord;
	DWORD   TagWord;
	DWORD   ErrorOffset;
	DWORD   ErrorSelector;
	DWORD   DataOffset;
	DWORD   DataSelector;
	BYTE    RegisterArea[SIZE_OF_80387_REGISTERS];
	DWORD   Spare0;
} FLOATING_SAVE_AREA;

typedef struct _CONTEXT {

	//
	// The flags values within this flag control the contents of
	// a CONTEXT record.
	//
	// If the context record is used as an input parameter, then
	// for each portion of the context record controlled by a flag
	// whose value is set, it is assumed that that portion of the
	// context record contains valid context. If the context record
	// is being used to modify a threads context, then only that
	// portion of the threads context will be modified.
	//
	// If the context record is used as an IN OUT parameter to capture
	// the context of a thread, then only those portions of the thread's
	// context corresponding to set flags will be returned.
	//
	// The context record is never used as an OUT only parameter.
	//

	DWORD ContextFlags;

	//
	// This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
	// set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
	// included in CONTEXT_FULL.
	//

	DWORD   Dr0;
	DWORD   Dr1;
	DWORD   Dr2;
	DWORD   Dr3;
	DWORD   Dr6;
	DWORD   Dr7;

	//
	// This section is specified/returned if the
	// ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
	//

	FLOATING_SAVE_AREA FloatSave;

	//
	// This section is specified/returned if the
	// ContextFlags word contians the flag CONTEXT_SEGMENTS.
	//

	DWORD   SegGs;
	DWORD   SegFs;
	DWORD   SegEs;
	DWORD   SegDs;

	//
	// This section is specified/returned if the
	// ContextFlags word contians the flag CONTEXT_INTEGER.
	//

	DWORD   Edi;
	DWORD   Esi;
	DWORD   Ebx;
	DWORD   Edx;
	DWORD   Ecx;
	DWORD   Eax;

	//
	// This section is specified/returned if the
	// ContextFlags word contians the flag CONTEXT_CONTROL.
	//

	DWORD   Ebp;
	DWORD   Eip;
	DWORD   SegCs;              // MUST BE SANITIZED
	DWORD   EFlags;             // MUST BE SANITIZED
	DWORD   Esp;
	DWORD   SegSs;

	//
	// This section is specified/returned if the ContextFlags word
	// contains the flag CONTEXT_EXTENDED_REGISTERS.
	// The format and contexts are processor specific
	//

	BYTE    ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];

} CONTEXT;

typedef CONTEXT* PCONTEXT;


#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum number of exception parameters

//
// Exception record definition.
//

typedef struct _EXCEPTION_RECORD {
	DWORD    ExceptionCode;
	DWORD ExceptionFlags;
	struct _EXCEPTION_RECORD* ExceptionRecord;
	PVOID ExceptionAddress;
	DWORD NumberParameters;
	ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD;

typedef EXCEPTION_RECORD* PEXCEPTION_RECORD;
typedef PVOID* PEXCEPTION_ROUTINE;

typedef struct _EXCEPTION_REGISTRATION_RECORD {
	struct _EXCEPTION_REGISTRATION_RECORD* Next;
	PEXCEPTION_ROUTINE Handler;
} EXCEPTION_REGISTRATION_RECORD;

typedef EXCEPTION_REGISTRATION_RECORD* PEXCEPTION_REGISTRATION_RECORD;




typedef struct EHEXCEPTION_RECORD
{
	DWORD ExceptionCode;
	DWORD ExceptionFlags;
	struct _EXCEPTION_RECODE* ExceptionRecord;
	void* ExceptionAddress;
	DWORD NumberParameters;
	struct EHParameters
	{
		DWORD magicNumber;
		void* pExceptionObject;
		_ThrowInfo* pThrowInfo;
	} params;
}EHEXCEPTION_RECORD;

#define EXCEPTION_NONCONTINUABLE 0x1    // Noncontinuable exception
#define EH_EXCEPTION_NUMBER 0xE06d7363    
#define EH_EXCEPTION_PARAMETERS 3
#define EH_MAGIC_NUMBER1 0x19930520
#define EH_PURE_MAGIC_NUMBER1   0x01994000

typedef struct _EXCEPTION_POINTERS {
	PEXCEPTION_RECORD ExceptionRecord;
	PCONTEXT ContextRecord;
} EXCEPTION_POINTERS, * PEXCEPTION_POINTERS;
