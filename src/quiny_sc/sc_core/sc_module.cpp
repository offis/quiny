// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_module.hpp"

#include "quiny/collector/collector.hpp"
#include "quiny_sc/sc_core/sc_time.hpp"

namespace quiny_sc
{

  namespace sc_core
  {    
    sc_module::
    sc_module()
    {
      ::quiny::collector::moduleCreated(id());
    }
    
    sc_module::
    sc_module(const char *name)
    : sc_object(name)
    {
      ::quiny::collector::moduleCreated(id());
    }
    
    sc_module::
    ~sc_module()
    {
    }
    
    void 
    sc_module::
    wait(int i)
    {
      ::quiny::collector::wait(i);
    }
    
    void
    sc_module::
    wait(const sc_time &t)
    {
      ::quiny::collector::waitTimeLiteral(t.id());
    }
  }
}
