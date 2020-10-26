// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_BREAKSTATEMENT_INCLUDED
#define QUINY_IR_BREAKSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class BreakStatement : public Statement
    {
      public:

        virtual
        ~BreakStatement();
    };

  }

}

#endif
