// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_POINTERTYPE_INCLUDED
#define QUINY_IR_POINTERTYPE_INCLUDED

#include "quiny/ir/ModifiedType.hpp"

namespace quiny
{

  namespace ir
  {

    class PointerType : public ModifiedType
    {
      public:

        virtual
        ~PointerType();
    };

  }

}

#endif
