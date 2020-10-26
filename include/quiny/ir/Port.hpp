// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_PORT_INCLUDED
#define QUINY_IR_PORT_INCLUDED

#include "quiny/ir/PortChannelBase.hpp"

namespace quiny
{

  namespace ir
  {

    class Port : public PortChannelBase
    {
      public:
              
        virtual
        ~Port();
                
    };

  }

}

#endif
