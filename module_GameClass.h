#pragma once

//关卡收集数据
enum StageCheatData_Type
{
    STAGE_ID = 1,                         // 阶段ID
    STAGE_PROGRESS = 2,                   // 阶段进展
    STAGE_MAX_SCORE = 3,                  // 阶段最大分数
    TIME_START = 1001,                    // 时间开始
    TIME_USE = 1002,                      // 使用时间
    AVG_FRAME_TIME = 1003,                // 平均帧时间
    PLAYER_LEVEL = 1004,                  // 玩家等级
    STAGE_SCORE = 1005,                   // 阶段分数
    AVATAR_ID_1 = 2001,                   // 女武神ID_1
    AVATAR_LEVEL_1 = 2002,                // 女武神等级_1
    AVATAR_COMBAT_1 = 2003,               // 女武神战斗力_1
    ATTACK_MAX_1 = 2004,                  // 攻击最大值_1
    SP_MAX_1 = 2005,                      // SP最大值_1
    SP_BEGIN_1 = 2006,                    // SP初始值_1
    SP_END_1 = 2007,                      // SP结束值_1
    SP_GAIN_1 = 2008,                     // SP获得值_1
    SP_USE_1 = 2009,                      // SP使用值_1
    HP_MAX_1 = 2010,                      // HP最大值_1
    HP_BEGIN_1 = 2011,                    // HP初始值_1
    HP_END_1 = 2012,                      // HP结束值_1
    HP_GAIN_1 = 2013,                     // HP获得值_1
    HIT_COUNT_1 = 2014,                   // 命中次数_1
    HIT_DAMAGE_1 = 2015,                  // 命中伤害_1
    HIT_NORMAL_DAMAGE_MAX_1 = 2016,       // 正常伤害最大值_1
    HIT_CRITICAL_DAMAGE_MAX_1 = 2017,     // 暴击伤害最大值_1
    BEHIT_COUNT_1 = 2018,                 // 被击中次数_1
    BEHIT_NORMAL_DAMAGE_MAX_1 = 2019,     // 被击中的正常伤害最大值_1
    BEHIT_CRITICAL_DAMAGE_MAX_1 = 2020,   // 被击中的暴击伤害最大值_1
    COMBO_MAX_1 = 2021,                   // 连击最大值_1
    AVATAR_TIME_USE_1 = 2022,             // 女武神使用时间_1
    WEAPON_LEVEL_1 = 2023,                // 武器等级_1
    STIGMATA_LEVEL_MAX_1 = 2024,          // 圣痕等级最大值_1
    MP_TEAM_SKILL_TIMES_1 = 2025,         // MP团队技能次数_1
    MP_QTE_SKILL_TIMES_1 = 2026,          // MPQTE技能次数_1
    MP_BE_RESCUED_TIMES_1 = 2027,         // MP被拯救次数_1
    MP_RESCUE_TIMES_1 = 2028,             // MP拯救次数_1
    MP_AVG_RESCUE_TIME_1 = 2029,          // MP平均救援时间_1
    MP_CHAT_TIMES_1 = 2030,               // MP聊天次数_1
    ULTIMATE_SKILL_TIMES_1 = 2031,        // 终极技能次数_1
    ULTIMATE_SKILL_DURATION_1 = 2032,     // 终极技能持续时间_1
    ATTACK_SP_GAIN_1 = 2033,              // 攻击获得SP_1
    WEAPON_SKILL_TIMES_1 = 2034,          // 武器技能次数_1
    AVATAR_ID_2 = 2101,                   // 女武神ID_2
    AVATAR_LEVEL_2 = 2102,                // 女武神等级_2
    AVATAR_COMBAT_2 = 2103,               // 女武神战斗力_2
    ATTACK_MAX_2 = 2104,                  // 攻击最大值_2
    SP_MAX_2 = 2105,                      // SP最大值_2
    SP_BEGIN_2 = 2106,                    // SP初始值_2
    SP_END_2 = 2107,                      // SP结束值_2
    SP_GAIN_2 = 2108,                     // SP获得值_2
    SP_USE_2 = 2109,                      // SP使用值_2
    HP_MAX_2 = 2110,                      // HP最大值_2
    HP_BEGIN_2 = 2111,                    // HP初始值_2
    HP_END_2 = 2112,                      // HP结束值_2
    HP_GAIN_2 = 2113,                     // HP获得值_2
    HIT_COUNT_2 = 2114,                   // 命中次数_2
    HIT_DAMAGE_2 = 2115,                  // 命中伤害_2
    HIT_NORMAL_DAMAGE_MAX_2 = 2116,       // 正常伤害最大值_2
    HIT_CRITICAL_DAMAGE_MAX_2 = 2117,     // 暴击伤害最大值_2
    BEHIT_COUNT_2 = 2118,                 // 被击中次数_2
    BEHIT_NORMAL_DAMAGE_MAX_2 = 2119,     // 被击中的正常伤害最大值_2
    BEHIT_CRITICAL_DAMAGE_MAX_2 = 2120,   // 被击中的暴击伤害最大值_2
    COMBO_MAX_2 = 2121,                   // 连击最大值_2
    AVATAR_TIME_USE_2 = 2122,             // 女武神使用时间_2
    WEAPON_LEVEL_2 = 2123,                // 武器等级_2
    STIGMATA_LEVEL_MAX_2 = 2124,          // 圣痕等级最大值_2
    MP_TEAM_SKILL_TIMES_2 = 2125,         // MP团队技能次数_2
    MP_QTE_SKILL_TIMES_2 = 2126,          // MPQTE技能次数_2
    MP_BE_RESCUED_TIMES_2 = 2127,         // MP被拯救次数_2
    MP_RESCUE_TIMES_2 = 2128,             // MP拯救次数_2
    MP_AVG_RESCUE_TIME_2 = 2129,          // MP平均救援时间_2
    MP_CHAT_TIMES_2 = 2130,               // MP聊天次数_2
    ULTIMATE_SKILL_TIMES_2 = 2131,        // 终极技能次数_2
    ULTIMATE_SKILL_DURATION_2 = 2132,     // 终极技能持续时间_2
    ATTACK_SP_GAIN_2 = 2133,              // 攻击获得SP_2
    WEAPON_SKILL_TIMES_2 = 2134,          // 武器技能次数_2
    AVATAR_ID_3 = 2201,                   // 女武神ID_3
    AVATAR_LEVEL_3 = 2202,                // 女武神等级_3
    AVATAR_COMBAT_3 = 2203,               // 女武神战斗力_3
    ATTACK_MAX_3 = 2204,                  // 攻击最大值_3
    SP_MAX_3 = 2205,                      // SP最大值_3
    SP_BEGIN_3 = 2206,                    // SP初始值_3
    SP_END_3 = 2207,                      // SP结束值_3
    SP_GAIN_3 = 2208,                     // SP获得值_3
    SP_USE_3 = 2209,                      // SP使用值_3
    HP_MAX_3 = 2210,                      // HP最大值_3
    HP_BEGIN_3 = 2211,                    // HP初始值_3
    HP_END_3 = 2212,                      // HP结束值_3
    HP_GAIN_3 = 2213,                     // HP获得值_3
    HIT_COUNT_3 = 2214,                   // 命中次数_3
    HIT_DAMAGE_3 = 2215,                  // 命中伤害_3
    HIT_NORMAL_DAMAGE_MAX_3 = 2216,       // 正常伤害最大值_3
    HIT_CRITICAL_DAMAGE_MAX_3 = 2217,     // 暴击伤害最大值_3
    BEHIT_COUNT_3 = 2218,                 // 被击中次数_3
    BEHIT_NORMAL_DAMAGE_MAX_3 = 2219,     // 被击中的正常伤害最大值_3
    BEHIT_CRITICAL_DAMAGE_MAX_3 = 2220,   // 被击中的暴击伤害最大值_3
    COMBO_MAX_3 = 2221,                   // 连击最大值_3
    AVATAR_TIME_USE_3 = 2222,             // 女武神使用时间_3
    WEAPON_LEVEL_3 = 2223,                // 武器等级_3
    STIGMATA_LEVEL_MAX_3 = 2224,          // 圣痕等级最大值_3
    MP_TEAM_SKILL_TIMES_3 = 2225,         // MP团队技能次数_3
    MP_QTE_SKILL_TIMES_3 = 2226,          // MPQTE技能次数_3
    MP_BE_RESCUED_TIMES_3 = 2227,         // MP被拯救次数_3
    MP_RESCUE_TIMES_3 = 2228,             // MP拯救次数_3
    MP_AVG_RESCUE_TIME_3 = 2229,          // MP平均救援时间_3
    MP_CHAT_TIMES_3 = 2230,               // MP聊天次数_3
    ULTIMATE_SKILL_TIMES_3 = 2231,        // 终极技能次数_3
    ULTIMATE_SKILL_DURATION_3 = 2232,     // 终极技能持续时间_3
    ATTACK_SP_GAIN_3 = 2233,              // 攻击获得SP_3
    WEAPON_SKILL_TIMES_3 = 2234,          // 武器技能次数_3
    ELF_ID = 2301,                        // 女儿ID_1
    ELF_LEVEL = 2302,                     // 女儿等级_1
    ELF_COMBAT = 2303,                    // 女儿战斗力_1
    ELF_ATTACK = 2304,                    // 女儿攻击_1
    ELF_SP_MAX = 2305,                    // 女儿SP最大值_1
    ELF_ULTIMATE_SKILL_TIMES = 2306,      // 女儿终极技能次数_1
    ELF_SP_USE = 2307,                    // 女儿SP使用值_1
    ELF_HIT_CRITICAL_DAMAGE_MAX = 2308,   // 女儿暴击伤害最大值_1
    ELF_HIT_NORMAL_DAMAGE_MAX = 2309,     // 女儿正常伤害最大值_1
    ELF_ID_2 = 2401,                      // 女儿ID_2
    ELF_LEVEL_2 = 2402,                   // 女儿等级_2
    ELF_COMBAT_2 = 2403,                  // 女儿战斗力_2
    ELF_ATTACK_2 = 2404,                  // 女儿攻击_2
    ELF_SP_MAX_2 = 2405,                  // 女儿SP最大值_2
    ELF_ULTIMATE_SKILL_TIMES_2 = 2406,    // 女儿终极技能次数_2
    ELF_SP_USE_2 = 2407,                  // 女儿SP使用值_2
    ELF_HIT_CRITICAL_DAMAGE_MAX_2 = 2408, // 女儿暴击伤害最大值_2
    ELF_HIT_NORMAL_DAMAGE_MAX_2 = 2409,   // 女儿正常伤害最大值_2
    ELF_ID_3 = 2501,                      // 女儿ID_3
    ELF_LEVEL_3 = 2502,                   // 女儿等级_3
    ELF_COMBAT_3 = 2503,                  // 女儿战斗力_3
    ELF_ATTACK_3 = 2504,                  // 女儿攻击_3
    ELF_SP_MAX_3 = 2505,                  // 女儿SP最大值_3
    ELF_ULTIMATE_SKILL_TIMES_3 = 2506,    // 女儿终极技能次数_3
    ELF_SP_USE_3 = 2507,                  // 女儿SP使用值_3
    ELF_HIT_CRITICAL_DAMAGE_MAX_3 = 2508, // 女儿暴击伤害最大值_3
    ELF_HIT_NORMAL_DAMAGE_MAX_3 = 2509,   // 女儿正常伤害最大值_3
    IS_MP_VOICE_USED = 3001,              // 是否使用MP语音
    MP_VOICE_USE_TIME = 3002,             // MP语音使用时间
    SEALED_EVENT_ID = 4001                // 密封事件ID
};

