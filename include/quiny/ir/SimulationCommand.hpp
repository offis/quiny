// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_SIMULATIONCOMMAND_INCLUDED
#define QUINY_IR_SIMULATIONCOMMAND_INCLUDED

#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    class SimulationCommand
    {
      public:
      
        DEFINE_ACCEPT_METHOD(SimulationCommand)
        
      virtual
      ~SimulationCommand();

    };

  }

}

#endif
