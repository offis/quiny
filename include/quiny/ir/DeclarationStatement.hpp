// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_DECLARATIONSTATEMENT_INCLUDED
#define QUINY_IR_DECLARATIONSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    class DeclarationStatement : public Statement
    {
      public:

        virtual
        ~DeclarationStatement();
    };

  }

}

#endif