//物品状态
enum MonoGoods_GoodsState
{
    Appear = 0,  // 出现
    Idle = 1,    // 闲置
    Attract = 2, // 吸引
    Consumed = 3 // 消耗
};

//TP登录类型
enum Tp2Entry
{
    ENTRY_ID_QZONE = 1,
    ENTRY_ID_MM = 2,
    ENTRT_ID_FACEBOOK = 3,
    ENTRY_ID_TWITTER = 4,
    ENTRY_ID_LINE = 5,
    ENTRY_ID_WHATSAPP = 6,
    ENTRY_ID_OTHERS = 99
};

// typedef void (*Il2CppMethodPointer)();
// typedef void* (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**);
// struct MethodInfo
// {
//     Il2CppMethodPointer methodPointer;
//     InvokerMethod invoker_method;
//     const char* name;
//     void *declaring_type;
//     const void *return_type;
//     const void* parameters;
// }

//打印StageCheatData数据
void StageCheatData_Print(StageCheatData_Type type, float value);

struct MethodInfo;
struct Il2CppType;
struct Il2CppClass;
union Il2CppRGCTXData;

typedef int32_t TypeIndex;
typedef int32_t TypeDefinitionIndex;
typedef int32_t FieldIndex;
typedef int32_t DefaultValueIndex;
typedef int32_t DefaultValueDataIndex;
typedef int32_t CustomAttributeIndex;
typedef int32_t ParameterIndex;
typedef int32_t MethodIndex;
typedef int32_t GenericMethodIndex;
typedef int32_t PropertyIndex;
typedef int32_t EventIndex;
typedef int32_t GenericContainerIndex;
typedef int32_t GenericParameterIndex;
typedef int16_t GenericParameterConstraintIndex;
typedef int32_t NestedTypeIndex;
typedef int32_t InterfacesIndex;
typedef int32_t VTableIndex;
typedef int32_t InterfaceOffsetIndex;
typedef int32_t RGCTXIndex;
typedef int32_t StringIndex;
typedef int32_t StringLiteralIndex;
typedef int32_t GenericInstIndex;
typedef int32_t ImageIndex;
typedef int32_t AssemblyIndex;
typedef int32_t InteropDataIndex;

