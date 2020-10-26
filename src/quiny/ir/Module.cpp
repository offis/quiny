// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/Module.hpp"

#include "quiny/ir/Port.hpp"
#include "quiny/ir/Signal.hpp"
#include "quiny/ir/Process.hpp"

#include "quiny/ir/ModuleType.hpp"

namespace quiny
{

  namespace ir
  {

    Module::
    Module(const std::string &name,
           utils::observer_ptr<StructuralObject> parent)
    : StructuralObject(name, parent)
    , m_moduleType(new ModuleType())
    {
    
    }

    Module::~Module()
    {
      /* TODO */
    }
    
    void
    Module::
    addSubModule(utils::owner_ptr<Module> subModule)
    {
      m_subModules.push_back(subModule);
    }
        
    utils::observer_iter<Module>
    Module::
    getSubModules() const
    {
      return m_subModules.begin();
    }

    void
    Module::
    addBinding(utils::owner_ptr<Binding> binding)
    {
      m_bindings.push_back(binding);
    }

    utils::observer_iter<Module::Binding>
    Module::
    getBindings() const
    {
      return m_bindings.begin();
    }

    void
    Module::
    addSignal(utils::owner_ptr<Signal> signal)
    {
      m_signals.push_back(signal);
    }

    utils::observer_iter<Signal>
    Module::
    getSignals() const
    {
      return m_signals.begin();
    }

    void
    Module::
    addProcess(utils::owner_ptr<Process> process)
    {
      m_processes.push_back(process);
    }

    utils::observer_iter<Process>
    Module::
    getProcesses() const
    {
      return m_processes.begin();
    }

//     void
//     Module::
//     setModuleType(utils::owner_ptr<ModuleType> moduleType)
//     {
//       m_moduleType = moduleType;
//     }
    
    utils::observer_ptr<ModuleType>
    Module::
    getModuleType() const
    {
      return m_moduleType;
    }
    
        
  }
}
