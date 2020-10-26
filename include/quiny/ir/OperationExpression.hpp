// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_OPERATIONEXPRESSION_INCLUDED
#define QUINY_IR_OPERATIONEXPRESSION_INCLUDED

#include "quiny/ir/Expression.hpp"

namespace quiny
{

  namespace ir
  {

    class OperationExpression : public Expression
    {
      public:

        virtual
        ~OperationExpression();
    };

  }

}

#endif
