// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_PORTCHANNELBASE_INCLUDED
#define QUINY_IR_PORTCHANNELBASE_INCLUDED

#include "quiny/ir/StructuralObject.hpp"

namespace quiny
{

  namespace ir
  {

    // Base class for ports and signals
    class PortChannelBase : public StructuralObject
    {
      public:

        virtual
        ~PortChannelBase();
        
    };

  }

}

#endif
