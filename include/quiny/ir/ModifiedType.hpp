// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_MODIFIEDTYPE_INCLUDED
#define QUINY_IR_MODIFIEDTYPE_INCLUDED

#include "quiny/ir/Type.hpp"

#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Port;

    class ModifiedType : public Type
    {
      public:

        virtual
        ~ModifiedType();
        
    };

  }

}

#endif
