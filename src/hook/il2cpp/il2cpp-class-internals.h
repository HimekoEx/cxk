#pragma once
#include "src/sdk/MiHoYoSDK.h"

#include "il2cpp-api-types.h"
#include "il2cpp-config.h"
#include "il2cpp-runtime-metadata.h"

//Hook架构
namespace Hook
{
//Lib加载模块
namespace Loaded
{
//Il2cpp模块
namespace Il2cpp
{

struct Il2CppType;
struct Il2CppObject;
struct Il2CppClass;
struct Il2CppGuid;
struct Il2CppImage;
struct Il2CppAssembly;
struct Il2CppAppDomain;
struct Il2CppAppDomainSetup;
struct Il2CppDelegate;
struct Il2CppAppContext;
struct Il2CppNameToTypeDefinitionIndexHashTable;

typedef void *(*InvokerMethod)(Il2CppMethodPointer, const MethodInfo *, void *, void **);

typedef void (*PInvokeMarshalToNativeFunc)(void *managedStructure, void *marshaledStructure);
typedef void (*PInvokeMarshalFromNativeFunc)(void *marshaledStructure, void *managedStructure);
typedef void (*PInvokeMarshalCleanupFunc)(void *marshaledStructure);
typedef struct Il2CppIUnknown *(*CreateCCWFunc)(Il2CppObject *obj);

struct Il2CppInteropData
{
    Il2CppMethodPointer delegatePInvokeWrapperFunction;
    PInvokeMarshalToNativeFunc pinvokeMarshalToNativeFunction;
    PInvokeMarshalFromNativeFunc pinvokeMarshalFromNativeFunction;
    PInvokeMarshalCleanupFunc pinvokeMarshalCleanupFunction;
    CreateCCWFunc createCCWFunction;
    const Il2CppGuid *guid;
    const Il2CppType *type;
};

struct Il2CppRuntimeInterfaceOffsetPair
{
    Il2CppClass *interfaceType;
    int32_t offset;
};

union Il2CppRGCTXData {
    void *rgctxDataDummy;
    const MethodInfo *method;
    const Il2CppType *type;
    Il2CppClass *klass;
};

struct VirtualInvokeData
{
    Il2CppMethodPointer methodPtr;
    const MethodInfo *method;
};

struct Il2CppClass
{
    // The following fields are always valid for a Il2CppClass structure
    const Il2CppImage *image;
    void *gc_desc;
    const char *name;
    const char *namespaze;
    const Il2CppType *byval_arg;
    const Il2CppType *this_arg;
    Il2CppClass *element_class;
    Il2CppClass *castClass;
    Il2CppClass *declaringType;
    Il2CppClass *parent;
    Il2CppGenericClass *generic_class;
    const Il2CppTypeDefinition *typeDefinition; // non-NULL for Il2CppClass's constructed from type defintions
    const Il2CppInteropData *interopData;
    // End always valid fields

    // The following fields need initialized before access. This can be done per field or as an aggregate via a call to Class::Init
    FieldInfo *fields;                                  // Initialized in SetupFields
    const EventInfo *events;                            // Initialized in SetupEvents
    const PropertyInfo *properties;                     // Initialized in SetupProperties
    const MethodInfo **methods;                         // Initialized in SetupMethods
    Il2CppClass **nestedTypes;                          // Initialized in SetupNestedTypes
    Il2CppClass **implementedInterfaces;                // Initialized in SetupInterfaces
    Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets; // Initialized in Init
    void *static_fields;                                // Initialized in Init
    const Il2CppRGCTXData *rgctx_data;                  // Initialized in Init
    // used for fast parent checks
    Il2CppClass **typeHierarchy; // Initialized in SetupTypeHierachy
    // End initialization required fields

    uint32_t cctor_started;
    uint32_t cctor_finished;
    ALIGN_TYPE(8)
    uint64_t cctor_thread;

    // Remaining fields are always valid except where noted
    GenericContainerIndex genericContainerIndex;
    CustomAttributeIndex customAttributeIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;

    uint16_t method_count; // lazily calculated for arrays, i.e. when rank > 0
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count; // lazily calculated for arrays, i.e. when rank > 0
    uint16_t interfaces_count;
    uint16_t interface_offsets_count; // lazily calculated for arrays, i.e. when rank > 0

    uint8_t typeHierarchyDepth; // Initialized in SetupTypeHierachy
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t packingSize;

    uint8_t valuetype : 1;
    uint8_t initialized : 1;
    uint8_t enumtype : 1;
    uint8_t is_generic : 1;
    uint8_t has_references : 1;
    uint8_t init_pending : 1;
    uint8_t size_inited : 1;
    uint8_t has_finalize : 1;
    uint8_t has_cctor : 1;
    uint8_t is_blittable : 1;
    uint8_t is_import_or_windows_runtime : 1;
    uint8_t is_vtable_initialized : 1;
    VirtualInvokeData vtable[IL2CPP_ZERO_LEN_ARRAY];
};

struct Il2CppImage
{
    const char *name;
    const char *nameNoExt;
    AssemblyIndex assemblyIndex;

    TypeDefinitionIndex typeStart;
    uint32_t typeCount;

    TypeDefinitionIndex exportedTypeStart;
    uint32_t exportedTypeCount;

    MethodIndex entryPointIndex;

    mutable Il2CppNameToTypeDefinitionIndexHashTable *nameToClassHashTable;

    uint32_t token;
};

struct ParameterInfo
{
    const char *name;
    int32_t position;
    uint32_t token;
    CustomAttributeIndex customAttributeIndex;
    const Il2CppType *parameter_type;
};

struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    InvokerMethod invoker_method;
    const char *name;
    Il2CppClass *declaring_type;
    const Il2CppType *return_type;
    const ParameterInfo *parameters;

    union {
        const Il2CppRGCTXData *rgctx_data; /* is_inflated is true and is_generic is false, i.e. a generic instance method */
        const Il2CppMethodDefinition *methodDefinition;
    };

    /* note, when is_generic == true and is_inflated == true the method represents an uninflated generic method on an inflated type. */
    union {
        const Il2CppGenericMethod *genericMethod;       /* is_inflated is true */
        const Il2CppGenericContainer *genericContainer; /* is_inflated is false and is_generic is true */
    };

    CustomAttributeIndex customAttributeIndex;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t is_generic : 1;  /* true if method is a generic method definition */
    uint8_t is_inflated : 1; /* true if declaring_type is a generic instance or if method is a generic instance*/
};

} // namespace Il2cpp
} // namespace Loaded
} // namespace Hook
