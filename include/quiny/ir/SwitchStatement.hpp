// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_SWITCHSTATEMENT_INCLUDED
#define QUINY_IR_SWITCHSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class SwitchStatement : public Statement
    {
      public:

        virtual
        ~SwitchStatement();
    };

  }

}

#endif
