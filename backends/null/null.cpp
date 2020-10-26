// 2006-03-24, Thorsten Schubert, OFFIS

#include <quiny/ir/ir.hpp>

using namespace quiny::ir;
using namespace quiny::utils;

int quiny_start(int argc, 
                char *argv[],
                quiny::utils::owner_ptr<StructuralObject> rootObject,
                quiny::utils::owner_ptr<SimulationCommands> simulationCommands)
{

  
  owner_ptr<StructuralObject>  *tmp1 = new owner_ptr<StructuralObject>(rootObject);
  owner_ptr<SimulationCommands> *tmp2 = new owner_ptr<SimulationCommands>(simulationCommands);
  
  return 0;
}
