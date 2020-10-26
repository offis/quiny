// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_PORT_CHANNEL_READ_INCLUDED
#define QUINY_IR_PORT_CHANNEL_READ_INCLUDED

#include "quiny/ir/Expression.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class PortChannelBase;

    class PortChannelRead : public Expression
    {
      public:

        DEFINE_ACCEPT_METHOD(PortChannelRead)
            
        PortChannelRead(utils::observer_ptr<PortChannelRead> source);
      
        virtual
        ~PortChannelRead();
        
        utils::observer_ptr<PortChannelBase>
        getSource() const;
        
        void
        setSource(utils::observer_ptr<PortChannelBase> source);
        
      protected:
        utils::observer_ptr<PortChannelBase>    m_source;
    };
  }
}
#endif