const TypeIndex kTypeIndexInvalid = -1;
const TypeDefinitionIndex kTypeDefinitionIndexInvalid = -1;
const DefaultValueDataIndex kDefaultValueIndexNull = -1;
const EventIndex kEventIndexInvalid = -1;
const FieldIndex kFieldIndexInvalid = -1;
const MethodIndex kMethodIndexInvalid = -1;
const PropertyIndex kPropertyIndexInvalid = -1;
const GenericContainerIndex kGenericContainerIndexInvalid = -1;
const GenericParameterIndex kGenericParameterIndexInvalid = -1;
const RGCTXIndex kRGCTXIndexInvalid = -1;
const StringLiteralIndex kStringLiteralIndexInvalid = -1;
const InteropDataIndex kInteropDataIndexInvalid = -1;

typedef void (*Il2CppMethodPointer)();
typedef void *(*InvokerMethod)(Il2CppMethodPointer, const MethodInfo *, void *, void **);

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

    mutable void *nameToClassHashTable;

    uint32_t token;
};

struct Il2CppArrayType
{
    const Il2CppType *etype;
    uint8_t rank;
    uint8_t numsizes;
    uint8_t numlobounds;
    int *sizes;
    int *lobounds;
};

struct Il2CppGenericContext
{
    /* The instantiation corresponding to the class generic parameters */
    const void *class_inst;
    /* The instantiation corresponding to the method generic parameters */
    const void *method_inst;
};

