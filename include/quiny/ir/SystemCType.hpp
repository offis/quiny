// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_SYSTEMCTYPE_INCLUDED
#define QUINY_IR_SYSTEMCTYPE_INCLUDED

#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    class SystemCType : public Type
    {
      public:

        DEFINE_ACCEPT_METHOD(SystemCType)
        
        enum EnumValue
        {
          SC_INT,
          SC_BIG_INT,
          SC_BV,
          SC_LV        
        };
      
        SystemCType(SystemCType::EnumValue type,
                    unsigned int bitWidth,
                    bool isSigned);

        virtual
        ~SystemCType();

        virtual
        std::string
        getName() const;
        
        unsigned int
        getBitWidth() const;

        bool
        isSigned() const;

        
      protected:
        SystemCType::EnumValue  m_type;
        unsigned int            m_bitWidth;
        bool                    m_isSigned;
    };

  }

}

#endif
