// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_MODULE_INCLUDED
#define QUINY_IR_MODULE_INCLUDED

#include "quiny/ir/StructuralObject.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Port;
    class Signal;    
    class PortChannelBase;
    class Process;
    class ModuleType;
    
    // This represents an instance of a module (see also ModuleType)
    // Note: The separation between Module and ModuleType seems to be a little bit awkward
    class Module : public StructuralObject
    {
      public:
        
        DEFINE_ACCEPT_METHOD(Module)
          
        struct Binding
        {
          utils::observer_ptr<Port>             m_port;
          utils::observer_ptr<PortChannelBase>  m_channelOrPort;
        };
        
        Module(const std::string &name="",
               utils::observer_ptr<StructuralObject> parent=0);

        virtual
        ~Module();
        
        void
        addSubModule(utils::owner_ptr<Module> subModule);
        
        utils::observer_iter<Module>
        getSubModules() const;

        void
        addBinding(utils::owner_ptr<Binding> binding);

        utils::observer_iter<Binding>
        getBindings() const;
        
        void
        addSignal(utils::owner_ptr<Signal> signal);
        
        utils::observer_iter<Signal>
        getSignals() const;

        void
        addProcess(utils::owner_ptr<Process> process);
        
        utils::observer_iter<Process>
        getProcesses() const;
                        
//        void
//        setModuleType(utils::owner_ptr<ModuleType> moduleType);
        
        utils::observer_ptr<ModuleType>
        getModuleType() const;
        
      protected:
        // Note: The ports are part of ModuleType
        utils::owner_ptr_list<Signal>    m_signals;

        utils::owner_ptr_list<Module>    m_subModules;
        // The bindings of the submodules
        utils::owner_ptr_list<Binding>   m_bindings;

        utils::owner_ptr_list<Process>   m_processes;        
        
        utils::owner_ptr<ModuleType>     m_moduleType;
        
    };

  }

}

#endif
