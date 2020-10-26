// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_TRACE_COMMAND_INCLUDED
#define QUINY_IR_TRACE_COMMAND_INCLUDED

#include "quiny/ir/SimulationCommand.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class PortChannelBase;

    class TraceCommand : public SimulationCommand
    {
      public:
      
        DEFINE_ACCEPT_METHOD(TraceCommand)      
        
        TraceCommand(utils::observer_ptr<PortChannelBase> target=0);
        
        virtual
        ~TraceCommand();
        
        utils::observer_ptr<PortChannelBase>
        getTarget() const;
        
        void
        setTarget(utils::observer_ptr<PortChannelBase> target);
        
      protected:
        utils::observer_ptr<PortChannelBase>    m_target;

    };

  }

}

#endif
