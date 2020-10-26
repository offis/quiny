// 2006-03-23, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_MODULETYPE_INCLUDED
#define QUINY_IR_MODULETYPE_INCLUDED

#include "quiny/ir/ClassType.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Port;

    class ModuleType : public ClassType
    {
      public:

        DEFINE_ACCEPT_METHOD(ModuleType)
            
        virtual
        ~ModuleType();
                
        void
        addPort(utils::owner_ptr<Port> port);
        
        utils::observer_iter<Port>
        getPorts() const;
                
      protected:
        // The ports are assumed to be instance-independent, because they represent
        // the module's interface
        utils::owner_ptr_list<Port>      m_ports;        
    };
  }
}

#endif
