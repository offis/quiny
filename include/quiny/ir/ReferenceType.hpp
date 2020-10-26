// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_REFERENCETYPE_INCLUDED
#define QUINY_IR_REFERENCETYPE_INCLUDED

#include "quiny/ir/ModifiedType.hpp"

namespace quiny
{

  namespace ir
  {

    class ReferenceType : public ModifiedType
    {
      public:

        virtual
        ~ReferenceType();
    };

  }

}

#endif
