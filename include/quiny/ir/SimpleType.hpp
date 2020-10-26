// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_SIMPLETYPE_INCLUDED
#define QUINY_IR_SIMPLETYPE_INCLUDED

#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    class SimpleType : public Type
    {
      public:
      
        DEFINE_ACCEPT_METHOD(SimpleType)
      
        enum EnumValue
        {
          Void,
          Bool,
          // neutral char
          Char,
          // signed or unsigned char
          SChar,
          Short,
          Int,
          Long,
          LongLong,
          Float,
          Double,
          LongDouble,
          WChar
        }; 
        
        static 
        bool
        isSignable(EnumValue typ);
              
        SimpleType(SimpleType::EnumValue t=SimpleType::Void, 
                   bool isSigned=false,
                   CVNess cvness=CVNess::NonConstNonVolatile);

        virtual
        ~SimpleType();
        
        virtual
        std::string
        getName() const;
        
        virtual
        bool
        isSigned() const;
        
        EnumValue
        whichSimpleType() const;
        
      protected:
      
        SimpleType::EnumValue   m_type;
        bool                    m_signed;
        
    };

  }

}

#endif