struct Il2CppGenericClass
{
    TypeDefinitionIndex typeDefinitionIndex; /* the generic type definition */
    Il2CppGenericContext context;            /* a context that contains the type instantiation doesn't contain any method instantiation */
    Il2CppClass *cached_class;               /* if present, the Il2CppClass corresponding to the instantiation.  */
};

enum Il2CppTypeEnum
{
    IL2CPP_TYPE_END = 0x00, /* End of List */
    IL2CPP_TYPE_VOID = 0x01,
    IL2CPP_TYPE_BOOLEAN = 0x02,
    IL2CPP_TYPE_CHAR = 0x03,
    IL2CPP_TYPE_I1 = 0x04,
    IL2CPP_TYPE_U1 = 0x05,
    IL2CPP_TYPE_I2 = 0x06,
    IL2CPP_TYPE_U2 = 0x07,
    IL2CPP_TYPE_I4 = 0x08,
    IL2CPP_TYPE_U4 = 0x09,
    IL2CPP_TYPE_I8 = 0x0a,
    IL2CPP_TYPE_U8 = 0x0b,
    IL2CPP_TYPE_R4 = 0x0c,
    IL2CPP_TYPE_R8 = 0x0d,
    IL2CPP_TYPE_STRING = 0x0e,
    IL2CPP_TYPE_PTR = 0x0f,         /* arg: <type> token */
    IL2CPP_TYPE_BYREF = 0x10,       /* arg: <type> token */
    IL2CPP_TYPE_VALUETYPE = 0x11,   /* arg: <type> token */
    IL2CPP_TYPE_CLASS = 0x12,       /* arg: <type> token */
    IL2CPP_TYPE_VAR = 0x13,         /* Generic parameter in a generic type definition, represented as number (compressed unsigned integer) number */
    IL2CPP_TYPE_ARRAY = 0x14,       /* type, rank, boundsCount, bound1, loCount, lo1 */
    IL2CPP_TYPE_GENERICINST = 0x15, /* <type> <type-arg-count> <type-1> \x{2026} <type-n> */
    IL2CPP_TYPE_TYPEDBYREF = 0x16,
    IL2CPP_TYPE_I = 0x18,
    IL2CPP_TYPE_U = 0x19,
    IL2CPP_TYPE_FNPTR = 0x1b, /* arg: full method signature */
    IL2CPP_TYPE_OBJECT = 0x1c,
    IL2CPP_TYPE_SZARRAY = 0x1d,   /* 0-based one-dim-array */
    IL2CPP_TYPE_MVAR = 0x1e,      /* Generic parameter in a generic method definition, represented as number (compressed unsigned integer)  */
    IL2CPP_TYPE_CMOD_REQD = 0x1f, /* arg: typedef or typeref token */
    IL2CPP_TYPE_CMOD_OPT = 0x20,  /* optional arg: typedef or typref token */
    IL2CPP_TYPE_INTERNAL = 0x21,  /* CLR internal type */

