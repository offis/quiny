// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_VARIABLEEXPRESSION_INCLUDED
#define QUINY_IR_VARIABLEEXPRESSION_INCLUDED

#include "quiny/ir/Expression.hpp"

namespace quiny
{

  namespace ir
  {

    class VariableExpression : public Expression
    {
      public:

        virtual
        ~VariableExpression();
    };

  }

}

#endif
