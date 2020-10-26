// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_INT_LITERAL_INCLUDED
#define QUINY_IR_INT_LITERAL_INCLUDED

#include "quiny/ir/Expression.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class SimpleType;

    class IntLiteral : public Expression
    {
      public:
        DEFINE_ACCEPT_METHOD(IntLiteral)
      
        IntLiteral(unsigned long long value, utils::owner_ptr<SimpleType> type);
      
        virtual
        ~IntLiteral();
        
        unsigned long long
        getValue() const;
        
        void
        setValue(unsigned long long value);
        
      protected:
        
        unsigned long long               m_value;
        utils::owner_ptr<SimpleType>     m_type;
    };

  }

}

#endif
