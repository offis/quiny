// 2006-03-24, Thorsten Schubert, OFFIS

#include <iostream>
#include <string>

#include "quiny/collector/collector.hpp"

#include "quiny/ir/StructuralObject.hpp"
#include "quiny/ir/SimulationCommands.hpp"

using namespace std;

int sc_main (int arg, char *argv[]);


namespace quiny { 
  
  namespace collector
  {  
    utils::owner_ptr<ir::StructuralObject>
    getRootObject();
    
    utils::owner_ptr<ir::SimulationCommands>
    getSimulationCommands();
  }
}
  

int quiny_start(int argc, 
                char *argv[],
                quiny::utils::owner_ptr<quiny::ir::StructuralObject> rootObject,
                quiny::utils::owner_ptr<quiny::ir::SimulationCommands> simulationCommands);

// namespace quiny { namespace collector {
// 
//   Collector *collectorCreator()
//   {
//     return new quiny::collector::Collector();
//   }
// 
// }}

void printHeader()
{
  
  cerr << "\n            Quiny 0.2 --- " << __DATE__ << " " << __TIME__
       << "\n         Copyright (c) 2006 The Quiny Team, OFFIS"
          "\n                   ALL RIGHTS RESERVED"
       << endl;

}

int main (int argc, char *argv[])
{
  printHeader();

  if (argc>1)
  {
    string firstArg(argv[1]);
    if (firstArg == "-QUINY_DEBUG")
    {
      --argc;
      ++argv;
      ::quiny::collector::setLogStream(&cerr);
    }
  }
//  quiny::collector::Collector *collector = quiny::collector::collectorCreator();

  quiny::collector::enteringScMain();
  int retScMain = sc_main(argc, argv);
  quiny::collector::leavingScMain();
  
  if (retScMain != 0)
  {
    cerr << "WARNING: sc_main did not return 0, but " << retScMain << endl;
  }

  /* TODO: pass the correct objects */
  /* Is it safe to delete the collector here? */
  return quiny_start(argc, argv, quiny::collector::getRootObject(), quiny::collector::getSimulationCommands());
}
