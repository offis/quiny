// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/SimulationCommands.hpp"

namespace quiny
{

  namespace ir
  {
    
    void
    SimulationCommands::
    addCommand(utils::owner_ptr<SimulationCommand> command)
    {
      m_simulationCommands.push_back(command); 
    }
  
    utils::observer_iter<SimulationCommand>
    SimulationCommands::
    getCommands() const
    {
      return m_simulationCommands.begin(); 
    }


  }
}