    IL2CPP_TYPE_MODIFIER = 0x40, /* Or with the following types */
    IL2CPP_TYPE_SENTINEL = 0x41, /* Sentinel for varargs method signature */
    IL2CPP_TYPE_PINNED = 0x45,   /* Local var that points to pinned object */

    IL2CPP_TYPE_ENUM = 0x55 /* an enumeration */
};

enum Il2CppTypeNameFormat
{
    IL2CPP_TYPE_NAME_FORMAT_IL,
    IL2CPP_TYPE_NAME_FORMAT_REFLECTION,
    IL2CPP_TYPE_NAME_FORMAT_FULL_NAME,
    IL2CPP_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED
};

struct Il2CppType
{
    union {
        // We have this dummy field first because pre C99 compilers (MSVC) can only initializer the first value in a union.
        void *dummy;
        TypeDefinitionIndex klassIndex; /* for VALUETYPE and CLASS */
        const Il2CppType *type;         /* for PTR and SZARRAY */
        Il2CppArrayType *array;         /* for ARRAY */
        //MonoMethodSignature *method;
        GenericParameterIndex genericParameterIndex; /* for VAR and MVAR */
        Il2CppGenericClass *generic_class;           /* for GENERICINST */
    } data;
    unsigned int attrs : 16; /* param attributes or field flags */
    Il2CppTypeEnum type : 8;
    unsigned int num_mods : 6; /* max 64 modifiers follow at the end */
    unsigned int byref : 1;
    unsigned int pinned : 1; /* valid when included in a local var signature */
    //MonoCustomMod modifiers [MONO_ZERO_LEN_ARRAY]; /* this may grow */
};

