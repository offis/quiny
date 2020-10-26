// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_ARRAYTYPE_INCLUDED
#define QUINY_IR_ARRAYTYPE_INCLUDED

#include "quiny/ir/ModifiedType.hpp"

namespace quiny
{

  namespace ir
  {

    class ArrayType : public ModifiedType
    {
      public:

        virtual
        ~ArrayType();
    };

  }

}

#endif
