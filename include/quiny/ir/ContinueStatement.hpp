// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_CONTINUESTATEMENT_INCLUDED
#define QUINY_IR_CONTINUESTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class ContinueStatement : public Statement
    {
      public:

        virtual
        ~ContinueStatement();
    };

  }

}

#endif
