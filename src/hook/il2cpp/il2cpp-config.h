#pragma once
#include "src/sdk/MiHoYoSDK.h"

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {
        //Il2cpp模块
        namespace Il2cpp
        {

            typedef int32_t il2cpp_hresult_t;

// Sorted numerically!
#define IL2CPP_S_OK ((il2cpp_hresult_t)0)
#define IL2CPP_E_BOUNDS ((il2cpp_hresult_t)0x8000000B)
#define IL2CPP_E_CHANGED_STATE ((il2cpp_hresult_t)0x8000000C)
#define IL2CPP_E_ILLEGAL_METHOD_CALL ((il2cpp_hresult_t)0x8000000E)
#define IL2CPP_RO_E_CLOSED ((il2cpp_hresult_t)0x80000013)
#define IL2CPP_E_NOTIMPL ((il2cpp_hresult_t)0x80004001)
#define IL2CPP_E_NOINTERFACE ((il2cpp_hresult_t)0x80004002)
#define IL2CPP_E_POINTER ((il2cpp_hresult_t)0x80004003)
#define IL2CPP_E_ABORT ((il2cpp_hresult_t)0x80004004)
#define IL2CPP_E_FAIL ((il2cpp_hresult_t)0x80004005)
#define IL2CPP_E_UNEXPECTED ((il2cpp_hresult_t)0x8000FFFF)
#define IL2CPP_RPC_E_DISCONNECTED ((il2cpp_hresult_t)0x80010108)
#define IL2CPP_RPC_E_WRONG_THREAD ((il2cpp_hresult_t)0x8001010E)
#define IL2CPP_DISP_E_PARAMNOTFOUND ((il2cpp_hresult_t)0x80020004)
#define IL2CPP_REGDB_E_CLASSNOTREG ((il2cpp_hresult_t)0x80040154)
#define IL2CPP_E_ACCESS_DENIED ((il2cpp_hresult_t)0x80070005)
#define IL2CPP_E_OUTOFMEMORY ((il2cpp_hresult_t)0x8007000E)
#define IL2CPP_E_INVALIDARG ((il2cpp_hresult_t)0x80070057)
#define IL2CPP_COR_E_EXCEPTION ((il2cpp_hresult_t)0x80131500)
#define IL2CPP_COR_E_INVALIDOPERATION ((il2cpp_hresult_t)0x80131509)
#define IL2CPP_COR_E_PLATFORMNOTSUPPORTED ((il2cpp_hresult_t)0x80131539)
#define IL2CPP_COR_E_OPERATIONCANCELED ((il2cpp_hresult_t)0x8013153B)
#define IL2CPP_COR_E_OBJECTDISPOSED ((il2cpp_hresult_t)0x80131622)

#define IL2CPP_HR_SUCCEEDED(hr) (((il2cpp_hresult_t)(hr)) >= 0)
#define IL2CPP_HR_FAILED(hr) (((il2cpp_hresult_t)(hr)) < 0)

#define IL2CPP_LITTLE_ENDIAN 1
#define IL2CPP_BIG_ENDIAN 2
#define IL2CPP_BYTE_ORDER IL2CPP_LITTLE_ENDIAN

// On ARMv7 with Thumb instructions the lowest bit is always set.
// With Thumb2 the second-to-lowest bit is also set. Mask both of
// them off so that we can do a comparison properly based on the data
// from the linker map file. On other architectures this operation should
// not matter, as we assume these two bits are always zero because the pointer
// will be aligned.
#define IL2CPP_POINTER_SPARE_BITS 3

#define IL2CPP_USE_GENERIC_CPU_INFO 1
#define IL2CPP_ZERO_LEN_ARRAY 0

#define ALIGN_TYPE(val) __attribute__((aligned(val)))

        } // namespace Il2cpp
    }     // namespace Loaded
} // namespace Hook