struct Il2CppTypeDefinition
{
    StringIndex nameIndex;
    StringIndex namespaceIndex;
    CustomAttributeIndex customAttributeIndex;
    TypeIndex byvalTypeIndex;
    TypeIndex byrefTypeIndex;

    TypeIndex declaringTypeIndex;
    TypeIndex parentIndex;
    TypeIndex elementTypeIndex; // we can probably remove this one. Only used for enums

    RGCTXIndex rgctxStartIndex;
    int32_t rgctxCount;

    GenericContainerIndex genericContainerIndex;

    uint32_t flags;

    FieldIndex fieldStart;
    MethodIndex methodStart;
    EventIndex eventStart;
    PropertyIndex propertyStart;
    NestedTypeIndex nestedTypesStart;
    InterfacesIndex interfacesStart;
    VTableIndex vtableStart;
    InterfacesIndex interfaceOffsetsStart;

    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;

    // bitfield to portably encode boolean values as single bits
    // 01 - valuetype;
    // 02 - enumtype;
    // 03 - has_finalize;
    // 04 - has_cctor;
    // 05 - is_blittable;
    // 06 - is_import_or_windows_runtime;
    // 07-10 - One of nine possible PackingSize values (0, 1, 2, 4, 8, 16, 32, 64, or 128)
    uint32_t bitfield;
    uint32_t token;
};

struct FieldInfo
{
    const char *name;
    const Il2CppType *type;
    Il2CppClass *parent;
    int32_t offset; // If offset is -1, then it's thread static
    CustomAttributeIndex customAttributeIndex;
    uint32_t token;
};

struct EventInfo
{
    const char *name;
    const Il2CppType *eventType;
    Il2CppClass *parent;
    const MethodInfo *add;
    const MethodInfo *remove;
    const MethodInfo *raise;
    CustomAttributeIndex customAttributeIndex;
    uint32_t token;
};

struct PropertyInfo
{
    Il2CppClass *parent;
    const char *name;
    const MethodInfo *get;
    const MethodInfo *set;
    uint32_t attrs;
    CustomAttributeIndex customAttributeIndex;
    uint32_t token;
};

struct Il2CppRuntimeInterfaceOffsetPair
{
    Il2CppClass *interfaceType;
    int32_t offset;
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
    const void *interopData;
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
};

struct ParameterInfo
{
    const char *name;
    int32_t position;
    uint32_t token;
    CustomAttributeIndex customAttributeIndex;
    const Il2CppType *parameter_type;
};

union Il2CppRGCTXData {
    void *rgctxDataDummy;
    const MethodInfo *method;
    const Il2CppType *type;
    Il2CppClass *klass;
};

struct Il2CppMethodDefinition
{
    StringIndex nameIndex;
    TypeDefinitionIndex declaringType;
    TypeIndex returnType;
    ParameterIndex parameterStart;
    CustomAttributeIndex customAttributeIndex;
    GenericContainerIndex genericContainerIndex;
    MethodIndex methodIndex;
    MethodIndex invokerIndex;
    MethodIndex reversePInvokeWrapperIndex;
    RGCTXIndex rgctxStartIndex;
    int32_t rgctxCount;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint16_t parameterCount;
};

struct Il2CppGenericMethod
{
    const MethodInfo *methodDefinition;
    Il2CppGenericContext context;
};

struct Il2CppGenericContainer
{
    /* index of the generic type definition or the generic method definition corresponding to this container */
    int32_t ownerIndex; // either index into Il2CppClass metadata array or Il2CppMethodDefinition array
    int32_t type_argc;
    /* If true, we're a generic method, otherwise a generic type definition. */
    int32_t is_method;
    /* Our type parameters. */
    GenericParameterIndex genericParameterStart;
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
