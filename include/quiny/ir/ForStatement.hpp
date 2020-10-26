// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_FORSTATEMENT_INCLUDED
#define QUINY_IR_FORSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class ForStatement : public Statement
    {
      public:

        virtual
        ~ForStatement();
    };

  }

}

#endif
