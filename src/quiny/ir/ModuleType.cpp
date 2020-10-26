// 2006-03-23, Thorsten Schubert, OFFIS

#include "quiny/ir/ModuleType.hpp"
#include "quiny/ir/Port.hpp"


namespace quiny
{

  namespace ir
  {

    ModuleType::~ModuleType()
    {
      /* TODO */
    }

    void
    ModuleType::
    addPort(utils::owner_ptr<Port> port)
    {
      m_ports.push_back(port); 
    }
    
    utils::observer_iter<Port>
    ModuleType::
    getPorts() const
    {
      return m_ports.begin(); 
    }
    
    
  }


}

