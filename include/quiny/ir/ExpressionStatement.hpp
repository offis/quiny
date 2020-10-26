// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_EXPRESSIONSTATEMENT_INCLUDED
#define QUINY_IR_EXPRESSIONSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class ExpressionStatement : public Statement
    {
      public:

        virtual
        ~ExpressionStatement();
    };

  }

}

#endif
