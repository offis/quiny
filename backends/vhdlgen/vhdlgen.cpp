// Thorsten Schubert, OFFIS

#include <quiny/ir/ir.hpp>
#include "Visitor.hpp"

#include <fstream>

using namespace std;
using namespace quiny::ir;
using namespace quiny::utils;

int quiny_start(int argc, 
                char *argv[],
                quiny::utils::owner_ptr<StructuralObject> rootObject,
                quiny::utils::owner_ptr<SimulationCommands> simulationCommands)
{

  vhdlgen::Visitor vhdlGenerator;
  
  rootObject->accept(vhdlGenerator);
  
  ofstream simDo("sim.do");
  simDo << "vsim UNKNOWN_" << rootObject->basename() << "_entity" << endl;
  vhdlGenerator.setOutputStream(&simDo);
  simulationCommands->accept(vhdlGenerator);
  simDo << "quit -f" << endl;
  
  owner_ptr<StructuralObject>  *tmp1 = new owner_ptr<StructuralObject>(rootObject);
  owner_ptr<SimulationCommands> *tmp2 = new owner_ptr<SimulationCommands>(simulationCommands);
  
  return 0;
}
