// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_BOOL_LITERAL_INCLUDED
#define QUINY_IR_BOOL_LITERAL_INCLUDED

#include "quiny/ir/Expression.hpp"

namespace quiny
{

  namespace ir
  {

    class BoolLiteral : public Expression
    {
      public:
      
        DEFINE_ACCEPT_METHOD(BoolLiteral)
      
        BoolLiteral(bool value);

        virtual
        ~BoolLiteral();
        
        bool
        getValue() const;
        
        void
        setValue(bool b);
        
      protected:
        bool          m_value;
    };

  }

}

#endif
