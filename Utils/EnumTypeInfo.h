#ifndef EnumTypeInfoH 
#define EnumTypeInfoH 

#include <TypInfo.hpp> 
#include <assert.h> 

#define DECLARE_ENUM_TYPEINFO(e) \
    \
    class e##_HACKED_ENUM_TYPEINFO : public TObject \
    { \
    private: \
        e FTestEnum; \
    __published: \
        __property e eProp = \
        { read = FTestEnum, write = FTestEnum }; \
    public: \
        static PTypeInfo TypeInfo(void) \
        { \
            PTypeInfo ClassTypeInfo; \
            PPropInfo PropertyInfo; \
            PTypeInfo PropertyTypeInfo; \
            \
            ClassTypeInfo = __typeinfo(e##_HACKED_ENUM_TYPEINFO); \
            assert(ClassTypeInfo != 0); \
            \
            PropertyInfo = GetPropInfo(ClassTypeInfo, "eProp"); \
            assert(PropertyInfo != 0); \
            \
            PropertyTypeInfo = *(PropertyInfo->PropType); \
            assert(PropertyTypeInfo != 0); \
            assert(PropertyTypeInfo->Kind == tkEnumeration); \
            \
            return PropertyTypeInfo; \
        } \
        \
        static PTypeData TypeData(void) \
        { \
            return GetTypeData(TypeInfo()); \
        } \
    };

#define GET_ENUM_TYPEINFO(e) \
   e##_HACKED_ENUM_TYPEINFO::TypeInfo()
#define GET_ENUM_TYPEDATA(e) \
   e##_HACKED_ENUM_TYPEINFO::TypeData()

#endif 