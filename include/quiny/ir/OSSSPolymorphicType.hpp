// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_OSSSPOLYMORPHICTYPE_INCLUDED
#define QUINY_IR_OSSSPOLYMORPHICTYPE_INCLUDED

#include "quiny/ir/ModifiedType.hpp"

namespace quiny
{

  namespace ir
  {

    class OSSSPolymorphicType : public ModifiedType
    {
      public:

        virtual
        ~OSSSPolymorphicType();
    };

  }

}

#endif
