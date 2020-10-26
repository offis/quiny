// Thorsten Schubert, OFFIS

#include "quiny/ir/StartCommand.hpp"
#include "quiny/ir/TimeLiteral.hpp"

namespace quiny
{

  namespace ir
  {

    StartCommand::
    StartCommand(utils::owner_ptr<TimeLiteral> duration)
    : m_duration(duration)
    {
    }
    
    StartCommand::
    ~StartCommand()
    {
    }
    
    utils::observer_ptr<TimeLiteral>
    StartCommand::
    getDuration() const
    {
      return m_duration;
    }
    
    void
    StartCommand::
    setDuration(utils::owner_ptr<TimeLiteral> duration)
    {
      m_duration = duration; 
    }

  }


}

