// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_sensitive_d.hpp"
#include "quiny_sc/sc_core/sc_event.hpp"
#include "quiny_sc/sc_core/sc_interface.hpp"
#include "quiny_sc/sc_core/sc_port_base.hpp"
#include "quiny_sc/sc_core/sc_event_finder.hpp"

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    sc_sensitive_d&
    sc_sensitive_d::
    operator << (const sc_event &)
    {
      return *this; 
    }    
    
    sc_sensitive_d&
    sc_sensitive_d::
    operator << (const sc_interface &i)
    {
      ::quiny::collector::sensitivity(i.id(), ::quiny::ir::Process::Sensitivity::AnyEdge);
      return *this; 
    }    

    sc_sensitive_d&
    sc_sensitive_d::
    operator << (const sc_port_base &p)
    {
      ::quiny::collector::sensitivity(p.id(), ::quiny::ir::Process::Sensitivity::AnyEdge);
      return *this; 
    }    

    sc_sensitive_d&
    sc_sensitive_d::
    operator << (sc_event_finder &e)
    {
      ::quiny::collector::sensitivity(e.getPortBase().id(), e.getEdge());
      return *this; 
    }    


  }


}

