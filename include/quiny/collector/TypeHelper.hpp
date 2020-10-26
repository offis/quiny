// 2006-03-28, Thorsten Schubert, OFFIS

#ifndef QUINY_COLLECTOR_TYPEHELPER_INCLUDED
#define QUINY_COLLECTOR_TYPEHELPER_INCLUDED

#include "quiny/collector/TypeHelperBase.hpp"

#include <sstream>

namespace quiny_sc
{
  namespace sc_dt
  {
    template<int WIDTH>
    class sc_uint;

  }
}

namespace quiny
{

  namespace collector
  {

    template<typename T>
    class TypeHelper : public TypeHelperBase
    {
      public:
        
      private:  
        // This unspecialised version should not be instantiated
        TypeHelper() 
        {}

    };

    template<typename T>
    class ConstHelper
    {
      public:
        typedef T NonConst_t;
      
        bool
        isConstType() const
        {
          return false;
        }      
    };

    template<typename T>
    class ConstHelper<const T>
    {
      public:
        typedef T NonConst_t;

        bool
        isConstType() const
        {
          return true;
        }      
    };

    template<typename T>
    class VolatileHelper
    {
      public:
        typedef T NonVolatile_t;
        
        bool
        isVolatileType() const
        {
          return false;
        }      
    };

    template<typename T>
    class VolatileHelper<volatile T>
    {
      public:
        typedef T NonVolatile_t;

        bool
        isVolatileType() const
        {
          return true;
        }      
    };


    template<typename T>
    class SignHelper
    {
      public:
        bool
        isSignedType() const
        {
          return false;
        }      
    };
    
#define DEFINE_SIGN_HELPER_SPECIALISATION(typ, value) \
    template<>\
    class SignHelper<typ> \
    {\
      public:\
      \
        bool\
        isSignedType() const \
        {\
          return value;\
        }      \
    };
    
#define DEFINE_SIGN_HELPER_SPECIALISATION_SIGNED_UNSIGNED(typ) \
  DEFINE_SIGN_HELPER_SPECIALISATION(signed typ, true) \
  DEFINE_SIGN_HELPER_SPECIALISATION(unsigned typ, false)

  DEFINE_SIGN_HELPER_SPECIALISATION_SIGNED_UNSIGNED(char)
  DEFINE_SIGN_HELPER_SPECIALISATION_SIGNED_UNSIGNED(short)
  DEFINE_SIGN_HELPER_SPECIALISATION_SIGNED_UNSIGNED(int)
  DEFINE_SIGN_HELPER_SPECIALISATION_SIGNED_UNSIGNED(long)

#undef DEFINE_SIGN_HELPER_SPECIALISATION_SIGNED_UNSIGNED
#undef DEFINE_SIGN_HELPER_SPECIALISATION

  

#define DEFINE_TYPE_HELPER_SPECIALISATION(typ, enumValue) \
    template<>\
    class TypeHelper<typ> : public TypeHelperBase,  \
                            SignHelper< \
                              VolatileHelper< \
                                ConstHelper<typ>::NonConst_t  \
                              >::NonVolatile_t\
                            >, \
                            ConstHelper<typ>, \
                            VolatileHelper<typ> \
    {\
      public:\
      \
        virtual \
        ~TypeHelper() {}\
\
        virtual\
        std::string\
        getName() const \
        {\
          return #typ ;\
        }\
\
        virtual\
        bool\
        isSimpleType() const\
        {\
          return true;\
        }\
        \
        virtual\
        ir::SimpleType::EnumValue\
        whichSimpleType() const\
        {\
          return ir::SimpleType::enumValue;\
        }\
        \
        virtual\
        ir::CVNess\
        getCVNess() const\
        {\
          return ir::CVNess(isConstType(), isVolatileType());\
        }\
        \
        virtual\
        bool\
        isSigned() const\
        {\
          return isSignedType();\
        }\
    };

#define DEFINE_TYPE_HELPER_SPECIALISATION_CV(typ, enumValue)\
  DEFINE_TYPE_HELPER_SPECIALISATION(typ, enumValue) \
  DEFINE_TYPE_HELPER_SPECIALISATION(const typ, enumValue) \
  DEFINE_TYPE_HELPER_SPECIALISATION(volatile typ, enumValue) \
  DEFINE_TYPE_HELPER_SPECIALISATION(const volatile typ, enumValue) 

  // Specialisations for "non-signable" types
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(bool, Bool)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(char, Char)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(wchar_t, WChar)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(float, Float)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(double, Double)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(long double, LongDouble)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(long long, LongLong)

#define DEFINE_TYPE_HELPER_SPECIALISATION_CV_SIGNEDNESS(typ, enumValue)\
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(signed typ, enumValue) \
  DEFINE_TYPE_HELPER_SPECIALISATION_CV(unsigned typ, enumValue)

  // Specialisations for the signed and unsigned version
  
  DEFINE_TYPE_HELPER_SPECIALISATION_CV_SIGNEDNESS(char, SChar)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV_SIGNEDNESS(short, Short)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV_SIGNEDNESS(int, Int)
  DEFINE_TYPE_HELPER_SPECIALISATION_CV_SIGNEDNESS(long, Long)

#undef DEFINE_TYPE_HELPER_SPECIALISATION_CV_SIGNEDNESS
#undef DEFINE_TYPE_HELPER_SPECIALISATION_CV
#undef DEFINE_TYPE_HELPER_SPECIALISATION

    // TODO: Either move this to sc_uint.hpp or move the corresponding specialisation
    //       of cpp_dt::Int from Int.hpp to this file
    template<int WIDTH>
    class TypeHelper< quiny_sc::sc_dt::sc_uint<WIDTH> > : public TypeHelperBase
    {
      public:

        virtual
        std::string
        getName() const 
        {
          std::ostringstream os;
          os << "sc_uint<" << WIDTH << ">";
          return os.str();
        }
                    
        virtual
        bool
        isSigned() const { return false; }

        virtual 
        bool
        isSystemCType() const { return true; }
        
        virtual
        ::quiny::ir::SystemCType::EnumValue
        whichSystemCType() const
        {
          return ::quiny::ir::SystemCType::SC_INT;
        }
        
        virtual
        unsigned int
        getBitWidth() const
        {
          return static_cast<unsigned int>(WIDTH);
        }
    };  

  }

}

#endif
