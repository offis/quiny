// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_FUNCTIONTYPE_INCLUDED
#define QUINY_IR_FUNCTIONTYPE_INCLUDED

#include "quiny/ir/ModifiedType.hpp"

namespace quiny
{

  namespace ir
  {

    class FunctionType : public ModifiedType
    {
      public:

        virtual
        ~FunctionType();
    };

  }

}

#endif
