// Thorsten Schubert, OFFIS

#include "quiny/ir/TraceCommand.hpp"

namespace quiny
{

  namespace ir
  {
    TraceCommand::
    TraceCommand(utils::observer_ptr<PortChannelBase> target)
    : m_target(target)
    {
      
    }
    
    TraceCommand::
    ~TraceCommand()
    {
    }
    
    utils::observer_ptr<PortChannelBase>
    TraceCommand::
    getTarget() const
    {
      return m_target;
    }
    
    void
    TraceCommand::
    setTarget(utils::observer_ptr<PortChannelBase> target)
    {
      m_target = target;
    }

  }
}

