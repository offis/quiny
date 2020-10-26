// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_START_COMMAND_INCLUDED
#define QUINY_IR_START_COMMAND_INCLUDED

#include "quiny/ir/SimulationCommand.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class TimeLiteral;

    // Represents sc_start    
    class StartCommand : public SimulationCommand
    {
      public:
      
        DEFINE_ACCEPT_METHOD(StartCommand)
              
        // No duration means: run until there are no more events
        StartCommand(utils::owner_ptr<TimeLiteral> duration=utils::owner_ptr<TimeLiteral>(0));
        
        virtual
        ~StartCommand();
        
        utils::observer_ptr<TimeLiteral>
        getDuration() const;
        
        void
        setDuration(utils::owner_ptr<TimeLiteral> duration);
        
      protected:
        utils::owner_ptr<TimeLiteral>     m_duration;
    };

  }
}

#endif
