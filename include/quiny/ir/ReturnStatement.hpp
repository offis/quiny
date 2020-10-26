// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_RETURNSTATEMENT_INCLUDED
#define QUINY_IR_RETURNSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class ReturnStatement : public Statement
    {
      public:

        virtual
        ~ReturnStatement();
    };

  }

}

#endif
