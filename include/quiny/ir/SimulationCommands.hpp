// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_SIMULATIONCOMMANDS_INCLUDED
#define QUINY_IR_SIMULATIONCOMMANDS_INCLUDED

#include "quiny/ir/SimulationCommand.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    // A container for multiple SimulationCommand objects
    class SimulationCommands
    {
      public:
      
        DEFINE_ACCEPT_METHOD(SimulationCommands)
              
        void
        addCommand(utils::owner_ptr<SimulationCommand> command);
      
        utils::observer_iter<SimulationCommand>
        getCommands() const;
      
      protected:
        utils::owner_ptr_list<SimulationCommand>   m_simulationCommands;
    };

  }

}

#endif
